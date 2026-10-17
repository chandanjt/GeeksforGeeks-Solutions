from pathlib import Path
from playwright.sync_api import sync_playwright

URL = 'https://www.geeksforgeeks.org/problems/count-digits-in-given-number-n-which-divide-n3331/1'
root = Path(__file__).resolve().parents[1]

with sync_playwright() as p:
    context = p.chromium.launch_persistent_context(user_data_dir=str(root / 'playwright_profile'), headless=False)
    context.grant_permissions(['clipboard-read', 'clipboard-write'], origin='https://www.geeksforgeeks.org')
    page = context.new_page()
    page.goto(URL, wait_until='domcontentloaded', timeout=60000)
    print('URL =', page.url)
    print('TITLE =', page.title())
    print('H1 count =', page.locator('h1').count())
    print('Body text sample =', page.locator('body').inner_text()[:1500])
    context.close()
