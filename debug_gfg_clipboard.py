
from pathlib import Path
from playwright.sync_api import sync_playwright

URL = ("https://www.geeksforgeeks.org/problems/cyclically-rotate-an-array-by-one2614/0")

SAVED = Path(
    "gfg_export_test/problems/"
    "cyclically-rotate-an-array-by-one2614.js"
)

def inspect(label, code):
    lines = code.splitlines()
    print(f"\n=== {label} ===")
    print("Characters:", len(code))
    print("Total lines:", len(lines))
    print("Blank lines:", sum(not x.strip() for x in lines))
    print("First 200 characters:", repr(code[:200]))

with sync_playwright() as p:
    context = p.chromium.launch_persistent_context(
        user_data_dir="./playwright_profile",
        headless=False
    )

    try:
        context.grant_permissions(
            ["clipboard-read", "clipboard-write"],
            origin="https://www.geeksforgeeks.org"
        )

        page = context.new_page()
        page.goto(URL, wait_until="domcontentloaded")

        page.get_by_text("Submissions", exact=True).click()

        row = page.locator("table tr").filter(
            has=page.get_by_text("Correct", exact=True)
        ).first

        row.wait_for(timeout=15000)
        row.get_by_text("View", exact=True).click()

        page.get_by_text("Copy", exact=True).click()

        clipboard_code = page.evaluate(
            "navigator.clipboard.readText()"
        )

        saved_code = SAVED.read_text(encoding="utf-8")

        inspect("GFG CLIPBOARD", clipboard_code)
        inspect("EXPORTED FILE", saved_code)

        print("\n=== COMPARISON ===")
        print("Exact text match:", clipboard_code == saved_code)

    finally:
        context.close()
