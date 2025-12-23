# Contributing to CPP-CLOC

Thank you for your interest in contributing to **CPP-CLOC** - the minimal C++ implementation of [`CLOC`](https://github.com/AlDanial/cloc) for counting lines of code, comments, and blank lines.
Your contributions help keep code counting accurate, fast, and cross-platform. 😎

## 📑 Table of Contents

- [Contributing to CPP-CLOC](#contributing-to-cpp-cloc)
  - [📑 Table of Contents](#-table-of-contents)
  - [How to Contribute](#how-to-contribute)
    - [1. Understand the Project Structure](#1-understand-the-project-structure)
      - [Key Directories](#key-directories)
    - [2. Fork the Repository](#2-fork-the-repository)
    - [3. Clone Your Fork](#3-clone-your-fork)
    - [4. Create a New Branch](#4-create-a-new-branch)
    - [5. Make Your Changes](#5-make-your-changes)
    - [6. Commit Using Angular Format](#6-commit-using-angular-format)
    - [7. Push Your Branch](#7-push-your-branch)
    - [8. Open a Pull Request](#8-open-a-pull-request)
  - [Development Tips](#development-tips)
  - [Reporting Issues](#reporting-issues)
  - [Code of Conduct](#code-of-conduct)
  - [Thank You!](#thank-you)

---

## How to Contribute

### 1. Understand the Project Structure

```bash
cpp-cloc/
├── include/           # Header files
│   ├── argparse/               # Source files
│   │   └── argparse.hpp
│   │
│   ├── analyzer.hpp
│   ├── comment_syntax.hpp
│   ├── detector.hpp
│   ├── list_files.hpp
│   ├── middleware.hpp
│   ├── print.hpp
│   ├── stats.hpp
│   └── string_operation_strip.hpp
│
├── src/               # Source files
│   ├── analyzer.cpp
│   ├── detector.cpp
│   ├── list_files.cpp
│   ├── middleware.cpp
│   ├── print.cpp
│   └── main.cpp
│
│
├── Makefile           # Build configuration
├── README.md
└── LICENSE
```

#### Key Directories

- `include/` → Header files and definitions
- `src/` → Source files containing core logic (analyzer, detector, CLI)
- `Makefile` → Build configuration for Linux/macOS
- `README.md` → Project documentation

---

### 2. Fork the Repository

Click **Fork** on GitHub to create your own workspace.

---

### 3. Clone Your Fork

```bash
git clone https://github.com/journeycodesayush/cpp-cloc.git
cd cpp-cloc
```

---

### 4. Create a New Branch

```bash
git checkout -b feat/my-feature
```

Use descriptive names:
`feat/multi-language-support`, `fix/multiline-comment-detection`, `docs/readme-update`

---

### 5. Make Your Changes

You may:

- Add support for a new programming language
- Improve comment detection logic
- Optimize file scanning speed
- Add or improve unit tests
- Update documentation

Test quickly using:

```bash
make
./cloc_cpp <filename or folder>
```

---

### 6. Commit Using Angular Format

Commit messages must follow:

```text
<type>(<scope>): <short summary>
```

Allowed types:

| Type     | Meaning                               |
| -------- | ------------------------------------- |
| feat     | New feature                           |
| fix      | Bug fix                               |
| docs     | Documentation                         |
| style    | Formatting only                       |
| refactor | Code improvement without new behavior |
| test     | Tests added/updated                   |
| chore    | Maintenance tasks                     |
| build    | Build system changes                  |

_Suggested scopes_:

`analyzer`, `detector`, `middleware`, `print`, `list_files`, `comment-syntax`, `stats`, `docs`, `tests`, `build`, `argparse`, `prototypes`

Examples:

```text
feat(analyzer): add support for Python files
fix(detector): correct multi-line comment counting
docs: improve README examples
refactor(analyzer): simplify code line detection
```

Commit body (for non-doc commits):

- Minimum 20 characters
- Explain why the change was made
- Use present tense

---

### 7. Push Your Branch

```bash
git push origin feat/my-feature
```

---

### 8. Open a Pull Request

Include:

- What you changed
- Why you changed it
- Any example outputs if relevant

---

## Development Tips

- Keep code modular and readable
- Follow existing patterns in `analyzer.cpp` and `detector.cpp`
- Test new features on multiple file types and languages
- Commit in small, focused steps

---

## Reporting Issues

Found a bug or have a suggestion?

Open a GitHub Issue with:

- Clear description
- Steps to reproduce
- Relevant file or code snippet

---

## Code of Conduct

This project follows [CODE_OF_CONDUCT](CODE_OF_CONDUCT.md).
Please keep the community respectful and welcoming.

---

## Thank You!

Whether you fix a typo, improve detection logic, or add a new language, every contribution strengthens **CPP-CLOC**.
Made with ❤️ by JourneyCodesAyush
