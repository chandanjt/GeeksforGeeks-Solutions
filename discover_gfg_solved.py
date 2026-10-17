
import json
from pathlib import Path
from urllib.parse import urljoin, urlparse
from playwright.sync_api import sync_playwright

PROFILE_URL = "https://www.geeksforgeeks.org/profile/chandanjt?from=explore"
OUTPUT = Path("gfg_solved_manifest.json")

with sync_playwright() as p:
    context = p.chromium.launch_persistent_context(
        user_data_dir="./playwright_profile",
        headless=False
    )

    try:
        page = context.new_page()
        page.goto(PROFILE_URL, wait_until="domcontentloaded")

        # Open the Coding Score section.
        page.get_by_role(
            "button", name="Coding Score"
        ).click()

        # Wait for the solved problem links.
        links = page.locator('a[href*="/problems/"]')
        links.first.wait_for(timeout=30000)

        page.wait_for_timeout(2000)

        raw = links.evaluate_all("""elements =>
            elements.map(a => ({
                title: a.innerText.trim().split("\\n")[0],
                url: a.href
            }))
        """)

        unique = {}

        for item in raw:
            url = urljoin(page.url, item["url"])
            path = urlparse(url).path.rstrip("/")

            if path and path not in unique:
                unique[path] = {
                    "title": item["title"],
                    "url": url
                }

        problems = list(unique.values())

        print("Unique solved problems found:", len(problems))

        if len(problems) != 389:
            raise RuntimeError(
                f"Expected 389 problems, found {len(problems)}. "
                "Manifest not saved; inspect the page."
            )

        manifest = {
            "source": "GeeksforGeeks profile",
            "total": len(problems),
            "problems": problems
        }

        OUTPUT.write_text(
            json.dumps(manifest, indent=2, ensure_ascii=False),
            encoding="utf-8"
        )

        print("SUCCESS: Manifest saved")
        print("File:", OUTPUT.resolve())
        print("First problem:", problems[0]["title"])

    finally:
        context.close()
