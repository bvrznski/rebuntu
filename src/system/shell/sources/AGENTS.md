# Shell Sources — Agent Guidance

## Project Identity

This is `src/system/shell/sources/`: Rebuntu's Shell Source Library.

**THIS IS NOT:** A general-purpose implementation language, a Python rewrite facility,
a duplicate runtime, or a shell-based system controller.

---

## Core Principles

### 1. Search Before Adding

Before creating a new source file:

1. Inspect existing sources in `src/system/shell/sources/`
2. Check if a similar capability exists under another category
3. Consider whether the functionality belongs in C++ instead
4. Look for native Linux mechanisms that already provide this

**Do not recreate existing capabilities merely because the name differs.**

### 2. One Canonical Home

Every shell-native capability has one canonical home.

If a function could fit multiple categories:

1. Choose the **primary semantic domain**
2. Document cross-references in the file header
3. Use metadata for multi-axis discoverability (not duplicate files)

Physical duplication is not classification.

### 3. Bash vs Python Boundary

Shell Sources are appropriate when:

* The problem is naturally **shell-shaped**:
  * Pipeline operations
  * Shell-native transformations
  * Environment manipulation
  * Lightweight glue code

Python is required when:

* Complex parsing or structured state management
* Persistent state storage
* Orchestration across multiple components
* Non-trivial validation or policy enforcement

**Do not reimplement Python functionality in Bash merely because it exists.**

### 4. Sourceability Is Mandatory

Every source file must behave correctly when loaded with `source filename`:

```bash
# This must succeed without side effects:
source src/system/shell/sources/paths.sh

# It should NOT:
# - Execute operations
# - Print output
# - Change directory
# - Alter shell options globally
# - Exit the parent shell
```

Loading definitions and executing behavior are separate concerns.

### 5. Pipeline Semantics

Functions intended for pipelines must respect Unix conventions:

| Stream | Purpose |
|--------|---------|
| stdout | Primary data output (what gets piped) |
| stderr | Diagnostics, errors, progress messages |
| Exit status | Machine-readable success/failure |

Never mix decorative output with pipeline payload.

### 6. Safety First

Classify each function by side-effect profile:

* **PURE** — no mutation
* **READ_ONLY** — observation only
* **MUTATING** — changes state
* **PRIVILEGED** — needs elevated rights
* **DESTRUCTIVE** — hard to reverse

**Destructive functions require explicit review before migration.**

### 7. Namespace Discipline

All public functions must use the `rebuntu_` prefix:

```bash
# Correct
rebuntu_path_normalize() { ... }

# Incorrect (namespace pollution)
path_normalize() { ... }
```

Internal helpers may use `_rebuntu_internal_*` naming.

### 8. Do Not Duplicate Python

If a Python module exists with the required functionality, do not recreate it in Bash.

The exception is when shell-specific composition makes Bash more appropriate:

* Pipeline integration
* Shell-native transformations
* Lightweight wrappers around native commands

**"Because I can write it faster in Bash" is not sufficient justification.**

### 9. Native Linux Integration

Before implementing shell logic, check whether established native mechanisms exist:

| Requirement | Native Mechanism |
|-------------|------------------|
| Process management | systemd, /proc, signals |
| Filesystem events | inotify, fanotify |
| Network state | netlink, iproute2, nmcli |
| Service control | systemctl, D-Bus |
| Configuration | native config formats |

Using standard tools is acceptable. Building brittle pipelines around human-formatted
output when structured interfaces exist is not.

### 10. Verification Matters

For mutating functions:

* Exit status `0` proves only command execution success
**Not semantic success.**
* Explicit postcondition verification where required
* Evidence of result, not just invocation

---

## Category Placement Rules

### Paths Category

Contains: **Safe path manipulation**

| Belongs Here | Not Here |
|--------------|----------|
| Path normalization (`..`, `~`) | File content operations |
| Canonicalization | Path traversal logic |
| Symlink handling | Path validation (that's parsing) |
| Relative/absolute conversion | Path encoding/formatting |

### Text Category

Contains: **Shell-native text transformations**

| Belongs Here | Not Here |
|--------------|----------|
| Whitespace trimming | Complex parsing grammars |
| Line-based transforms | Structured data parsing |
| Case transformations | JSON/YAML processing |
| Simple string operations | AST manipulation |

### Flow Category

Contains: **Pipeline composition primitives**

| Belongs Here | Not Here |
|--------------|----------|
| `clip` (pipe to clipboard) | Workflow orchestration |
| Pipeline utilities | Task scheduling |
| Input buffering | Job management |

### Paths vs Text vs Parsing

* **paths/** — path strings as data, safe manipulation
* **text/** — text transformations, line operations
* **parsing/** — structured input → structured output

If it parses JSON, YAML, or complex syntax, use Python.

---

## Historical Code Review Checklist

Before migrating any historical source:

- [ ] Function semantics understood
- [ ] Input/output contract documented
- [ ] Side-effect profile classified (PURE/READ_ONLY/MUTATING/PRIVILEGED/DESTRUCTIVE)
- [ ] Dependencies identified and verified
- [ ] Edge cases considered (spaces in paths, empty input, etc.)
- [ ] Test strategy defined (where to run tests safely)
- [ ] Safety review completed for destructive functions

**If any item is `UNKNOWN`, defer migration until resolved.**

---

## Testing Requirements

Each source file must include tests that verify:

1. **Sourceability:** File loads without side effects
2. **Namespace isolation:** Only intended exports created
3. **Argument handling:** Valid inputs produce expected outputs
4. **Invalid input behavior:** Graceful failure for malformed input
5. **Path safety:** Spaces, special characters handled correctly
6. **Missing dependency behavior:** Clear error messages

For mutating operations, use temporary directories/contexts.

---

## Completion Checklist

A source file is complete when:

* [ ] Documentation header with purpose, inputs, outputs
* [ ] Function name follows `rebuntu_` convention
* [ ] Error handling for all expected failure modes
* [ ] Tests pass in isolation (no host-system mutation)
* [ ] Sourceability verified (loads cleanly)
* [ ] Namespace pollution checked
* [ ] Pipeline behavior documented
* [ ] Safety classification recorded

---

## What This Is Not

This library is **NOT**:

1. A replacement for C++ implementation
2. A duplicate runtime layer
3. An authentication/authorization system
4. A service lifecycle manager
5. A general-purpose programming language in Bash
6. A Python-to-Bash translator

If the question "Should this be in C++?" has a clear yes, it belongs there.

---

## Summary

| Do | Don't |
|----|-------|
| Source files that are side-effect-free at load time | Execute operations during sourcing |
| Use `rebuntu_` prefix for all public functions | Pollute global namespace |
| Document input/output contracts | Rely on undocumented behavior |
| Respect Unix pipeline semantics | Mix diagnostics with data output |
| Classify by safety profile | Migrate destructive code without review |
| Prefer native Linux mechanisms | Build brittle pipelines around human output |

---

## See Also

* `README.md` — Overview of Shell Source Library
* `AGENTS.md` (root) — Repository-wide guidance
* `ARCHITECTURE.md` — Structural taxonomy