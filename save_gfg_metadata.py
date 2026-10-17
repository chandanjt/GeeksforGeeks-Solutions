
import csv
import json
from pathlib import Path
from playwright.sync_api import sync_playwright

URL = "https://www.geeksforgeeks.org/problems/count-digits-in-given-number-n-which-divide-n3331/1"

output = Path("gfg_export_test")
solution = output / "problems" / "count-digits.cpp"

if not solution.is_file():
    raise FileNotFoundError(f"Verified solution missing: {solution}")

with sync_playwright() as p:
    context = p.chromium.launch_persistent_context(
        user_data_dir="./playwright_profile",
        headless=False
    )
    try:
        page = context.new_page()
        page.goto(URL, wait_until="domcontentloaded")
        page.get_by_text("Submissions", exact=True).click()

        row = page.locator("table tr").filter(
            has=page.get_by_text("Correct", exact=True)
        ).first
        row.wait_for(timeout=15000)

        cells = [c.strip() for c in row.locator("td").all_inner_texts()]
        if len(cells) != 6 or cells[1] != "Correct":
            raise RuntimeError(f"Unexpected submission row: {cells}")

        metadata = {
            "title": "Count digits in a given number N which divide N",
            "problem_url": URL,
            "difficulty": None,
            "topics": [],
            "submission": {
                "date_ist": cells[0],
                "status": cells[1],
                "marks": cells[2],
                "language": cells[3],
                "test_cases": cells[4]
            },
            "solution_file": "problems/count-digits.cpp",
            "verification": "manually_verified"
        }

        output.mkdir(parents=True, exist_ok=True)

        metadata_path = output / "problems" / "count-digits.metadata.json"
        metadata_path.write_text(
            json.dumps(metadata, indent=2),
            encoding="utf-8"
        )

        index_path = output / "problems.csv"
        fields = [
            "title", "problem_url", "difficulty", "topics",
            "language", "status", "date_ist", "solution_file"
        ]

        record = {
            "title": metadata["title"],
            "problem_url": URL,
            "difficulty": "",
            "topics": "",
            "language": cells[3],
            "status": cells[1],
            "date_ist": cells[0],
            "solution_file": metadata["solution_file"]
        }

        with index_path.open("w", newline="", encoding="utf-8") as f:
            writer = csv.DictWriter(f, fieldnames=fields)
            writer.writeheader()
            writer.writerow(record)

        print("SUCCESS: Metadata saved")
        print("Metadata:", metadata_path)
        print("Index:", index_path)
        print("Submission:", cells)
    finally:
        context.close()
