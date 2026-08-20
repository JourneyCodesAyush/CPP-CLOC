# 📄 Changelog

All notable, user-visible changes to CPP-CLOC are documented in this file.

CPP-CLOC follows Semantic Versioning.
Versions prior to 1.0.0 indicate a stable analyzer core with evolving features.
Counting behaviors aligned with `cloc` are intentional and not considered bugs.

---

## 0.7.0

### Added

- Parallel file processing: files are split into chunks and analyzed
  concurrently via `std::async`, one worker per chunk, sized to
  `std::thread::hardware_concurrency()`.
- `PARALLEL_THRESHOLD` guard (200 files): below this, cpp-cloc runs
  sequentially, since thread-spawn overhead outweighs any gain at
  small scale. See [`benchmarks/README.md`](./benchmarks/README.md) for measured numbers and
  methodology.
- `benchmarks/` directory with reproducible benchmark scripts
  (`generate_test_data.py`, `run_benchmark.py`).

### Changed

- Build now links `-pthread` (required for `std::thread`/`std::async`
  on Linux/macOS via g++).

### Fixed

- N/A

---

## v0.6.3 – Build Optimization & Performance Improvements

### Added

- Introduced **release build mode** via Makefile using `-O3` optimization:
  - Enabled with: `make RELEASE=1`
- Improved runtime performance by disabling synchronization between C++ streams and C stdio:
  - Added `std::ios::sync_with_stdio(false)` in `main()`

### Changed

- Default build remains debug (`-g`) for development and testing
- Release builds are now recommended for analyzing large codebases

### Notes

- No changes to analyzer behavior or cloc-style counting semantics
- These changes are purely performance-oriented and do not affect output correctness

---

## v0.6.2 – Output File Handling Fix

### Fixed

- Prevent attempting to open an empty output filename when `--output` is not specified. Ensures output defaults to STDOUT without errors.

---

## v0.6.1 – Output Formatting Stabilization

### Fixed

- Widened STDOUT table columns to prevent overflow on large repositories.
- Normalized JSON header spacing for consistent formatting.
- Removed sentinel `"STDOUT"` default for `--output`; empty value now correctly represents standard output.

### Notes

- No changes to analyzer behavior or cloc-style counting semantics.

---

## v0.6.0 – `--exclude-dir`

### Added

- Introduced `--exclude-dir` CLI flag to exclude directories by name during recursive file discovery.
- Default exclusions include common VCS and dependency directories (`.git`, `.svn`, `.hg`, `.bzr`, `.cvs`, `.snapshot`, `node_modules`).
- Input validation rejects directory names containing `/` or `\` to enforce **name-only matching**.

### Changed / Refactored

- Replaced all `return 1` exits in `main.cpp` with `exit(EXIT_FAILURE)` for **consistent and explicit error handling**.
- Catch2 test build updated to include `string_operation_strip.cpp` to ensure compilation and linking succeed.

### Notes

- No changes to analyzer behavior or cloc-style counting semantics.

---

## v0.5.0 - Analyzer Test Suite & Behavioral Stabilization

### Added

- Introduced Catch2-based test suite.
- Added invariant tests for analyzer core behavior:
  - Single-line comments
  - Inline comments counted as code
  - Multi-line comment blocks
  - Same-line multi-line comments with surrounding code
  - Unterminated multi-line comments at EOF
  - Blank line handling
  - Mixed-state scenarios

### Notes

- No changes to analyzer runtime behavior.
- The analyzer state machine is now formally verified and considered stable.
- Future updates will focus on infrastructure and usability rather than semantic counting changes.

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
