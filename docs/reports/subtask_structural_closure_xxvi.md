# XXVI — Subtask-Driven Structural Closure

This pass materializes explicit canonical implementation and test targets for every source prompt currently indexed by the Rebuntu phase system.

## Invariants
- Every prompt gets an implementation header, implementation source, structural test target, and machine-readable target manifest.
- Targets live under the phase's existing canonical runtime component, never under a runtime `phase_XX` tree.
- Role buckets are inferred conservatively (contracts, planning, execution, verification, recovery, security, integration, observability, resolution, lifecycle, persistence, requirements).
- These files are architectural reservations only. They confer **zero behavioral maturity credit**.
- Existing architecture is preserved. Later agents should implement/morph these slots in place and may bridge/migrate only with ledger evidence.
- Native Linux remains authoritative; a target slot never authorizes reimplementation of Linux mechanics.

## Verified census
- Source prompts mapped: **8,329**
- New target artifacts: **33,316** (4 per subtask)
- Missing target artifacts after validation: **0**
- Aggregate strict compile of all 8,329 generated target headers: **PASS** (`-std=c++20 -Wall -Wextra -Wpedantic -Werror`)
- Aggregate phase contracts: **107/107 PASS**
- Subtask ledger source mappings: **8,329/8,329 PASS**

Each aggregate `TASK.md` now names the implementation `.hpp`, `.cpp`, and structural test target for every subtask entry.
