#!/usr/bin/env python3
"""Read-only CRCRLF audit for the first 10 GFG exports.

This script resolves each CSV solution_file entry relative to gfg_export_test and
counts raw CRCRLF occurrences in each source file. No writes, no repairs, and no
browser access are performed.
"""

from __future__ import annotations

import csv
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
EXPORT_ROOT = PROJECT_ROOT / "gfg_export_test"
CSV_PATH = EXPORT_ROOT / "problems.csv"
MAX_BATCH = 10


def resolve_solution_path(solution_file: str) -> Path:
    if not solution_file:
        raise ValueError("Empty solution_file in problems.csv")
    candidate = Path(solution_file)
    if candidate.is_absolute():
        return candidate
    return EXPORT_ROOT / candidate


def read_first_ten_rows() -> list[dict[str, str]]:
    with CSV_PATH.open("r", encoding="utf-8", newline="") as handle:
        rows = list(csv.DictReader(handle))
    return rows[:MAX_BATCH]


def find_corrupted_sources() -> list[dict[str, object]]:
    findings: list[dict[str, object]] = []
    for row in read_first_ten_rows():
        source_path = resolve_solution_path(row["solution_file"])
        if not source_path.exists():
            print(f"MISSING: {source_path} -> 0 occurrences")
            findings.append({
                "title": row["title"],
                "path": str(source_path),
                "count": 0,
            })
            continue

        raw = source_path.read_bytes()
        count = raw.count(b"\r\r\n")
        findings.append({
            "title": row["title"],
            "path": str(source_path),
            "count": count,
        })
        print(f"{source_path} -> {count} occurrences")
    return findings


def main() -> None:
    findings = find_corrupted_sources()
    corrupted = [entry for entry in findings if entry["count"] > 0]
    clean = [entry for entry in findings if entry["count"] == 0]
    print(f"\nDetected corrupted files: {len(corrupted)}")
    for entry in corrupted:
        print(f"CRLF: {entry['path']} -> {entry['count']} occurrences")
    print(f"Clean files: {len(clean)}")
    print(f"Total audited: {len(findings)}")


if __name__ == "__main__":
    main()
