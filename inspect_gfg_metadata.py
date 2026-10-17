
from playwright.sync_api import sync_playwright

URL = (
    "https://www.geeksforgeeks.org/problems/"
    "count-digits-in-given-number-n-which-divide-n3331/1"
)

with sync_playwright() as p:
    context = p.chromium.launch_persistent_context(
        user_data_dir="./playwright_profile",
        headless=False
    )

    try:
        page = context.new_page()
        page.goto(URL, wait_until="domcontentloaded")

        print("\n=== PROBLEM DETAILS ===")
        print("URL:", page.url)

        headings = page.locator("h1").all_text_contents()
        print("Headings:", headings[:5])

        # Open historical submissions
        page.get_by_text("Submissions", exact=True).click()

        # Wait until successful submission is visible
        page.get_by_text("Correct", exact=True).first.wait_for(
            timeout=15000
        )

        print("\n=== SUBMISSION TABLE ===")

        headers = page.locator("table th").all_text_contents()
        print("Headers:", headers)

        rows = page.locator("table tr").all_text_contents()
        for row in rows[:5]:
            print("ROW:", repr(row.strip()))

        print("\n=== INSPECTION COMPLETED ===")

    finally:
        context.close()
