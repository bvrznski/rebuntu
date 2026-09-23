# Phase 101 — Operational Attention Priority — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-101-operational-attention-priority/`
- Primary prompt location: `.phases/phases/phase-101-operational-attention-priority/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_101` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 101 — Operational Attention & Priority System
- Rebuntu — Phase 101.15: Crash restart reconciliation recovery
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
- Canonical skeleton: `src/operator/operational-attention-priority/`
- Structural files: `src/operator/operational-attention-priority/component.hpp`, `src/operator/operational-attention-priority/component.cpp`, `src/operator/operational-attention-priority/IMPLEMENTATION.json`
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

- Structural skeleton materialized at `src/operator/operational-attention-priority/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/operator/operational-attention-priority/model/`
- `src/operator/operational-attention-priority/contracts/`
- `src/operator/operational-attention-priority/integration/`
- `src/operator/operational-attention-priority/verification/`
- `src/operator/operational-attention-priority/lifecycle/`
- `src/operator/operational-attention-priority/state/`
- `src/operator/operational-attention-priority/execution/`
- `src/operator/operational-attention-priority/transactions/`
- `src/operator/operational-attention-priority/events/`
- `src/operator/operational-attention-priority/scheduling/`
- `src/operator/operational-attention-priority/recovery/`
- `src/operator/operational-attention-priority/principals/`
- `src/operator/operational-attention-priority/groups/`
- `src/operator/operational-attention-priority/roles/`
- `src/operator/operational-attention-priority/resolution/`
- `src/operator/operational-attention-priority/authorization/`
- `src/operator/operational-attention-priority/credentials/`
- `src/operator/operational-attention-priority/policy/`



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

### `101.0`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.0.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_b0a8b334/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b0a8b334.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b0a8b334.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_b0a8b334.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.1`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.1.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_b13492d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b13492d1.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b13492d1.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_b13492d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.10`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.10.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_30d4e52d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_30d4e52d.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_30d4e52d.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_30d4e52d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.11`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.11.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_87e6b1b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_87e6b1b0.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_87e6b1b0.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_87e6b1b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.12`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.12.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_b90ed5bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b90ed5bb.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b90ed5bb.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_b90ed5bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.13`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.13.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_09e2d0ac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_09e2d0ac.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_09e2d0ac.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_09e2d0ac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.14`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.14.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_2b35dbe7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_2b35dbe7.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_2b35dbe7.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_2b35dbe7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.15`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.15.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_3c8ba666/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_3c8ba666.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_3c8ba666.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_3c8ba666.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.16`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.16.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_169a2c9c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_169a2c9c.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_169a2c9c.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_169a2c9c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.17`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.17.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_575a090e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_575a090e.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_575a090e.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_575a090e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.18`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.18.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_471ffabf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_471ffabf.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_471ffabf.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_471ffabf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.19`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.19.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_e79d1a02/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_e79d1a02.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_e79d1a02.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_e79d1a02.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.2`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.2.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_b67e97d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b67e97d4.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_b67e97d4.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_b67e97d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.20`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.20.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_a61063e6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_a61063e6.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_a61063e6.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_a61063e6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.21`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.21.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_660f384b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_660f384b.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_660f384b.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_660f384b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.22`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.22.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_af15101e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_af15101e.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_af15101e.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_af15101e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.23`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.23.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_7c0ffd00/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_7c0ffd00.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_7c0ffd00.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_7c0ffd00.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.3`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.3.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_8c282dd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_8c282dd4.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_8c282dd4.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_8c282dd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.4`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.4.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_e464e8b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_e464e8b1.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_e464e8b1.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_e464e8b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.5`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.5.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_99483db4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_99483db4.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_99483db4.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_99483db4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.6`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.6.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_15851de7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_15851de7.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_15851de7.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_15851de7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.7`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.7.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_ffc88b16/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_ffc88b16.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_ffc88b16.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_ffc88b16.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.8`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.8.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_eff59cbe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_eff59cbe.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_eff59cbe.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_eff59cbe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `101.9`
- **Source:** `.phases/phases/phase-101-operational-attention-priority/prompts/101.9.md`
- **Structural package:** `src/operator/operational-attention-priority/subtask_packages/verification/requirement_973ab372/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_973ab372.hpp`, `src/operator/operational-attention-priority/subtask_targets/requirements/requirement_973ab372.cpp`
- **Structural test target:** `tests/structural-closure/operator/operational-attention-priority/requirements/test_requirement_973ab372.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

