# Phase 06 — Native Command Operation Execution — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-06-native-command-operation-execution/`
- Primary prompt location: `.phases/phases/phase-06-native-command-operation-execution/prompts/`
- Prompt/specification Markdown files currently present: **86**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 86 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_06` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 6: Native Command Operation Execution
- Layout
- Prompt Index
- Agent Handoff — Phase 6
- Rebuntu — Phase 6
- C++-Native Command, Operation & Execution System
- TASK 6.66 — Historical action architecture archaeology
- TASK 6.48 — IPC command boundary
- Rebuntu — Phase 6.14 — Command Collision Protection
- Agent Task
- Phase Mission
- 1. Global Agent Contract

## Structural skeleton / canonical destination
- Canonical skeleton: `src/runtime/native-command-operation-execution/`
- Structural files: `src/runtime/native-command-operation-execution/component.hpp`, `src/runtime/native-command-operation-execution/component.cpp`, `src/runtime/native-command-operation-execution/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/runtime/execution/README.md`
- `src/runtime/execution/contract.hpp`
- `src/system/shell/sources/execution/_init.sh`
- `src/system/shell/sources/execution/test_exec.sh`

### Existing test evidence
- `tests/native/test_operations.cpp`

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
- Baseline ledger created automatically from the current repository. Depth **3/5** is deliberately conservative and not a completion claim.

- Structural skeleton materialized at `src/runtime/native-command-operation-execution/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/runtime/native-command-operation-execution/model/`
- `src/runtime/native-command-operation-execution/contracts/`
- `src/runtime/native-command-operation-execution/integration/`
- `src/runtime/native-command-operation-execution/verification/`
- `src/runtime/native-command-operation-execution/lifecycle/`
- `src/runtime/native-command-operation-execution/state/`
- `src/runtime/native-command-operation-execution/execution/`
- `src/runtime/native-command-operation-execution/transactions/`
- `src/runtime/native-command-operation-execution/events/`
- `src/runtime/native-command-operation-execution/scheduling/`
- `src/runtime/native-command-operation-execution/recovery/`
- `src/runtime/native-command-operation-execution/principals/`
- `src/runtime/native-command-operation-execution/groups/`
- `src/runtime/native-command-operation-execution/roles/`
- `src/runtime/native-command-operation-execution/resolution/`
- `src/runtime/native-command-operation-execution/authorization/`
- `src/runtime/native-command-operation-execution/credentials/`
- `src/runtime/native-command-operation-execution/policy/`



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

### `6.0`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.0.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_cf46d6f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_cf46d6f2.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_cf46d6f2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_cf46d6f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.10`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.10.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_87b46bd1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_87b46bd1.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_87b46bd1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_87b46bd1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.11`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.11.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_21a79ccf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_21a79ccf.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_21a79ccf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_21a79ccf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.12`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.12.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_5fe4c982/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_5fe4c982.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_5fe4c982.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_5fe4c982.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.13`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.13.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_912e621f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_912e621f.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_912e621f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_912e621f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.14`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.14.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_d7592a6a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_d7592a6a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_d7592a6a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_d7592a6a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.15`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.15.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_71c99a2c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_71c99a2c.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_71c99a2c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_71c99a2c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.16`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.16.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_00d3a4b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_00d3a4b2.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_00d3a4b2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_00d3a4b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.17`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.17.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_72d808f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_72d808f4.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_72d808f4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_72d808f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.18`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.18.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_1cbc6777/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_1cbc6777.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_1cbc6777.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_1cbc6777.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.19_output_capture_semantics`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.19_output_capture_semantics.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/output_capture_semantics_b35c42ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/output_capture_semantics_b35c42ba.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/output_capture_semantics_b35c42ba.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_output_capture_semantics_b35c42ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.1_typed_command_model`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.1_typed_command_model.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/typed_command_model_05e208a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/typed_command_model_05e208a7.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/typed_command_model_05e208a7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_typed_command_model_05e208a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.2`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.2.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_813c43f6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_813c43f6.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_813c43f6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_813c43f6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.20_exit_and_signal_result_semantics`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.20_exit_and_signal_result_semantics.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/exit_and_signal_result_semantics_ca7881ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/exit_and_signal_result_semantics_ca7881ca.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/exit_and_signal_result_semantics_ca7881ca.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_exit_and_signal_result_semantics_ca7881ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.21_execution_verification_integration`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.21_execution_verification_integration.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/execution_verification_integration_5e816420/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/execution_verification_integration_5e816420.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/execution_verification_integration_5e816420.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_execution_verification_integration_5e816420.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.22_verification_freshness`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.22_verification_freshness.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/verification_freshness_a8c976e6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/verification_freshness_a8c976e6.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/verification_freshness_a8c976e6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_verification_freshness_a8c976e6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.23_idempotency_classification`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.23_idempotency_classification.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/idempotency_classification_e20160e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/idempotency_classification_e20160e5.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/idempotency_classification_e20160e5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_idempotency_classification_e20160e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.24_retry_mechanics_integration`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.24_retry_mechanics_integration.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/retry_mechanics_integration_6ab2bcd2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/integration/retry_mechanics_integration_6ab2bcd2.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/integration/retry_mechanics_integration_6ab2bcd2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/integration/test_retry_mechanics_integration_6ab2bcd2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.25_partial_execution_semantics`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.25_partial_execution_semantics.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/partial_execution_semantics_aeb00e5c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/partial_execution_semantics_aeb00e5c.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/partial_execution_semantics_aeb00e5c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_partial_execution_semantics_aeb00e5c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.26_compensation_semantics`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.26_compensation_semantics.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/compensation_semantics_fe836f7a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/recovery/compensation_semantics_fe836f7a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/recovery/compensation_semantics_fe836f7a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/recovery/test_compensation_semantics_fe836f7a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.27_dry-run_semantics`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.27_dry-run_semantics.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/dry_run_semantics_881d8926/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/dry_run_semantics_881d8926.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/dry_run_semantics_881d8926.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_dry_run_semantics_881d8926.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.28_explain-plan_output`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.28_explain-plan_output.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/explain_plan_output_1fe3dc02/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/observability/explain_plan_output_1fe3dc02.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/observability/explain_plan_output_1fe3dc02.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/observability/test_explain_plan_output_1fe3dc02.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.29_operation_cancellation`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.29_operation_cancellation.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/operation_cancellation_81578c2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/operation_cancellation_81578c2e.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/operation_cancellation_81578c2e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_operation_cancellation_81578c2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.3`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.3.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_ed98ea1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_ed98ea1a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_ed98ea1a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_ed98ea1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.30_operation_deadlines`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.30_operation_deadlines.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/operation_deadlines_68b46adc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/operation_deadlines_68b46adc.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/operation_deadlines_68b46adc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_operation_deadlines_68b46adc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.31_execution_concurrency_control`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.31_execution_concurrency_control.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/execution_concurrency_control_f246909d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/execution_concurrency_control_f246909d.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/execution_concurrency_control_f246909d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_execution_concurrency_control_f246909d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.32_cross-operation_conflict_detection`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.32_cross-operation_conflict_detection.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/cross_operation_conflict_detection_b2dd627a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/cross_operation_conflict_detection_b2dd627a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/cross_operation_conflict_detection_b2dd627a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_cross_operation_conflict_detection_b2dd627a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.33_operation_resource_declarations`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.33_operation_resource_declarations.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/operation_resource_declarations_2faf3646/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/operation_resource_declarations_2faf3646.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/operation_resource_declarations_2faf3646.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_operation_resource_declarations_2faf3646.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.34_privilege_requirement_metadata`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.34_privilege_requirement_metadata.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/privilege_requirement_metadata_1cf555d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/security/privilege_requirement_metadata_1cf555d4.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/security/privilege_requirement_metadata_1cf555d4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/security/test_privilege_requirement_metadata_1cf555d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.35_privileged_helper_invocation`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.35_privileged_helper_invocation.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/privileged_helper_invocation_e36fa4f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/security/privileged_helper_invocation_e36fa4f7.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/security/privileged_helper_invocation_e36fa4f7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/security/test_privileged_helper_invocation_e36fa4f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.36_privilege_minimization`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.36_privilege_minimization.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/privilege_minimization_b0778c3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/security/privilege_minimization_b0778c3a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/security/privilege_minimization_b0778c3a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/security/test_privilege_minimization_b0778c3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.37_operation_evidence_bundle`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.37_operation_evidence_bundle.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/operation_evidence_bundle_41581cb6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/operation_evidence_bundle_41581cb6.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/operation_evidence_bundle_41581cb6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_operation_evidence_bundle_41581cb6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.38_execution_journald_diagnostics`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.38_execution_journald_diagnostics.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/execution_journald_diagnostics_8e9fdc7a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/observability/execution_journald_diagnostics_8e9fdc7a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/observability/execution_journald_diagnostics_8e9fdc7a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/observability/test_execution_journald_diagnostics_8e9fdc7a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.39_execution_record_persistence`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.39_execution_record_persistence.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/execution_record_persistence_4457c1b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/execution_record_persistence_4457c1b0.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/execution_record_persistence_4457c1b0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_execution_record_persistence_4457c1b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.4`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.4.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_948cc852/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_948cc852.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_948cc852.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_948cc852.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.40_crash_reconciliation_integration`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.40_crash_reconciliation_integration.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/crash_reconciliation_integration_87252fbc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/recovery/crash_reconciliation_integration_87252fbc.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/recovery/crash_reconciliation_integration_87252fbc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/recovery/test_crash_reconciliation_integration_87252fbc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.41_command_replay_semantics`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.41_command_replay_semantics.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/command_replay_semantics_a3dbc708/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/command_replay_semantics_a3dbc708.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/command_replay_semantics_a3dbc708.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_command_replay_semantics_a3dbc708.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.42_batch_command_boundary`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.42_batch_command_boundary.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/batch_command_boundary_8c45f864/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/batch_command_boundary_8c45f864.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/batch_command_boundary_8c45f864.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_batch_command_boundary_8c45f864.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.43_sequential_composition`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.43_sequential_composition.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/sequential_composition_55b5f59f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/sequential_composition_55b5f59f.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/sequential_composition_55b5f59f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_sequential_composition_55b5f59f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.44_parallel_composition`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.44_parallel_composition.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/parallel_composition_17b8db31/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/parallel_composition_17b8db31.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/parallel_composition_17b8db31.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_parallel_composition_17b8db31.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.45_dependency-aware_execution`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.45_dependency-aware_execution.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/dependency_aware_execution_be3c845c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/dependency_aware_execution_be3c845c.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/dependency_aware_execution_be3c845c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_dependency_aware_execution_be3c845c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.46_command_parser_boundary`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.46_command_parser_boundary.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/command_parser_boundary_8c83dbb4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/command_parser_boundary_8c83dbb4.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/command_parser_boundary_8c83dbb4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_command_parser_boundary_8c83dbb4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.47_machine-readable_command_boundary`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.47_machine-readable_command_boundary.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/machine_readable_command_boundary_276a1a10/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/machine_readable_command_boundary_276a1a10.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/machine_readable_command_boundary_276a1a10.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_machine_readable_command_boundary_276a1a10.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.48_ipc_command_boundary`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.48_ipc_command_boundary.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/ipc_command_boundary_21e2c371/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/ipc_command_boundary_21e2c371.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/ipc_command_boundary_21e2c371.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_ipc_command_boundary_21e2c371.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.49_data-to-control_gate_enforcement`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.49_data-to-control_gate_enforcement.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/data_to_control_gate_enforcement_e1682918/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/data_to_control_gate_enforcement_e1682918.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/data_to_control_gate_enforcement_e1682918.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_data_to_control_gate_enforcement_e1682918.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.5`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.5.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_720db305/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_720db305.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_720db305.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_720db305.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.50_semantic_candidate_boundary`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.50_semantic_candidate_boundary.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/semantic_candidate_boundary_a10f4a50/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/semantic_candidate_boundary_a10f4a50.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/semantic_candidate_boundary_a10f4a50.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_semantic_candidate_boundary_a10f4a50.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.51_semantic_service_absence_behavior`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.51_semantic_service_absence_behavior.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/semantic_service_absence_behavior_e468998c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/semantic_service_absence_behavior_e468998c.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/semantic_service_absence_behavior_e468998c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_semantic_service_absence_behavior_e468998c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.52_provider_result_distrust`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.52_provider_result_distrust.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/provider_result_distrust_2331e76e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/security/provider_result_distrust_2331e76e.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/security/provider_result_distrust_2331e76e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/security/test_provider_result_distrust_2331e76e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.53_context_authority_audit`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.53_context_authority_audit.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/context_authority_audit_df689edb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/context_authority_audit_df689edb.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/context_authority_audit_df689edb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_context_authority_audit_df689edb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.54_stale-plan_adversarial_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.54_stale-plan_adversarial_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/stale_plan_adversarial_tests_23e8eb12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/stale_plan_adversarial_tests_23e8eb12.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/stale_plan_adversarial_tests_23e8eb12.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_stale_plan_adversarial_tests_23e8eb12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.55_ambiguous-target_adversarial_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.55_ambiguous-target_adversarial_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/ambiguous_target_adversarial_tests_ea8c896e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/ambiguous_target_adversarial_tests_ea8c896e.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/ambiguous_target_adversarial_tests_ea8c896e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_ambiguous_target_adversarial_tests_ea8c896e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.56_pid_reuse_and_transient_identity_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.56_pid_reuse_and_transient_identity_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/pid_reuse_and_transient_identity_tests_1d84faf0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/pid_reuse_and_transient_identity_tests_1d84faf0.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/pid_reuse_and_transient_identity_tests_1d84faf0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_pid_reuse_and_transient_identity_tests_1d84faf0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.57_device_reorder_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.57_device_reorder_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/device_reorder_tests_0fa795c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/device_reorder_tests_0fa795c3.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/device_reorder_tests_0fa795c3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_device_reorder_tests_0fa795c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.58_command_injection_adversarial_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.58_command_injection_adversarial_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/command_injection_adversarial_tests_f2b03e4a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/command_injection_adversarial_tests_f2b03e4a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/command_injection_adversarial_tests_f2b03e4a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_command_injection_adversarial_tests_f2b03e4a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.59_path_safety_audit`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.59_path_safety_audit.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/path_safety_audit_1ed0801e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/path_safety_audit_1ed0801e.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/path_safety_audit_1ed0801e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_path_safety_audit_1ed0801e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.6`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.6.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_624f70de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_624f70de.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_624f70de.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_624f70de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.60_malformed_provider_output_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.60_malformed_provider_output_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/malformed_provider_output_tests_f14078eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/malformed_provider_output_tests_f14078eb.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/malformed_provider_output_tests_f14078eb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_malformed_provider_output_tests_f14078eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.61_execution_storm_and_backpressure_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.61_execution_storm_and_backpressure_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/execution_storm_and_backpressure_tests_fba28ef6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/execution_storm_and_backpressure_tests_fba28ef6.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/execution_storm_and_backpressure_tests_fba28ef6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_execution_storm_and_backpressure_tests_fba28ef6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.62_cancellation_race_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.62_cancellation_race_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/cancellation_race_tests_cec0eb28/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/cancellation_race_tests_cec0eb28.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/cancellation_race_tests_cec0eb28.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_cancellation_race_tests_cec0eb28.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.63_timeout_ambiguity_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.63_timeout_ambiguity_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/timeout_ambiguity_tests_ed8aba43/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/timeout_ambiguity_tests_ed8aba43.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/timeout_ambiguity_tests_ed8aba43.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_timeout_ambiguity_tests_ed8aba43.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.64_privilege_escalation_adversarial_tests`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.64_privilege_escalation_adversarial_tests.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/privilege_escalation_adversarial_tests_55b86667/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/privilege_escalation_adversarial_tests_55b86667.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/privilege_escalation_adversarial_tests_55b86667.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_privilege_escalation_adversarial_tests_55b86667.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.65_python_execution-path_eradication`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.65_python_execution-path_eradication.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/python_execution_path_eradication_f87458fa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/python_execution_path_eradication_f87458fa.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/python_execution_path_eradication_f87458fa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_python_execution_path_eradication_f87458fa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.66_historical_action_architecture_archaeology`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.66_historical_action_architecture_archaeology.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/historical_action_architecture_archaeology_7321997e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/observability/historical_action_architecture_archaeology_7321997e.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/observability/historical_action_architecture_archaeology_7321997e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/observability/test_historical_action_architecture_archaeology_7321997e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.67_duplicate_executor_audit`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.67_duplicate_executor_audit.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/duplicate_executor_audit_187a56d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/duplicate_executor_audit_187a56d6.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/duplicate_executor_audit_187a56d6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_duplicate_executor_audit_187a56d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.68_native_provider_coverage_audit`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.68_native_provider_coverage_audit.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/native_provider_coverage_audit_df121734/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/native_provider_coverage_audit_df121734.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/native_provider_coverage_audit_df121734.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_native_provider_coverage_audit_df121734.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.69_cli_execution_vertical_slice`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.69_cli_execution_vertical_slice.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/cli_execution_vertical_slice_63e37b40/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/execution/cli_execution_vertical_slice_63e37b40.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/execution/cli_execution_vertical_slice_63e37b40.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/execution/test_cli_execution_vertical_slice_63e37b40.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.7`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.7.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_d2ac4ac4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_d2ac4ac4.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_d2ac4ac4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_d2ac4ac4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.70_contained_mutation_integration_test`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.70_contained_mutation_integration_test.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/contained_mutation_integration_test_e7764990/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/contained_mutation_integration_test_e7764990.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/contained_mutation_integration_test_e7764990.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_contained_mutation_integration_test_e7764990.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.71_read-only_command_integration_test`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.71_read-only_command_integration_test.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/read_only_command_integration_test_ab4111d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/read_only_command_integration_test_ab4111d5.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/read_only_command_integration_test_ab4111d5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_read_only_command_integration_test_ab4111d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.72_restart_integration_test`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.72_restart_integration_test.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/restart_integration_test_4b03b115/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/restart_integration_test_4b03b115.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/restart_integration_test_4b03b115.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_restart_integration_test_4b03b115.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.73_build_and_runtime_reachability_audit`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.73_build_and_runtime_reachability_audit.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/build_and_runtime_reachability_audit_d17fbb19/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/build_and_runtime_reachability_audit_d17fbb19.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/build_and_runtime_reachability_audit_d17fbb19.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_build_and_runtime_reachability_audit_d17fbb19.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.74_sanitizer_and_static-analysis_pass`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.74_sanitizer_and_static-analysis_pass.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/sanitizer_and_static_analysis_pass_64c78173/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/sanitizer_and_static_analysis_pass_64c78173.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/sanitizer_and_static_analysis_pass_64c78173.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_sanitizer_and_static_analysis_pass_64c78173.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.75_documentation_and_agents_synchronization`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.75_documentation_and_agents_synchronization.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/documentation_and_agents_synchronization_a924b52a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/documentation_and_agents_synchronization_a924b52a.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/documentation_and_agents_synchronization_a924b52a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_documentation_and_agents_synchronization_a924b52a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.76_first_closure_audit`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.76_first_closure_audit.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/first_closure_audit_e4177e29/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/verification/first_closure_audit_e4177e29.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/verification/first_closure_audit_e4177e29.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/verification/test_first_closure_audit_e4177e29.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.77_adversarial_new-agent_simulation`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.77_adversarial_new-agent_simulation.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/adversarial_new_agent_simulation_c4764aba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/adversarial_new_agent_simulation_c4764aba.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/adversarial_new_agent_simulation_c4764aba.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_adversarial_new_agent_simulation_c4764aba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.78_independent_second_rediscovery`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.78_independent_second_rediscovery.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/independent_second_rediscovery_9316f9f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/resolution/independent_second_rediscovery_9316f9f2.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/resolution/independent_second_rediscovery_9316f9f2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/resolution/test_independent_second_rediscovery_9316f9f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.79_phase_6_final_closure`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.79_phase_6_final_closure.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/final_closure_2f19cd1e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/final_closure_2f19cd1e.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/final_closure_2f19cd1e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_final_closure_2f19cd1e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.8`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.8.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_9879f8f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_9879f8f2.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_9879f8f2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_9879f8f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `6.9`
- **Source:** `.phases/phases/phase-06-native-command-operation-execution/prompts/6.9.md`
- **Structural package:** `src/runtime/native-command-operation-execution/subtask_packages/verification/requirement_9d18a48e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_9d18a48e.hpp`, `src/runtime/native-command-operation-execution/subtask_targets/requirements/requirement_9d18a48e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/native-command-operation-execution/requirements/test_requirement_9d18a48e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`


## MASS IMPLEMENTATION XXII — Structural Skeleton Oversaturation
- Expanded canonical structural address space in `src/adapters`, `src/core`, `src/governance`, `src/interfaces`, `src/portability`, and `src/system`.
- Added explicit contracts/model/verification facets with local `AGENTS.md` boundaries and compilable skeleton tags.
- Evidence: `docs/reports/structural_saturation_xxii.md`, `docs/reports/structural_saturation_xxii.json`, `tools/materialize_structural_saturation.py`.
- Verification observed: `STRUCTURAL_HEADERS_STRICT_COMPILE_PASS`; phase-contract and subtask-ledger validators pass.
- **Maturity rule:** this is structural scaffolding only. It does not implement prompt behavior and does not raise this phase's depth. Future behavioral passes must replace/saturate these placement points with real integrated code and per-subtask evidence.
- Native Authority: compliant; no native Linux mechanism was reimplemented.

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

