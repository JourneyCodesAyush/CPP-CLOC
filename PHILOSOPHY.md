# CPP-CLOC Philosophy

CPP-CLOC is a **C++ reimplementation of of [`CLOC`](https://github.com/AlDanial/cloc)** (Count Lines of Code), designed for **simplicity, speed, and maintainability**. Its purpose is **not to perfectly parse code**, but to give results consistent with the style and behavior of cloc.

This document explains the guiding principles of CPP-CLOC and how contributors should think about issues, features, and bug reports.

---

## Table of Contents

- [CPP-CLOC Philosophy](#cpp-cloc-philosophy)
  - [Table of Contents](#table-of-contents)
  - [Core Goals](#core-goals)
  - [Known and Accepted Limitations](#known-and-accepted-limitations)
  - [How to Open Issues](#how-to-open-issues)
  - [Feature Requests](#feature-requests)
  - [Developer Guidance](#developer-guidance)

---

## Core Goals

- **Single-pass text-based analysis:**
  Analyze files line-by-line using simple rules; avoid half/full parsing of the language.

- **Consistency with cloc:**
  CPP-CLOC intentionally mirrors cloc’s quirks and counting rules.

- **Extensibility and clarity:**
  The codebase is organized for maintainable extensions, not semantic correctness.

- **Cross-platform C++17:**
  Designed to work on major OSes using standard C++17 features.

---

## Known and Accepted Limitations

CPP-CLOC follows **cloc’s behavior** closely. Some limitations are known and intentional:

- **Lines with both code and comments:**
  Counted as **code**, not comments.

- **Comment markers inside strings or here-documents:**
  Treated as comment markers, even if they appear inside string literals.

  ```c++
  printf(" /* ");
  for (i = 0; i < 100; i++) { a += i; }
  printf(" */ ");
  ```

  CPP-CLOC will count this as **two lines of code and three lines of comments**, consistent with cloc.

- **Embedded languages are not recognized:**
  For example, JavaScript inside HTML is counted entirely as HTML.

- **Python docstrings:**
  Treated as comments by default, even if they contain executable code. A separate switch to treat docstrings as code is **out of scope** for CPP-CLOC.

  > [!WARNING]
  > ⚠️ Only triple-double-quoted strings (""" """) are recognized as comments in Python; single-quote docstrings (''') are not.

- **Language definition files:**
  Must be plain ASCII text.

- **Compiler pragmas:**
  Lines like `#if ... #endif` are counted as code, even if they block compilation.

- **Path length limitations on Windows:**
  Very long file paths may fail; use WSL if needed.

- **Nested comments:**
  Regular expressions are used for comment detection, so **nested comments using the same markers** may not be counted perfectly.

- **Special XML cases:**
  XML comments inside CDATA blocks are counted as comments, not code.

> These are **intentional behaviors** to preserve cloc’s counting philosophy. Issues arising from these cases may be **closed as “by design”**. CPP-CLOC prioritizes **single-pass simplicity and cloc compatibility** over perfect parsing.

> [!IMPORTANT]
> cpp-cloc intentionally does not distinguish comment markers inside strings, docstrings, or other language constructs, because doing so would require partial parsing and violate its strictly text-based analysis model.

---

## How to Open Issues

**Before opening an issue:**

- Is it a **real bug**, or a cloc-aligned behavior?
- Does the feature request **extend analysis/output** without changing cloc rules?

If it is about a case where CPP-CLOC counts differently from what you _expect_, check the known limitations first. Issues that conflict with cloc’s philosophy may be **closed as “by design”**.

---

## Feature Requests

Features should:

- Support **new languages or comment syntaxes**.
- Improve **performance or usability**.
- Enhance **output formats** or **reporting**.

Features that attempt to **“correct” cloc behavior** or **fully parse code** are outside CPP-CLOC’s scope.

---

## Developer Guidance

- Follow the **single-pass analyzer philosophy**.
- Keep contributions consistent with **cloc-style limitations**.
- Maintain **clean separation of concerns** (detection, analysis, aggregation, printing).
- Avoid hacks aimed at semantic correctness; clarity and consistency matter more.

---

This document is a **reference for contributors and users** to understand the design philosophy, limitations, and expectations for CPP-CLOC.
