# Scripts — Agent Guidance

## Project Identity

This is `src/system/shell/scripts/`: Rebuntu's Script Library.

**THIS IS NOT:** A replacement for C++ implementation, a duplicate runtime layer,
an authentication/authorization system, or a service lifecycle manager.

---

## Core Principles

### 1. Script vs Shell Source

* **Script** — standalone executable artifact with explicit entry point and bounded work
* **Shell Source** — reusable shell functions designed to be sourced for composition

Do not create both forms of the same functionality unless there's a genuine need for
both execution models.

### 2. Script vs bin Entry Point

* **Script** — internal executable, may or may not be user-facing
* **bin/** — user-facing public command surface, thin dispatchers to canonical Rebuntu

A script implementation should not be duplicated into bin/ merely for exposure.
Bin entry points are thin wrappers that parse and dispatch.

### 3. Script vs Operation

* **Script** — implementation artifact (how work is executed)
* **Operation** — semantic system capability (what can be done)

One operation may use a script; one script may invoke several operations.
Do not collapse operational ontology into executable-file organization.

### 4. Script vs Task/Job

* **Script** — the actual execution artifact
* **Task/Job** — specification of what work should be done

A job may execute a script, but they are conceptually distinct.

### 5. Script vs Workflow

* **Script** — bounded executable procedure with start/end
* **Workflow** — orchestration across multiple steps/phases

If a script implements phases, stages, branching, or parallel threads,
it should become a workflow using stable operations rather than being
implemented inside Bash.

### 6. Script vs Service/Daemon

* **Script** — bounded work with start and end
* **Service/Daemon** — persistent managed entity

A script that must run periodically does not become its own scheduler.
Use systemd timers, cron, or Rebuntu's scheduler instead of implementing
`while true; sleep 60` loops inside scripts.

### 7. Native Linux First

Before implementing script infrastructure, investigate native facilities:

| Concern | Native Mechanism |
|---------|------------------|
| Service lifecycle | systemd (D-Bus where appropriate) |
| Process observation | procfs / kernel interfaces |
| Resource control | cgroups v2 |
| Filesystem events | inotify / fanotify |
| Network state | netlink |
| Logging | journald |

A Script should perform bounded work.
Linux should provide Linux infrastructure.

### 8. No Blind Migration

Do not migrate historical scripts merely because they exist.
Each script must be:

* **Validated** — works correctly in current environment
* **Classified** — safety profile and ownership understood
* **Tested** — behavior matches expectations

Destructive or privileged scripts require additional review.

### 9. Safety Classification

Classify each script by side-effect profile:

| Class | Description |
|-------|-------------|
| PURE | No mutation, no side effects |
| READ_ONLY | Observation only |
| MUTATING | State changes but reversible |
| PRIVILEGED | Requires elevated rights |
| DESTRUCTIVE | Irreversible or hard-to-reverse |

Destructive scripts require explicit confirmation and should support dry-run mode.

### 10. Output Semantics

* **stdout** — primary output/result (pipeline payload where applicable)
* **stderr** — diagnostics, errors, progress messages
* Exit status — machine-readable success/failure (0 = success)

Do not mix decorative output with pipeline data.

---

## Script Categories

| Category | Purpose | Examples |
|----------|---------|----------|
| `administration/` | System administration operations | user/group management, permission adjustments |
| `configuration/`  | Configuration inspection/modification | reading config files, validating structure |
| `diagnostics/`    | Non-mutating analysis | system state inspection, problem identification |
| `maintenance/`    | Cyclic maintenance tasks | log rotation, cache pruning, index regeneration |
| `recovery/`       | Recovery and repair procedures | checkpoint, rollback, quarantine |
| `setup/`          | Initial environment establishment | bootstrap config, validate prerequisites |
| `support/`        | Development/debugging utilities | debug output, environment info collection |
| `verification/`   | Postcondition verification | confirm operation success, generate evidence |

Categories are hypotheses. Adjust based on actual needs.

---

## Script Contract Checklist

A script should have:

* [ ] Clear identity and purpose
* [ ] Explicit entry point (`main()` for Bash, `def main() -> int` for Python)
* [ ] Documented arguments and options
* [ ] Proper stdout/stderr separation
* [ ] Defined exit codes for failure modes
* [ ] Identified dependencies
* [ ] Safety classification recorded
* [ ] Evidence generation where audit matters

---

## Script Development Rules

1. **Search before creating** — check if existing script covers the need
2. **Classify before placing** — determine category and safety profile
3. **Document inputs/outputs** — specify expected arguments and result format
4. **Test safely** — use isolated temporary environments for destructive scripts
5. **Preserve evidence** — log changes where audit matters
6. **Support dry-run** — add `--dry-run` for scripts with significant mutation

---

## What This Is Not

Scripts are not:

1. A replacement for C++ implementation
2. A duplicate runtime layer
3. An authentication/authorization system
4. A service lifecycle manager (use systemd)
5. A scheduler (use systemd timers, cron)
6. A workflow engine (use proper workflow orchestration)

If the question "Should this be in C++?" has a clear yes, it belongs there.

---

## See Also

* `src/system/shell/README.md` — Shell environment overview
* `src/system/shell/sources/AGENTS.md` — Shell Source guidance
* `AGENTS.md` (root) — Repository-wide guidance
* `ARCHITECTURE.md` — Structural taxonomy
* `VOCABULARY.md` — Term definitions