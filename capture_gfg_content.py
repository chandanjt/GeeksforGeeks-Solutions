
import json
import re
from datetime import datetime, timezone
from pathlib import Path
from playwright.sync_api import sync_playwright

root = Path("gfg_export_test")
metadata_path = root / "problems/count-digits.metadata.json"

metadata = json.loads(metadata_path.read_text(encoding="utf-8"))
url = metadata["problem_url"]
title = metadata["title"]

with sync_playwright() as p:
    context = p.chromium.launch_persistent_context(
        user_data_dir="./playwright_profile",
        headless=False
    )

    try:
        page = context.new_page()
        page.goto(url, wait_until="domcontentloaded")
        page.get_by_text("Difficulty:", exact=False).first.wait_for()

        body = page.locator("body").inner_text()

        # Isolate the current problem content.
        start = body.find(title)
        if start == -1:
            raise RuntimeError("Problem title not found on page")

        end = body.find("Topic Tags", start)
        if end == -1:
            raise RuntimeError("End of problem content not found")

        section = body[start + len(title):end]

        # Remove metadata header from the description.
        header = re.search(r"Points:\s*\d+", section)
        if not header:
            raise RuntimeError("Problem metadata header not found")

        content = section[header.end():].strip()

        # Separate description, examples and constraints.
        description, marker, remainder = content.partition(
            "Examples:"
        )
        if not marker:
            raise RuntimeError("Examples section not found")

        examples, marker, constraints = remainder.partition(
            "Constraints:"
        )
        if not marker:
            constraints = ""

        data = {
            "title": title,
            "problem_url": url,
            "description": description.strip(),
            "examples_text": examples.strip(),
            "constraints_text": constraints.strip(),
            "captured_at": datetime.now(
                timezone.utc
            ).isoformat(),
            "source": "GFG problem tab",
            "format_verified": False
        }

        # Keep original problem text outside published source files.
        output = root / "private" / "problem_content.json"
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(
            json.dumps(data, indent=2, ensure_ascii=False),
            encoding="utf-8"
        )

        print("SUCCESS: Problem content captured")
        print("Description length:", len(data["description"]))
        print("Examples length:", len(data["examples_text"]))
        print("Constraints:", repr(data["constraints_text"]))
        print("Saved:", output)

    finally:
        context.close()

