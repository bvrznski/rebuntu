# Phases 40–45 and prompt/archive consolidation

## Implemented runtime

The C++20 runtime now contains a cross-phase implementation for:

- Phase 40 — unified federated search/provider registry, deterministic ranking/de-duplication and query scoping.
- Phase 41 — typed workflow definitions, dependency scheduling, retries and run-state tracking.
- Phase 42 — typed knowledge graph nodes/relations, evidence-bearing relations, neighborhood and bounded path traversal.
- Phase 43 — evidence-grounded operator diagnosis/recommendation objects with confidence and deterministic ranking.
- Phase 44 — protected-target adaptation proposals, explicit authorization, reversible application and rollback.
- Phase 45 — unified plan → validate → authorize → execute → verify/rollback control-plane lifecycle, operation journal and history.

The control plane federates the existing Phase 30–39 Linux domain discovery providers rather than creating a second source of system truth.

## ZIP audit

All prompt ZIP archives under `.phases` were inspected before removal. Existing canonical prompts were never overwritten. Missing numbered prompt specifications were imported where no phase-number collision existed. This recovered the previously absent Phase 24 Evergreen Platform series and additional extended Phase 5–8 specifications.

A native Phase 24 Evergreen Platform runtime boundary was added to `phases_20_30`: platform fingerprinting, dry-run upgrade plans, preflight, explicit authorization, rollback-contract requirements and post-change verification.

The detailed archive import log is in `docs/reports/ZIP_PROMPT_AUDIT.md`.

## Prompt organization

`.phases/PHASES` is now organized as one directory per major phase (`phase-00-*` through `phase-45-*`). Existing descriptive filenames were retained; imported prompts retain their original short descriptions. Phase 40–45 rich packages (README, manifest, architecture docs and prompts) were moved into the corresponding canonical phase directory.

Backup/rejected `.bak` material and all `.zip` prompt archives were removed after reconciliation. Legitimate specifications whose *subject* is rejection/obsolete-code handling were retained because they are active requirements, not rejected prompts.

## Verification

The new/changed Phase 20–30 and 40–45 C++ translation units and the Phase 40–45 integration test pass C++20 syntax/type checking. A complete CMake build was attempted; the repository compiles through the changed units, but the full all-target build exceeds the execution window in this environment due to the size of the pre-existing test/build graph. No compile error remains in the changed units.
