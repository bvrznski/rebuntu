# Phase 74 — System Experimentation Controlled Optimization — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-74-system-experimentation-controlled-optimization/`
- Primary prompt location: `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_74` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 74 — System Experimentation & Controlled Optimization System
- Rebuntu — Phase 74.2: Definitions and lifecycle
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
- Canonical skeleton: `src/domains/system-experimentation-controlled-optimization/`
- Structural files: `src/domains/system-experimentation-controlled-optimization/component.hpp`, `src/domains/system-experimentation-controlled-optimization/component.cpp`, `src/domains/system-experimentation-controlled-optimization/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** SKELETON
- **Implementation depth:** **1/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- No implementation evidence was matched automatically; inspect `src/` before concluding that the requirement is absent.

### Existing test evidence
- No phase-specific test evidence was matched automatically. Existing broader tests must still be inspected.

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

- Structural skeleton materialized at `src/domains/system-experimentation-controlled-optimization/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/system-experimentation-controlled-optimization/model/`
- `src/domains/system-experimentation-controlled-optimization/contracts/`
- `src/domains/system-experimentation-controlled-optimization/integration/`
- `src/domains/system-experimentation-controlled-optimization/verification/`
- `src/domains/system-experimentation-controlled-optimization/lifecycle/`
- `src/domains/system-experimentation-controlled-optimization/state/`
- `src/domains/system-experimentation-controlled-optimization/execution/`
- `src/domains/system-experimentation-controlled-optimization/transactions/`
- `src/domains/system-experimentation-controlled-optimization/events/`
- `src/domains/system-experimentation-controlled-optimization/scheduling/`
- `src/domains/system-experimentation-controlled-optimization/recovery/`
- `src/domains/system-experimentation-controlled-optimization/principals/`
- `src/domains/system-experimentation-controlled-optimization/groups/`
- `src/domains/system-experimentation-controlled-optimization/roles/`
- `src/domains/system-experimentation-controlled-optimization/resolution/`
- `src/domains/system-experimentation-controlled-optimization/authorization/`
- `src/domains/system-experimentation-controlled-optimization/credentials/`
- `src/domains/system-experimentation-controlled-optimization/policy/`



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

### `74.0`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.0.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_cff78e2a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_cff78e2a.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_cff78e2a.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_cff78e2a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.1`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.1.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_98afce51/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_98afce51.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_98afce51.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_98afce51.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.10`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.10.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_30b642c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_30b642c9.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_30b642c9.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_30b642c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.11`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.11.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_69c2085a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_69c2085a.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_69c2085a.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_69c2085a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.12`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.12.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_35c9bc83/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_35c9bc83.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_35c9bc83.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_35c9bc83.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.13`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.13.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_50da8a7d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_50da8a7d.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_50da8a7d.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_50da8a7d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.14`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.14.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_ce24a77a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_ce24a77a.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_ce24a77a.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_ce24a77a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.15`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.15.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_f918b913/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_f918b913.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_f918b913.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_f918b913.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.16`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.16.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_e1733131/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_e1733131.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_e1733131.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_e1733131.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.17`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.17.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_25a1c59f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_25a1c59f.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_25a1c59f.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_25a1c59f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.18`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.18.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_38001263/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_38001263.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_38001263.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_38001263.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.19`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.19.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_6c0b76f8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_6c0b76f8.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_6c0b76f8.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_6c0b76f8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.2`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.2.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_3ef7697a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_3ef7697a.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_3ef7697a.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_3ef7697a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.20`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.20.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_cb15cf33/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_cb15cf33.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_cb15cf33.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_cb15cf33.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.21`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.21.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_05905d99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_05905d99.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_05905d99.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_05905d99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.22`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.22.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_fdea5160/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_fdea5160.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_fdea5160.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_fdea5160.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.23`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.23.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_ba9bdd28/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_ba9bdd28.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_ba9bdd28.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_ba9bdd28.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.3`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.3.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_5d997ef7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_5d997ef7.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_5d997ef7.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_5d997ef7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.4`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.4.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_31f72beb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_31f72beb.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_31f72beb.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_31f72beb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.5`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.5.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_97b7c24b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_97b7c24b.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_97b7c24b.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_97b7c24b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.6`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.6.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_a7fd73c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_a7fd73c9.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_a7fd73c9.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_a7fd73c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.7`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.7.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_491f4882/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_491f4882.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_491f4882.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_491f4882.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.8`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.8.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_5e289e94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_5e289e94.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_5e289e94.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_5e289e94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `74.9`
- **Source:** `.phases/phases/phase-74-system-experimentation-controlled-optimization/prompts/74.9.md`
- **Structural package:** `src/domains/system-experimentation-controlled-optimization/subtask_packages/verification/requirement_c89804de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_c89804de.hpp`, `src/domains/system-experimentation-controlled-optimization/subtask_targets/requirements/requirement_c89804de.cpp`
- **Structural test target:** `tests/structural-closure/domains/system-experimentation-controlled-optimization/requirements/test_requirement_c89804de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

