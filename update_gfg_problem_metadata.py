
import json
import re
from pathlib import Path
from playwright.sync_api import sync_playwright

URL = (
    "https://www.geeksforgeeks.org/problems/"
    "count-digits-in-given-number-n-which-divide-n3331/1"
)

metadata_path = Path(
    "gfg_export_test/problems/count-digits.metadata.json"
)

if not metadata_path.exists():
    raise FileNotFoundError(metadata_path)

with sync_playwright() as p:
    context = p.chromium.launch_persistent_context(
        user_data_dir="./playwright_profile",
        headless=False
    )

    try:
        page = context.new_page()
        page.goto(URL, wait_until="domcontentloaded")

        page.get_by_text("Problem", exact=True).first.click()

        page.get_by_text(
            "Difficulty:", exact=False
        ).first.wait_for(timeout=15000)

        text = page.locator("body").inner_text()
        lines = [line.strip() for line in text.splitlines()
                 if line.strip()]

        difficulty = re.search(
            r"Difficulty:\s*(Easy|Medium|Hard)",
            text, re.IGNORECASE
        )
        accuracy = re.search(
            r"Accuracy:\s*([\d.]+)%",
            text
        )
        submissions = re.search(
            r"Submissions:\s*([\d.KMB+]+)",
            text
        )
        points = re.search(
            r"Points:\s*(\d+)",
            text
        )

        if not difficulty:
            raise RuntimeError("Difficulty not found")

        difficulty_line = next(
            (i for i, line in enumerate(lines)
             if "Difficulty:" in line),
            None
        )

        if difficulty_line is None or difficulty_line == 0:
            raise RuntimeError("Problem title not found")

        title = lines[difficulty_line - 1]

        metadata = json.loads(
            metadata_path.read_text(encoding="utf-8")
        )

        metadata["title"] = title
        metadata["difficulty"] = difficulty.group(1)
        metadata["accuracy_percent"] = (
            float(accuracy.group(1)) if accuracy else None
        )
        metadata["total_submissions_display"] = (
            submissions.group(1) if submissions else None
        )
        metadata["points"] = (
            int(points.group(1)) if points else None
        )

        metadata_path.write_text(
            json.dumps(metadata, indent=2, ensure_ascii=False),
            encoding="utf-8"
        )

        print("SUCCESS: Problem metadata updated")
        print("Title:", metadata["title"])
        print("Difficulty:", metadata["difficulty"])
        print("Accuracy:", metadata["accuracy_percent"])
        print("Submissions:", metadata["total_submissions_display"])
        print("Points:", metadata["points"])

    finally:
        context.close()
