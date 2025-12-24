# Pull Request

Thank you for contributing to **CPP-CLOC**! Please complete this form so we can review your pull request efficiently.

---

## PR Summary

_Provide a short, descriptive summary of the changes._

**Example:**  
Fix miscounting of code lines when multiline comments end mid-line

---

## What has changed?

_List the key changes made in this PR._

- Fixed analyzer handling of code after multiline comments
- Updated comment syntax logic for certain edge cases
- Added unit tests for edge cases in `tests/`

---

## Affected Areas

_(Check all that apply)_

- [ ] Core logic (`src/analyzer.cpp`, `src/comment_syntax.cpp`, etc.)
- [ ] Tests
- [ ] Configuration / CI
- [ ] Documentation
- [ ] Other: \***\*\_\_\*\***

---

## Related Issue

_Link to any related issues (if applicable)_

**Example:** Closes #12

---

## Testing Instructions

_How should we test this change?_

1. Run `cloc_cpp` on test files with multiline comments
2. Verify code, comment, and blank line counts match expected output
3. Check additional edge cases such as code before/after multiline comments

---

## Checklist

_(Check all that apply)_

- [ ] My code follows the project's style guidelines
- [ ] I have tested my changes locally
- [ ] I have added relevant tests
- [ ] I have updated related documentation
- [ ] This PR is ready for review
