#!/usr/bin/env python3
"""Consolidated GeeksforGeeks exporter.

This script preserves the original verified extraction flow already used in the
workspace: it opens the persistent authenticated Playwright profile, navigates to
an individual problem URL, copies the accepted historical submission, parses the
current metadata, stores the original problem text privately, and writes a public
summary README plus a CSV index without restructuring the original solution.
"""

from __future__ import annotations

import argparse
import csv
import json
import re
from datetime import datetime, timezone
from pathlib import Path
from typing import Any
from urllib.parse import urlparse

from playwright.sync_api import sync_playwright

DEFAULT_PROBLEM_URL = (
    "https://www.geeksforgeeks.org/problems/"
    "count-digits-in-given-number-n-which-divide-n3331/1"
)

KNOWN_PROBLEM_OVERRIDES = {
    "count-digits-in-given-number-n-which-divide-n3331": "count-digits",
}

MANUALLY_VERIFIED_PROBLEM_URLS = {
    "https://www.geeksforgeeks.org/problems/count-digits-in-given-number-n-which-divide-n3331/1",
}

LANGUAGE_EXTENSIONS = {
    "cpp": ".cpp",
    "c++": ".cpp",
    "c": ".c",
    "javascript": ".js",
    "js": ".js",
    "python": ".py",
    "py": ".py",
    "java": ".java",
    "go": ".go",
    "ruby": ".rb",
    "swift": ".swift",
    "php": ".php",
    "typescript": ".ts",
    "ts": ".ts",
    "kotlin": ".kt",
    "rust": ".rs",
    "c#": ".cs",
    "cs": ".cs",
    "scala": ".scala",
}

INVALID_TAG_VALUES = {
    "related articles",
    "topic tags",
    "articles",
    "practice",
    "expected complexities",
    "company tags",
    "report an issue",
    "start timer",
    "custom input",
    "compile & run",
    "compile & runsubmit",
    "submit",
    "if you are facing any issue on this page. please let us know.",
}


def root_dir() -> Path:
    return Path(__file__).resolve().parents[1]


def normalize_problem_url(raw_url: str) -> str:
    url = raw_url.strip()
    if not url:
        return DEFAULT_PROBLEM_URL
    if not url.startswith("http"):
        url = "https://" + url
    return url.rstrip("/")


def slug_from_problem_url(problem_url: str) -> str:
    parsed = urlparse(problem_url)
    path_parts = [part for part in parsed.path.split("/") if part]
    if not path_parts:
        return "problem"

    slug = path_parts[-2] if len(path_parts) > 1 and path_parts[-1].isdigit() else path_parts[-1]
    slug = slug.split("?")[0]
    return KNOWN_PROBLEM_OVERRIDES.get(slug, slug)


def ensure_text(value: Any, default: str = "unknown") -> str:
    if value is None:
        return default
    text = str(value).strip()
    return text if text else default


def normalize_language(language: str) -> str:
    return re.sub(r"[^a-z0-9+]+", "", str(language or "")).lower()


def language_extension(language: str) -> str:
    key = normalize_language(language)
    return LANGUAGE_EXTENSIONS.get(key, ".txt")


def looks_like_ui_control_tag(tag: str) -> bool:
    value = re.sub(r"\s+", " ", ensure_text(tag, "")).strip()
    if not value:
        return True
    lowered = value.lower()
    if lowered in INVALID_TAG_VALUES:
        return True
    if lowered.startswith("related"):
        return True
    ui_markers = (
        "report an issue",
        "if you are facing any issue",
        "start timer",
        "custom input",
        "compile & run",
        "compile",
        "submit",
        "expected complexities",
        "company tags",
        "problem statement",
        "ask a doubt",
        "give me a hint",
    )
    return any(marker in lowered for marker in ui_markers)


def clean_tags(tags: list[str]) -> list[str]:
    cleaned: list[str] = []
    seen: set[str] = set()
    for tag in tags:
        value = re.sub(r"\s+", " ", ensure_text(tag, "")).strip()
        if not value:
            continue
        lowered = value.lower()
        if lowered in INVALID_TAG_VALUES:
            continue
        if looks_like_ui_control_tag(value):
            continue
        if lowered.startswith("related"):
            continue
        if lowered in seen:
            continue
        seen.add(lowered)
        cleaned.append(value)
    return cleaned


def safe_int(value: Any) -> int | None:
    if value is None:
        return None
    text = str(value).strip()
    if not text:
        return None
    try:
        return int(text)
    except ValueError:
        return None


def safe_float(value: Any) -> float | None:
    if value is None:
        return None
    text = str(value).strip()
    if not text:
        return None
    try:
        return float(text)
    except ValueError:
        return None


def get_browser_context(playwright: Any, root: Path):
    profile_dir = root / "playwright_profile"
    context = playwright.chromium.launch_persistent_context(
        user_data_dir=str(profile_dir),
        headless=False,
    )
    context.grant_permissions(
        ["clipboard-read", "clipboard-write"],
        origin="https://www.geeksforgeeks.org",
    )
    return context


def extract_title(page) -> str:
    page_title = page.title().strip()
    if page_title:
        title = page_title.split("|", 1)[0].strip()
        if title:
            return title

    body_text = page.locator("body").inner_text()
    lines = [line.strip() for line in body_text.splitlines() if line.strip()]
    for index, line in enumerate(lines):
        if "Difficulty:" in line and index > 0:
            return lines[index - 1]
    return "unknown"


def extract_tags_from_text(text: str) -> list[str]:
    if not text:
        return []

    lower_text = text.lower()
    tag_index = lower_text.find("topic tags")
    if tag_index == -1:
        return []

    tail = text[tag_index + len("Topic Tags") :]
    for stop_marker in (
        "Company Tags",
        "Related Articles",
        "Expected Complexities",
        "Difficulty",
        "Accuracy",
        "Points",
        "Examples",
        "Constraints",
        "Practice",
    ):
        marker_index = tail.lower().find(stop_marker.lower())
        if marker_index != -1:
            tail = tail[:marker_index]

    topic_candidates: list[str] = []
    for chunk in re.split(r"[\n|•]+", tail):
        for token in chunk.split():
            candidate = re.sub(r"\s+", " ", token).strip(" :;,-")
            if candidate:
                topic_candidates.append(candidate)

    return clean_tags(topic_candidates)


def extract_tags(page) -> list[str]:
    tag_blocks = page.locator("div.problems_accordion_tags__JJ2DX")
    topic_candidates: list[str] = []

    try:
        for index in range(tag_blocks.count()):
            block = tag_blocks.nth(index)
            headings = block.locator("strong")
            if headings.count() == 0:
                continue
            heading = re.sub(r"\s+", " ", headings.first.inner_text().strip())
            if not re.fullmatch(r"Topic Tags", heading, re.IGNORECASE):
                continue

            labels = block.locator("a.ui.label.problems_tag_label__A4Ism")
            if labels.count() == 0:
                block_text = block.inner_text()
                topic_candidates.extend(extract_tags_from_text(block_text))
                continue

            for label_index in range(labels.count()):
                label = labels.nth(label_index)
                if label.count() == 0:
                    continue
                candidate = re.sub(r"\s+", " ", label.inner_text().strip())
                if candidate:
                    topic_candidates.append(candidate)
    except Exception:
        topic_candidates = []

    if topic_candidates:
        return clean_tags(topic_candidates)

    body_text = page.locator("body").inner_text()
    return extract_tags_from_text(body_text)


def extract_problem_metadata(page) -> dict[str, Any]:
    text = page.locator("body").inner_text()
    difficulty_match = re.search(r"Difficulty\s*:\s*(Basic|Easy|Medium|Hard|Expert|Beginner)", text, re.IGNORECASE)
    accuracy_match = re.search(r"Accuracy\s*:\s*([\d.]+)%", text)
    points_match = re.search(r"Points\s*:\s*(\d+)", text)
    tags = extract_tags(page)

    metadata = {
        "title": extract_title(page),
        "difficulty": difficulty_match.group(1).title() if difficulty_match else "unknown",
        "accuracy_percent": safe_float(accuracy_match.group(1)) if accuracy_match else None,
        "points": safe_int(points_match.group(1)) if points_match else None,
        "tags": tags,
    }
    return metadata


def extract_historical_submission(page) -> dict[str, Any]:
    page.get_by_text("Submissions", exact=True).click(force=True)
    page.get_by_text("Correct", exact=True).first.wait_for(timeout=15000)

    row = page.locator("table tr").filter(has=page.get_by_text("Correct", exact=True)).first
    row.wait_for(timeout=15000)

    cells = [cell.strip() for cell in row.locator("td").all_inner_texts()]
    normalized = cells[:6]
    if len(normalized) < 5:
        normalized.extend(["unknown"] * (5 - len(normalized) + 1))

    status = normalized[1] if len(normalized) > 1 else "unknown"
    language = normalized[3] if len(normalized) > 3 else "unknown"
    test_cases = normalized[4] if len(normalized) > 4 else "unknown"

    return {
        "date_ist": normalized[0] if len(normalized) > 0 else "unknown",
        "status": status,
        "marks": normalized[2] if len(normalized) > 2 else "unknown",
        "language": language,
        "test_cases": test_cases,
    }


def copy_historical_submission(page) -> str:
    page.get_by_text("Submissions", exact=True).click(force=True)
    page.get_by_text("Correct", exact=True).first.wait_for(timeout=15000)
    page.get_by_text("View", exact=True).first.click(force=True)
    page.get_by_text("Copy", exact=True).first.wait_for(timeout=15000)
    page.get_by_text("Copy", exact=True).first.click(force=True)

    code = page.evaluate("navigator.clipboard.readText()")
    code = code or ""
    if not code.strip():
        raise RuntimeError("No code was copied from the GFG historical submission popup.")
    return code


def extract_problem_text(page, title: str) -> dict[str, str]:
    body = page.locator("body").inner_text()
    start = body.find(title)
    if start == -1:
        raise RuntimeError(f"Problem title '{title}' was not found in the problem body.")

    end = body.find("Topic Tags", start)
    if end == -1:
        end = len(body)

    section = body[start + len(title) : end]
    header_match = re.search(r"Points:\s*\d+", section)
    if header_match:
        section = section[header_match.end() :]
    elif section.startswith("\n"):
        section = section.lstrip()

    description, marker, remainder = section.partition("Examples:")
    if not marker:
        description = section
        examples = ""
        constraints = ""
    else:
        examples, marker, constraints = remainder.partition("Constraints:")
        if not marker:
            constraints = ""

    return {
        "description": description.strip(),
        "examples": examples.strip(),
        "constraints": constraints.strip(),
    }


def save_source_code(path: Path, code: str) -> None:
    path.write_bytes(code.encode("utf-8"))


def export_problem(problem_url: str, root: Path, force: bool = False) -> dict[str, Any]:
    problem_url = normalize_problem_url(problem_url)
    slug = slug_from_problem_url(problem_url)
    base_dir = root / "gfg_export_test"
    problems_dir = base_dir / "problems"
    private_dir = base_dir / "private"
    problems_dir.mkdir(parents=True, exist_ok=True)
    private_dir.mkdir(parents=True, exist_ok=True)

    with sync_playwright() as playwright:
        context = get_browser_context(playwright, root)
        try:
            page = context.new_page()
            page.goto(problem_url, wait_until="domcontentloaded")
            page.locator("body").wait_for(timeout=15000)

            title = extract_title(page)
            metadata = extract_problem_metadata(page)
            metadata["problem_url"] = problem_url
            metadata["title"] = ensure_text(title, "unknown")

            problem_text = extract_problem_text(page, title)
            submission = extract_historical_submission(page)
            submission_language = ensure_text(submission.get("language"), "unknown")
            extension = language_extension(submission_language)
            metadata["submission"] = {
                "date_ist": ensure_text(submission.get("date_ist"), "unknown"),
                "status": ensure_text(submission.get("status"), "unknown"),
                "marks": ensure_text(submission.get("marks"), "unknown"),
                "language": submission_language,
                "test_cases": ensure_text(submission.get("test_cases"), "unknown"),
            }

            metadata_path = problems_dir / f"{slug}.metadata.json"
            source_path = problems_dir / f"{slug}{extension}"
            public_readme_path = problems_dir / f"{slug}.README.md"
            private_problem_path = private_dir / f"{slug}.problem_content.json"

            if metadata_path.exists() and source_path.exists() and not force:
                existing = json.loads(metadata_path.read_text(encoding="utf-8"))
                print(f"Problem already exported: {existing.get('title', slug)}")
                return existing

            if source_path.exists() and source_path.stat().st_size > 0 and not force:
                raise FileExistsError(
                    f"Refusing to overwrite verified source for {slug}: {source_path}. "
                    "Use --force only when intentionally replacing the exported solution."
                )

            code = copy_historical_submission(page)
            save_source_code(source_path, code)

            metadata["solution_file"] = f"problems/{source_path.name}"
            metadata["private_problem_snapshot"] = f"private/{private_problem_path.name}"
            metadata["public_readme_file"] = f"problems/{public_readme_path.name}"
            metadata["verification"] = (
                "manually_verified"
                if problem_url in MANUALLY_VERIFIED_PROBLEM_URLS
                else "auto_exported"
            )
            metadata["captured_at_utc"] = datetime.now(timezone.utc).isoformat()

            private_payload = {
                "title": metadata["title"],
                "problem_url": problem_url,
                "description": problem_text["description"],
                "examples_text": problem_text["examples"],
                "constraints_text": problem_text["constraints"],
                "captured_at": datetime.now(timezone.utc).isoformat(),
                "source": "GFG problem tab",
                "format_verified": True,
            }
            private_problem_path.write_text(
                json.dumps(private_payload, indent=2, ensure_ascii=False),
                encoding="utf-8",
            )

            problem_summary = (
                "This repository preserves the original accepted solution, problem metadata, "
                "and historical submission details without modifying the source code."
            )
            accuracy_value = (
                f"{metadata['accuracy_percent']}%"
                if metadata.get("accuracy_percent") is not None
                else "unknown"
            )
            points_value = (
                metadata["points"] if metadata.get("points") is not None else "unknown"
            )
            public_readme = f"""# {metadata['title']}

- Original problem: [{problem_url}]({problem_url})
- Difficulty: {metadata['difficulty']}
- Accuracy: {accuracy_value}
- Points: {points_value}
- Tags: {', '.join(metadata['tags']) if metadata['tags'] else 'unknown'}
- Historical submission: {metadata['submission']['date_ist']} | {metadata['submission']['status']} | {metadata['submission']['marks']} | {metadata['submission']['language']} | {metadata['submission']['test_cases']}

## Summary

{problem_summary}

## Solution

This repository keeps the original accepted code exactly as submitted and does not modify or recompile it.

```{metadata['submission']['language']}
{code}
```
"""
            public_readme_path.write_text(public_readme, encoding="utf-8")

            metadata_path.write_text(
                json.dumps(metadata, indent=2, ensure_ascii=False),
                encoding="utf-8",
            )

            csv_path = base_dir / "problems.csv"
            fields = [
                "title",
                "problem_url",
                "difficulty",
                "tags",
                "language",
                "status",
                "date_ist",
                "solution_file",
                "public_readme_file",
            ]
            record = {
                "title": metadata["title"],
                "problem_url": problem_url,
                "difficulty": metadata["difficulty"],
                "tags": "; ".join(metadata["tags"]) if metadata["tags"] else "",
                "language": metadata["submission"]["language"],
                "status": metadata["submission"]["status"],
                "date_ist": metadata["submission"]["date_ist"],
                "solution_file": metadata["solution_file"],
                "public_readme_file": metadata["public_readme_file"],
            }

            existing_rows = []
            if csv_path.exists():
                existing_rows = list(csv.DictReader(csv_path.open("r", encoding="utf-8", newline="")))

            existing_by_url = {row.get("problem_url"): row for row in existing_rows}
            if problem_url not in existing_by_url:
                existing_rows.append(record)
            else:
                existing_rows = [
                    record if row.get("problem_url") == problem_url else row for row in existing_rows
                ]

            with csv_path.open("w", newline="", encoding="utf-8") as handle:
                writer = csv.DictWriter(handle, fieldnames=fields)
                writer.writeheader()
                writer.writerows(existing_rows)

            metadata_rows = []
            for row in existing_rows:
                metadata_rows.append(
                    {
                        "title": row.get("title"),
                        "problem_url": row.get("problem_url"),
                        "difficulty": row.get("difficulty"),
                        "accuracy_percent": None,
                        "points": None,
                        "tags": row.get("tags", "unknown").split("; ") if row.get("tags") and row.get("tags") != "unknown" else [],
                    }
                )

            root_metadata = {
                "generated_at_utc": datetime.now(timezone.utc).isoformat(),
                "problem_count": len(metadata_rows),
                "problems": metadata_rows,
            }
            (base_dir / "metadata.json").write_text(
                json.dumps(root_metadata, indent=2, ensure_ascii=False),
                encoding="utf-8",
            )

            print("SUCCESS: GFG exporter completed")
            print(f"Problem: {metadata['title']}")
            print(f"Metadata: {metadata_path}")
            print(f"Source: {source_path}")
            print(f"Private snapshot: {private_problem_path}")
            print(f"Index: {csv_path}")
            print(f"Public README: {public_readme_path}")
            return metadata
        finally:
            context.close()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Export a single GFG problem and preserve its original source code.")
    parser.add_argument("url", nargs="?", default=DEFAULT_PROBLEM_URL, help="The GeeksforGeeks problem URL to export.")
    parser.add_argument("--force", action="store_true", help="Overwrite an existing exported problem snapshot.")
    return parser.parse_args()


if __name__ == "__main__":
    args = parse_args()
    export_problem(args.url, root_dir(), force=args.force)
