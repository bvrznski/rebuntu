# src/system/shell/sources — Shell Source Library

## Purpose

The `src/system/shell/sources/` directory contains Rebuntu's **Shell Source Library**: a collection of reusable, semantically organized shell-native artifacts intended to be sourced into the Rebuntu shell environment.

This library exists at the boundary between:

* **Native shell operations** (pipelines, redirections, shell-native composition)
* **Rebuntu's deterministic C++ runtime** (canonical operations, verification, evidence)

It is NOT a general-purpose Rebuntu implementation language. It provides shell-specific
capabilities that are naturally expressed in shell but benefit from Rebuntu's discipline.

---

## What is a Shell Source?

A **Shell Source** is:

* A shell-native reusable implementation artifact (typically `.sh` or `.bash`)
* Intended to be sourced (`source file`) into the shell environment
* Designed for composition through pipelines and function calls

A Shell Source may provide:

| Category | Description |
|----------|-------------|
| Shell functions | Reusable operations expressed in shell |
| Composition primitives | Pipeline-friendly utilities (e.g., `clip`, flow control) |
| Environment integration | Shell-specific configuration access |
| Command wrappers | Linux commands enhanced with Rebuntu semantics |
| Shell-native transformations | Text, path, and data manipulation |

A Shell Source should NOT automatically contain:

* General Rebuntu business logic
* Python functionality rewritten in Bash
* Daemon implementations
* Service lifecycle management (owned by systemd)
* Large state-management frameworks

---

## Canonical Location

```
src/system/shell/sources/
├── administration/     # System administration helpers
├── configuration/      # Shell-native configuration access
├── construction/       # Command/source artifact construction
├── coordination/       # Task orchestration primitives
├── execution/          # Shell command invocation wrappers
├── filesystem/         # Filesystem operations
├── flow/               # Pipeline and flow control
├── information/        # Inspection and observation helpers
├── input/              # Input handling and prompts
├── output/             # Output formatting and presentation
├── parsing/            # Text and data parsing utilities
├── paths/              # Path manipulation (safe, robust)
├── processes/          # Process inspection/control wrappers
├── requests/           # Shell-native request primitives
├── security/           # Security-aware helpers
├── state/              # Shell state management
├── structures/         # Bash data structures
├── text/               # Text transformations
├── time/               # Time and duration helpers
└── verification/       # Postcondition verification
```

This is a **starting hypothesis**. Categories may be:
* **RETAIN** — useful semantic category
* **RENAME** — name imprecise, needs clarification
* **MERGE** — overlap with sibling categories
* **SPLIT** — too broad, requires subdivision
* **MOVE_TO_PYTHON** — better expressed in Python
* **REPLACE_WITH_NATIVE** — Linux already provides better mechanism

---

## Bash/Python Boundary

Shell Sources are appropriate when:

| Shell Sources | Python |
|---------------|--------|
| Shell environment manipulation | Complex parsing/state management |
| Pipelines and redirections | Persistent state |
| Shell-native composition (aliases, functions) | Orchestration |
| Lightweight invocation glue | Non-trivial validation |

**Rule:** If the problem is naturally shell-shaped (pipeline operations,
shell-native transformations), use Bash. If it requires structured state,
complex logic, or persistent data, move to Python.

---

## Sourceability Rules

A sourced file must behave correctly when loaded with `source filename`:

* **DO:** Define functions, variables, aliases
* **DO NOT:** Execute operations, mutate filesystem, start processes
* **DO NOT:** Print output during sourcing
* **DO NOT:** Change directory
* **DO NOT:** Alter shell options globally
* **DO NOT:** Exit the caller
* **DO NOT:** Install packages

Loading definitions and executing behavior are separate operations.

---

## Pipeline Semantics

Functions intended for pipelines must follow Unix conventions:

| Stream | Purpose |
|--------|---------|
| `stdout` | Primary data output (pipeline payload) |
| `stderr` | Diagnostics, errors, progress messages |
| Exit status | Machine-readable success/failure indication |

Avoid mixing decorative messages with pipeline data.

---

## Safety Classification

Source functions should be classified by their side-effect profile:

| Class | Description | Examples |
|-------|-------------|----------|
| PURE | Transform input without mutation | Text transformations |
| READ_ONLY | Observe system state | File existence checks, property queries |
| MUTATING | Change state | File modifications, environment changes |
| PRIVILEGED | Require elevated privilege | System configuration changes |
| DESTRUCTIVE | Irreversible or hard-to-reverse | `rm -rf`, format operations |

Destructive sources require additional review before migration from historical code.

---

## Namespace Conventions

All public shell functions use the `rebuntu_` prefix:

```bash
# Public API (exported)
rebuntu_path_normalize() { ... }
rebuntu_text_trim() { ... }

# Internal helpers (not exported)
_rebuntu_internal_helper() { ... }
```

This prevents:
* Shell built-in shadowing
* Collision with PATH executables
* Namespace pollution after sourcing

---

## Input/Output Contracts

For reusable functions, document:

| Aspect | Expected behavior |
|--------|-------------------|
| Arguments | Positional and named parameters |
| stdin | Accepts piped input? Expected format |
| stdout | Primary data output format |
| stderr | Diagnostics format |
| Exit status | Success (0) vs failure (>0) semantics |

Example:
```bash
rebuntu_path_normalize() {
    # INPUT:  Path string (may contain ~, .., symlinks)
    # OUTPUT: Canonical path to stdout
    # STDERR: Error messages on failure
    # EXIT:   0 on success, non-zero on error
}
```

---

## Loading Mechanism

Categories are loaded independently:

```bash
# Load specific category
source /path/to/sources/paths.sh

# Or source individual functions
source /path/to/sources/paths/normalize.sh
```

Loading should be idempotent where possible (detect redefinition).

---

## Testing Strategy

Each source file should include tests for:

* Sourceability (no unexpected side effects when sourced)
* Namespace collisions (function names not already used)
| Expected exports (only intended functions exported)
| Argument handling (valid and invalid inputs)
| Exit codes (success and failure paths)

For mutating functions, use isolated temporary environments.

---

## Historical Migration Policy

Historical Rebuntu contained extensive shell sources. Before migrating:

1. **Discover** — locate historical implementation
2. **Classify** — determine safety profile and ownership
3. **Validate** — verify functionality in current environment
4. **Adapt** — integrate with modern category taxonomy
5. **Test** — confirm behavior matches expectations

**Never blindly migrate destructive code.** Review each destructive function individually.

---

## Completion Criteria (Phase 0.3)

Phase 0.3 is complete when:

* `src/system/shell/sources/` has a clearly defined purpose
* Category taxonomy is documented with semantic boundaries
* Bash/Python responsibility boundary is established
* Public/internal API convention is established (`rebuntu_` prefix)
* Sourceability rules are documented and enforced
* Pipeline stdin/stdout/stderr conventions are specified
* Safety classification framework exists
* Destructive historical sources identified (not blindly migrated)
* Representative safe sources migrated to validate architecture

---

## See Also

* `src/system/shell/README.md` — Shell environment overview
* `ARCHITECTURE.md` — Rebuntu structural taxonomy
* `VOCABULARY.md` — Semantic definitions
* `ONTOLOGY.md` — Concept relationships