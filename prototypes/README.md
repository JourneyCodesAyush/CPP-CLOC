# Prototypes

This folder contains **experimental implementations** of a CLOC (Count Lines of Code) utility in multiple languages.
These prototypes were created during the early design and exploration phase of the project.

## Purpose

- Explore different approaches for counting lines of code, comments, and blank lines.
- Compare implementations across languages (C, C++, Python).
- Test algorithms before writing the final C++ version with full features.

---

## Contents

### C

- **File:** `cloc.c`
- **Description:** Prototype using `FILE*` to read characters.
- **Features:**

  - Single-line comment detection (`//`)
  - Partial multi-line comment handling (`/* ... */`)
  - Line counting, blank line counting (experimental)

- **Status:** Partial / Prototype. Incomplete multi-line comment handling.

### Python

- **File:** `cloc_py.py`
- **Description:** Reference line-wise implementation.
- **Features:**

  - Line-wise reading of files
  - Detects single-line (`//`) and multi-line (`/* ... */`) comments
  - Counts blank lines
  - Outputs a formatted table with code, comments, blank lines, and total lines

- **Status:** Working / Reference implementation.

### C++

- **File:** `cloc_cpp.cpp`
- **Description:** Prototype in C++ using file streams (`ifstream`).
- **Features:**

  - Line-wise reading with whitespace stripping
  - Detects single-line and multi-line comments
  - Counts blank lines
  - Outputs a formatted table similar to the Python version

- **Status:** Working prototype; closely mirrors Python reference.

---

## Usage

Run any prototype from the command line, providing a source file as argument:

```bash
# C
# Create executable named cloc and execute
./cloc input_file.c # On Unix/Linux machines
.\cloc.ext input_file.c # On Windows

# Python
# Make sure atleast Python 3.10 is available
python cloc_py.py input_file.c

# C++
# Create executable named cloc_cpp and execute
./cloc_cpp input_file.c # On Unix/Linux machines
.\cloc_cpp input_file.c # On Windows
```

---

## Notes

- Some prototypes are incomplete or contain commented-out experimental code.
- These are **not used in the final build**; they exist for learning, reference, and experimentation.
- The prototypes may differ in style, readability, and completeness, their purpose is to test and compare approaches.
