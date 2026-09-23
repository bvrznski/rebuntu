# Script Index

This file documents Rebuntu's scripts, their categories, and purposes.

## Current Scripts

| Path | Category | Purpose | Language | Status |
|------|----------|---------|----------|--------|
| `scripts/bootstrap.sh` | setup | Create project directory skeleton | Bash | CURRENT |
| `scripts/generate_tree.sh` | maintenance | Regenerate __tree__.txt visualization | Bash | CURRENT |

## Script Classifications

### scripts/bootstrap.sh
* **Purpose:** Create project directory skeleton for Rebuntu repository structure
* **Safety Classification:** MUTATING (mkdir only, no deletions)
* **Privilege:** None required
* **Idempotent:** Yes (only creates new directories; reports existing as "exists")
* **Dry-run support:** Yes (`--dry-run` flag)
* **Execution model:** Standalone executable with explicit entry point

### scripts/generate_tree.sh
* **Purpose:** Regenerate __tree__.txt visualization of repository structure
* **Safety Classification:** MUTATING (writes only to __tree__.txt)
* **Privilege:** None required
* **Idempotent:** Yes (replaces file deterministically)
* **Dry-run support:** Not applicable (file output is the result)
* **Execution model:** Standalone executable with explicit entry point

## Future Script Categories

The following categories are reserved for future scripts as needed:

| Category | Reserved Purpose |
|----------|------------------|
| `scripts/administration/` | System administration operations |
| `scripts/configuration/`  | Configuration inspection/modification |
| `scripts/diagnostics/`    | Non-mutating analysis and diagnostics |
| `scripts/maintenance/`    | Cyclic maintenance tasks |
| `scripts/recovery/`       | Recovery and repair procedures |
| `scripts/setup/`          | Initial environment establishment |
| `scripts/support/`        | Support utilities for development/debugging |
| `scripts/verification/`   | Postcondition verification |

## Script vs Other Concepts

### Script vs Shell Source
* **Script** — standalone executable artifact with explicit entry point and bounded work
* **Shell Source** — reusable shell functions designed to be sourced (`source file`) for composition

See `src/system/shell/README.md` for detailed comparison.

### Script vs bin Entry Point
* **Script** — internal executable, may or may not be user-facing
* **bin/** — user-facing public command surface (thin dispatchers to canonical Rebuntu)

The `bin/rebuntu` entry point is a thin dispatcher that calls the C++ binary.
It does NOT contain business logic.

### Script vs Operation
* **Script** — implementation artifact (how work is executed)
* **Operation** — semantic system capability (what can be done)

One operation may use multiple scripts; one script may invoke several operations.

### Script vs Task/Job
* **Script** — the actual execution artifact
* **Task/Job** — specification of what work should be done

A job may execute a script, but they are conceptually distinct.

### Script vs Workflow
* **Script** — bounded executable procedure with start/end
* **Workflow** — orchestration across multiple steps/phases

If a script implements phases, stages, branching, or parallel threads,
it should become a workflow using stable operations.

### Script vs Service/Daemon
* **Script** — bounded work with start and end
* **Service/Daemon** — persistent managed entity

A script that must run periodically does not become its own scheduler.
Use systemd timers or cron instead of implementing loops inside scripts.

## Historical Scripts

No historical scripts have been migrated from the prior Rebuntu corpus.
The current script space is intentionally minimal to avoid blindly replicating
historical implementation decisions.

## Migration Policy

Before migrating a historical script:

1. **Discover** — locate the script and understand its purpose
2. **Classify** — determine safety profile (PURE/READ_ONLY/MUTATING/PRIVILEGED/DESTRUCTIVE)
3. **Validate** — verify functionality in current environment
4. **Adapt** — integrate with new category taxonomy
5. **Test** — confirm behavior matches expectations

Destructive scripts require additional safety review before migration.

## See Also

* `src/system/shell/README.md` — Script architecture overview
* `src/system/shell/scripts/AGENTS.md` — Script development guidance
* `src/system/shell/sources/SOURCES_INDEX.md` — Shell Source index