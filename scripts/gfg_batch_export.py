#!/usr/bin/env python3
"""Batch export runner for the local GeeksforGeeks solved manifest.

This runner intentionally reuses the verified single-problem workflow from
scripts/gfg_exporter.py and avoids any automatic --force behaviour. It is
safe to run in dry-run mode and can resume from a JSONL progress file.
"""

from __future__ import annotations

import argparse
import json
import sys
import time
from collections import OrderedDict
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT_DIR = SCRIPT_DIR.parent

if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from gfg_exporter import (  # noqa: E402
    export_problem,
    language_extension,
    normalize_problem_url,
    root_dir,
    slug_from_problem_url,
)

MANIFEST_PATH = ROOT_DIR / "gfg_solved_manifest.json"
EXPORT_ROOT = ROOT_DIR / "gfg_export_test"
PROGRESS_PATH = EXPORT_ROOT / "batch_progress.jsonl"
UNRESOLVED_FAILED_PROBLEMS_PATH = EXPORT_ROOT / "unresolved_failed_problems.json"


def utc_now_iso() -> str:
    return datetime.now(timezone.utc).isoformat()


def load_manifest(path: Path = MANIFEST_PATH) -> list[dict[str, Any]]:
    if not path.exists():
        raise FileNotFoundError(f"Manifest not found: {path}")
    manifest = json.loads(path.read_text(encoding="utf-8"))
    problems = manifest.get("problems") or []
    if not isinstance(problems, list):
        raise ValueError(f"Manifest at {path} does not contain a valid 'problems' list.")
    return problems


def canonical_slug(url: str) -> str:
    normalized = normalize_problem_url(url)
    slug = slug_from_problem_url(normalized)
    if not slug or slug == "problem":
        raise ValueError(f"Could not determine canonical slug from URL: {url}")
    return slug


def manifest_entries(limit: int | None = None, *, exclude_duplicates: bool = True) -> list[dict[str, Any]]:
    unique: OrderedDict[str, dict[str, Any]] = OrderedDict()
    manifest = load_manifest()

    for index, entry in enumerate(manifest):
        if not isinstance(entry, dict):
            continue
        raw_url = entry.get("url") or entry.get("problem_url") or entry.get("link")
        title = str(entry.get("title") or "").strip() or f"Problem {index + 1}"
        if not raw_url:
            continue
        try:
            normalized_url = normalize_problem_url(raw_url)
            slug = canonical_slug(normalized_url)
        except Exception:
            continue

        if exclude_duplicates and slug in unique:
            continue

        unique[slug] = {
            "title": title,
            "url": normalized_url,
            "slug": slug,
        }

    entries = list(unique.values())
    if limit is not None:
        return entries[:limit]
    return entries


def progress_file_path() -> Path:
    PROGRESS_PATH.parent.mkdir(parents=True, exist_ok=True)
    return PROGRESS_PATH


def deferred_failed_slugs(progress: dict[str, dict[str, Any]]) -> set[str]:
    deferred: set[str] = set()
    for slug, record in (progress or {}).items():
        status = str(record.get("status") or "").strip().lower()
        if status in {"failed", "deferred_failed"}:
            deferred.add(str(slug))
    return deferred


def build_unresolved_failed_report(
    progress_path: Path = PROGRESS_PATH,
    report_path: Path = UNRESOLVED_FAILED_PROBLEMS_PATH,
) -> dict[str, Any]:
    progress = load_progress(progress_path)
    unresolved: list[dict[str, Any]] = []
    for slug, record in sorted(progress.items(), key=lambda item: str(item[0])):
        status = str(record.get("status") or "").strip().lower()
        if status not in {"failed", "deferred_failed"}:
            continue
        unresolved.append({
            "slug": slug,
            "title": record.get("title"),
            "url": record.get("url"),
            "status": status,
            "error": record.get("error") or record.get("message"),
            "timestamp_utc": record.get("timestamp_utc"),
        })

    payload = {
        "generated_at_utc": utc_now_iso(),
        "count": len(unresolved),
        "problems": unresolved,
    }
    report_path.parent.mkdir(parents=True, exist_ok=True)
    report_path.write_text(json.dumps(payload, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")
    return payload


def write_unresolved_failed_report(
    progress_path: Path = PROGRESS_PATH,
    report_path: Path = UNRESOLVED_FAILED_PROBLEMS_PATH,
) -> dict[str, Any]:
    return build_unresolved_failed_report(progress_path=progress_path, report_path=report_path)


def append_progress(record: dict[str, Any]) -> None:
    path = progress_file_path()
    with path.open("a", encoding="utf-8") as handle:
        handle.write(json.dumps(record, ensure_ascii=False) + "\n")
    build_unresolved_failed_report(path, UNRESOLVED_FAILED_PROBLEMS_PATH)


def load_progress(path: Path = PROGRESS_PATH) -> dict[str, dict[str, Any]]:
    if not path.exists():
        return {}

    records: dict[str, dict[str, Any]] = {}
    with path.open("r", encoding="utf-8") as handle:
        for line in handle:
            line = line.strip()
            if not line:
                continue
            try:
                record = json.loads(line)
            except json.JSONDecodeError:
                continue
            slug = record.get("slug")
            if slug and isinstance(record, dict):
                records[slug] = record
    return records


def valid_resume_statuses() -> set[str]:
    return {"existing_valid", "exported_successfully"}


def deferred_statuses() -> set[str]:
    return {"failed", "deferred_failed"}


def real_status_to_summary_label(status: str) -> str:
    if status == "exported_successfully":
        return "successful"
    if status == "existing_valid":
        return "existing_valid"
    if status == "pending":
        return "pending"
    if status == "failed":
        return "failed"
    if status == "skipped":
        return "skipped"
    return status


def export_metadata_path(slug: str) -> Path:
    return EXPORT_ROOT / "problems" / f"{slug}.metadata.json"


def export_source_path(slug: str, language: str) -> Path:
    extension = language_extension(language)
    return EXPORT_ROOT / "problems" / f"{slug}{extension}"


def export_readme_path(slug: str) -> Path:
    return EXPORT_ROOT / "problems" / f"{slug}.README.md"


def export_snapshot_path(slug: str) -> Path:
    return EXPORT_ROOT / "private" / f"{slug}.problem_content.json"


def is_previously_exported(slug: str, url: str) -> bool:
    metadata_path = export_metadata_path(slug)
    if not metadata_path.exists():
        return False
    try:
        metadata = json.loads(metadata_path.read_text(encoding="utf-8"))
    except Exception:
        return False

    metadata_url = metadata.get("problem_url")
    if metadata_url and canonical_slug(metadata_url) != canonical_slug(url):
        return False

    source_name = metadata.get("solution_file")
    if isinstance(source_name, str) and source_name.startswith("problems/"):
        source_path = EXPORT_ROOT / source_name
        if source_path.exists() and source_path.stat().st_size > 0:
            return True

    return False


def validate_successful_result(result: dict[str, Any]) -> None:
    problem_url = normalize_problem_url(str(result.get("problem_url") or ""))
    slug = canonical_slug(problem_url)
    metadata_path = export_metadata_path(slug)
    if not metadata_path.exists():
        raise ValueError(f"Missing metadata file for {slug}: {metadata_path}")

    metadata = json.loads(metadata_path.read_text(encoding="utf-8"))
    submission = metadata.get("submission") or {}
    language = str(submission.get("language") or "unknown").strip()
    source_path = export_source_path(slug, language)

    if not source_path.exists() or source_path.stat().st_size <= 0:
        raise ValueError(f"Source file missing or empty for {slug}: {source_path}")

    if source_path.suffix.lower() != language_extension(language).lower():
        raise ValueError(
            f"Language extension mismatch for {slug}: expected {language_extension(language)}, got {source_path.suffix}"
        )

    if str(submission.get("status") or "").strip().lower() != "correct":
        raise ValueError(f"Submission status is not Correct for {slug}: {submission.get('status')}")

    expected_solution = f"problems/{source_path.name}"
    expected_readme = f"problems/{slug}.README.md"
    expected_snapshot = f"private/{slug}.problem_content.json"

    metadata_solution = EXPORT_ROOT / metadata.get("solution_file", "") if metadata.get("solution_file") else None
    if metadata_solution is not None and (not metadata_solution.exists() or metadata_solution.stat().st_size <= 0):
        raise ValueError(f"Metadata solution file missing or empty for {slug}: {metadata_solution}")

    if metadata.get("solution_file") != expected_solution:
        raise ValueError(f"Metadata solution path mismatch for {slug}: {metadata.get('solution_file')} != {expected_solution}")
    if metadata.get("public_readme_file") != expected_readme:
        raise ValueError(f"README path mismatch for {slug}: {metadata.get('public_readme_file')} != {expected_readme}")
    if metadata.get("private_problem_snapshot") != expected_snapshot:
        raise ValueError(f"Private snapshot path mismatch for {slug}: {metadata.get('private_problem_snapshot')} != {expected_snapshot}")

    readme_path = export_readme_path(slug)
    if not readme_path.exists() or readme_path.stat().st_size <= 0:
        raise ValueError(f"README missing or empty for {slug}: {readme_path}")

    snapshot_path = export_snapshot_path(slug)
    if not snapshot_path.exists() or snapshot_path.stat().st_size <= 0:
        raise ValueError(f"Private snapshot missing or empty for {slug}: {snapshot_path}")

    if not isinstance(metadata.get("tags"), list):
        raise ValueError(f"Tags are not a list for {slug}: {metadata.get('tags')!r}")


def build_summary(records: list[dict[str, Any]]) -> dict[str, int]:
    summary = {
        "attempted": 0,
        "existing_valid": 0,
        "pending": 0,
        "successful": 0,
        "failed": 0,
        "deferred_failed": 0,
        "skipped": 0,
        "remaining": 0,
    }
    for record in records:
        status = str(record.get("status") or "")
        if status == "exported_successfully":
            summary["successful"] += 1
        elif status == "existing_valid":
            summary["existing_valid"] += 1
        elif status == "pending":
            summary["pending"] += 1
        elif status == "failed":
            summary["failed"] += 1
        elif status == "deferred_failed":
            summary["deferred_failed"] += 1
        elif status == "skipped":
            summary["skipped"] += 1

        if status in {"existing_valid", "pending", "exported_successfully", "failed", "deferred_failed", "skipped"}:
            summary["attempted"] += 1

    summary["remaining"] = summary["pending"] + summary["deferred_failed"]
    return summary


def process_problem(entry: dict[str, Any], *, dry_run: bool = False, delay: float = 1.0) -> dict[str, Any]:
    slug = entry["slug"]
    url = entry["url"]
    title = entry["title"]

    if dry_run:
        if is_previously_exported(slug, url):
            record = {
                "slug": slug,
                "title": title,
                "url": url,
                "status": "existing_valid",
                "timestamp_utc": utc_now_iso(),
                "message": "Already exported and valid; dry run indicates no live work needed.",
            }
            print(f"[DRY RUN] EXISTING VALID: {title} ({slug}) -> {url}")
            return record

        record = {
            "slug": slug,
            "title": title,
            "url": url,
            "status": "pending",
            "timestamp_utc": utc_now_iso(),
            "message": "Pending live export; dry run only.",
        }
        print(f"[DRY RUN] PENDING: {title} ({slug}) -> {url}")
        return record

    if is_previously_exported(slug, url):
        record = {
            "slug": slug,
            "title": title,
            "url": url,
            "status": "existing_valid",
            "timestamp_utc": utc_now_iso(),
            "message": "Previously exported and valid; skipping.",
        }
        append_progress(record)
        print(f"[EXISTING VALID] {title} ({slug}) -> {url}")
        return record

    try:
        time.sleep(delay)
        result = export_problem(url, root_dir(), force=False)
        validate_successful_result(result)
        record = {
            "slug": slug,
            "title": title,
            "url": url,
            "status": "exported_successfully",
            "timestamp_utc": utc_now_iso(),
            "message": "Export validated successfully.",
            "result": {
                "solution_file": result.get("solution_file"),
                "metadata_file": result.get("metadata_file"),
                "public_readme_file": result.get("public_readme_file"),
            },
        }
        append_progress(record)
        print(f"[SUCCESS] {title} ({slug}) -> {url}")
        return record
    except Exception as exc:  # pragma: no cover - runtime branch
        record = {
            "slug": slug,
            "title": title,
            "url": url,
            "status": "failed",
            "timestamp_utc": utc_now_iso(),
            "message": str(exc),
            "error": str(exc),
        }
        append_progress(record)
        print(f"[FAILED] {title} ({slug}) -> {url}: {exc}")
        return record


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Safely process GeeksforGeeks solved problems from the manifest.")
    parser.add_argument("--dry-run", action="store_true", help="Validate URLs and planned work without exporting source code.")
    parser.add_argument("--limit", type=int, default=None, help="Process at most this many unique manifest entries.")
    parser.add_argument("--resume", action="store_true", help="Resume from the existing progress file and skip already recorded successes.")
    parser.add_argument("--defer-failed", action="store_true", help="Skip entries recorded as failed in the batch history and keep them in the unresolved-failure report for later recovery.")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    all_entries = manifest_entries(limit=args.limit)
    progress = load_progress() if (args.resume or args.defer_failed) else {}

    if args.defer_failed:
        deferred_slugs = deferred_failed_slugs(progress)
        write_unresolved_failed_report()
    else:
        deferred_slugs = set()

    if args.resume:
        entries = []
        for entry in all_entries:
            slug = entry["slug"]
            if args.defer_failed and slug in deferred_slugs:
                record = {
                    "slug": slug,
                    "title": entry["title"],
                    "url": entry["url"],
                    "status": "deferred_failed",
                    "timestamp_utc": utc_now_iso(),
                    "message": "Deferred because it failed in the previous batch history; not retried in this run.",
                    "error": "Deferred from prior failed batch history",
                }
                print(f"[DEFERRED FAILED] {entry['title']} ({slug}) -> {entry['url']}")
                entries.append(record)
                continue

            existing = progress.get(slug)
            if existing and str(existing.get("status") or "") in valid_resume_statuses():
                record = {
                    "slug": slug,
                    "title": entry["title"],
                    "url": entry["url"],
                    "status": "skipped",
                    "timestamp_utc": utc_now_iso(),
                    "message": "Resume skipped previously successful or valid export.",
                }
                print(f"[RESUME SKIP] {entry['title']} ({slug}) -> {entry['url']}")
                entries.append(record)
                continue
            entries.append(entry)
    else:
        entries = []
        for entry in all_entries:
            slug = entry["slug"]
            if args.defer_failed and slug in deferred_slugs:
                record = {
                    "slug": slug,
                    "title": entry["title"],
                    "url": entry["url"],
                    "status": "deferred_failed",
                    "timestamp_utc": utc_now_iso(),
                    "message": "Deferred because it failed in the previous batch history; not retried in this run.",
                    "error": "Deferred from prior failed batch history",
                }
                print(f"[DEFERRED FAILED] {entry['title']} ({slug}) -> {entry['url']}")
                entries.append(record)
                continue
            entries.append(entry)

    print(f"Manifest entries available: {len(manifest_entries())}")
    print(f"Selected for processing: {len(entries)}")
    print(f"Dry run: {args.dry_run}")
    print(f"Resume mode: {args.resume}")
    print(f"Defer failed: {args.defer_failed}")

    records: list[dict[str, Any]] = []
    for index, entry in enumerate(entries, start=1):
        print(f"[{index}/{len(entries)}] {entry.get('title', 'unknown')} :: {entry.get('url', 'unknown')}")
        if args.resume and entry.get("status") == "skipped" and "Resume skipped" in str(entry.get("message") or ""):
            records.append(entry)
            continue
        if args.defer_failed and entry.get("status") == "deferred_failed":
            records.append(entry)
            continue
        record = process_problem(entry, dry_run=args.dry_run, delay=1.0)
        records.append(record)

    summary = build_summary(records)
    if args.dry_run:
        summary["remaining"] = summary["pending"] + summary["deferred_failed"]
    else:
        summary["remaining"] = max(0, len(entries) - summary["attempted"])
    print("\nSummary:")
    print(json.dumps(summary, indent=2, ensure_ascii=False))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
