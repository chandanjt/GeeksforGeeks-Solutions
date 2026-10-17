
import csv
import json
import shutil
from pathlib import Path

root = Path("gfg_export_test")

source_code = root / "problems" / "count-digits.cpp"
source_metadata = root / "problems" / "count-digits.metadata.json"

if not source_code.is_file() or not source_metadata.is_file():
    raise FileNotFoundError("Previous verified export files are missing.")

metadata = json.loads(source_metadata.read_text(encoding="utf-8"))
code = source_code.read_text(encoding="utf-8")

if not code.strip():
    raise ValueError("Solution source code is empty.")

slug = "digits-in-n-that-divide-it"
folder = root / "Other" / slug
folder.mkdir(parents=True, exist_ok=True)

destination_code = folder / "solution.cpp"
destination_metadata = folder / "metadata.json"
destination_readme = folder / "README.md"

# Never silently overwrite a different solution.
if destination_code.exists():
    if destination_code.read_text(encoding="utf-8") != code:
        raise RuntimeError("Existing solution differs. Review manually.")
else:
    shutil.copyfile(source_code, destination_code)

metadata["solution_file"] = "solution.cpp"
metadata["verification"] = "manually_verified"

destination_metadata.write_text(
    json.dumps(metadata, indent=2, ensure_ascii=False),
    encoding="utf-8"
)

submission = metadata["submission"]
title = metadata["title"]
url = metadata["problem_url"]
difficulty = metadata.get("difficulty") or "Unknown"
topics = metadata.get("topics") or []
topic_text = ", ".join(topics) if topics else "Not yet classified"

readme = f"""# {title}

**Problem:** [View on GeeksforGeeks]({url})

| Attribute | Value |
|---|---|
| Difficulty | {difficulty} |
| Topics | {topic_text} |
| Language | {submission['language']} |
| Status | {submission['status']} |
| Submitted (IST) | {submission['date_ist']} |
| Marks | {submission['marks']} |
| Test Cases | {submission['test_cases']} |

## My Accepted Solution

```cpp
{code.rstrip()}
```

## Notes

Original historical submission, preserved without rewriting.
Problem details may have changed since the submission date.
"""

destination_readme.write_text(readme, encoding="utf-8")

# Rebuild the master index from packaged metadata.
fields = [
    "title", "difficulty", "topics", "language",
    "status", "date_ist", "problem_url", "solution_file"
]

records = []

for metadata_file in sorted(root.glob("*/**/metadata.json")):
    data = json.loads(metadata_file.read_text(encoding="utf-8"))
    sub = data.get("submission", {})

    records.append({
        "title": data.get("title", ""),
        "difficulty": data.get("difficulty") or "",
        "topics": ", ".join(data.get("topics") or []),
        "language": sub.get("language", ""),
        "status": sub.get("status", ""),
        "date_ist": sub.get("date_ist", ""),
        "problem_url": data.get("problem_url", ""),
        "solution_file": str(
            (metadata_file.parent / data["solution_file"]).relative_to(root)
        ).replace("\\", "/")
    })

with (root / "problems.csv").open(
    "w", newline="", encoding="utf-8"
) as f:
    writer = csv.DictWriter(f, fieldnames=fields)
    writer.writeheader()
    writer.writerows(records)

print("SUCCESS: Problem package created")
print("Folder:", folder)
print("Files: solution.cpp, metadata.json, README.md")
print("Master index:", root / "problems.csv")
print("Total indexed problems:", len(records))

