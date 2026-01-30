# 📚✨ CPP-CLOC - C++ Implementation of CLOC

![C++](https://img.shields.io/badge/C%2B%2B-17-orange)
![License](https://img.shields.io/badge/license-MIT-green)
![PRs Welcome](https://img.shields.io/badge/PRs-welcome-lightgrey)

---

## 📑 Table of Contents

- [📚✨ CPP-CLOC - C++ Implementation of CLOC](#-cpp-cloc---c-implementation-of-cloc)
  - [📑 Table of Contents](#-table-of-contents)
  - [Current Version](#current-version)
  - [🌍 Overview](#-overview)
  - [⚡ Quick Install](#-quick-install)
    - [Linux / macOS](#linux--macos)
    - [Windows (via Command Prompt / PowerShell)](#windows-via-command-prompt--powershell)
  - [💻 Usage](#-usage)
  - [📝 Examples](#-examples)
    - [Directory Analysis](#directory-analysis)
    - [Single File Analysis](#single-file-analysis)
  - [⚙️ Features](#️-features)
  - [📦 Dependencies](#-dependencies)
  - [⚠️ Known Limitations](#️-known-limitations)
  - [🧭 Design Philosophy](#-design-philosophy)
  - [📁 Project Structure](#-project-structure)
  - [🧑‍💻 Development Guide](#-development-guide)
  - [🤝 Contributing](#-contributing)
  - [LICENSE](#license)
  - [📬 Author](#-author)

---

## Current Version

**v0.4.1** – Fixed incorrect file type classification for C/C++ headers and Markdown files. See [CHANGELOG](./CHANGELOG.md) for details.

---

## 🌍 Overview

**CPP-CLOC** is a minimal **C++ implementation of [`CLOC`](https://github.com/AlDanial/cloc)** (Count Lines of Code) for multiple programming languages:

- C, C++, C/C++ headers
- Java
- Python
- HTML, MarkDown, CSS
- JavaScript / TypeScript
- Bash / PowerShell / Batch
- Unknown (Not analyzed)

It provides **fast, cross-platform analysis** of code files, counting:

- Lines of code
- Comment lines
- Blank lines
- Total lines

> ⚡ Designed for speed and simplicity, written in modern C++.

---

## ⚡ Quick Install

> ⚠️ Requires **C++17** compatible compiler and includes `argparse.hpp` header

### Linux / macOS

```bash
git clone https://github.com/journeycodesayush/cpp-cloc.git
cd cpp-cloc
make
./cloc_cpp <filename>
```

### Windows (via Command Prompt / PowerShell)

```powershell
git clone https://github.com/journeycodesayush/cpp-cloc.git
cd cpp-cloc
mkdir build
.\cloc_cpp.exe <filename>
```

---

## 💻 Usage

Run **cpp-cloc** on a directory or single file:

```bash
cloc_cpp src/
```

Optional output format flags (mutually exclusive):

```bash
cloc_cpp src/ --json
cloc_cpp src/ --csv
cloc_cpp src/ --xml

# Scan a directory and save results to a file
cpp-cloc ./src --output=results.txt

# Select output format and save to a file
cpp-cloc ./src --json --output=results.json
```

> If no flag is provided, output is printed in the default table format.

Output includes:

- Number of files analyzed
- Total lines of code
- Total comment lines
- Total blank lines
- Total lines overall

**_Languages supported_**:

| Language   | Extension(s)       | Comment Style  |
| ---------- | ------------------ | -------------- |
| C/C++      | `.c`, `.cpp`, `.h` | `//`, `/* */`  |
| Java       | `.java`            | `//`, `/* */`  |
| Python     | `.py`              | `#`, `""" """` |
| HTML       | `.html`            | `<!-- -->`     |
| MarkDown   | `.md`              | `<!-- -->`     |
| CSS        | `.css`             | `/* */`        |
| JS/TS      | `.js`, `.ts`       | `//`, `/* */`  |
| Bash       | `.sh`              | `#`            |
| PowerShell | `.ps1`             | `#`            |
| Batch      | `.bat`             | `REM`          |

> [!NOTE]
> Only triple-double-quoted(""" """) strings are recognized for Python

---

## 📝 Examples

### Directory Analysis

```bash
./cpp_cloc ./src
```

Output example:

```
C++ implementation of CLOC
Total time: 0.091 seconds
------------------------------------------------------------------------------
Language               Files     Code    Comments        Blank          Total
------------------------------------------------------------------------------
C++                        6      372           6           45            423
------------------------------------------------------------------------------
SUM                        6      372           6           45            423
------------------------------------------------------------------------------
```

### Single File Analysis

```bash
./cpp_cloc ./src/main.cpp
```

---

## ⚙️ Features

- ✅ Supports **multiple programming languages**
- ✅ Counts code, comments, blank lines, and total lines
- ✅ Handles multi-line comments (/ ... /) and single-line comments
- ✅ Cross-platform (Windows, Linux, macOS)
- ✅ Lightweight and fast
- ⚠️ Minimal dependency: requires `argparse.hpp` (included in `include/argparse/`)

---

## 📦 Dependencies

**CPP-CLOC** includes the following external dependency:

| Library        | License | Notes                                                                                                                          |
| -------------- | ------- | ------------------------------------------------------------------------------------------------------------------------------ |
| `argparse.hpp` | MIT     | Header-only C++17 library for command-line argument parsing, included in `include/argparse/`. Original authors retain license. |

> ⚠️ All external code is included as-is and is subject to its original license. CPP-CLOC itself is MIT-licensed.

---

## ⚠️ Known Limitations

- Multi-line comments **inside strings are intentionally treated as comments**

```c
printf("/*");
for(size_t i = 0; i <= 5; i++){
    printf("%d ",i);
}
printf("*/");
```

is counted as **2 lines of code** and **3 lines of comment**

- comment markers inside strings are counted as **comments**
- Does not detect nested comment blocks by design
- Only triple-double-quoted (""" """) strings are treated as comments in Python; single-quote docstrings (''') are not recognized.

---

## 🧭 Design Philosophy

- CPP-CLOC follows **single-pass text-based analysis**; it does not fully parse languages.
- Some counting behaviors are **cloc-aligned quirks**, not bugs:
  - Lines with code + comments are counted as code.
  - Comment markers inside strings are treated as comments.
  - Embedded languages are not recognized.
  - Python docstrings are intentionally treated as comments.
- Contributions may extend supported languages, improve performance, or refactor code, provided analyzer behavior and cloc-style counting semantics remain unchanged.

> [!IMPORTANT]
> cpp-cloc intentionally does not distinguish comment markers inside strings, docstrings, or other language constructs, because doing so would require partial parsing and violate its strictly text-based analysis model.

> See [PHILOSOPHY.md](PHILOSOPHY.md) for a detailed guide.

---

## 📁 Project Structure

```bash
cpp-cloc/
├── include/           # Header files
├── src/               # Source files
│   ├── analyzer.cpp
│   ├── detector.cpp
│   ├── list_files.cpp
│   ├── middleware.cpp
│   ├── print.cpp
│   └── main.cpp
│
├── Makefile     # Build configuration
├── README.md
└── LICENSE
```

---

## 🧑‍💻 Development Guide

- **Analyzer**: `analyzer.cpp` contains core logic
- **Stats**: `stats.cpp` defines counting structures
- **String utilities**: trimming, stripping whitespace
- **Languages supported**: extend `comment_syntax.hpp` and update the `detector.cpp` and `middleware.cpp` to recognize the language

> Tip: Add new languages by defining `CommentSyntax` and following the above instruction.

---

## 🤝 Contributing

1. Fork the repo

```bash
git clone https://github.com/journeycodesayush/cpp-cloc.git
```

2. Create a branch: `feat/new-language` or `fix/bug`

```bash
git switch -c feat/new-language
```

3. Make changes & test locally
4. Open a PR with clear description

Follow **Angular Commit Message Convention**:

```text
feat(analyzer): add support for new language
fix(stats): correct blank line counting
docs(readme): update usage section
chore(build): update Makefile
refactor(analyzer): improve multiline comment detection
```

---

## LICENSE

```text
MIT License

Copyright (c) 2025 JourneyCodesAyush

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

---

## 📬 Author

Made with ❤️ by [JourneyCodesAyush](https://github.com/JourneyCodesAyush)
