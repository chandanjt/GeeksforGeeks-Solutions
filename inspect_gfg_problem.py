
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

        page.get_by_text("Difficulty:", exact=False).first.wait_for(
            timeout=15000
        )

        # Inspect visible problem details and likely containers
        print("\n=== PROBLEM TEXT ===")
        print(page.locator("body").inner_text()[:6000])

        print("\n=== POTENTIAL DESCRIPTION CONTAINERS ===")

        selectors = [
            "[class*='problem-statement']",
            "[class*='problemStatement']",
            "[class*='problem-description']",
            "[class*='problemDescription']",
            "[class*='prose']"
        ]

        for selector in selectors:
            elements = page.locator(selector)
            count = min(elements.count(), 3)

            for i in range(count):
                print(f"\nSelector: {selector} #{i}")
                print(elements.nth(i).inner_text()[:1500])

    finally:
        context.close()

