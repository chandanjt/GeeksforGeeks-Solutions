#!/usr/bin/env python3
"""Repair the first 10 CRCRLF-corrupted GFG exports without touching clean files.

This workflow intentionally operates only on the eight files reported by the read-only
scanner. Count Digits is treated as a manual-approval case because its metadata marks it
as manually_verified; the recovered original is staged in a separate file and the original
source remains unchanged until approval.
"""

from __future__ import annotations

import csv
import importlib.util
import json
from datetime import datetime, timezone
from pathlib import Path
from typing import Any

from playwright.sync_api import sync_playwright

PROJECT_ROOT = Path(__file__).resolve().parents[1]
EXPORT_ROOT = PROJECT_ROOT / "gfg_export_test"
CSV_PATH = EXPORT_ROOT / "problems.csv"
BACKUP_ROOT = EXPORT_ROOT / "backups"


def normalize_language(value: Any) -> str:
    import re

    return re.sub(r"[^a-z0-9+]+", "", str(value or "")).lower()


def resolve_solution_path(solution_file: str) -> Path:
    if not solution_file:
        raise ValueError("Empty solution_file in problems.csv")
    candidate = Path(solution_file)
    return candidate if candidate.is_absolute() else EXPORT_ROOT / candidate


def read_csv_rows() -> list[dict[str, str]]:
    with CSV_PATH.open("r", encoding="utf-8", newline="") as handle:
        return list(csv.DictReader(handle))


def load_audit_module():
    spec = importlib.util.spec_from_file_location(
        "repair_first_ten_gfg_batch",
        PROJECT_ROOT / "scripts" / "repair_first_ten_gfg_batch.py",
    )
    if spec is None or spec.loader is None:
        raise RuntimeError("Unable to load the read-only CRLF audit module")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def find_corrupted_rows() -> list[dict[str, Any]]:
    module = load_audit_module()
    findings = module.find_corrupted_sources()
    rows_by_name = {row["problem_url"]: row for row in read_csv_rows() if row.get("problem_url")}

    targets: list[dict[str, Any]] = []
    for finding in findings:
        if int(finding.get("count") or 0) <= 0:
            continue
        path = Path(str(finding["path"]))
        row = next((r for r in read_csv_rows() if Path(r["solution_file"]).name == path.name), None)
        if row is None:
            raise RuntimeError(f"No CSV row matched the corrupted file: {path}")
        metadata_path = path.with_suffix(".metadata.json")
        metadata = json.loads(metadata_path.read_text(encoding="utf-8")) if metadata_path.exists() else {}
        target = {
            "title": row.get("title") or metadata.get("title") or path.stem,
            "problem_url": row.get("problem_url") or metadata.get("problem_url"),
            "path": str(path),
            "source_path": path,
            "metadata_path": metadata_path,
            "readme_path": path.with_name(f"{path.stem}.README.md"),
            "backup_dir": None,
            "backup_path": None,
            "manual_approval_required": metadata.get("verification") == "manually_verified",
            "date_ist": metadata.get("submission", {}).get("date_ist") or row.get("date_ist"),
            "language": metadata.get("submission", {}).get("language") or row.get("language"),
            "status": metadata.get("submission", {}).get("status") or row.get("status"),
            "count": int(finding.get("count") or 0),
        }
        targets.append(target)
    return targets


def build_repair_targets() -> list[dict[str, Any]]:
    return find_corrupted_rows()


def find_matching_correct_submission_row(page, expected_date: str, expected_language: str):
    rows = page.locator("table tr")
    for index in range(rows.count()):
        row = rows.nth(index)
        cells = [cell.strip() for cell in row.locator("td").all_inner_texts()]
        if len(cells) < 5:
            continue
        status = cells[1].strip()
        if status.lower() != "correct":
            continue
        date_value = cells[0].strip()
        language_value = cells[3].strip()
        if date_value == expected_date and normalize_language(language_value) == normalize_language(expected_language):
            return row

    for index in range(rows.count()):
        row = rows.nth(index)
        cells = [cell.strip() for cell in row.locator("td").all_inner_texts()]
        if len(cells) < 5:
            continue
        if cells[1].strip().lower() != "correct":
            continue
        if cells[0].strip() == expected_date:
            return row

    return None


def recover_historical_submission(problem_url: str, expected_date: str, expected_language: str) -> str:
    with sync_playwright() as playwright:
        context = playwright.chromium.launch_persistent_context(
            user_data_dir=str(PROJECT_ROOT / "playwright_profile"),
            headless=True,
        )
        try:
            context.grant_permissions(["clipboard-read", "clipboard-write"], origin="https://www.geeksforgeeks.org")
            page = context.new_page()
            page.goto(problem_url, wait_until="domcontentloaded")
            page.get_by_text("Submissions", exact=True).click(force=True)
            page.get_by_text("Correct", exact=True).first.wait_for(timeout=20000)
            row = find_matching_correct_submission_row(page, expected_date, expected_language)
            if row is None:
                raise RuntimeError(
                    f"No exact matching Correct submission found for {problem_url} at date={expected_date!r} and language={expected_language!r}"
                )
            row.get_by_text("View", exact=True).first.click(force=True)

            copy_locator = page.locator("button:has-text('Copy')")
            copy_locator.first.wait_for(state="visible", timeout=30000)
            copy_locator.first.click(force=True)

            clipboard_code = page.evaluate("navigator.clipboard.readText()") or ""
            if not clipboard_code.strip():
                raise RuntimeError(f"No code was copied for {problem_url}")
            return clipboard_code
        finally:
            context.close()


def render_readme(metadata: dict[str, Any], code: str) -> str:
    problem_url = metadata.get("problem_url") or "unknown"
    title = metadata.get("title") or "unknown"
    difficulty = metadata.get("difficulty") or "unknown"
    accuracy = metadata.get("accuracy_percent")
    points = metadata.get("points")
    tags = metadata.get("tags") or []
    submission = metadata.get("submission") or {}
    language = submission.get("language") or "unknown"
    assignment = (
        f"{submission.get('date_ist', 'unknown')} | {submission.get('status', 'unknown')} | {submission.get('marks', 'unknown')} | {submission.get('language', 'unknown')} | {submission.get('test_cases', 'unknown')}"
    )

    return (
        f"# {title}\n\n"
        f"- Original problem: [{problem_url}]({problem_url})\n"
        f"- Difficulty: {difficulty}\n"
        f"- Accuracy: {accuracy if accuracy is not None else 'unknown'}\n"
        f"- Points: {points if points is not None else 'unknown'}\n"
        f"- Tags: {', '.join(tags) if tags else 'unknown'}\n"
        f"- Historical submission: {assignment}\n\n"
        "## Summary\n\n"
        "This repository preserves the original accepted code exactly as submitted and does not modify or recompile it.\n\n"
        "## Solution\n\n"
        f"```{language}\n{code}\n```\n"
    )


def write_backup(source_path: Path, backup_dir: Path) -> Path:
    backup_dir.mkdir(parents=True, exist_ok=True)
    backup_path = backup_dir / source_path.name
    backup_path.write_bytes(source_path.read_bytes())
    return backup_path


def repair_target(target: dict[str, Any], timestamp_dir: Path) -> dict[str, Any]:
    source_path = target["source_path"]
    metadata_path = target["metadata_path"]
    metadata = json.loads(metadata_path.read_text(encoding="utf-8")) if metadata_path.exists() else {}

    if target["manual_approval_required"]:
        backup_dir = timestamp_dir / "manual_approval"
        backup_dir.mkdir(parents=True, exist_ok=True)
        staged_path = backup_dir / f"{source_path.stem}.recovered{source_path.suffix}"
        clipboard_code = recover_historical_submission(
            str(metadata["problem_url"]),
            str(metadata["submission"]["date_ist"]),
            str(metadata["submission"]["language"]),
        )
        staged_path.write_bytes(clipboard_code.encode("utf-8"))
        bytes_ok = staged_path.read_bytes() == clipboard_code.encode("utf-8")
        return {
            "title": target["title"],
            "path": str(source_path),
            "status": "staged_manual_approval",
            "backup_path": None,
            "staged_path": str(staged_path),
            "byte_match": bytes_ok,
            "manual_approval_required": True,
            "message": "Original historical submission captured for manual approval; source file was not overwritten.",
        }

    backup_dir = timestamp_dir / "repaired"
    backup_path = write_backup(source_path, backup_dir)
    clipboard_code = recover_historical_submission(
        str(metadata["problem_url"]),
        str(metadata["submission"]["date_ist"]),
        str(metadata["submission"]["language"]),
    )
    source_path.write_bytes(clipboard_code.encode("utf-8"))
    byte_match = source_path.read_bytes() == clipboard_code.encode("utf-8")

    if not byte_match:
        return {
            "title": target["title"],
            "path": str(source_path),
            "status": "failed",
            "backup_path": str(backup_path),
            "staged_path": None,
            "byte_match": False,
            "manual_approval_required": False,
            "message": "Recovered file bytes did not match the clipboard payload exactly.",
        }

    readme_text = render_readme(metadata, clipboard_code)
    target["readme_path"].write_bytes(readme_text.encode("utf-8"))
    return {
        "title": target["title"],
        "path": str(source_path),
        "status": "repaired",
        "backup_path": str(backup_path),
        "staged_path": None,
        "byte_match": True,
        "manual_approval_required": False,
        "message": "Recovered from the matching historical Correct submission and verified byte-for-byte.",
    }


def run_repair_workflow() -> dict[str, Any]:
    timestamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ")
    timestamp_dir = BACKUP_ROOT / timestamp
    timestamp_dir.mkdir(parents=True, exist_ok=True)

    targets = build_repair_targets()
    results: list[dict[str, Any]] = []
    for target in targets:
        try:
            result = repair_target(target, timestamp_dir)
        except Exception as exc:  # pragma: no cover - continue after per-file failure
            result = {
                "title": target["title"],
                "path": str(target["source_path"]),
                "status": "failed",
                "backup_path": None,
                "staged_path": None,
                "byte_match": False,
                "manual_approval_required": target["manual_approval_required"],
                "message": str(exc),
            }
        results.append(result)
        print(f"{result['status']}: {result['title']} -> {result['path']} | {result['message']}")

    audit_module = load_audit_module()
    remaining = [entry for entry in audit_module.find_corrupted_sources() if int(entry.get("count") or 0) > 0]
    report = {
        "timestamp_dir": str(timestamp_dir),
        "initial_corrupted_count": len(targets),
        "successfully_repaired": sum(1 for item in results if item.get("status") == "repaired"),
        "staged_for_manual_approval": sum(1 for item in results if item.get("status") == "staged_manual_approval"),
        "failed": sum(1 for item in results if item.get("status") == "failed"),
        "remaining_corrupted": len(remaining),
        "results": results,
    }
    print("\nRepair summary")
    print(f"Initial corrupted count: {report['initial_corrupted_count']}")
    print(f"Successfully repaired: {report['successfully_repaired']}")
    print(f"Staged for manual approval: {report['staged_for_manual_approval']}")
    print(f"Failed: {report['failed']}")
    print(f"Remaining corrupted: {report['remaining_corrupted']}")
    print(f"Backup directory: {report['timestamp_dir']}")
    return report


def main() -> None:
    run_repair_workflow()


if __name__ == "__main__":
    main()
