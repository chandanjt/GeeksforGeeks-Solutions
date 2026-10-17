
import importlib.util
import json
import tempfile
from pathlib import Path

from playwright.sync_api import sync_playwright

PROBLEM_URL = (
    "https://www.geeksforgeeks.org/problems/"
    "count-digits-in-given-number-n-which-divide-n3331/1"
)

TEST_URLS = {
    "https://www.geeksforgeeks.org/problems/count-digits-in-given-number-n-which-divide-n3331/1": ["Mathematics"],
    "https://www.geeksforgeeks.org/problems/cyclically-rotate-an-array-by-one2614/0": ["Arrays", "implementation"],
    "https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/0": ["Searching", "Sorting"],
}


def load_exporter_module():
    root = Path(__file__).resolve().parent
    spec = importlib.util.spec_from_file_location("gfg_exporter", root / "scripts" / "gfg_exporter.py")
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)
    return module


def validate_topic_tag_extraction():
    exporter = load_exporter_module()
    with sync_playwright() as playwright:
        context = playwright.chromium.launch_persistent_context(
            user_data_dir="./playwright_profile",
            headless=False,
        )
        try:
            for url, expected_tags in TEST_URLS.items():
                page = context.new_page()
                page.goto(url, wait_until="domcontentloaded")
                page.get_by_text("Difficulty:", exact=False).first.wait_for(timeout=20000)
                tags = exporter.extract_tags(page)
                assert tags == expected_tags, f"Expected tags {expected_tags} for {url}, got {tags}"
                assert not any("issue" in tag.lower() for tag in tags), f"UI control leaked into tags for {url}: {tags}"
                assert not any("timer" in tag.lower() for tag in tags), f"Timer control leaked into tags for {url}: {tags}"
                assert not any("compile" in tag.lower() or "submit" in tag.lower() for tag in tags), f"Compiler/submit control leaked into tags for {url}: {tags}"
                print(f"OK: {url} -> {tags}")
        finally:
            context.close()


def export_count_digits_code():
    with sync_playwright() as playwright:
        context = playwright.chromium.launch_persistent_context(
            user_data_dir="./playwright_profile",
            headless=False,
        )

        try:
            context.grant_permissions(
                ["clipboard-read", "clipboard-write"],
                origin="https://www.geeksforgeeks.org",
            )

            page = context.new_page()
            page.goto(PROBLEM_URL)

            page.get_by_text("Submissions", exact=True).click()
            page.get_by_text("View", exact=True).first.click()
            page.get_by_text("Copy", exact=True).click()

            code = page.evaluate("navigator.clipboard.readText()")

            if not code.strip():
                raise RuntimeError("No code was copied from GFG.")

            output = Path("gfg_export_test/problems/count-digits.cpp")
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_text(code, encoding="utf-8")

            print("SUCCESS: Code extracted from GFG popup")
            print(f"Saved to: {output}")
            print(f"Characters: {len(code)}")
            print("Verification: PENDING manual comparison")

        finally:
            context.close()



def validate_source_code_byte_preservation():
    exporter = load_exporter_module()
    crlf_text = "const a = 1;\r\nif (a > 0) {\r\n  console.log(a);\r\n}\r\n"
    lf_text = "const a = 1;\nif (a > 0) {\n  console.log(a);\n}\n"

    with tempfile.TemporaryDirectory() as tmp_dir:
        root = Path(tmp_dir)

        crlf_path = root / "crlf.js"
        exporter.save_source_code(crlf_path, crlf_text)
        assert crlf_path.read_bytes() == crlf_text.encode("utf-8"), "CRLF input was altered on save"
        assert b"\r\r\n" not in crlf_path.read_bytes(), "CRLF data was double-encoded during save"

        lf_path = root / "lf.js"
        exporter.save_source_code(lf_path, lf_text)
        assert lf_path.read_bytes() == lf_text.encode("utf-8"), "LF input was altered on save"

    print("OK: source-byte preservation -> CRLF and LF inputs are unchanged")


def validate_crlf_detection_counts():
    root = Path(__file__).resolve().parent
    spec = importlib.util.spec_from_file_location("repair_first_ten_gfg_batch", root / "scripts" / "repair_first_ten_gfg_batch.py")
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)

    findings = module.find_corrupted_sources()
    corrupted = {Path(entry["path"]).name: entry["count"] for entry in findings if entry["count"] > 0}
    expected = {
        "count-digits.cpp": 16,
        "floor-in-a-sorted-array-1587115620.cpp": 21,
        "largest-subarray-with-0-sum.cpp": 26,
        "index-of-an-extra-element.cpp": 20,
        "count-numbers-containing-43022.cpp": 26,
        "armstrong-numbers2727.cpp": 17,
        "find-the-number-of-islands.cpp": 30,
        "flood-fill-algorithm1856.cpp": 31,
    }

    assert corrupted == expected, f"Expected exactly 8 corrupted files with counts {expected}, got {corrupted}"
    assert len(corrupted) == 8, f"Expected 8 corrupted files, found {len(corrupted)}"
    assert sum(1 for entry in findings if entry["count"] == 0) == 2, "Expected exactly 2 clean files in the first 10"

    print("OK: CRLF audit -> exactly 8 corrupted files and 2 clean files detected")


def validate_repair_targets_contract():
    root = Path(__file__).resolve().parent
    spec = importlib.util.spec_from_file_location("repair_first_ten_gfg_repair", root / "scripts" / "repair_first_ten_gfg_batch_workflow.py")
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)

    targets = module.build_repair_targets()
    corrupted = [entry for entry in targets if entry["manual_approval_required"] is False]
    manual = [entry for entry in targets if entry["manual_approval_required"] is True]

    assert len(targets) == 8, f"Expected 8 repair targets, got {len(targets)}"
    assert len(corrupted) == 7, f"Expected 7 repairable files, got {len(corrupted)}"
    assert len(manual) == 1, f"Expected 1 manual-approval file, got {len(manual)}"
    assert manual[0]["path"].endswith("count-digits.cpp"), f"Manual approval target should be count-digits.cpp, got {manual[0]['path']}"
    assert all("js" not in entry["path"].lower() for entry in targets), "Clean JavaScript files should not be in repair targets"

    print("OK: repair targets -> 7 repairable files + 1 manual-approval target, no clean JS files")


def validate_batch_manifest():
    import importlib.util
    from pathlib import Path

    root = Path(__file__).resolve().parent
    spec = importlib.util.spec_from_file_location("gfg_batch_export", root / "scripts" / "gfg_batch_export.py")
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)

    entries = module.manifest_entries(limit=10)
    assert len(entries) == 10, f"Expected first 10 unique manifest entries, got {len(entries)}"
    slugs = {entry["slug"] for entry in entries}
    assert len(slugs) == len(entries), "Deduplication failed for manifest entries"

    url_0 = "https://www.geeksforgeeks.org/problems/count-digits-in-given-number-n-which-divide-n3331/0"
    url_1 = "https://www.geeksforgeeks.org/problems/count-digits-in-given-number-n-which-divide-n3331/1"
    assert module.canonical_slug(url_0) == module.canonical_slug(url_1), "/0 and /1 URLs should share one canonical slug"
    print(f"OK: manifest validation -> {len(entries)} unique entries checked")


def validate_batch_dry_run_semantics():
    root = Path(__file__).resolve().parent
    spec = importlib.util.spec_from_file_location("gfg_batch_export", root / "scripts" / "gfg_batch_export.py")
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)

    entries = module.manifest_entries(limit=10)
    existing_valid = [entry for entry in entries if module.is_previously_exported(entry["slug"], entry["url"])]
    pending = [entry for entry in entries if not module.is_previously_exported(entry["slug"], entry["url"])]

    assert len(existing_valid) == 3, f"Expected 3 existing valid entries in first 10, got {len(existing_valid)}"
    assert len(pending) == 7, f"Expected 7 pending entries in first 10, got {len(pending)}"

    with tempfile.TemporaryDirectory() as tmp_dir:
        progress_path = Path(tmp_dir) / "batch_progress.jsonl"
        module.PROGRESS_PATH = progress_path
        dry_run_records = [module.process_problem(entry, dry_run=True) for entry in entries]
        assert not progress_path.exists(), "Dry-run created a progress file"
        assert sum(1 for record in dry_run_records if record["status"] == "existing_valid") == 3
        assert sum(1 for record in dry_run_records if record["status"] == "pending") == 7
        assert not any(record["status"] == "skipped" for record in dry_run_records)

    print("OK: dry-run semantics -> 3 existing_valid, 7 pending, no progress file writes")


def validate_resume_skips_only_valid_exports():
    root = Path(__file__).resolve().parent
    spec = importlib.util.spec_from_file_location("gfg_batch_export", root / "scripts" / "gfg_batch_export.py")
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)

    progress_records = [
        {"slug": "count-digits", "status": "existing_valid", "message": "already valid"},
        {"slug": "rotate-array", "status": "exported_successfully", "message": "success"},
        {"slug": "failed-problem", "status": "failed", "message": "bad parse"},
    ]

    with tempfile.TemporaryDirectory() as tmp_dir:
        progress_path = Path(tmp_dir) / "batch_progress.jsonl"
        progress_path.write_text("\n".join(json.dumps(record) for record in progress_records) + "\n", encoding="utf-8")
        module.PROGRESS_PATH = progress_path
        progress = module.load_progress(progress_path)

        entries = [
            {"slug": "count-digits", "title": "Count Digits", "url": "https://example.com/1"},
            {"slug": "rotate-array", "title": "Rotate Array", "url": "https://example.com/2"},
            {"slug": "failed-problem", "title": "Failed Problem", "url": "https://example.com/3"},
            {"slug": "new-problem", "title": "New Problem", "url": "https://example.com/4"},
        ]

        resume_skips = []
        pending = []
        for entry in entries:
            existing = progress.get(entry["slug"])
            if existing and str(existing.get("status") or "") in module.valid_resume_statuses():
                resume_skips.append({
                    "status": "skipped",
                    "slug": entry["slug"],
                    "title": entry["title"],
                    "url": entry["url"],
                    "message": "Resume skipped previously successful or valid export.",
                })
            else:
                pending.append({
                    "status": "pending",
                    "slug": entry["slug"],
                    "title": entry["title"],
                    "url": entry["url"],
                })

        assert len(resume_skips) == 2, f"Expected 2 resume skips, got {len(resume_skips)}"
        assert len(pending) == 2, f"Expected 2 pending entries, got {len(pending)}"
        assert all(record["slug"] != "failed-problem" for record in resume_skips), "Failed record was incorrectly skipped on resume"

    print("OK: resume semantics -> only valid/successful entries are skipped; failed remains pending")


def validate_optional_metadata_fallbacks():
    exporter = load_exporter_module()

    class FakeLocator:
        def __init__(self, text: str):
            self._text = text

        def inner_text(self):
            return self._text

        def count(self):
            return 0

    class FakePage:
        def __init__(self):
            self._body_text = """Problem: Max Splits
Difficulty: Medium
Topic Tags
Arrays
Greedy
Examples
Constraints
"""

        def title(self):
            return "Max Splits | GeeksforGeeks"

        def locator(self, selector):
            if selector == "body":
                return FakeLocator(self._body_text)
            return FakeLocator("")

    page = FakePage()
    metadata = exporter.extract_problem_metadata(page)
    assert metadata["difficulty"] == "Medium", metadata
    assert metadata["tags"] == ["Arrays", "Greedy"], metadata

    print("OK: optional metadata fallback -> missing DOM selectors still parse body text")


def validate_batch_defer_failed_dry_run():
    root = Path(__file__).resolve().parent
    spec = importlib.util.spec_from_file_location("gfg_batch_export", root / "scripts" / "gfg_batch_export.py")
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)

    entries = module.manifest_entries(limit=30)
    assert len(entries) == 30, f"Expected 30 manifest entries, got {len(entries)}"

    progress_records = module.load_progress(module.PROGRESS_PATH)
    failed_slugs = module.deferred_failed_slugs(progress_records)
    assert failed_slugs == {"max-splits", "need-some-change"}, f"Expected deferred failures to be max-splits and need-some-change, got {failed_slugs}"

    dry_run_records = []
    for entry in entries:
        if entry["slug"] in failed_slugs:
            dry_run_records.append({
                "slug": entry["slug"],
                "title": entry["title"],
                "url": entry["url"],
                "status": "deferred_failed",
                "message": "Deferred because it has a recorded failure in history; dry run does not retry it.",
            })
            continue
        dry_run_records.append({
            "slug": entry["slug"],
            "title": entry["title"],
            "url": entry["url"],
            "status": "existing_valid" if module.is_previously_exported(entry["slug"], entry["url"]) else "pending",
        })

    valid = sum(1 for record in dry_run_records if record["status"] == "existing_valid")
    deferred = sum(1 for record in dry_run_records if record["status"] == "deferred_failed")
    pending = sum(1 for record in dry_run_records if record["status"] == "pending")

    assert valid == 28, f"Expected 28 existing valid entries in the first 30, got {valid}"
    assert deferred == 2, f"Expected 2 deferred failures in the first 30, got {deferred}"
    assert pending == 0, f"Expected no new export attempts in the first 30 dry run, got {pending} pending entries"

    print("OK: first 30 dry run -> 28 existing valid exports and 2 deferred failures, no new export attempts")


if __name__ == "__main__":
    validate_topic_tag_extraction()
    validate_source_code_byte_preservation()
    validate_optional_metadata_fallbacks()
    validate_batch_defer_failed_dry_run()
    validate_crlf_detection_counts()
    validate_repair_targets_contract()
    validate_batch_manifest()
    validate_batch_dry_run_semantics()
    validate_resume_skips_only_valid_exports()
