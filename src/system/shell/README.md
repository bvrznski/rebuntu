# src/system/shell — Shell Environment

## Purpose

`src/system/shell/` is Rebuntu's shell environment subsystem. It contains:

* **Shell Sources** (`sources/`) — reusable shell functions designed to be sourced
  into the shell environment for composition and pipeline usage
* **Scripts** (this directory) — standalone executable artifacts with explicit
  invocation boundaries

This directory establishes the architecture for scripts in Rebuntu.

---

## Script vs Shell Source

The fundamental distinction:

| Aspect | Shell Source | Script |
|--------|-------------|--------|
| **Primary use** | Sourced into shell environment (`source file`) | Executed as standalone process (`./file`) |
| **Purpose** | Reusable functions, composition primitives | Bounded executable work with result/exit semantics |
| **Execution model** | No process boundary; loads definitions into caller | Process-level invocation with entry point |
| **Side effects** | None during load (definitions only) | Explicit side effects as part of purpose |
| **Output streams** | Pipeline-friendly stdout/stderr separation | stdout = primary result, stderr = diagnostics/errors |

### When to use Shell Source

Use `sources/` when:

* Exposing reusable shell functions for composition
* Implementing pipeline utilities (`clip`, flow control)
* Shell-native transformations (text, path manipulation)
* Wrapping Linux commands with shell-specific enhancements
* The functionality is naturally shell-shaped (pipelines, redirections)

### When to use Script

Use `scripts/` when:

* A standalone executable artifact is needed
* An explicit entry point with bounded work is required
* Exit semantics and result reporting matter
* The behavior includes a clear start/end lifecycle
* It's not primarily intended for sourcing into other shell code

---

## Physical Structure

```
src/system/shell/
├── sources/         # Shell Source Library (reusable, sourced)
└── scripts/         # Standalone executable artifacts
```

### src/system/shell/scripts/

Contains runtime-managed Rebuntu script artifacts.

**Categories:**

| Category | Purpose |
|----------|---------|
| `administration/` | System administration operations |
| `configuration/`  | Configuration inspection/modification |
| `diagnostics/`    | Observation, inspection, non-mutating analysis |
| `maintenance/`    | Scheduled/cyclic maintenance tasks |
| `recovery/`       | Recovery and repair procedures |
| `setup/`          | Initial environment establishment |
| `support/`        | Support utilities for development/debugging |
| `verification/`   | Postcondition verification checks |

**Categories may be adjusted based on actual needs.**

---

## Script Contract

Every script should implement:

### Identity
* Clear purpose described in documentation/header
* Appropriate naming reflecting bounded action

### Invocation
* Explicit entry point (`main()` for Bash, `def main() -> int` for Python)
* Acceptable arguments documented
* Shebang line appropriate to interpreter

### Inputs/Outputs
* `stdin`: any piped input expected
* `stdout`: primary output/result (machine-readable where applicable)
* `stderr`: diagnostics, errors, progress messages
* Exit status: 0 = success, non-zero = failure

### Dependencies
* External commands required
* Shell environment assumptions

### Side Effects
* Mutations performed (file changes, system state)
* Privilege requirements
* Safety classification (PURE, READ_ONLY, MUTATING, PRIVILEGED, DESTRUCTIVE)

### Result Semantics
* Verification postconditions where applicable
* Evidence generation for audit/traceability

---

## Script Categories

### scripts/administration/

System administration operations:

* User/group management
* Service control
* Permission adjustments
* Policy enforcement

**Not for:** Long-running daemons (use systemd), scheduled tasks (use timers)

### scripts/configuration/

Configuration inspection and modification:

* Reading configuration files
* Modifying settings where native mechanisms allow it
* Validating configuration structure

**Not for:** Application state persistence

### scripts/diagnostics/

Observation and analysis without mutation:

* System state inspection
* Problem identification
* Evidence collection

**Not for:** Repair (use `recovery/`)

### scripts/maintenance/

Cyclic/scheduled maintenance tasks:

* Log rotation
* Cache pruning
* Index regeneration
* Schema migrations

**Key principle:** Bounded, idempotent where possible

### scripts/recovery/

Recovery and repair:

* Checkpoint creation before destructive changes
* Rollback procedures
* Quarentine of problematic state
* Verification after recovery actions

**Safety first:** Require explicit confirmation for destructive operations

### scripts/setup/

Initial environment establishment:

* Bootstrap minimal configuration
* Validate prerequisites
* Create initial artifacts

**Not for:** Ongoing maintenance (use `maintenance/`)

### scripts/support/

Support utilities:

* Debug output generation
* Environment information collection
* Development helper utilities

**Not for:** Production runtime operations

### scripts/verification/

Postcondition verification:

* Confirming operation success
* Validating system state after changes
* Evidence generation for audit

---

## Script Implementation Guidelines

### Bash Scripts

* Use `#!/usr/bin/env bash` shebang
* Follow strict mode: `set -euo pipefail`
* Implement clear entry point:
  ```bash
  main() {
      # argument parsing
      # execution logic
  }
  
  main "$@"
  ```
* Quote all variables: `"${var}"`
* Use temporary files safely with `mktemp`
* Exit with explicit codes for distinct failure modes

### Python Scripts

* Use appropriate shebang or rely on installed package entry point
* Implement `def main() -> int` pattern:
  ```python
  def main() -> int:
      # execution logic
      return 0
  
  if __name__ == "__main__":
      raise SystemExit(main())
  ```
* Follow project linting, formatting, typing rules
* Reusable logic should migrate to `src/rebuntu/` Python modules

---

## Script Safety Model

### Classification Categories

| Class | Description | Examples |
|-------|-------------|----------|
| PURE | No mutation, no side effects | Text transformations, inspections |
| READ_ONLY | Observation only | Status queries, diagnostics |
| MUTATING | State changes but reversible | File modifications, environment updates |
| PRIVILEGED | Requires elevated rights | System configuration, user management |
| DESTRUCTIVE | Irreversible or hard-to-reverse | `rm -rf`, format operations |

### Safety Requirements

* **Destructive scripts:** Require explicit confirmation
* **Privileged scripts:** Document required privileges clearly
* **Mutating scripts:** Support dry-run mode where appropriate
* **All scripts:** Preserve evidence of changes where audit matters

---

## Script vs Other Concepts

| Concept | Distinction |
|---------|-------------|
| **Shell Source** | Script = standalone execution; Shell Source = sourced for composition |
| **bin/ entry point** | Script = internal executable; bin/ = user-facing public command surface |
| **Operation** | Script = implementation artifact; Operation = semantic system capability |
| **Task/Job** | Script = how work is executed; Task/Job = what work is specified |
| **Workflow** | Script = bounded procedure; Workflow = orchestration across multiple steps |
| **Service/Daemon** | Script = bounded work with start/end; Service = persistent managed entity |

---

## Script Development Checklist

Before committing a script:

* [ ] Purpose clearly documented
* [ ] Entry point explicit and clear
* [ ] Arguments and options documented
* [ ] Output streams (stdout/stderr) properly separated
* [ ] Exit codes defined for failure modes
* [ ] Dependencies identified and checked where appropriate
* [ ] Safety classification recorded
* [ ] Dry-run support added where mutation is involved
* [ ] Tests written and passing
* [ ] No hardcoded paths assuming repository root
* [ ] No secrets in code or command-line arguments

---

## See Also

* `src/system/shell/sources/README.md` — Shell Source Library documentation
* `ARCHITECTURE.md` — Rebuntu structural taxonomy
* `VOCABULARY.md` — Semantic definitions
* `ONTOLOGY.md` — Concept relationships