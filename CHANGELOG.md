# 📄 Changelog

All notable, user-visible changes to CPP-CLOC are documented in this file.

CPP-CLOC follows Semantic Versioning.
Versions prior to 1.0.0 indicate a stable analyzer core with evolving features.
Counting behaviors aligned with `cloc` are intentional and not considered bugs.

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
