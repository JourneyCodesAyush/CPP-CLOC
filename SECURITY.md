# 🔒 Security Policy

Even though **CPP-CLOC** is a local tool and only analyzes code, we encourage responsible reporting of any suspicious behavior, bugs that could be exploited, or potential security concerns.

> ⚠️ Note: CPP-CLOC only reads and counts code; it does **not execute** any of the analyzed files.

---

## 🛡️ Supported Versions

- The **main branch** is maintained.
- Security issues will be reviewed and fixed on a best-effort basis.

---

## 🐞 Reporting a Vulnerability

If you find any of the following:

- Unexpected crashes or segmentation faults
- Misbehavior with crafted input files
- Dependency-related security concerns

Please follow these steps:

### 1. **Do NOT create a public GitHub issue**

Report security concerns privately.

### 2. **Contact the maintainer directly**

Email: **[journeycodes.ayush@gmail.com](mailto:journeycodes.ayush@gmail.com)**

Include:

- Description of the issue
- Steps to reproduce
- Expected vs actual behavior
- Potential impact

### 3. **Await acknowledgment**

You will receive a response within **48–72 hours**.

---

## 🔍 What Happens Next?

- The report will be verified
- A fix will be created if needed
- A patched release may be published
- You may be credited (optional)

---

## 🧪 Security Best Practices for Contributors

- Avoid adding code that executes arbitrary files or commands
- Only run **CPP-CLOC** on files you trust
- Do not commit secrets or credentials
- Keep changes modular and reviewable

---

## ⚖️ About Dependencies

All included dependencies (`argparse.hpp`, there is only one so far) are distributed under their original licenses.  
Security concerns in dependencies should be reported along with any issues in the main code.

---

## 🙏 Thank You

Your diligence helps keep **CPP-CLOC** safe, fast, and reliable.
Responsible disclosure is greatly appreciated.
