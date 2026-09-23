# Phase 10 — Workflow Foundation — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-10-workflow-foundation/`
- Primary prompt location: `.phases/phases/phase-10-workflow-foundation/prompts/`
- Prompt/specification Markdown files currently present: **25**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 25 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_10` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 10: Workflow Foundation
- Layout
- Prompt Index
- Agent Handoff — Phase 10
- Rebuntu --- Phase 10.15 --- Cancellation
- Agent Task
- Phase Mission
- Global Agent Contract
- Binding earlier phases
- Workflow is not Automation
- Workflow is not Operation
- Definition versus execution

## Structural skeleton / canonical destination
- Canonical skeleton: `src/automation/workflow-foundation/`
- Structural files: `src/automation/workflow-foundation/component.hpp`, `src/automation/workflow-foundation/component.cpp`, `src/automation/workflow-foundation/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/runtime/workflow.hpp`

### Existing test evidence
- `tests/native/test_workflow.cpp`

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
- Baseline ledger created automatically from the current repository. Depth **2/5** is deliberately conservative and not a completion claim.

- Structural skeleton materialized at `src/automation/workflow-foundation/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/automation/workflow-foundation/model/`
- `src/automation/workflow-foundation/contracts/`
- `src/automation/workflow-foundation/integration/`
- `src/automation/workflow-foundation/verification/`
- `src/automation/workflow-foundation/lifecycle/`
- `src/automation/workflow-foundation/state/`
- `src/automation/workflow-foundation/execution/`
- `src/automation/workflow-foundation/transactions/`
- `src/automation/workflow-foundation/events/`
- `src/automation/workflow-foundation/scheduling/`
- `src/automation/workflow-foundation/recovery/`
- `src/automation/workflow-foundation/principals/`
- `src/automation/workflow-foundation/groups/`
- `src/automation/workflow-foundation/roles/`
- `src/automation/workflow-foundation/resolution/`
- `src/automation/workflow-foundation/authorization/`
- `src/automation/workflow-foundation/credentials/`
- `src/automation/workflow-foundation/policy/`



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

### `10.0`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.0.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_67420e46/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_67420e46.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_67420e46.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_67420e46.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.1`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.1.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_8a4a2fae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_8a4a2fae.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_8a4a2fae.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_8a4a2fae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.10`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.10.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_5210bd88/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_5210bd88.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_5210bd88.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_5210bd88.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.11`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.11.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_f2b6dea0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_f2b6dea0.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_f2b6dea0.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_f2b6dea0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.12`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.12.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_445a7172/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_445a7172.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_445a7172.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_445a7172.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.13`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.13.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_e24c6858/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_e24c6858.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_e24c6858.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_e24c6858.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.14`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.14.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_0aa721f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_0aa721f9.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_0aa721f9.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_0aa721f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.15`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.15.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_9a51abfd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_9a51abfd.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_9a51abfd.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_9a51abfd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.16`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.16.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_ed2af8c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_ed2af8c1.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_ed2af8c1.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_ed2af8c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.17`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.17.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_89f7b740/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_89f7b740.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_89f7b740.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_89f7b740.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.18`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.18.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_2a043905/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_2a043905.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_2a043905.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_2a043905.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.2`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.2.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_ed169325/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_ed169325.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_ed169325.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_ed169325.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.3`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.3.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_94b9da59/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_94b9da59.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_94b9da59.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_94b9da59.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.4`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.4.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_58fa02c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_58fa02c2.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_58fa02c2.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_58fa02c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.5`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.5.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_5539d390/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_5539d390.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_5539d390.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_5539d390.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.6`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.6.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_a08b3f2d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_a08b3f2d.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_a08b3f2d.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_a08b3f2d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.7`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.7.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_5ef416a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_5ef416a1.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_5ef416a1.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_5ef416a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.8`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.8.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_981d5078/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_981d5078.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_981d5078.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_981d5078.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `10.9`
- **Source:** `.phases/phases/phase-10-workflow-foundation/prompts/10.9.md`
- **Structural package:** `src/automation/workflow-foundation/subtask_packages/verification/requirement_7acb23f1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/workflow-foundation/subtask_targets/requirements/requirement_7acb23f1.hpp`, `src/automation/workflow-foundation/subtask_targets/requirements/requirement_7acb23f1.cpp`
- **Structural test target:** `tests/structural-closure/automation/workflow-foundation/requirements/test_requirement_7acb23f1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

