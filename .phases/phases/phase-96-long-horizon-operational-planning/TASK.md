# Phase 96 — Long Horizon Operational Planning — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-96-long-horizon-operational-planning/`
- Primary prompt location: `.phases/phases/phase-96-long-horizon-operational-planning/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_96` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 96 — Long-Horizon Operational Planning System
- Rebuntu — Phase 96.6: Capability and affordance integration
- Mission
- Non-negotiable invariants
- Repository discovery
- DISCOVER
- RECONSTRUCT
- DESIGN
- IMPLEMENT
- INTEGRATE
- SECURE
- VERIFY

## Structural skeleton / canonical destination
- Canonical skeleton: `src/planning/long-horizon-operational-planning/`
- Structural files: `src/planning/long-horizon-operational-planning/component.hpp`, `src/planning/long-horizon-operational-planning/component.cpp`, `src/planning/long-horizon-operational-planning/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** SKELETON
- **Implementation depth:** **1/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- No implementation evidence was matched automatically; inspect `src/` before concluding that the requirement is absent.

### Existing test evidence
- `tests/native/test_install_planning.cpp`

## What is already implemented
- The paths above are candidate evidence of concrete implementation related to this phase.
- Treat an item as implemented only after confirming its behavior satisfies the corresponding prompt requirement.
- Shared infrastructure may satisfy parts of several phases; record that relationship rather than duplicating code.

## What remains to implement
- [ ] Read every source prompt and turn this section into a requirement-by-requirement gap list.
- [ ] Verify every candidate implementation path above against actual behavior and callers.
- [ ] Identify requirements represented only by contracts/skeletons/coverage registries and implement real behavior.
- [ ] Integrate phase semantics into the canonical architecture rather than phase-specific runtime directories.
- [ ] Identify and correct any Linux-mechanism duplication using aggregational morphing.
- [ ] Add missing verification, negative-path, recovery and integration tests required by the prompts.
- [ ] Remove/retire superseded mechanics only after callers have migrated and tests verify the new path.
- [ ] Recalculate implementation depth using `.phases/AGENTS.md`.

## Native Authority / architectural compliance
- Native Linux facilities remain authoritative for mechanics they own.
- Rebuntu code for this phase must justify itself through Rebuntu-specific semantics: composition, identity, evidence/provenance, desired state, policy/security, capability/affordance reasoning, planning, verification, reconciliation, recovery, automation or operator coordination.
- **Provider rule:** typed, narrow, observable; no shadow source of truth.
- **Current audit state:** requires phase-specific verification during the next implementation pass.

## Expected implementation destinations
Determine exact destinations from responsibility, not phase number. Typical canonical roots are:
`src/runtime/`, `src/semantics/`, `src/observation/`, `src/knowledge/`, `src/planning/`, `src/control/`, `src/security/`, `src/domains/`, `src/automation/`, `src/operator/`, `src/distributed/`, `src/portability/`, `src/providers/linux/`.

## Acceptance criteria
- [ ] All source prompts have been read and represented in the requirement checklist.
- [ ] Every applicable requirement has concrete implementation evidence.
- [ ] Cross-domain behavior is integrated through canonical contracts.
- [ ] Native Authority boundaries are respected.
- [ ] No parallel/duplicate subsystem was introduced merely for phase coverage.
- [ ] Relevant tests cover successful behavior and meaningful failure/verification/recovery paths.
- [ ] Build/test results are recorded from actual execution.
- [ ] Remaining gaps are explicit; nothing is marked complete merely because a type or file exists.
- [ ] Depth is 5/5 only after all criteria above are satisfied.

## Update log
- Baseline ledger created automatically from the current repository. Depth **0/5** is deliberately conservative and not a completion claim.

- Structural skeleton materialized at `src/planning/long-horizon-operational-planning/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/planning/long-horizon-operational-planning/model/`
- `src/planning/long-horizon-operational-planning/contracts/`
- `src/planning/long-horizon-operational-planning/integration/`
- `src/planning/long-horizon-operational-planning/verification/`
- `src/planning/long-horizon-operational-planning/lifecycle/`
- `src/planning/long-horizon-operational-planning/state/`
- `src/planning/long-horizon-operational-planning/execution/`
- `src/planning/long-horizon-operational-planning/transactions/`
- `src/planning/long-horizon-operational-planning/events/`
- `src/planning/long-horizon-operational-planning/scheduling/`
- `src/planning/long-horizon-operational-planning/recovery/`
- `src/planning/long-horizon-operational-planning/preflight/`
- `src/planning/long-horizon-operational-planning/planning/`
- `src/planning/long-horizon-operational-planning/staging/`
- `src/planning/long-horizon-operational-planning/ownership/`
- `src/planning/long-horizon-operational-planning/repair/`
- `src/planning/long-horizon-operational-planning/upgrade/`
- `src/planning/long-horizon-operational-planning/uninstall/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `96.0`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.0.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_74c52bb4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_74c52bb4.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_74c52bb4.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_74c52bb4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.1`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.1.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_1adcc05e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1adcc05e.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1adcc05e.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_1adcc05e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.10`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.10.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_97e1e0e9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_97e1e0e9.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_97e1e0e9.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_97e1e0e9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.11`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.11.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_24568d6d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_24568d6d.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_24568d6d.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_24568d6d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.12`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.12.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_c3152c49/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_c3152c49.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_c3152c49.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_c3152c49.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.13`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.13.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_3216a591/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_3216a591.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_3216a591.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_3216a591.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.14`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.14.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_1391f5d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1391f5d8.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1391f5d8.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_1391f5d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.15`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.15.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_977b03cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_977b03cf.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_977b03cf.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_977b03cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.16`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.16.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_9b33bba6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_9b33bba6.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_9b33bba6.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_9b33bba6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.17`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.17.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_668c8d8a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_668c8d8a.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_668c8d8a.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_668c8d8a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.18`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.18.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_91a4b957/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_91a4b957.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_91a4b957.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_91a4b957.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.19`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.19.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_1f9373c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1f9373c4.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1f9373c4.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_1f9373c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.2`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.2.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_c7e73ddc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_c7e73ddc.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_c7e73ddc.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_c7e73ddc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.20`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.20.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_f81410a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_f81410a7.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_f81410a7.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_f81410a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.21`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.21.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_57e40620/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_57e40620.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_57e40620.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_57e40620.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.22`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.22.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_1c1761b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1c1761b1.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_1c1761b1.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_1c1761b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.23`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.23.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_42c5c96c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_42c5c96c.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_42c5c96c.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_42c5c96c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.3`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.3.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_582a7be7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_582a7be7.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_582a7be7.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_582a7be7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.4`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.4.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_e431889e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_e431889e.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_e431889e.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_e431889e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.5`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.5.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_ad82507c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_ad82507c.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_ad82507c.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_ad82507c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.6`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.6.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_e7752ddc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_e7752ddc.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_e7752ddc.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_e7752ddc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.7`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.7.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_ece34408/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_ece34408.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_ece34408.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_ece34408.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.8`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.8.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_97474fa9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_97474fa9.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_97474fa9.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_97474fa9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `96.9`
- **Source:** `.phases/phases/phase-96-long-horizon-operational-planning/prompts/96.9.md`
- **Structural package:** `src/planning/long-horizon-operational-planning/subtask_packages/verification/requirement_5f95379a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_5f95379a.hpp`, `src/planning/long-horizon-operational-planning/subtask_targets/requirements/requirement_5f95379a.cpp`
- **Structural test target:** `tests/structural-closure/planning/long-horizon-operational-planning/requirements/test_requirement_5f95379a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

