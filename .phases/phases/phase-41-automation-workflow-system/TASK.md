# Phase 41 — Automation Workflow System — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-41-automation-workflow-system/`
- Primary prompt location: `.phases/phases/phase-41-automation-workflow-system/prompts/`
- Prompt/specification Markdown files currently present: **139**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 139 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_41` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 41 — Automation & Workflow System
- Required agent sequence
- Phase 41 Index
- Architecture
- Full prompts
- Agent Handoff
- Phase 41.117 — End-to-end workflow scenarios
- Objective
- Mandatory repository-first execution
- System invariants
- Implementation requirements
- Validation

## Structural skeleton / canonical destination
- Canonical skeleton: `src/automation/automation-workflow-system/`
- Structural files: `src/automation/automation-workflow-system/component.hpp`, `src/automation/automation-workflow-system/component.cpp`, `src/automation/automation-workflow-system/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/automation/workflows/README.md`
- `src/automation/workflows/automation_runtime.hpp`
- `src/automation/workflows/contract.hpp`
- `src/automation/README.md`
- `src/automation/actions/README.md`
- `src/automation/actions/contract.hpp`
- `src/automation/approvals/README.md`
- `src/automation/approvals/contract.hpp`
- `src/automation/compensation/README.md`
- `src/automation/compensation/contract.hpp`
- `src/automation/conditions/README.md`
- `src/automation/conditions/contract.hpp`

### Existing test evidence
- `tests/native/test_workflow.cpp`
- `tests/native/test_automation.cpp`

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

- Structural skeleton materialized at `src/automation/automation-workflow-system/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/automation/automation-workflow-system/model/`
- `src/automation/automation-workflow-system/contracts/`
- `src/automation/automation-workflow-system/integration/`
- `src/automation/automation-workflow-system/verification/`
- `src/automation/automation-workflow-system/lifecycle/`
- `src/automation/automation-workflow-system/state/`
- `src/automation/automation-workflow-system/execution/`
- `src/automation/automation-workflow-system/transactions/`
- `src/automation/automation-workflow-system/events/`
- `src/automation/automation-workflow-system/scheduling/`
- `src/automation/automation-workflow-system/recovery/`
- `src/automation/automation-workflow-system/principals/`
- `src/automation/automation-workflow-system/groups/`
- `src/automation/automation-workflow-system/roles/`
- `src/automation/automation-workflow-system/resolution/`
- `src/automation/automation-workflow-system/authorization/`
- `src/automation/automation-workflow-system/credentials/`
- `src/automation/automation-workflow-system/policy/`



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

### `41.000-foundation-and-repository-archaeology`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.000-foundation-and-repository-archaeology.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/foundation_and_repository_archaeology_6ad88cf1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/observability/foundation_and_repository_archaeology_6ad88cf1.hpp`, `src/automation/automation-workflow-system/subtask_targets/observability/foundation_and_repository_archaeology_6ad88cf1.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/observability/test_foundation_and_repository_archaeology_6ad88cf1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.001-ownership-map-and-automation-inventory`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.001-ownership-map-and-automation-inventory.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/ownership_map_and_automation_inventory_8ba32d84/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/ownership_map_and_automation_inventory_8ba32d84.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/ownership_map_and_automation_inventory_8ba32d84.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_ownership_map_and_automation_inventory_8ba32d84.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.002-canonical-architecture-and-source-tree-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.002-canonical-architecture-and-source-tree-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/canonical_architecture_and_source_tree_integration_094cf6e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/canonical_architecture_and_source_tree_integration_094cf6e7.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/canonical_architecture_and_source_tree_integration_094cf6e7.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_canonical_architecture_and_source_tree_integration_094cf6e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.003-native-c++-workflow-runtime-foundation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.003-native-c++-workflow-runtime-foundation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/native_c_workflow_runtime_foundation_e98d3d3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/native_c_workflow_runtime_foundation_e98d3d3a.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/native_c_workflow_runtime_foundation_e98d3d3a.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_native_c_workflow_runtime_foundation_e98d3d3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.004-strong-identifiers-and-core-types`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.004-strong-identifiers-and-core-types.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/strong_identifiers_and_core_types_3cbb774d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/contracts/strong_identifiers_and_core_types_3cbb774d.hpp`, `src/automation/automation-workflow-system/subtask_targets/contracts/strong_identifiers_and_core_types_3cbb774d.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/contracts/test_strong_identifiers_and_core_types_3cbb774d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.005-workflow-definition-schema`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.005-workflow-definition-schema.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/workflow_definition_schema_da6ecd7e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/contracts/workflow_definition_schema_da6ecd7e.hpp`, `src/automation/automation-workflow-system/subtask_targets/contracts/workflow_definition_schema_da6ecd7e.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/contracts/test_workflow_definition_schema_da6ecd7e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.006-workflow-definition-parser-and-serializer`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.006-workflow-definition-parser-and-serializer.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/workflow_definition_parser_and_serializer_89987d66/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/workflow_definition_parser_and_serializer_89987d66.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/workflow_definition_parser_and_serializer_89987d66.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_workflow_definition_parser_and_serializer_89987d66.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.007-definition-normalization`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.007-definition-normalization.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/definition_normalization_14460b50/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/definition_normalization_14460b50.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/definition_normalization_14460b50.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_definition_normalization_14460b50.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.008-static-workflow-validation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.008-static-workflow-validation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/static_workflow_validation_f0b62c1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/static_workflow_validation_f0b62c1f.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/static_workflow_validation_f0b62c1f.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_static_workflow_validation_f0b62c1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.009-workflow-compiler-and-executable-plan`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.009-workflow-compiler-and-executable-plan.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/workflow_compiler_and_executable_plan_dd1aae3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/execution/workflow_compiler_and_executable_plan_dd1aae3f.hpp`, `src/automation/automation-workflow-system/subtask_targets/execution/workflow_compiler_and_executable_plan_dd1aae3f.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/execution/test_workflow_compiler_and_executable_plan_dd1aae3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.010-run-state-model`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.010-run-state-model.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/run_state_model_469d9a11/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/lifecycle/run_state_model_469d9a11.hpp`, `src/automation/automation-workflow-system/subtask_targets/lifecycle/run_state_model_469d9a11.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/lifecycle/test_run_state_model_469d9a11.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.011-node-and-attempt-state-model`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.011-node-and-attempt-state-model.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/node_and_attempt_state_model_d4615767/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/lifecycle/node_and_attempt_state_model_d4615767.hpp`, `src/automation/automation-workflow-system/subtask_targets/lifecycle/node_and_attempt_state_model_d4615767.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/lifecycle/test_node_and_attempt_state_model_d4615767.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.012-durable-definition-repository`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.012-durable-definition-repository.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/durable_definition_repository_995b6696/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/persistence/durable_definition_repository_995b6696.hpp`, `src/automation/automation-workflow-system/subtask_targets/persistence/durable_definition_repository_995b6696.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/persistence/test_durable_definition_repository_995b6696.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.013-durable-run-repository`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.013-durable-run-repository.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/durable_run_repository_02f25db8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/persistence/durable_run_repository_02f25db8.hpp`, `src/automation/automation-workflow-system/subtask_targets/persistence/durable_run_repository_02f25db8.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/persistence/test_durable_run_repository_02f25db8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.014-transactional-state-transitions`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.014-transactional-state-transitions.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/transactional_state_transitions_31fad8d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/lifecycle/transactional_state_transitions_31fad8d2.hpp`, `src/automation/automation-workflow-system/subtask_targets/lifecycle/transactional_state_transitions_31fad8d2.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/lifecycle/test_transactional_state_transitions_31fad8d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.015-manual-operator-trigger`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.015-manual-operator-trigger.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/manual_operator_trigger_d09bf949/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/manual_operator_trigger_d09bf949.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/manual_operator_trigger_d09bf949.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_manual_operator_trigger_d09bf949.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.016-schedule-trigger-foundation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.016-schedule-trigger-foundation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/schedule_trigger_foundation_78591c48/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/planning/schedule_trigger_foundation_78591c48.hpp`, `src/automation/automation-workflow-system/subtask_targets/planning/schedule_trigger_foundation_78591c48.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/planning/test_schedule_trigger_foundation_78591c48.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.017-timezone-model`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.017-timezone-model.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/timezone_model_b092a0f3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/contracts/timezone_model_b092a0f3.hpp`, `src/automation/automation-workflow-system/subtask_targets/contracts/timezone_model_b092a0f3.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/contracts/test_timezone_model_b092a0f3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.018-dst-transition-semantics`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.018-dst-transition-semantics.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/dst_transition_semantics_da4908c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/lifecycle/dst_transition_semantics_da4908c1.hpp`, `src/automation/automation-workflow-system/subtask_targets/lifecycle/dst_transition_semantics_da4908c1.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/lifecycle/test_dst_transition_semantics_da4908c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.019-missed-schedules-and-reboot-catch-up`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.019-missed-schedules-and-reboot-catch-up.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/missed_schedules_and_reboot_catch_up_c2d02842/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/planning/missed_schedules_and_reboot_catch_up_c2d02842.hpp`, `src/automation/automation-workflow-system/subtask_targets/planning/missed_schedules_and_reboot_catch_up_c2d02842.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/planning/test_missed_schedules_and_reboot_catch_up_c2d02842.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.020-phase-39-event-trigger-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.020-phase-39-event-trigger-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/event_trigger_integration_4dfa2e89/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/event_trigger_integration_4dfa2e89.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/event_trigger_integration_4dfa2e89.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_event_trigger_integration_4dfa2e89.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.021-condition-watch-trigger-foundation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.021-condition-watch-trigger-foundation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/condition_watch_trigger_foundation_9c2ad15f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/condition_watch_trigger_foundation_9c2ad15f.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/condition_watch_trigger_foundation_9c2ad15f.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_condition_watch_trigger_foundation_9c2ad15f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.022-condition-evaluation-semantics`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.022-condition-evaluation-semantics.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/condition_evaluation_semantics_a73f1714/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/condition_evaluation_semantics_a73f1714.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/condition_evaluation_semantics_a73f1714.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_condition_evaluation_semantics_a73f1714.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.023-trigger-deduplication`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.023-trigger-deduplication.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/trigger_deduplication_4ae27f16/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/trigger_deduplication_4ae27f16.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/trigger_deduplication_4ae27f16.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_trigger_deduplication_4ae27f16.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.024-trigger-coalescing`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.024-trigger-coalescing.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/trigger_coalescing_f914a352/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/trigger_coalescing_f914a352.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/trigger_coalescing_f914a352.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_trigger_coalescing_f914a352.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.025-debounce-semantics`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.025-debounce-semantics.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/debounce_semantics_f0b2dbed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/debounce_semantics_f0b2dbed.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/debounce_semantics_f0b2dbed.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_debounce_semantics_f0b2dbed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.026-cooldown-semantics`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.026-cooldown-semantics.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/cooldown_semantics_fafa978d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/cooldown_semantics_fafa978d.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/cooldown_semantics_fafa978d.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_cooldown_semantics_fafa978d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.027-hysteresis-semantics`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.027-hysteresis-semantics.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/hysteresis_semantics_143d30ad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/hysteresis_semantics_143d30ad.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/hysteresis_semantics_143d30ad.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_hysteresis_semantics_143d30ad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.028-dag-execution-engine`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.028-dag-execution-engine.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/dag_execution_engine_846dee8f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/execution/dag_execution_engine_846dee8f.hpp`, `src/automation/automation-workflow-system/subtask_targets/execution/dag_execution_engine_846dee8f.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/execution/test_dag_execution_engine_846dee8f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.029-node-readiness-and-dependency-resolution`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.029-node-readiness-and-dependency-resolution.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/node_readiness_and_dependency_resolution_1b7ee19a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/node_readiness_and_dependency_resolution_1b7ee19a.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/node_readiness_and_dependency_resolution_1b7ee19a.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_node_readiness_and_dependency_resolution_1b7ee19a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.030-parallel-branch-execution`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.030-parallel-branch-execution.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/parallel_branch_execution_fd7d0955/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/execution/parallel_branch_execution_fd7d0955.hpp`, `src/automation/automation-workflow-system/subtask_targets/execution/parallel_branch_execution_fd7d0955.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/execution/test_parallel_branch_execution_fd7d0955.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.031-join-semantics`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.031-join-semantics.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/join_semantics_1778ac12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/join_semantics_1778ac12.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/join_semantics_1778ac12.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_join_semantics_1778ac12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.032-conditional-branching`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.032-conditional-branching.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/conditional_branching_648cd7a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/conditional_branching_648cd7a3.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/conditional_branching_648cd7a3.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_conditional_branching_648cd7a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.033-bounded-loops`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.033-bounded-loops.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/bounded_loops_295ef893/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/bounded_loops_295ef893.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/bounded_loops_295ef893.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_bounded_loops_295ef893.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.034-loop-termination-and-safety`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.034-loop-termination-and-safety.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/loop_termination_and_safety_a8ffdb14/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/loop_termination_and_safety_a8ffdb14.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/loop_termination_and_safety_a8ffdb14.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_loop_termination_and_safety_a8ffdb14.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.035-subworkflow-invocation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.035-subworkflow-invocation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/subworkflow_invocation_8e7a9e9a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/subworkflow_invocation_8e7a9e9a.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/subworkflow_invocation_8e7a9e9a.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_subworkflow_invocation_8e7a9e9a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.036-typed-workflow-inputs`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.036-typed-workflow-inputs.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/typed_workflow_inputs_82d66582/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/contracts/typed_workflow_inputs_82d66582.hpp`, `src/automation/automation-workflow-system/subtask_targets/contracts/typed_workflow_inputs_82d66582.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/contracts/test_typed_workflow_inputs_82d66582.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.037-typed-workflow-outputs`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.037-typed-workflow-outputs.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/typed_workflow_outputs_5943c3c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/contracts/typed_workflow_outputs_5943c3c1.hpp`, `src/automation/automation-workflow-system/subtask_targets/contracts/typed_workflow_outputs_5943c3c1.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/contracts/test_typed_workflow_outputs_5943c3c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.038-node-dataflow`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.038-node-dataflow.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/node_dataflow_e99f793f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/node_dataflow_e99f793f.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/node_dataflow_e99f793f.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_node_dataflow_e99f793f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.039-expression-and-predicate-boundary`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.039-expression-and-predicate-boundary.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/expression_and_predicate_boundary_02cc7460/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/expression_and_predicate_boundary_02cc7460.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/expression_and_predicate_boundary_02cc7460.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_expression_and_predicate_boundary_02cc7460.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.040-phase-40-commandintent-action-adapter`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.040-phase-40-commandintent-action-adapter.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/commandintent_action_adapter_64a03e04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/commandintent_action_adapter_64a03e04.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/commandintent_action_adapter_64a03e04.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_commandintent_action_adapter_64a03e04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.041-domain-capability-action-adapter`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.041-domain-capability-action-adapter.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/domain_capability_action_adapter_1ba2e5c6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/domain_capability_action_adapter_1ba2e5c6.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/domain_capability_action_adapter_1ba2e5c6.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_domain_capability_action_adapter_1ba2e5c6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.042-action-applicability-checks`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.042-action-applicability-checks.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/action_applicability_checks_c5f2dc60/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/action_applicability_checks_c5f2dc60.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/action_applicability_checks_c5f2dc60.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_action_applicability_checks_c5f2dc60.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.043-action-planning-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.043-action-planning-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/action_planning_integration_fd132341/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/action_planning_integration_fd132341.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/action_planning_integration_fd132341.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_action_planning_integration_fd132341.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.044-action-validation-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.044-action-validation-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/action_validation_integration_ce895905/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/action_validation_integration_ce895905.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/action_validation_integration_ce895905.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_action_validation_integration_ce895905.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.045-execution-time-authorization`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.045-execution-time-authorization.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/execution_time_authorization_020f3881/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/execution_time_authorization_020f3881.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/execution_time_authorization_020f3881.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_execution_time_authorization_020f3881.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.046-scoped-delegation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.046-scoped-delegation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/scoped_delegation_0c573e46/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/scoped_delegation_0c573e46.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/scoped_delegation_0c573e46.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_scoped_delegation_0c573e46.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.047-delegation-expiry-and-revocation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.047-delegation-expiry-and-revocation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/delegation_expiry_and_revocation_2cc29ab6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/delegation_expiry_and_revocation_2cc29ab6.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/delegation_expiry_and_revocation_2cc29ab6.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_delegation_expiry_and_revocation_2cc29ab6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.048-phase-37-secretref-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.048-phase-37-secretref-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/secretref_integration_1b8e2609/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/secretref_integration_1b8e2609.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/secretref_integration_1b8e2609.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_secretref_integration_1b8e2609.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.049-secret-safe-workflow-state`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.049-secret-safe-workflow-state.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/secret_safe_workflow_state_ab7cba95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/secret_safe_workflow_state_ab7cba95.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/secret_safe_workflow_state_ab7cba95.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_secret_safe_workflow_state_ab7cba95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.050-shell-compatibility-boundary`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.050-shell-compatibility-boundary.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/shell_compatibility_boundary_a417bf92/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/shell_compatibility_boundary_a417bf92.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/shell_compatibility_boundary_a417bf92.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_shell_compatibility_boundary_a417bf92.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.051-safe-process-execution`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.051-safe-process-execution.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/safe_process_execution_cc93de36/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/execution/safe_process_execution_cc93de36.hpp`, `src/automation/automation-workflow-system/subtask_targets/execution/safe_process_execution_cc93de36.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/execution/test_safe_process_execution_cc93de36.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.052-environment-and-working-directory-policy`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.052-environment-and-working-directory-policy.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/environment_and_working_directory_policy_b2b99bbb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/environment_and_working_directory_policy_b2b99bbb.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/environment_and_working_directory_policy_b2b99bbb.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_environment_and_working_directory_policy_b2b99bbb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.053-timeouts-and-deadlines`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.053-timeouts-and-deadlines.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/timeouts_and_deadlines_9c68fd87/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/timeouts_and_deadlines_9c68fd87.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/timeouts_and_deadlines_9c68fd87.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_timeouts_and_deadlines_9c68fd87.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.054-cancellation-propagation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.054-cancellation-propagation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/cancellation_propagation_80289459/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/cancellation_propagation_80289459.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/cancellation_propagation_80289459.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_cancellation_propagation_80289459.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.055-retry-policy-model`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.055-retry-policy-model.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/retry_policy_model_1dba053c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/retry_policy_model_1dba053c.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/retry_policy_model_1dba053c.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_retry_policy_model_1dba053c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.056-backoff-and-jitter`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.056-backoff-and-jitter.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/backoff_and_jitter_d9befdb3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/backoff_and_jitter_d9befdb3.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/backoff_and_jitter_d9befdb3.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_backoff_and_jitter_d9befdb3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.057-retry-classification`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.057-retry-classification.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/retry_classification_54b33921/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/retry_classification_54b33921.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/retry_classification_54b33921.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_retry_classification_54b33921.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.058-idempotency-keys`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.058-idempotency-keys.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/idempotency_keys_f211f831/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/idempotency_keys_f211f831.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/idempotency_keys_f211f831.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_idempotency_keys_f211f831.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.059-action-deduplication`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.059-action-deduplication.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/action_deduplication_d812ace9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/action_deduplication_d812ace9.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/action_deduplication_d812ace9.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_action_deduplication_d812ace9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.060-external-side-effect-reconciliation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.060-external-side-effect-reconciliation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/external_side_effect_reconciliation_5ffd37e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/external_side_effect_reconciliation_5ffd37e4.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/external_side_effect_reconciliation_5ffd37e4.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_external_side_effect_reconciliation_5ffd37e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.061-compensation-model`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.061-compensation-model.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/compensation_model_00282394/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/recovery/compensation_model_00282394.hpp`, `src/automation/automation-workflow-system/subtask_targets/recovery/compensation_model_00282394.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/recovery/test_compensation_model_00282394.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.062-compensation-ordering-and-failure`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.062-compensation-ordering-and-failure.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/compensation_ordering_and_failure_01575cf7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/recovery/compensation_ordering_and_failure_01575cf7.hpp`, `src/automation/automation-workflow-system/subtask_targets/recovery/compensation_ordering_and_failure_01575cf7.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/recovery/test_compensation_ordering_and_failure_01575cf7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.063-checkpointing`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.063-checkpointing.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/checkpointing_adf626ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/checkpointing_adf626ba.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/checkpointing_adf626ba.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_checkpointing_adf626ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.064-crash-recovery`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.064-crash-recovery.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/crash_recovery_90232a13/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/recovery/crash_recovery_90232a13.hpp`, `src/automation/automation-workflow-system/subtask_targets/recovery/crash_recovery_90232a13.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/recovery/test_crash_recovery_90232a13.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.065-daemon-restart-recovery`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.065-daemon-restart-recovery.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/daemon_restart_recovery_7e745f20/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/recovery/daemon_restart_recovery_7e745f20.hpp`, `src/automation/automation-workflow-system/subtask_targets/recovery/daemon_restart_recovery_7e745f20.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/recovery/test_daemon_restart_recovery_7e745f20.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.066-reboot-continuity`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.066-reboot-continuity.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/reboot_continuity_a62b4a17/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/reboot_continuity_a62b4a17.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/reboot_continuity_a62b4a17.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_reboot_continuity_a62b4a17.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.067-run-resumption-policy`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.067-run-resumption-policy.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/run_resumption_policy_dce1320d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/run_resumption_policy_dce1320d.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/run_resumption_policy_dce1320d.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_run_resumption_policy_dce1320d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.068-ambiguous-outcome-and-unknown-handling`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.068-ambiguous-outcome-and-unknown-handling.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/ambiguous_outcome_and_unknown_handling_e51c5846/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/ambiguous_outcome_and_unknown_handling_e51c5846.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/ambiguous_outcome_and_unknown_handling_e51c5846.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_ambiguous_outcome_and_unknown_handling_e51c5846.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.069-bounded-concurrency`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.069-bounded-concurrency.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/bounded_concurrency_2f0208e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/bounded_concurrency_2f0208e3.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/bounded_concurrency_2f0208e3.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_bounded_concurrency_2f0208e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.070-queueing-and-backpressure`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.070-queueing-and-backpressure.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/queueing_and_backpressure_e3b06941/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/queueing_and_backpressure_e3b06941.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/queueing_and_backpressure_e3b06941.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_queueing_and_backpressure_e3b06941.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.071-priority-and-fairness`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.071-priority-and-fairness.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/priority_and_fairness_bec16b74/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/priority_and_fairness_bec16b74.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/priority_and_fairness_bec16b74.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_priority_and_fairness_bec16b74.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.072-phase-29-workload-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.072-phase-29-workload-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/workload_integration_3d87da4d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/workload_integration_3d87da4d.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/workload_integration_3d87da4d.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_workload_integration_3d87da4d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.073-phase-30-resource-aware-scheduling`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.073-phase-30-resource-aware-scheduling.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/resource_aware_scheduling_6b053e68/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/resource_aware_scheduling_6b053e68.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/resource_aware_scheduling_6b053e68.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_resource_aware_scheduling_6b053e68.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.074-resource-admission-control`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.074-resource-admission-control.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/resource_admission_control_c4f22c8a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/resource_admission_control_c4f22c8a.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/resource_admission_control_c4f22c8a.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_resource_admission_control_c4f22c8a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.075-resource-reservations`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.075-resource-reservations.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/resource_reservations_69853588/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/resource_reservations_69853588.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/resource_reservations_69853588.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_resource_reservations_69853588.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.076-workflow-failure-policy`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.076-workflow-failure-policy.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/workflow_failure_policy_a19e14bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/workflow_failure_policy_a19e14bf.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/workflow_failure_policy_a19e14bf.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_workflow_failure_policy_a19e14bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.077-node-failure-policy`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.077-node-failure-policy.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/node_failure_policy_886670e2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/node_failure_policy_886670e2.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/node_failure_policy_886670e2.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_node_failure_policy_886670e2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.078-fallback-paths`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.078-fallback-paths.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/fallback_paths_193d4388/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/fallback_paths_193d4388.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/fallback_paths_193d4388.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_fallback_paths_193d4388.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.079-safe-mode`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.079-safe-mode.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/safe_mode_2ddfbd5c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/safe_mode_2ddfbd5c.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/safe_mode_2ddfbd5c.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_safe_mode_2ddfbd5c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.080-emergency-quiescence`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.080-emergency-quiescence.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/emergency_quiescence_934bdb62/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/emergency_quiescence_934bdb62.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/emergency_quiescence_934bdb62.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_emergency_quiescence_934bdb62.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.081-operator-pause-resume-and-cancel`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.081-operator-pause-resume-and-cancel.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/operator_pause_resume_and_cancel_753b8353/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/recovery/operator_pause_resume_and_cancel_753b8353.hpp`, `src/automation/automation-workflow-system/subtask_targets/recovery/operator_pause_resume_and_cancel_753b8353.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/recovery/test_operator_pause_resume_and_cancel_753b8353.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.082-workflow-enable-disable-lifecycle`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.082-workflow-enable-disable-lifecycle.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/workflow_enable_disable_lifecycle_3cfceca3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/lifecycle/workflow_enable_disable_lifecycle_3cfceca3.hpp`, `src/automation/automation-workflow-system/subtask_targets/lifecycle/workflow_enable_disable_lifecycle_3cfceca3.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/lifecycle/test_workflow_enable_disable_lifecycle_3cfceca3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.083-definition-versioning`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.083-definition-versioning.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/definition_versioning_5efc13a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/definition_versioning_5efc13a3.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/definition_versioning_5efc13a3.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_definition_versioning_5efc13a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.084-running-version-pinning`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.084-running-version-pinning.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/running_version_pinning_dc2d1491/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/running_version_pinning_dc2d1491.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/running_version_pinning_dc2d1491.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_running_version_pinning_dc2d1491.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.085-definition-migration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.085-definition-migration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/definition_migration_a9f50a63/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/definition_migration_a9f50a63.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/definition_migration_a9f50a63.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_definition_migration_a9f50a63.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.086-import-and-export-representation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.086-import-and-export-representation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/import_and_export_representation_dab57775/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/import_and_export_representation_dab57775.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/import_and_export_representation_dab57775.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_import_and_export_representation_dab57775.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.087-cli-workflow-inspection`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.087-cli-workflow-inspection.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/cli_workflow_inspection_024da44d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/cli_workflow_inspection_024da44d.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/cli_workflow_inspection_024da44d.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_cli_workflow_inspection_024da44d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.088-cli-workflow-authoring`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.088-cli-workflow-authoring.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/cli_workflow_authoring_15d207ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/cli_workflow_authoring_15d207ec.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/cli_workflow_authoring_15d207ec.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_cli_workflow_authoring_15d207ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.089-cli-run-control`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.089-cli-run-control.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/cli_run_control_fe8d8bab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/cli_run_control_fe8d8bab.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/cli_run_control_fe8d8bab.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_cli_run_control_fe8d8bab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.090-phase-25-panel-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.090-phase-25-panel-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/panel_integration_0779b37a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/panel_integration_0779b37a.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/panel_integration_0779b37a.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_panel_integration_0779b37a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.091-phase-40-unified-search-integration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.091-phase-40-unified-search-integration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/unified_search_integration_26283280/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/unified_search_integration_26283280.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/unified_search_integration_26283280.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_unified_search_integration_26283280.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.092-workflow-search-facets-and-references`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.092-workflow-search-facets-and-references.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/workflow_search_facets_and_references_02de19f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/resolution/workflow_search_facets_and_references_02de19f9.hpp`, `src/automation/automation-workflow-system/subtask_targets/resolution/workflow_search_facets_and_references_02de19f9.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/resolution/test_workflow_search_facets_and_references_02de19f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.093-phase-39-timeline-recording`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.093-phase-39-timeline-recording.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/timeline_recording_36a28ecc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/timeline_recording_36a28ecc.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/timeline_recording_36a28ecc.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_timeline_recording_36a28ecc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.094-structured-observability-and-diagnostics`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.094-structured-observability-and-diagnostics.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/structured_observability_and_diagnostics_0b815096/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/observability/structured_observability_and_diagnostics_0b815096.hpp`, `src/automation/automation-workflow-system/subtask_targets/observability/structured_observability_and_diagnostics_0b815096.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/observability/test_structured_observability_and_diagnostics_0b815096.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.095-metrics-and-performance-telemetry`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.095-metrics-and-performance-telemetry.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/metrics_and_performance_telemetry_8fee0a74/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/observability/metrics_and_performance_telemetry_8fee0a74.hpp`, `src/automation/automation-workflow-system/subtask_targets/observability/metrics_and_performance_telemetry_8fee0a74.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/observability/test_metrics_and_performance_telemetry_8fee0a74.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.096-audit-and-provenance`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.096-audit-and-provenance.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/audit_and_provenance_d27908f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/audit_and_provenance_d27908f9.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/audit_and_provenance_d27908f9.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_audit_and_provenance_d27908f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.097-secret-safe-logging-and-redaction`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.097-secret-safe-logging-and-redaction.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/secret_safe_logging_and_redaction_49bce56d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/secret_safe_logging_and_redaction_49bce56d.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/secret_safe_logging_and_redaction_49bce56d.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_secret_safe_logging_and_redaction_49bce56d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.098-semantic-workflow-authoring-boundary`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.098-semantic-workflow-authoring-boundary.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/semantic_workflow_authoring_boundary_2ddb228a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/semantic_workflow_authoring_boundary_2ddb228a.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/semantic_workflow_authoring_boundary_2ddb228a.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_semantic_workflow_authoring_boundary_2ddb228a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.099-semantic-explanation-and-annotation-boundary`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.099-semantic-explanation-and-annotation-boundary.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/semantic_explanation_and_annotation_boundary_23270020/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/planning/semantic_explanation_and_annotation_boundary_23270020.hpp`, `src/automation/automation-workflow-system/subtask_targets/planning/semantic_explanation_and_annotation_boundary_23270020.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/planning/test_semantic_explanation_and_annotation_boundary_23270020.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.100-semantic-candidate-validation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.100-semantic-candidate-validation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/semantic_candidate_validation_9c78bfd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/semantic_candidate_validation_9c78bfd4.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/semantic_candidate_validation_9c78bfd4.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_semantic_candidate_validation_9c78bfd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.101-cron-discovery-and-migration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.101-cron-discovery-and-migration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/cron_discovery_and_migration_4119d862/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/cron_discovery_and_migration_4119d862.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/cron_discovery_and_migration_4119d862.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_cron_discovery_and_migration_4119d862.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.102-systemd-timer-discovery-and-migration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.102-systemd-timer-discovery-and-migration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/systemd_timer_discovery_and_migration_7a642e5f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/systemd_timer_discovery_and_migration_7a642e5f.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/systemd_timer_discovery_and_migration_7a642e5f.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_systemd_timer_discovery_and_migration_7a642e5f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.103-legacy-script-automation-migration`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.103-legacy-script-automation-migration.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/legacy_script_automation_migration_a1fbb621/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/integration/legacy_script_automation_migration_a1fbb621.hpp`, `src/automation/automation-workflow-system/subtask_targets/integration/legacy_script_automation_migration_a1fbb621.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/integration/test_legacy_script_automation_migration_a1fbb621.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.104-existing-rebuntu-workflow-reconciliation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.104-existing-rebuntu-workflow-reconciliation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/existing_rebuntu_workflow_reconciliation_cd13ee95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/existing_rebuntu_workflow_reconciliation_cd13ee95.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/existing_rebuntu_workflow_reconciliation_cd13ee95.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_existing_rebuntu_workflow_reconciliation_cd13ee95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.105-existing-automation-package-reconciliation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.105-existing-automation-package-reconciliation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/existing_automation_package_reconciliation_64a069e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/existing_automation_package_reconciliation_64a069e5.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/existing_automation_package_reconciliation_64a069e5.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_existing_automation_package_reconciliation_64a069e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.106-duplicate-authority-audit`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.106-duplicate-authority-audit.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/duplicate_authority_audit_709c706b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/duplicate_authority_audit_709c706b.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/duplicate_authority_audit_709c706b.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_duplicate_authority_audit_709c706b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.107-security-threat-model`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.107-security-threat-model.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/security_threat_model_e9ab326f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/security/security_threat_model_e9ab326f.hpp`, `src/automation/automation-workflow-system/subtask_targets/security/security_threat_model_e9ab326f.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/security/test_security_threat_model_e9ab326f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.108-privilege-boundary-audit`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.108-privilege-boundary-audit.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/privilege_boundary_audit_afa32024/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/privilege_boundary_audit_afa32024.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/privilege_boundary_audit_afa32024.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_privilege_boundary_audit_afa32024.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.109-race-and-toctou-audit`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.109-race-and-toctou-audit.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/race_and_toctou_audit_509a23eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/race_and_toctou_audit_509a23eb.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/race_and_toctou_audit_509a23eb.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_race_and_toctou_audit_509a23eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.110-failure-injection-framework`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.110-failure-injection-framework.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/failure_injection_framework_9250d9fd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/failure_injection_framework_9250d9fd.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/failure_injection_framework_9250d9fd.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_failure_injection_framework_9250d9fd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.111-trigger-determinism-tests`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.111-trigger-determinism-tests.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/trigger_determinism_tests_3226ca52/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/trigger_determinism_tests_3226ca52.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/trigger_determinism_tests_3226ca52.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_trigger_determinism_tests_3226ca52.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.112-dst-clock-jump-and-reboot-tests`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.112-dst-clock-jump-and-reboot-tests.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/dst_clock_jump_and_reboot_tests_16fd429c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/dst_clock_jump_and_reboot_tests_16fd429c.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/dst_clock_jump_and_reboot_tests_16fd429c.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_dst_clock_jump_and_reboot_tests_16fd429c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.113-crash-restart-recovery-tests`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.113-crash-restart-recovery-tests.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/crash_restart_recovery_tests_02944ac6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/crash_restart_recovery_tests_02944ac6.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/crash_restart_recovery_tests_02944ac6.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_crash_restart_recovery_tests_02944ac6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.114-retry-idempotency-reconciliation-tests`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.114-retry-idempotency-reconciliation-tests.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/retry_idempotency_reconciliation_tests_964446f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/retry_idempotency_reconciliation_tests_964446f2.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/retry_idempotency_reconciliation_tests_964446f2.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_retry_idempotency_reconciliation_tests_964446f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.115-authorization-and-delegation-tests`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.115-authorization-and-delegation-tests.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/authorization_and_delegation_tests_0f54fc5b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/authorization_and_delegation_tests_0f54fc5b.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/authorization_and_delegation_tests_0f54fc5b.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_authorization_and_delegation_tests_0f54fc5b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.116-resource-and-backpressure-tests`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.116-resource-and-backpressure-tests.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/resource_and_backpressure_tests_e6dabea2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/resource_and_backpressure_tests_e6dabea2.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/resource_and_backpressure_tests_e6dabea2.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_resource_and_backpressure_tests_e6dabea2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.117-end-to-end-workflow-scenarios`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.117-end-to-end-workflow-scenarios.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/end_to_end_workflow_scenarios_c6b40008/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/end_to_end_workflow_scenarios_c6b40008.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/end_to_end_workflow_scenarios_c6b40008.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_end_to_end_workflow_scenarios_c6b40008.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.118-performance-and-scalability-validation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.118-performance-and-scalability-validation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/performance_and_scalability_validation_3b087810/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/performance_and_scalability_validation_3b087810.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/performance_and_scalability_validation_3b087810.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_performance_and_scalability_validation_3b087810.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.119-documentation-reconciliation`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.119-documentation-reconciliation.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/documentation_reconciliation_e17150e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/documentation_reconciliation_e17150e7.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/documentation_reconciliation_e17150e7.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_documentation_reconciliation_e17150e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.120-agents.md-permanent-contract`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.120-agents.md-permanent-contract.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/agents_md_permanent_contract_ec1faadd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/contracts/agents_md_permanent_contract_ec1faadd.hpp`, `src/automation/automation-workflow-system/subtask_targets/contracts/agents_md_permanent_contract_ec1faadd.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/contracts/test_agents_md_permanent_contract_ec1faadd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.121-repository-wide-recursive-rediscovery`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.121-repository-wide-recursive-rediscovery.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/repository_wide_recursive_rediscovery_b3f960ff/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/resolution/repository_wide_recursive_rediscovery_b3f960ff.hpp`, `src/automation/automation-workflow-system/subtask_targets/resolution/repository_wide_recursive_rediscovery_b3f960ff.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/resolution/test_repository_wide_recursive_rediscovery_b3f960ff.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.122-adversarial-closure-audit`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.122-adversarial-closure-audit.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/adversarial_closure_audit_82559a8c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/verification/adversarial_closure_audit_82559a8c.hpp`, `src/automation/automation-workflow-system/subtask_targets/verification/adversarial_closure_audit_82559a8c.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/verification/test_adversarial_closure_audit_82559a8c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `41.123-phase-41-closure-and-handoff`
- **Source:** `.phases/phases/phase-41-automation-workflow-system/prompts/41.123-phase-41-closure-and-handoff.md`
- **Structural package:** `src/automation/automation-workflow-system/subtask_packages/verification/closure_and_handoff_46a86860/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/automation/automation-workflow-system/subtask_targets/requirements/closure_and_handoff_46a86860.hpp`, `src/automation/automation-workflow-system/subtask_targets/requirements/closure_and_handoff_46a86860.cpp`
- **Structural test target:** `tests/structural-closure/automation/automation-workflow-system/requirements/test_closure_and_handoff_46a86860.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

