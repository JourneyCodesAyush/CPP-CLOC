# 📄 Changelog

All notable, user-visible changes to CPP-CLOC are documented in this file.

CPP-CLOC follows Semantic Versioning.
Versions prior to 1.0.0 indicate a stable analyzer core with evolving features.
Counting behaviors aligned with `cloc` are intentional and not considered bugs.

---

## v0.4.1 - File Type Classification Fix

### Fixed

- Corrected `detector::FileType` passed to the analyzer:
  - C/C++ header files now use `C_CPP_HEADER`.
  - Markdown files are now correctly classified as `MARKDOWN`.

### Notes

- No changes to analyzer logic or cloc-style counting semantics.
- This is a patch release correcting internal classification only.

---

## v0.4.0 - Output Metadata & STDOUT Enhancements

### Added

- Metadata in outputs:
  - **STDOUT:** `total_files`, `analyzed_files`, and `ignored_files`.
  - **JSON & XML:** `n_files` field.

- CSV, JSON, and XML outputs remain strictly machine-readable.
- Minor design note: single-line Bash scripts or one-liner loops may count as multiple lines if line breaks exist; this aligns with cloc-style text-based counting.

### Changed

- STDOUT table now includes total/ignored files information for better user insight.
- JSON and XML headers updated to use `cpp_cloc_url` and `cpp_cloc_tag` instead of `cloc_url` / `cloc_version`.

### Notes

- Analyzer behavior remains cloc-aligned; line counting quirks are intentional.
- Prepares CPP-CLOC for v0.4.0 release with improved metadata tracking.

---

## v0.3.0 - Output Redirection & Printing Refactor

### Added

- `--output` CLI flag to redirect output to a file (users can now save cpp-cloc output instead of printing to console).
- `print_result_map` now returns formatted output as a `std::string`.
- `main.cpp` updated to consume string output from `print_result_map`.

### Changed

- Printing logic refactored: output is collected in `std::stringstream` and returned as string instead of direct console printing.
- CommentSyntax variables marked `inline` for cleaner header usage.

### Fixed

- Corrected Python file type aggregation in `middleware` (previously miscounted some Python files).

### Notes

- Future improvement: consider streaming output directly to the file to handle very large directories more efficiently.
- All changes preserve existing cloc-style behavior, including line counting quirks.

---

## v0.2.0 - Output Formats and CLI Improvements

### Added

- JSON, CSV, and XML output formats
- Mutually exclusive CLI flags: --json, --csv, --xml

### Changed

- Middleware now returns a Result struct instead of printing directly
- Main function selects output format and delegates rendering to print module

### Notes

- Analyzer behavior and cloc-style counting semantics remain unchanged

---

## v0.1.0 - Initial Stable Milestone

### Added

- Single-pass, text-based analyzer consistent with cloc behavior
- Multi-language support via configurable comment syntax
- Recursive directory and single-file analysis
- Aggregated per-language statistics
- Execution time measurement
- Cross-platform C++17 support

### Notes

- Analyzer semantics and cloc-style limitations are considered stable as of this version.
- Future releases will focus on output formats, testing, and maintainability.
