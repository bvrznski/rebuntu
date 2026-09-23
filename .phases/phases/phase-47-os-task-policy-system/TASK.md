# Phase 47 — Os Task Policy System — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-47-os-task-policy-system/`
- Primary prompt location: `.phases/phases/phase-47-os-task-policy-system/prompts/`
- Prompt/specification Markdown files currently present: **586**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 586 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_47` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 47 — OS Task Policy System
- Phase 47 Index
- Normative architecture
- Full executable prompts
- Phase 47 Agent Handoff
- Phase 47.31 — Interactive task class
- Objective
- Repository-first execution
- Task-policy invariants
- Policy lifecycle
- Context, capabilities and data flow
- Cross-phase authority

## Structural skeleton / canonical destination
- Canonical skeleton: `src/runtime/os-task-policy-system/`
- Structural files: `src/runtime/os-task-policy-system/component.hpp`, `src/runtime/os-task-policy-system/component.cpp`, `src/runtime/os-task-policy-system/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/security/policy/README.md`
- `src/security/policy/contract.hpp`
- `src/security/policy/operation_policy.hpp`
- `src/security/policy/policy_engine.hpp`
- `src/control/runtime/policy_engine.cpp`

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
- Baseline ledger created automatically from the current repository. Depth **2/5** is deliberately conservative and not a completion claim.

- Structural skeleton materialized at `src/runtime/os-task-policy-system/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/runtime/os-task-policy-system/model/`
- `src/runtime/os-task-policy-system/contracts/`
- `src/runtime/os-task-policy-system/integration/`
- `src/runtime/os-task-policy-system/verification/`
- `src/runtime/os-task-policy-system/lifecycle/`
- `src/runtime/os-task-policy-system/state/`
- `src/runtime/os-task-policy-system/execution/`
- `src/runtime/os-task-policy-system/transactions/`
- `src/runtime/os-task-policy-system/events/`
- `src/runtime/os-task-policy-system/scheduling/`
- `src/runtime/os-task-policy-system/recovery/`
- `src/runtime/os-task-policy-system/principals/`
- `src/runtime/os-task-policy-system/groups/`
- `src/runtime/os-task-policy-system/roles/`
- `src/runtime/os-task-policy-system/resolution/`
- `src/runtime/os-task-policy-system/authorization/`
- `src/runtime/os-task-policy-system/credentials/`
- `src/runtime/os-task-policy-system/policy/`



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

### `47.000-foundation-and-repository-archaeology`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.000-foundation-and-repository-archaeology.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/foundation_and_repository_archaeology_3c3e8e7c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/observability/foundation_and_repository_archaeology_3c3e8e7c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/observability/foundation_and_repository_archaeology_3c3e8e7c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/observability/test_foundation_and_repository_archaeology_3c3e8e7c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.001-existing-task-policy-inventory`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.001-existing-task-policy-inventory.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/existing_task_policy_inventory_b595db06/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/existing_task_policy_inventory_b595db06.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/existing_task_policy_inventory_b595db06.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_existing_task_policy_inventory_b595db06.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.002-existing-authorization-rule-inventory`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.002-existing-authorization-rule-inventory.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/existing_authorization_rule_inventory_13bdab48/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/existing_authorization_rule_inventory_13bdab48.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/existing_authorization_rule_inventory_13bdab48.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_existing_authorization_rule_inventory_13bdab48.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.003-existing-safety-gate-inventory`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.003-existing-safety-gate-inventory.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/existing_safety_gate_inventory_efeeda2c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/existing_safety_gate_inventory_efeeda2c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/existing_safety_gate_inventory_efeeda2c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_existing_safety_gate_inventory_efeeda2c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.004-existing-workflow-policy-inventory`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.004-existing-workflow-policy-inventory.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/existing_workflow_policy_inventory_e38483c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/existing_workflow_policy_inventory_e38483c3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/existing_workflow_policy_inventory_e38483c3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_existing_workflow_policy_inventory_e38483c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.005-existing-semantic-execution-policy-inventory`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.005-existing-semantic-execution-policy-inventory.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/existing_semantic_execution_policy_inventory_7a3be9b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/existing_semantic_execution_policy_inventory_7a3be9b1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/existing_semantic_execution_policy_inventory_7a3be9b1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_existing_semantic_execution_policy_inventory_7a3be9b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.006-canonical-os-task-policy-architecture`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.006-canonical-os-task-policy-architecture.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/canonical_os_task_policy_architecture_7e1f5bcd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/canonical_os_task_policy_architecture_7e1f5bcd.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/canonical_os_task_policy_architecture_7e1f5bcd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_canonical_os_task_policy_architecture_7e1f5bcd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.007-c-first-deterministic-policy-runtime`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.007-c-first-deterministic-policy-runtime.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/c_first_deterministic_policy_runtime_05282980/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/c_first_deterministic_policy_runtime_05282980.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/c_first_deterministic_policy_runtime_05282980.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_c_first_deterministic_policy_runtime_05282980.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.008-task-strong-types`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.008-task-strong-types.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_strong_types_6ca5b896/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/task_strong_types_6ca5b896.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/task_strong_types_6ca5b896.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_task_strong_types_6ca5b896.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.009-task-identity`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.009-task-identity.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_identity_6f3454a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/task_identity_6f3454a9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/task_identity_6f3454a9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_task_identity_6f3454a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.010-task-origin`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.010-task-origin.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_origin_247fa8a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_origin_247fa8a8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_origin_247fa8a8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_origin_247fa8a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.011-task-requester`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.011-task-requester.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_requester_8490e05c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_requester_8490e05c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_requester_8490e05c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_requester_8490e05c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.012-task-delegation-chain`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.012-task-delegation-chain.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_delegation_chain_e6dda145/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_delegation_chain_e6dda145.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_delegation_chain_e6dda145.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_delegation_chain_e6dda145.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.013-task-context`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.013-task-context.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_context_ab3bb7d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_context_ab3bb7d5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_context_ab3bb7d5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_context_ab3bb7d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.014-task-scope`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.014-task-scope.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_scope_76a1cdb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_scope_76a1cdb9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_scope_76a1cdb9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_scope_76a1cdb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.015-task-target`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.015-task-target.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_target_e06a4e5b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_target_e06a4e5b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_target_e06a4e5b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_target_e06a4e5b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.016-task-capability-requirements`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.016-task-capability-requirements.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_capability_requirements_756a41b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_capability_requirements_756a41b1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_capability_requirements_756a41b1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_capability_requirements_756a41b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.017-task-resource-requirements`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.017-task-resource-requirements.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_resource_requirements_22fd9f79/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_resource_requirements_22fd9f79.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_resource_requirements_22fd9f79.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_resource_requirements_22fd9f79.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.018-task-data-flow-effects`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.018-task-data-flow-effects.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_data_flow_effects_14a06b96/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_data_flow_effects_14a06b96.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_data_flow_effects_14a06b96.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_data_flow_effects_14a06b96.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.019-task-risk-metadata`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.019-task-risk-metadata.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_risk_metadata_e44fda93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_risk_metadata_e44fda93.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_risk_metadata_e44fda93.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_risk_metadata_e44fda93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.020-task-reversibility-metadata`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.020-task-reversibility-metadata.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_reversibility_metadata_98ca1ec0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_reversibility_metadata_98ca1ec0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_reversibility_metadata_98ca1ec0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_reversibility_metadata_98ca1ec0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.021-task-verification-requirements`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.021-task-verification-requirements.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_verification_requirements_fed7eaff/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/task_verification_requirements_fed7eaff.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/task_verification_requirements_fed7eaff.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_task_verification_requirements_fed7eaff.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.022-task-provenance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.022-task-provenance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_provenance_ae0c434e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_provenance_ae0c434e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_provenance_ae0c434e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_provenance_ae0c434e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.023-task-freshness`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.023-task-freshness.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_freshness_091fc941/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_freshness_091fc941.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_freshness_091fc941.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_freshness_091fc941.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.024-task-lifecycle`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.024-task-lifecycle.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_lifecycle_02859bd7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/lifecycle/task_lifecycle_02859bd7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/lifecycle/task_lifecycle_02859bd7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/lifecycle/test_task_lifecycle_02859bd7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.025-task-intent-versus-task-instance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.025-task-intent-versus-task-instance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_intent_versus_task_instance_bf46883b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_intent_versus_task_instance_bf46883b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_intent_versus_task_instance_bf46883b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_intent_versus_task_instance_bf46883b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.026-task-definition-versus-execution`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.026-task-definition-versus-execution.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_definition_versus_execution_b6389e27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/execution/task_definition_versus_execution_b6389e27.hpp`, `src/runtime/os-task-policy-system/subtask_targets/execution/task_definition_versus_execution_b6389e27.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/execution/test_task_definition_versus_execution_b6389e27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.027-task-plan-linkage`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.027-task-plan-linkage.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_plan_linkage_f1772fb8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/task_plan_linkage_f1772fb8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/task_plan_linkage_f1772fb8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_task_plan_linkage_f1772fb8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.028-task-outcome-linkage`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.028-task-outcome-linkage.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_outcome_linkage_a3452456/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_outcome_linkage_a3452456.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_outcome_linkage_a3452456.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_outcome_linkage_a3452456.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.029-read-only-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.029-read-only-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/read_only_task_class_b8dfb95f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/read_only_task_class_b8dfb95f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/read_only_task_class_b8dfb95f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_read_only_task_class_b8dfb95f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.030-mutating-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.030-mutating-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/mutating_task_class_edecceb8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/mutating_task_class_edecceb8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/mutating_task_class_edecceb8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_mutating_task_class_edecceb8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.031-interactive-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.031-interactive-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/interactive_task_class_8316951a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/interactive_task_class_8316951a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/interactive_task_class_8316951a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_interactive_task_class_8316951a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.032-scheduled-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.032-scheduled-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/scheduled_task_class_0f1cc569/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/scheduled_task_class_0f1cc569.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/scheduled_task_class_0f1cc569.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_scheduled_task_class_0f1cc569.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.033-recurring-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.033-recurring-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/recurring_task_class_94befa7d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/recurring_task_class_94befa7d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/recurring_task_class_94befa7d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_recurring_task_class_94befa7d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.034-conditional-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.034-conditional-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/conditional_task_class_7eef1a48/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/conditional_task_class_7eef1a48.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/conditional_task_class_7eef1a48.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_conditional_task_class_7eef1a48.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.035-workflow-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.035-workflow-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_task_class_4c568480/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_task_class_4c568480.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_task_class_4c568480.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_workflow_task_class_4c568480.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.036-automation-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.036-automation-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/automation_task_class_2d674f8c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/automation_task_class_2d674f8c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/automation_task_class_2d674f8c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_automation_task_class_2d674f8c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.037-semantic-originated-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.037-semantic-originated-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/semantic_originated_task_class_7d24248a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/semantic_originated_task_class_7d24248a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/semantic_originated_task_class_7d24248a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_semantic_originated_task_class_7d24248a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.038-agent-originated-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.038-agent-originated-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_originated_task_class_ba77f25c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/agent_originated_task_class_ba77f25c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/agent_originated_task_class_ba77f25c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_agent_originated_task_class_ba77f25c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.039-system-originated-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.039-system-originated-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_originated_task_class_1818a56a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/system_originated_task_class_1818a56a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/system_originated_task_class_1818a56a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_system_originated_task_class_1818a56a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.040-maintenance-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.040-maintenance-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/maintenance_task_class_d4bbb58d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/maintenance_task_class_d4bbb58d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/maintenance_task_class_d4bbb58d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_maintenance_task_class_d4bbb58d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.041-emergency-task-class`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.041-emergency-task-class.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/emergency_task_class_93d6d5e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/emergency_task_class_93d6d5e5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/emergency_task_class_93d6d5e5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_emergency_task_class_93d6d5e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.042-policy-strong-types`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.042-policy-strong-types.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_strong_types_97563648/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_strong_types_97563648.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_strong_types_97563648.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_strong_types_97563648.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.043-policy-identity`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.043-policy-identity.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_identity_cfc74671/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_identity_cfc74671.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_identity_cfc74671.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_identity_cfc74671.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.044-policy-version`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.044-policy-version.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_version_1bdd2bc0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_version_1bdd2bc0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_version_1bdd2bc0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_version_1bdd2bc0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.045-policy-provenance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.045-policy-provenance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_provenance_c5607c60/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_provenance_c5607c60.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_provenance_c5607c60.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_provenance_c5607c60.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.046-policy-scope`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.046-policy-scope.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_scope_2405b656/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_scope_2405b656.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_scope_2405b656.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_scope_2405b656.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.047-policy-selector`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.047-policy-selector.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_selector_3af40903/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_selector_3af40903.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_selector_3af40903.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_selector_3af40903.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.048-policy-condition`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.048-policy-condition.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_condition_12bc1feb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_condition_12bc1feb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_condition_12bc1feb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_condition_12bc1feb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.049-policy-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.049-policy-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_effect_13659ee7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_effect_13659ee7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_effect_13659ee7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_effect_13659ee7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.050-policy-obligation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.050-policy-obligation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_obligation_af35694f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_obligation_af35694f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_obligation_af35694f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_obligation_af35694f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.051-policy-priority`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.051-policy-priority.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_priority_994b4e4b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_priority_994b4e4b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_priority_994b4e4b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_priority_994b4e4b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.052-policy-precedence`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.052-policy-precedence.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_precedence_f7d1f6da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_precedence_f7d1f6da.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_precedence_f7d1f6da.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_precedence_f7d1f6da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.053-policy-activation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.053-policy-activation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_activation_7eb1e36e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_activation_7eb1e36e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_activation_7eb1e36e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_activation_7eb1e36e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.054-policy-expiry`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.054-policy-expiry.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_expiry_d8ce5c0b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_expiry_d8ce5c0b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_expiry_d8ce5c0b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_expiry_d8ce5c0b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.055-policy-enable-disable`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.055-policy-enable-disable.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_enable_disable_b280b079/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_enable_disable_b280b079.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_enable_disable_b280b079.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_enable_disable_b280b079.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.056-policy-inheritance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.056-policy-inheritance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_inheritance_3963e4f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_inheritance_3963e4f7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_inheritance_3963e4f7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_inheritance_3963e4f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.057-policy-composition`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.057-policy-composition.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_composition_61918f15/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_composition_61918f15.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_composition_61918f15.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_composition_61918f15.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.058-policy-conflict-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.058-policy-conflict-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_conflict_detection_12e51671/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_detection_12e51671.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_detection_12e51671.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_conflict_detection_12e51671.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.059-policy-conflict-resolution`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.059-policy-conflict-resolution.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_conflict_resolution_63fdd0d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_resolution_63fdd0d8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_resolution_63fdd0d8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_conflict_resolution_63fdd0d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.060-explicit-deny-semantics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.060-explicit-deny-semantics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/explicit_deny_semantics_23d02ea8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/explicit_deny_semantics_23d02ea8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/explicit_deny_semantics_23d02ea8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_explicit_deny_semantics_23d02ea8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.061-explicit-allow-semantics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.061-explicit-allow-semantics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/explicit_allow_semantics_26fcfeb4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/explicit_allow_semantics_26fcfeb4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/explicit_allow_semantics_26fcfeb4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_explicit_allow_semantics_26fcfeb4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.062-default-policy-semantics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.062-default-policy-semantics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/default_policy_semantics_14b45669/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/default_policy_semantics_14b45669.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/default_policy_semantics_14b45669.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_default_policy_semantics_14b45669.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.063-unknown-policy-semantics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.063-unknown-policy-semantics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/unknown_policy_semantics_19cc4b6d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/unknown_policy_semantics_19cc4b6d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/unknown_policy_semantics_19cc4b6d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_unknown_policy_semantics_19cc4b6d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.064-missing-context-semantics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.064-missing-context-semantics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/missing_context_semantics_37172764/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/missing_context_semantics_37172764.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/missing_context_semantics_37172764.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_missing_context_semantics_37172764.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.065-require-clarification-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.065-require-clarification-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_clarification_effect_6c4d19ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_clarification_effect_6c4d19ae.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_clarification_effect_6c4d19ae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_clarification_effect_6c4d19ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.066-require-justification-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.066-require-justification-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_justification_effect_82e3ca49/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_justification_effect_82e3ca49.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_justification_effect_82e3ca49.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_justification_effect_82e3ca49.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.067-require-confirmation-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.067-require-confirmation-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_confirmation_effect_8667bb91/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_confirmation_effect_8667bb91.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_confirmation_effect_8667bb91.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_confirmation_effect_8667bb91.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.068-require-authorization-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.068-require-authorization-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_authorization_effect_50c25372/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/require_authorization_effect_50c25372.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/require_authorization_effect_50c25372.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_require_authorization_effect_50c25372.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.069-require-stronger-authorization-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.069-require-stronger-authorization-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_stronger_authorization_effect_78b72e4c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/require_stronger_authorization_effect_78b72e4c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/require_stronger_authorization_effect_78b72e4c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_require_stronger_authorization_effect_78b72e4c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.070-require-advisory-review-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.070-require-advisory-review-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_advisory_review_effect_583db70e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_advisory_review_effect_583db70e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_advisory_review_effect_583db70e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_advisory_review_effect_583db70e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.071-restrict-scope-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.071-restrict-scope-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/restrict_scope_effect_6f5c52bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/restrict_scope_effect_6f5c52bf.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/restrict_scope_effect_6f5c52bf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_restrict_scope_effect_6f5c52bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.072-require-sandbox-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.072-require-sandbox-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_sandbox_effect_affe7ea1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_sandbox_effect_affe7ea1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_sandbox_effect_affe7ea1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_sandbox_effect_affe7ea1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.073-require-resource-limit-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.073-require-resource-limit-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_resource_limit_effect_fabdce8f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_resource_limit_effect_fabdce8f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_resource_limit_effect_fabdce8f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_resource_limit_effect_fabdce8f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.074-require-fresh-observation-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.074-require-fresh-observation-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_fresh_observation_effect_1823120e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/observability/require_fresh_observation_effect_1823120e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/observability/require_fresh_observation_effect_1823120e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/observability/test_require_fresh_observation_effect_1823120e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.075-require-rollback-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.075-require-rollback-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_rollback_effect_ea4d5532/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/require_rollback_effect_ea4d5532.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/require_rollback_effect_ea4d5532.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_require_rollback_effect_ea4d5532.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.076-require-verification-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.076-require-verification-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_verification_effect_20edb393/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/require_verification_effect_20edb393.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/require_verification_effect_20edb393.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_require_verification_effect_20edb393.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.077-require-operator-presence-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.077-require-operator-presence-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_operator_presence_effect_1e2a789b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_operator_presence_effect_1e2a789b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_operator_presence_effect_1e2a789b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_operator_presence_effect_1e2a789b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.078-require-maintenance-window-effect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.078-require-maintenance-window-effect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/require_maintenance_window_effect_f37757db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/require_maintenance_window_effect_f37757db.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/require_maintenance_window_effect_f37757db.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_require_maintenance_window_effect_f37757db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.079-policy-decision-schema`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.079-policy-decision-schema.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_schema_785dbb9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_schema_785dbb9b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_schema_785dbb9b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_schema_785dbb9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.080-policy-decision-provenance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.080-policy-decision-provenance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_provenance_a645cdc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_provenance_a645cdc3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_provenance_a645cdc3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_provenance_a645cdc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.081-policy-decision-explanation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.081-policy-decision-explanation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_explanation_cade51a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_explanation_cade51a3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_explanation_cade51a3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_explanation_cade51a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.082-policy-decision-scope-binding`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.082-policy-decision-scope-binding.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_scope_binding_bb716a21/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_scope_binding_bb716a21.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_scope_binding_bb716a21.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_scope_binding_bb716a21.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.083-policy-decision-plan-binding`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.083-policy-decision-plan-binding.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_plan_binding_4744884c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_plan_binding_4744884c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_plan_binding_4744884c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_plan_binding_4744884c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.084-policy-decision-target-binding`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.084-policy-decision-target-binding.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_target_binding_b7f8515b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_target_binding_b7f8515b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_target_binding_b7f8515b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_target_binding_b7f8515b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.085-policy-decision-requester-binding`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.085-policy-decision-requester-binding.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_requester_binding_69c05574/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_requester_binding_69c05574.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_requester_binding_69c05574.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_requester_binding_69c05574.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.086-policy-decision-destination-binding`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.086-policy-decision-destination-binding.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_destination_binding_d55a191a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_destination_binding_d55a191a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_destination_binding_d55a191a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_destination_binding_d55a191a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.087-policy-decision-freshness`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.087-policy-decision-freshness.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_freshness_5a5f16f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_freshness_5a5f16f9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_freshness_5a5f16f9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_freshness_5a5f16f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.088-policy-decision-expiry`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.088-policy-decision-expiry.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_expiry_6d0af77c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_expiry_6d0af77c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_expiry_6d0af77c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_expiry_6d0af77c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.089-policy-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.089-policy-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_invalidation_481ab7a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_invalidation_481ab7a9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_invalidation_481ab7a9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_invalidation_481ab7a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.090-policy-re-evaluation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.090-policy-re-evaluation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_re_evaluation_49dc290a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_re_evaluation_49dc290a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_re_evaluation_49dc290a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_re_evaluation_49dc290a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.091-material-plan-change-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.091-material-plan-change-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/material_plan_change_invalidation_ac4ae3fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/material_plan_change_invalidation_ac4ae3fe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/material_plan_change_invalidation_ac4ae3fe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_material_plan_change_invalidation_ac4ae3fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.092-material-context-change-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.092-material-context-change-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/material_context_change_invalidation_1f879925/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/material_context_change_invalidation_1f879925.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/material_context_change_invalidation_1f879925.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_material_context_change_invalidation_1f879925.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.093-target-change-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.093-target-change-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/target_change_invalidation_755abf44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/target_change_invalidation_755abf44.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/target_change_invalidation_755abf44.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_target_change_invalidation_755abf44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.094-destination-change-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.094-destination-change-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/destination_change_invalidation_e76fc775/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/destination_change_invalidation_e76fc775.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/destination_change_invalidation_e76fc775.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_destination_change_invalidation_e76fc775.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.095-requester-change-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.095-requester-change-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/requester_change_invalidation_0f8d3376/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/requester_change_invalidation_0f8d3376.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/requester_change_invalidation_0f8d3376.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_requester_change_invalidation_0f8d3376.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.096-state-drift-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.096-state-drift-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/state_drift_invalidation_2ded1f52/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/lifecycle/state_drift_invalidation_2ded1f52.hpp`, `src/runtime/os-task-policy-system/subtask_targets/lifecycle/state_drift_invalidation_2ded1f52.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/lifecycle/test_state_drift_invalidation_2ded1f52.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.097-contextual-policy-foundation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.097-contextual-policy-foundation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/contextual_policy_foundation_4e246f17/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/contextual_policy_foundation_4e246f17.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/contextual_policy_foundation_4e246f17.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_contextual_policy_foundation_4e246f17.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.098-phase-46-contextual-legitimacy-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.098-phase-46-contextual-legitimacy-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/contextual_legitimacy_integration_2820898e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/contextual_legitimacy_integration_2820898e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/contextual_legitimacy_integration_2820898e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_contextual_legitimacy_integration_2820898e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.099-current-state-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.099-current-state-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/current_state_policy_f6bd4a0c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/current_state_policy_f6bd4a0c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/current_state_policy_f6bd4a0c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_current_state_policy_f6bd4a0c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.100-system-health-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.100-system-health-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_health_policy_b28a7ee3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/system_health_policy_b28a7ee3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/system_health_policy_b28a7ee3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_system_health_policy_b28a7ee3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.101-active-project-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.101-active-project-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/active_project_policy_b879b0b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/active_project_policy_b879b0b1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/active_project_policy_b879b0b1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_active_project_policy_b879b0b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.102-active-workflow-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.102-active-workflow-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/active_workflow_policy_b2c2bab6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/active_workflow_policy_b2c2bab6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/active_workflow_policy_b2c2bab6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_active_workflow_policy_b2c2bab6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.103-recent-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.103-recent-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/recent_action_policy_1ff45611/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/recent_action_policy_1ff45611.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/recent_action_policy_1ff45611.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_recent_action_policy_1ff45611.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.104-known-service-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.104-known-service-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/known_service_policy_e38a488e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/known_service_policy_e38a488e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/known_service_policy_e38a488e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_known_service_policy_e38a488e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.105-known-endpoint-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.105-known-endpoint-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/known_endpoint_policy_07cb6db2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/known_endpoint_policy_07cb6db2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/known_endpoint_policy_07cb6db2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_known_endpoint_policy_07cb6db2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.106-known-data-flow-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.106-known-data-flow-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/known_data_flow_policy_a988c3bc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/known_data_flow_policy_a988c3bc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/known_data_flow_policy_a988c3bc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_known_data_flow_policy_a988c3bc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.107-maintenance-state-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.107-maintenance-state-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/maintenance_state_policy_7af4e539/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/maintenance_state_policy_7af4e539.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/maintenance_state_policy_7af4e539.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_maintenance_state_policy_7af4e539.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.108-time-window-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.108-time-window-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/time_window_policy_3d5ce188/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/time_window_policy_3d5ce188.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/time_window_policy_3d5ce188.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_time_window_policy_3d5ce188.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.109-location-independent-policy-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.109-location-independent-policy-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/location_independent_policy_boundary_a352d39c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/location_independent_policy_boundary_a352d39c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/location_independent_policy_boundary_a352d39c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_location_independent_policy_boundary_a352d39c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.110-session-context-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.110-session-context-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/session_context_policy_6f639210/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/session_context_policy_6f639210.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/session_context_policy_6f639210.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_session_context_policy_6f639210.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.111-interactive-versus-unattended-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.111-interactive-versus-unattended-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/interactive_versus_unattended_policy_8d1c9981/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/interactive_versus_unattended_policy_8d1c9981.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/interactive_versus_unattended_policy_8d1c9981.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_interactive_versus_unattended_policy_8d1c9981.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.112-human-present-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.112-human-present-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/human_present_policy_995d5a9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/human_present_policy_995d5a9b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/human_present_policy_995d5a9b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_human_present_policy_995d5a9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.113-background-automation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.113-background-automation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/background_automation_policy_86827b7f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/background_automation_policy_86827b7f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/background_automation_policy_86827b7f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_background_automation_policy_86827b7f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.114-capability-policy-foundation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.114-capability-policy-foundation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/capability_policy_foundation_87df3b5c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/capability_policy_foundation_87df3b5c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/capability_policy_foundation_87df3b5c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_capability_policy_foundation_87df3b5c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.115-capability-allowlist`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.115-capability-allowlist.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/capability_allowlist_19d481b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/capability_allowlist_19d481b4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/capability_allowlist_19d481b4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_capability_allowlist_19d481b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.116-capability-denylist`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.116-capability-denylist.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/capability_denylist_fa23eb9a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/capability_denylist_fa23eb9a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/capability_denylist_fa23eb9a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_capability_denylist_fa23eb9a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.117-capability-combination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.117-capability-combination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/capability_combination_policy_2cffc658/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/capability_combination_policy_2cffc658.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/capability_combination_policy_2cffc658.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_capability_combination_policy_2cffc658.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.118-cross-domain-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.118-cross-domain-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cross_domain_capability_policy_d2b3f89b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cross_domain_capability_policy_d2b3f89b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cross_domain_capability_policy_d2b3f89b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cross_domain_capability_policy_d2b3f89b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.119-privilege-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.119-privilege-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/privilege_capability_policy_f8509173/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/privilege_capability_policy_f8509173.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/privilege_capability_policy_f8509173.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_privilege_capability_policy_f8509173.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.120-persistence-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.120-persistence-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/persistence_capability_policy_127bbcc7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/persistence_capability_policy_127bbcc7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/persistence_capability_policy_127bbcc7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_persistence_capability_policy_127bbcc7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.121-network-listener-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.121-network-listener-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/network_listener_capability_policy_6af89fc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/network_listener_capability_policy_6af89fc3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/network_listener_capability_policy_6af89fc3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_network_listener_capability_policy_6af89fc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.122-network-egress-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.122-network-egress-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/network_egress_capability_policy_d2a8ef40/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/network_egress_capability_policy_d2a8ef40.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/network_egress_capability_policy_d2a8ef40.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_network_egress_capability_policy_d2a8ef40.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.123-data-access-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.123-data-access-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/data_access_capability_policy_05b145ff/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/data_access_capability_policy_05b145ff.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/data_access_capability_policy_05b145ff.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_data_access_capability_policy_05b145ff.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.124-sensitive-data-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.124-sensitive-data-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/sensitive_data_capability_policy_573e1908/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/sensitive_data_capability_policy_573e1908.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/sensitive_data_capability_policy_573e1908.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_sensitive_data_capability_policy_573e1908.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.125-credential-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.125-credential-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/credential_capability_policy_ab13d6ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/credential_capability_policy_ab13d6ec.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/credential_capability_policy_ab13d6ec.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_credential_capability_policy_ab13d6ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.126-secret-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.126-secret-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/secret_capability_policy_d5b7572e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/secret_capability_policy_d5b7572e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/secret_capability_policy_d5b7572e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_secret_capability_policy_d5b7572e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.127-process-creation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.127-process-creation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/process_creation_capability_policy_dd54281e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/process_creation_capability_policy_dd54281e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/process_creation_capability_policy_dd54281e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_process_creation_capability_policy_dd54281e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.128-resource-amplification-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.128-resource-amplification-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/resource_amplification_capability_policy_bbcbd6f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/resource_amplification_capability_policy_bbcbd6f7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/resource_amplification_capability_policy_bbcbd6f7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_resource_amplification_capability_policy_bbcbd6f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.129-storage-mutation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.129-storage-mutation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/storage_mutation_capability_policy_71fa191c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/storage_mutation_capability_policy_71fa191c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/storage_mutation_capability_policy_71fa191c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_storage_mutation_capability_policy_71fa191c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.130-boot-mutation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.130-boot-mutation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/boot_mutation_capability_policy_0cc5dbed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/boot_mutation_capability_policy_0cc5dbed.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/boot_mutation_capability_policy_0cc5dbed.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_boot_mutation_capability_policy_0cc5dbed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.131-security-control-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.131-security-control-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/security_control_capability_policy_3f5256d3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/security_control_capability_policy_3f5256d3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/security_control_capability_policy_3f5256d3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_security_control_capability_policy_3f5256d3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.132-identity-mutation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.132-identity-mutation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/identity_mutation_capability_policy_ffa021b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/identity_mutation_capability_policy_ffa021b1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/identity_mutation_capability_policy_ffa021b1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_identity_mutation_capability_policy_ffa021b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.133-package-mutation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.133-package-mutation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/package_mutation_capability_policy_9710a525/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/package_mutation_capability_policy_9710a525.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/package_mutation_capability_policy_9710a525.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_package_mutation_capability_policy_9710a525.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.134-service-mutation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.134-service-mutation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/service_mutation_capability_policy_1f7197bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/service_mutation_capability_policy_1f7197bf.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/service_mutation_capability_policy_1f7197bf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_service_mutation_capability_policy_1f7197bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.135-gpu-mutation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.135-gpu-mutation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gpu_mutation_capability_policy_adf8eebb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gpu_mutation_capability_policy_adf8eebb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gpu_mutation_capability_policy_adf8eebb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gpu_mutation_capability_policy_adf8eebb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.136-configuration-mutation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.136-configuration-mutation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/configuration_mutation_capability_policy_656069ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/configuration_mutation_capability_policy_656069ea.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/configuration_mutation_capability_policy_656069ea.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_configuration_mutation_capability_policy_656069ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.137-workflow-creation-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.137-workflow-creation-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_creation_capability_policy_c47a4334/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workflow_creation_capability_policy_c47a4334.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workflow_creation_capability_policy_c47a4334.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workflow_creation_capability_policy_c47a4334.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.138-scheduled-persistence-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.138-scheduled-persistence-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/scheduled_persistence_capability_policy_ac3d4482/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/scheduled_persistence_capability_policy_ac3d4482.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/scheduled_persistence_capability_policy_ac3d4482.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_scheduled_persistence_capability_policy_ac3d4482.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.139-data-flow-policy-foundation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.139-data-flow-policy-foundation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/data_flow_policy_foundation_68cc606c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/data_flow_policy_foundation_68cc606c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/data_flow_policy_foundation_68cc606c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_data_flow_policy_foundation_68cc606c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.140-data-source-model`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.140-data-source-model.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/data_source_model_2ad10b3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/data_source_model_2ad10b3a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/data_source_model_2ad10b3a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_data_source_model_2ad10b3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.141-data-sink-model`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.141-data-sink-model.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/data_sink_model_cee4c810/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/data_sink_model_cee4c810.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/data_sink_model_cee4c810.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_data_sink_model_cee4c810.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.142-data-classification-model`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.142-data-classification-model.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/data_classification_model_02264bda/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/data_classification_model_02264bda.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/data_classification_model_02264bda.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_data_classification_model_02264bda.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.143-destination-trust-model`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.143-destination-trust-model.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/destination_trust_model_b3772bc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/destination_trust_model_b3772bc3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/destination_trust_model_b3772bc3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_destination_trust_model_b3772bc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.144-local-destination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.144-local-destination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/local_destination_policy_b1d4b29f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/local_destination_policy_b1d4b29f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/local_destination_policy_b1d4b29f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_local_destination_policy_b1d4b29f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.145-lan-destination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.145-lan-destination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/lan_destination_policy_d1240e38/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/lan_destination_policy_d1240e38.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/lan_destination_policy_d1240e38.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_lan_destination_policy_d1240e38.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.146-known-remote-destination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.146-known-remote-destination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/known_remote_destination_policy_37f1c373/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/known_remote_destination_policy_37f1c373.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/known_remote_destination_policy_37f1c373.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_known_remote_destination_policy_37f1c373.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.147-unknown-remote-destination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.147-unknown-remote-destination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/unknown_remote_destination_policy_bb04abec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/unknown_remote_destination_policy_bb04abec.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/unknown_remote_destination_policy_bb04abec.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_unknown_remote_destination_policy_bb04abec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.148-sensitive-source-plus-egress-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.148-sensitive-source-plus-egress-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/sensitive_source_plus_egress_policy_a488a8eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/sensitive_source_plus_egress_policy_a488a8eb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/sensitive_source_plus_egress_policy_a488a8eb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_sensitive_source_plus_egress_policy_a488a8eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.149-secret-source-plus-egress-deny`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.149-secret-source-plus-egress-deny.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/secret_source_plus_egress_deny_73fde3d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/secret_source_plus_egress_deny_73fde3d4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/secret_source_plus_egress_deny_73fde3d4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_secret_source_plus_egress_deny_73fde3d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.150-logs-plus-external-destination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.150-logs-plus-external-destination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/logs_plus_external_destination_policy_8483d4e2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/logs_plus_external_destination_policy_8483d4e2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/logs_plus_external_destination_policy_8483d4e2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_logs_plus_external_destination_policy_8483d4e2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.151-history-plus-external-destination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.151-history-plus-external-destination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/history_plus_external_destination_policy_f9158eea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/history_plus_external_destination_policy_f9158eea.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/history_plus_external_destination_policy_f9158eea.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_history_plus_external_destination_policy_f9158eea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.152-environment-plus-external-destination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.152-environment-plus-external-destination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/environment_plus_external_destination_policy_bdfec958/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/environment_plus_external_destination_policy_bdfec958.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/environment_plus_external_destination_policy_bdfec958.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_environment_plus_external_destination_policy_bdfec958.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.153-home-data-exposure-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.153-home-data-exposure-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/home_data_exposure_policy_79b4027b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/home_data_exposure_policy_79b4027b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/home_data_exposure_policy_79b4027b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_home_data_exposure_policy_79b4027b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.154-bulk-data-export-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.154-bulk-data-export-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/bulk_data_export_policy_c86d62c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/bulk_data_export_policy_c86d62c4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/bulk_data_export_policy_c86d62c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_bulk_data_export_policy_c86d62c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.155-persistence-plus-egress-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.155-persistence-plus-egress-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/persistence_plus_egress_policy_7b2c747f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/persistence_plus_egress_policy_7b2c747f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/persistence_plus_egress_policy_7b2c747f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_persistence_plus_egress_policy_7b2c747f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.156-privilege-plus-persistence-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.156-privilege-plus-persistence-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/privilege_plus_persistence_policy_11d08df0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/privilege_plus_persistence_policy_11d08df0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/privilege_plus_persistence_policy_11d08df0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_privilege_plus_persistence_policy_11d08df0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.157-privilege-plus-egress-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.157-privilege-plus-egress-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/privilege_plus_egress_policy_8374d069/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/privilege_plus_egress_policy_8374d069.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/privilege_plus_egress_policy_8374d069.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_privilege_plus_egress_policy_8374d069.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.158-cross-step-data-flow-composition`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.158-cross-step-data-flow-composition.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cross_step_data_flow_composition_f9e6ba29/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/cross_step_data_flow_composition_f9e6ba29.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/cross_step_data_flow_composition_f9e6ba29.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_cross_step_data_flow_composition_f9e6ba29.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.159-cross-task-data-flow-composition`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.159-cross-task-data-flow-composition.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cross_task_data_flow_composition_00272a00/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/cross_task_data_flow_composition_00272a00.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/cross_task_data_flow_composition_00272a00.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_cross_task_data_flow_composition_00272a00.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.160-task-splitting-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.160-task-splitting-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_splitting_detection_280e54de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_splitting_detection_280e54de.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_splitting_detection_280e54de.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_splitting_detection_280e54de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.161-policy-evasion-by-decomposition`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.161-policy-evasion-by-decomposition.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_evasion_by_decomposition_f3d54281/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_evasion_by_decomposition_f3d54281.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_evasion_by_decomposition_f3d54281.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_evasion_by_decomposition_f3d54281.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.162-resource-policy-foundation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.162-resource-policy-foundation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/resource_policy_foundation_25f35cc0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/resource_policy_foundation_25f35cc0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/resource_policy_foundation_25f35cc0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_resource_policy_foundation_25f35cc0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.163-cpu-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.163-cpu-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cpu_budget_policy_f767d134/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cpu_budget_policy_f767d134.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cpu_budget_policy_f767d134.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cpu_budget_policy_f767d134.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.164-memory-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.164-memory-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/memory_budget_policy_b32a271e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/memory_budget_policy_b32a271e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/memory_budget_policy_b32a271e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_memory_budget_policy_b32a271e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.165-gpu-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.165-gpu-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gpu_budget_policy_c031724d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gpu_budget_policy_c031724d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gpu_budget_policy_c031724d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gpu_budget_policy_c031724d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.166-vram-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.166-vram-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/vram_budget_policy_16ca0ccc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/vram_budget_policy_16ca0ccc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/vram_budget_policy_16ca0ccc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_vram_budget_policy_16ca0ccc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.167-storage-i-o-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.167-storage-i-o-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/storage_i_o_budget_policy_461990e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/storage_i_o_budget_policy_461990e3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/storage_i_o_budget_policy_461990e3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_storage_i_o_budget_policy_461990e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.168-network-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.168-network-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/network_budget_policy_7884b5c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/network_budget_policy_7884b5c4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/network_budget_policy_7884b5c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_network_budget_policy_7884b5c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.169-process-count-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.169-process-count-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/process_count_budget_policy_deb5d361/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/process_count_budget_policy_deb5d361.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/process_count_budget_policy_deb5d361.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_process_count_budget_policy_deb5d361.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.170-execution-time-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.170-execution-time-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/execution_time_budget_policy_1b5572cc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/execution_time_budget_policy_1b5572cc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/execution_time_budget_policy_1b5572cc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_execution_time_budget_policy_1b5572cc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.171-output-size-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.171-output-size-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/output_size_budget_policy_9daad3f6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/output_size_budget_policy_9daad3f6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/output_size_budget_policy_9daad3f6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_output_size_budget_policy_9daad3f6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.172-concurrency-budget-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.172-concurrency-budget-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/concurrency_budget_policy_78c9e8f6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/concurrency_budget_policy_78c9e8f6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/concurrency_budget_policy_78c9e8f6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_concurrency_budget_policy_78c9e8f6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.173-rate-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.173-rate-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/rate_policy_7d8e7803/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/rate_policy_7d8e7803.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/rate_policy_7d8e7803.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_rate_policy_7d8e7803.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.174-per-user-task-budget`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.174-per-user-task-budget.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/per_user_task_budget_4f41bbd3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/per_user_task_budget_4f41bbd3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/per_user_task_budget_4f41bbd3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_per_user_task_budget_4f41bbd3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.175-per-session-task-budget`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.175-per-session-task-budget.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/per_session_task_budget_c26c0b35/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/per_session_task_budget_c26c0b35.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/per_session_task_budget_c26c0b35.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_per_session_task_budget_c26c0b35.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.176-per-workflow-task-budget`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.176-per-workflow-task-budget.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/per_workflow_task_budget_083e5b60/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/per_workflow_task_budget_083e5b60.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/per_workflow_task_budget_083e5b60.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_per_workflow_task_budget_083e5b60.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.177-per-capability-task-budget`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.177-per-capability-task-budget.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/per_capability_task_budget_45a65395/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/per_capability_task_budget_45a65395.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/per_capability_task_budget_45a65395.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_per_capability_task_budget_45a65395.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.178-resource-exhaustion-prevention`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.178-resource-exhaustion-prevention.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/resource_exhaustion_prevention_d3d83865/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/resource_exhaustion_prevention_d3d83865.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/resource_exhaustion_prevention_d3d83865.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_resource_exhaustion_prevention_d3d83865.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.179-fork-bomb-effect-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.179-fork-bomb-effect-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/fork_bomb_effect_policy_813c2e7c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/fork_bomb_effect_policy_813c2e7c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/fork_bomb_effect_policy_813c2e7c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_fork_bomb_effect_policy_813c2e7c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.180-unbounded-recursion-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.180-unbounded-recursion-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/unbounded_recursion_policy_cd86eaae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/unbounded_recursion_policy_cd86eaae.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/unbounded_recursion_policy_cd86eaae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_unbounded_recursion_policy_cd86eaae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.181-unbounded-retry-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.181-unbounded-retry-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/unbounded_retry_policy_ce190175/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/unbounded_retry_policy_ce190175.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/unbounded_retry_policy_ce190175.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_unbounded_retry_policy_ce190175.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.182-unbounded-fan-out-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.182-unbounded-fan-out-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/unbounded_fan_out_policy_66a97c6e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/unbounded_fan_out_policy_66a97c6e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/unbounded_fan_out_policy_66a97c6e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_unbounded_fan_out_policy_66a97c6e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.183-phase-29-workload-policy-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.183-phase-29-workload-policy-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workload_policy_integration_f32d9ac0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workload_policy_integration_f32d9ac0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workload_policy_integration_f32d9ac0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workload_policy_integration_f32d9ac0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.184-phase-30-resource-policy-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.184-phase-30-resource-policy-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/resource_policy_integration_0c2050c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/resource_policy_integration_0c2050c9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/resource_policy_integration_0c2050c9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_resource_policy_integration_0c2050c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.185-protected-resource-policy-foundation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.185-protected-resource-policy-foundation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/protected_resource_policy_foundation_cc63b5d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/protected_resource_policy_foundation_cc63b5d5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/protected_resource_policy_foundation_cc63b5d5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_protected_resource_policy_foundation_cc63b5d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.186-boot-protection-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.186-boot-protection-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/boot_protection_policy_03626cc0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/boot_protection_policy_03626cc0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/boot_protection_policy_03626cc0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_boot_protection_policy_03626cc0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.187-root-filesystem-protection-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.187-root-filesystem-protection-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/root_filesystem_protection_policy_8127dd44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/root_filesystem_protection_policy_8127dd44.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/root_filesystem_protection_policy_8127dd44.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_root_filesystem_protection_policy_8127dd44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.188-home-protection-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.188-home-protection-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/home_protection_policy_9a71497f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/home_protection_policy_9a71497f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/home_protection_policy_9a71497f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_home_protection_policy_9a71497f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.189-storage-integrity-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.189-storage-integrity-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/storage_integrity_policy_38023e36/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/storage_integrity_policy_38023e36.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/storage_integrity_policy_38023e36.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_storage_integrity_policy_38023e36.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.190-network-maintenance-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.190-network-maintenance-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/network_maintenance_policy_ca86e798/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/network_maintenance_policy_ca86e798.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/network_maintenance_policy_ca86e798.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_network_maintenance_policy_ca86e798.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.191-ssh-maintenance-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.191-ssh-maintenance-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/ssh_maintenance_policy_e04963c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/ssh_maintenance_policy_e04963c4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/ssh_maintenance_policy_e04963c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_ssh_maintenance_policy_e04963c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.192-graphical-session-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.192-graphical-session-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/graphical_session_policy_991956ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/graphical_session_policy_991956ca.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/graphical_session_policy_991956ca.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_graphical_session_policy_991956ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.193-security-control-protection-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.193-security-control-protection-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/security_control_protection_policy_3819c7b6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/security_control_protection_policy_3819c7b6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/security_control_protection_policy_3819c7b6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_security_control_protection_policy_3819c7b6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.194-package-trust-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.194-package-trust-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/package_trust_policy_9f822e3d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/package_trust_policy_9f822e3d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/package_trust_policy_9f822e3d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_package_trust_policy_9f822e3d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.195-identity-access-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.195-identity-access-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/identity_access_policy_59100712/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/identity_access_policy_59100712.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/identity_access_policy_59100712.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_identity_access_policy_59100712.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.196-rebuntu-control-plane-protection-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.196-rebuntu-control-plane-protection-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/rebuntu_control_plane_protection_policy_91ea85a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/rebuntu_control_plane_protection_policy_91ea85a8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/rebuntu_control_plane_protection_policy_91ea85a8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_rebuntu_control_plane_protection_policy_91ea85a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.197-phase-37-secret-protection-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.197-phase-37-secret-protection-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/secret_protection_policy_b4cfb41a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/secret_protection_policy_b4cfb41a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/secret_protection_policy_b4cfb41a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_secret_protection_policy_b4cfb41a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.198-emergency-override-model`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.198-emergency-override-model.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/emergency_override_model_8bfe14c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/emergency_override_model_8bfe14c5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/emergency_override_model_8bfe14c5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_emergency_override_model_8bfe14c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.199-break-glass-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.199-break-glass-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/break_glass_policy_e34d3502/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/break_glass_policy_e34d3502.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/break_glass_policy_e34d3502.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_break_glass_policy_e34d3502.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.200-break-glass-authorization`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.200-break-glass-authorization.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/break_glass_authorization_16552ad1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/break_glass_authorization_16552ad1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/break_glass_authorization_16552ad1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_break_glass_authorization_16552ad1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.201-break-glass-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.201-break-glass-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/break_glass_audit_59dcd2cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/break_glass_audit_59dcd2cf.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/break_glass_audit_59dcd2cf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_break_glass_audit_59dcd2cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.202-break-glass-expiry`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.202-break-glass-expiry.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/break_glass_expiry_7af5d707/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/break_glass_expiry_7af5d707.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/break_glass_expiry_7af5d707.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_break_glass_expiry_7af5d707.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.203-break-glass-scope`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.203-break-glass-scope.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/break_glass_scope_451a8cae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/break_glass_scope_451a8cae.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/break_glass_scope_451a8cae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_break_glass_scope_451a8cae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.204-break-glass-recovery`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.204-break-glass-recovery.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/break_glass_recovery_dacf68a5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/break_glass_recovery_dacf68a5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/break_glass_recovery_dacf68a5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_break_glass_recovery_dacf68a5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.205-no-semantic-break-glass-authority`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.205-no-semantic-break-glass-authority.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/no_semantic_break_glass_authority_24d5f530/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/no_semantic_break_glass_authority_24d5f530.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/no_semantic_break_glass_authority_24d5f530.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_no_semantic_break_glass_authority_24d5f530.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.206-delegation-policy-foundation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.206-delegation-policy-foundation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/delegation_policy_foundation_63419153/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/delegation_policy_foundation_63419153.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/delegation_policy_foundation_63419153.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_delegation_policy_foundation_63419153.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.207-human-delegation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.207-human-delegation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/human_delegation_d491807a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/human_delegation_d491807a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/human_delegation_d491807a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_human_delegation_d491807a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.208-ask-delegation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.208-ask-delegation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/ask_delegation_42ecc39d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/ask_delegation_42ecc39d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/ask_delegation_42ecc39d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_ask_delegation_42ecc39d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.209-phase-41-workflow-delegation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.209-phase-41-workflow-delegation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_delegation_d1ef4dc6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_delegation_d1ef4dc6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_delegation_d1ef4dc6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_workflow_delegation_d1ef4dc6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.210-automation-delegation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.210-automation-delegation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/automation_delegation_ac272f6d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/automation_delegation_ac272f6d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/automation_delegation_ac272f6d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_automation_delegation_ac272f6d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.211-service-delegation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.211-service-delegation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/service_delegation_29bf1742/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/service_delegation_29bf1742.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/service_delegation_29bf1742.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_service_delegation_29bf1742.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.212-coding-agent-delegation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.212-coding-agent-delegation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/coding_agent_delegation_19caa856/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/coding_agent_delegation_19caa856.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/coding_agent_delegation_19caa856.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_coding_agent_delegation_19caa856.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.213-bitnet-origin-handling`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.213-bitnet-origin-handling.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/bitnet_origin_handling_5b50f687/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/bitnet_origin_handling_5b50f687.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/bitnet_origin_handling_5b50f687.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_bitnet_origin_handling_5b50f687.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.214-gordon-origin-handling`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.214-gordon-origin-handling.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gordon_origin_handling_263f48ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/gordon_origin_handling_263f48ba.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/gordon_origin_handling_263f48ba.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_gordon_origin_handling_263f48ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.215-semantic-provider-origin-handling`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.215-semantic-provider-origin-handling.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/semantic_provider_origin_handling_8e54940b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/semantic_provider_origin_handling_8e54940b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/semantic_provider_origin_handling_8e54940b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_semantic_provider_origin_handling_8e54940b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.216-delegated-authority-narrowing`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.216-delegated-authority-narrowing.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/delegated_authority_narrowing_7b6ddec8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/delegated_authority_narrowing_7b6ddec8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/delegated_authority_narrowing_7b6ddec8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_delegated_authority_narrowing_7b6ddec8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.217-no-authority-amplification`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.217-no-authority-amplification.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/no_authority_amplification_cf8f65b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/no_authority_amplification_cf8f65b7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/no_authority_amplification_cf8f65b7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_no_authority_amplification_cf8f65b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.218-delegation-depth`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.218-delegation-depth.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/delegation_depth_b03e22c7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_depth_b03e22c7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_depth_b03e22c7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_delegation_depth_b03e22c7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.219-delegation-expiry`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.219-delegation-expiry.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/delegation_expiry_32d1fea9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_expiry_32d1fea9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_expiry_32d1fea9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_delegation_expiry_32d1fea9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.220-delegation-revocation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.220-delegation-revocation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/delegation_revocation_8f84dd43/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_revocation_8f84dd43.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_revocation_8f84dd43.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_delegation_revocation_8f84dd43.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.221-delegation-provenance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.221-delegation-provenance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/delegation_provenance_d7e7529f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_provenance_d7e7529f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/delegation_provenance_d7e7529f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_delegation_provenance_d7e7529f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.222-authority-laundering-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.222-authority-laundering-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/authority_laundering_detection_02c7a987/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/authority_laundering_detection_02c7a987.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/authority_laundering_detection_02c7a987.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_authority_laundering_detection_02c7a987.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.223-context-laundering-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.223-context-laundering-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/context_laundering_detection_338573a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/context_laundering_detection_338573a2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/context_laundering_detection_338573a2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_context_laundering_detection_338573a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.224-task-laundering-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.224-task-laundering-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_laundering_detection_823f9ea4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_laundering_detection_823f9ea4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_laundering_detection_823f9ea4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_laundering_detection_823f9ea4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.225-phase-45-authorization-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.225-phase-45-authorization-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/authorization_integration_9ba8aa95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/authorization_integration_9ba8aa95.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/authorization_integration_9ba8aa95.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_authorization_integration_9ba8aa95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.226-phase-45-plan-policy-hook`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.226-phase-45-plan-policy-hook.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/plan_policy_hook_c0fe4ba9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/plan_policy_hook_c0fe4ba9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/plan_policy_hook_c0fe4ba9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_plan_policy_hook_c0fe4ba9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.227-pre-plan-policy-evaluation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.227-pre-plan-policy-evaluation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/pre_plan_policy_evaluation_154638b9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/pre_plan_policy_evaluation_154638b9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/pre_plan_policy_evaluation_154638b9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_pre_plan_policy_evaluation_154638b9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.228-post-plan-policy-evaluation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.228-post-plan-policy-evaluation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/post_plan_policy_evaluation_89d7315f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/post_plan_policy_evaluation_89d7315f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/post_plan_policy_evaluation_89d7315f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_post_plan_policy_evaluation_89d7315f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.229-pre-authorization-policy-evaluation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.229-pre-authorization-policy-evaluation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/pre_authorization_policy_evaluation_c9c5b185/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/pre_authorization_policy_evaluation_c9c5b185.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/pre_authorization_policy_evaluation_c9c5b185.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_pre_authorization_policy_evaluation_c9c5b185.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.230-pre-execution-policy-recheck`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.230-pre-execution-policy-recheck.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/pre_execution_policy_recheck_7f724e38/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/pre_execution_policy_recheck_7f724e38.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/pre_execution_policy_recheck_7f724e38.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_pre_execution_policy_recheck_7f724e38.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.231-post-execution-policy-recording`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.231-post-execution-policy-recording.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/post_execution_policy_recording_b8bc9605/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/post_execution_policy_recording_b8bc9605.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/post_execution_policy_recording_b8bc9605.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_post_execution_policy_recording_b8bc9605.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.232-verification-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.232-verification-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/verification_policy_2c02342c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/verification_policy_2c02342c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/verification_policy_2c02342c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_verification_policy_2c02342c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.233-rollback-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.233-rollback-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/rollback_policy_3f586f11/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/rollback_policy_3f586f11.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/rollback_policy_3f586f11.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_rollback_policy_3f586f11.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.234-compensation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.234-compensation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/compensation_policy_1c35fda7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/compensation_policy_1c35fda7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/compensation_policy_1c35fda7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_compensation_policy_1c35fda7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.235-phase-39-task-event-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.235-phase-39-task-event-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_event_integration_9e067cd7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/task_event_integration_9e067cd7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/task_event_integration_9e067cd7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_task_event_integration_9e067cd7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.236-phase-39-policy-event-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.236-phase-39-policy-event-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_event_integration_cd2d2c89/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_event_integration_cd2d2c89.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_event_integration_cd2d2c89.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_event_integration_cd2d2c89.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.237-phase-42-task-graph-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.237-phase-42-task-graph-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_graph_integration_b6a1827f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/task_graph_integration_b6a1827f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/task_graph_integration_b6a1827f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_task_graph_integration_b6a1827f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.238-phase-42-policy-relation-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.238-phase-42-policy-relation-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_relation_integration_efe3efc0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_relation_integration_efe3efc0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_relation_integration_efe3efc0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_relation_integration_efe3efc0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.239-phase-43-policy-explanation-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.239-phase-43-policy-explanation-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_explanation_integration_642a6b3d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_explanation_integration_642a6b3d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_explanation_integration_642a6b3d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_explanation_integration_642a6b3d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.240-phase-43-advisory-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.240-phase-43-advisory-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/advisory_integration_b882629d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/advisory_integration_b882629d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/advisory_integration_b882629d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_advisory_integration_b882629d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.241-phase-44-adaptive-task-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.241-phase-44-adaptive-task-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adaptive_task_policy_0a3b7dc8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/adaptive_task_policy_0a3b7dc8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/adaptive_task_policy_0a3b7dc8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_adaptive_task_policy_0a3b7dc8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.242-phase-46-ask-task-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.242-phase-46-ask-task-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/ask_task_policy_a6b167b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/ask_task_policy_a6b167b0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/ask_task_policy_a6b167b0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_ask_task_policy_a6b167b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.243-phase-40-command-task-mapping`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.243-phase-40-command-task-mapping.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/command_task_mapping_4f93affa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/execution/command_task_mapping_4f93affa.hpp`, `src/runtime/os-task-policy-system/subtask_targets/execution/command_task_mapping_4f93affa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/execution/test_command_task_mapping_4f93affa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.244-phase-41-workflow-task-mapping`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.244-phase-41-workflow-task-mapping.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_task_mapping_aa294939/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_task_mapping_aa294939.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_task_mapping_aa294939.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_workflow_task_mapping_aa294939.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.245-taskwarrior-provider-discovery`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.245-taskwarrior-provider-discovery.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_provider_discovery_2daf4ee9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/taskwarrior_provider_discovery_2daf4ee9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/taskwarrior_provider_discovery_2daf4ee9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_taskwarrior_provider_discovery_2daf4ee9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.246-taskwarrior-record-model`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.246-taskwarrior-record-model.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_record_model_79238e8e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/taskwarrior_record_model_79238e8e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/taskwarrior_record_model_79238e8e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_taskwarrior_record_model_79238e8e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.247-taskwarrior-human-task-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.247-taskwarrior-human-task-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_human_task_boundary_a5d2416a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_human_task_boundary_a5d2416a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_human_task_boundary_a5d2416a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_taskwarrior_human_task_boundary_a5d2416a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.248-taskwarrior-os-task-bridge`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.248-taskwarrior-os-task-bridge.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_os_task_bridge_7d03f943/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/taskwarrior_os_task_bridge_7d03f943.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/taskwarrior_os_task_bridge_7d03f943.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_taskwarrior_os_task_bridge_7d03f943.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.249-taskwarrior-executable-task-opt-in`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.249-taskwarrior-executable-task-opt-in.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_executable_task_opt_in_7885c99c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/execution/taskwarrior_executable_task_opt_in_7885c99c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/execution/taskwarrior_executable_task_opt_in_7885c99c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/execution/test_taskwarrior_executable_task_opt_in_7885c99c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.250-taskwarrior-project-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.250-taskwarrior-project-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_project_policy_6af7690e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_project_policy_6af7690e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_project_policy_6af7690e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_taskwarrior_project_policy_6af7690e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.251-taskwarrior-tag-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.251-taskwarrior-tag-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_tag_policy_86f20fed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_tag_policy_86f20fed.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_tag_policy_86f20fed.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_taskwarrior_tag_policy_86f20fed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.252-taskwarrior-priority-mapping`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.252-taskwarrior-priority-mapping.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_priority_mapping_4f6870b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_priority_mapping_4f6870b5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_priority_mapping_4f6870b5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_taskwarrior_priority_mapping_4f6870b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.253-taskwarrior-due-date-mapping`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.253-taskwarrior-due-date-mapping.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_due_date_mapping_8cf511f3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_due_date_mapping_8cf511f3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_due_date_mapping_8cf511f3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_taskwarrior_due_date_mapping_8cf511f3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.254-taskwarrior-recurring-task-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.254-taskwarrior-recurring-task-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_recurring_task_boundary_3741695d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_recurring_task_boundary_3741695d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/taskwarrior_recurring_task_boundary_3741695d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_taskwarrior_recurring_task_boundary_3741695d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.255-taskwarrior-natural-language-integration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.255-taskwarrior-natural-language-integration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_natural_language_integration_e6cee1a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/integration/taskwarrior_natural_language_integration_e6cee1a2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/integration/taskwarrior_natural_language_integration_e6cee1a2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/integration/test_taskwarrior_natural_language_integration_e6cee1a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.256-taskwarrior-bulk-mutation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.256-taskwarrior-bulk-mutation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_bulk_mutation_policy_3cd989db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_bulk_mutation_policy_3cd989db.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_bulk_mutation_policy_3cd989db.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_taskwarrior_bulk_mutation_policy_3cd989db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.257-taskwarrior-deletion-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.257-taskwarrior-deletion-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_deletion_policy_8566b3c0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_deletion_policy_8566b3c0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_deletion_policy_8566b3c0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_taskwarrior_deletion_policy_8566b3c0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.258-taskwarrior-completion-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.258-taskwarrior-completion-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_completion_policy_def39c33/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_completion_policy_def39c33.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_completion_policy_def39c33.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_taskwarrior_completion_policy_def39c33.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.259-task-versus-workflow-distinction`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.259-task-versus-workflow-distinction.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_versus_workflow_distinction_3f4dcbf4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_versus_workflow_distinction_3f4dcbf4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_versus_workflow_distinction_3f4dcbf4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_versus_workflow_distinction_3f4dcbf4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.260-task-versus-command-distinction`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.260-task-versus-command-distinction.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_versus_command_distinction_c4abac95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/execution/task_versus_command_distinction_c4abac95.hpp`, `src/runtime/os-task-policy-system/subtask_targets/execution/task_versus_command_distinction_c4abac95.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/execution/test_task_versus_command_distinction_c4abac95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.261-task-versus-automation-distinction`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.261-task-versus-automation-distinction.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_versus_automation_distinction_2c9af424/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_versus_automation_distinction_2c9af424.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_versus_automation_distinction_2c9af424.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_versus_automation_distinction_2c9af424.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.262-task-versus-recommendation-distinction`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.262-task-versus-recommendation-distinction.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_versus_recommendation_distinction_b683c277/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/task_versus_recommendation_distinction_b683c277.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/task_versus_recommendation_distinction_b683c277.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_task_versus_recommendation_distinction_b683c277.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.263-task-versus-policy-distinction`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.263-task-versus-policy-distinction.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_versus_policy_distinction_6afad400/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/task_versus_policy_distinction_6afad400.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/task_versus_policy_distinction_6afad400.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_task_versus_policy_distinction_6afad400.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.264-policy-language-foundation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.264-policy-language-foundation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_language_foundation_91797bdc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_language_foundation_91797bdc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_language_foundation_91797bdc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_language_foundation_91797bdc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.265-typed-policy-schema`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.265-typed-policy-schema.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/typed_policy_schema_831345d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/typed_policy_schema_831345d5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/typed_policy_schema_831345d5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_typed_policy_schema_831345d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.266-policy-parser`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.266-policy-parser.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_parser_d07af0bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_parser_d07af0bb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_parser_d07af0bb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_parser_d07af0bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.267-policy-schema-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.267-policy-schema-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_schema_validation_a41c217b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_schema_validation_a41c217b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_schema_validation_a41c217b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_schema_validation_a41c217b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.268-policy-static-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.268-policy-static-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_static_validation_f67be9b6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_static_validation_f67be9b6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_static_validation_f67be9b6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_static_validation_f67be9b6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.269-policy-semantic-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.269-policy-semantic-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_semantic_validation_05ccbe64/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_semantic_validation_05ccbe64.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_semantic_validation_05ccbe64.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_semantic_validation_05ccbe64.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.270-policy-reference-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.270-policy-reference-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_reference_validation_50ab8c5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_reference_validation_50ab8c5d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_reference_validation_50ab8c5d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_reference_validation_50ab8c5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.271-policy-capability-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.271-policy-capability-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_capability_validation_914d91ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_capability_validation_914d91ae.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_capability_validation_914d91ae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_capability_validation_914d91ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.272-policy-target-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.272-policy-target-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_target_validation_a0983464/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_target_validation_a0983464.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_target_validation_a0983464.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_target_validation_a0983464.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.273-policy-conflict-linting`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.273-policy-conflict-linting.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_conflict_linting_502a5962/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_linting_502a5962.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_linting_502a5962.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_conflict_linting_502a5962.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.274-policy-unreachable-rule-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.274-policy-unreachable-rule-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_unreachable_rule_detection_441389c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_unreachable_rule_detection_441389c9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_unreachable_rule_detection_441389c9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_unreachable_rule_detection_441389c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.275-policy-shadowing-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.275-policy-shadowing-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_shadowing_detection_8d0bef18/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_shadowing_detection_8d0bef18.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_shadowing_detection_8d0bef18.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_shadowing_detection_8d0bef18.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.276-policy-redundancy-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.276-policy-redundancy-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_redundancy_detection_28624cf0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_redundancy_detection_28624cf0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_redundancy_detection_28624cf0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_redundancy_detection_28624cf0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.277-policy-unsafe-default-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.277-policy-unsafe-default-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_unsafe_default_detection_683e8dbe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_unsafe_default_detection_683e8dbe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_unsafe_default_detection_683e8dbe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_unsafe_default_detection_683e8dbe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.278-policy-executable-code-prohibition`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.278-policy-executable-code-prohibition.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_executable_code_prohibition_c63917ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_executable_code_prohibition_c63917ee.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_executable_code_prohibition_c63917ee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_executable_code_prohibition_c63917ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.279-policy-shell-execution-prohibition`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.279-policy-shell-execution-prohibition.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_shell_execution_prohibition_8daec536/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_shell_execution_prohibition_8daec536.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_shell_execution_prohibition_8daec536.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_shell_execution_prohibition_8daec536.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.280-policy-include-import-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.280-policy-include-import-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_include_import_boundary_5c27fe45/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_include_import_boundary_5c27fe45.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_include_import_boundary_5c27fe45.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_include_import_boundary_5c27fe45.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.281-policy-variable-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.281-policy-variable-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_variable_boundary_d9d1f09a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_variable_boundary_d9d1f09a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_variable_boundary_d9d1f09a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_variable_boundary_d9d1f09a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.282-policy-parameterization`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.282-policy-parameterization.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_parameterization_41f1cfc6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_parameterization_41f1cfc6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_parameterization_41f1cfc6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_parameterization_41f1cfc6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.283-policy-templates`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.283-policy-templates.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_templates_90d12344/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_templates_90d12344.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_templates_90d12344.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_templates_90d12344.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.284-policy-profiles`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.284-policy-profiles.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_profiles_349b171e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_profiles_349b171e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_profiles_349b171e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_profiles_349b171e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.285-system-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.285-system-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_policy_3f4ef66e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/system_policy_3f4ef66e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/system_policy_3f4ef66e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_system_policy_3f4ef66e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.286-user-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.286-user-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/user_policy_07e10cc2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/user_policy_07e10cc2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/user_policy_07e10cc2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_user_policy_07e10cc2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.287-session-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.287-session-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/session_policy_02724ae9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/session_policy_02724ae9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/session_policy_02724ae9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_session_policy_02724ae9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.288-project-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.288-project-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/project_policy_2f80a2eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/project_policy_2f80a2eb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/project_policy_2f80a2eb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_project_policy_2f80a2eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.289-workflow-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.289-workflow-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_policy_357ba664/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workflow_policy_357ba664.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workflow_policy_357ba664.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workflow_policy_357ba664.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.290-service-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.290-service-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/service_policy_c9f7a979/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/service_policy_c9f7a979.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/service_policy_c9f7a979.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_service_policy_c9f7a979.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.291-capability-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.291-capability-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/capability_policy_1efa8125/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/capability_policy_1efa8125.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/capability_policy_1efa8125.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_capability_policy_1efa8125.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.292-domain-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.292-domain-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/domain_policy_30f7a6d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/domain_policy_30f7a6d1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/domain_policy_30f7a6d1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_domain_policy_30f7a6d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.293-emergency-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.293-emergency-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/emergency_policy_c3cdadfe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/emergency_policy_c3cdadfe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/emergency_policy_c3cdadfe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_emergency_policy_c3cdadfe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.294-policy-merge-semantics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.294-policy-merge-semantics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_merge_semantics_4de3a961/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_merge_semantics_4de3a961.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_merge_semantics_4de3a961.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_merge_semantics_4de3a961.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.295-policy-evaluation-engine`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.295-policy-evaluation-engine.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_evaluation_engine_b7b66bfc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_evaluation_engine_b7b66bfc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_evaluation_engine_b7b66bfc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_evaluation_engine_b7b66bfc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.296-deterministic-evaluator`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.296-deterministic-evaluator.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/deterministic_evaluator_865d7cb6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/deterministic_evaluator_865d7cb6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/deterministic_evaluator_865d7cb6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_deterministic_evaluator_865d7cb6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.297-policy-decision-trace`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.297-policy-decision-trace.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_trace_ff6e367d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_trace_ff6e367d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_trace_ff6e367d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_trace_ff6e367d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.298-policy-explainability`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.298-policy-explainability.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_explainability_6fdb263c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_explainability_6fdb263c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_explainability_6fdb263c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_explainability_6fdb263c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.299-why-allowed-explanation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.299-why-allowed-explanation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/why_allowed_explanation_534e52bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/why_allowed_explanation_534e52bb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/why_allowed_explanation_534e52bb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_why_allowed_explanation_534e52bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.300-why-denied-explanation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.300-why-denied-explanation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/why_denied_explanation_10f5ee57/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/why_denied_explanation_10f5ee57.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/why_denied_explanation_10f5ee57.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_why_denied_explanation_10f5ee57.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.301-why-justification-required-explanation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.301-why-justification-required-explanation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/why_justification_required_explanation_98f37c20/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/why_justification_required_explanation_98f37c20.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/why_justification_required_explanation_98f37c20.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_why_justification_required_explanation_98f37c20.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.302-why-confirmation-required-explanation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.302-why-confirmation-required-explanation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/why_confirmation_required_explanation_01fc883b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/why_confirmation_required_explanation_01fc883b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/why_confirmation_required_explanation_01fc883b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_why_confirmation_required_explanation_01fc883b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.303-why-authorization-required-explanation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.303-why-authorization-required-explanation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/why_authorization_required_explanation_d86ef8e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/why_authorization_required_explanation_d86ef8e4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/why_authorization_required_explanation_d86ef8e4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_why_authorization_required_explanation_d86ef8e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.304-which-policy-matched-query`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.304-which-policy-matched-query.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/which_policy_matched_query_5c00314b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/which_policy_matched_query_5c00314b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/which_policy_matched_query_5c00314b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_which_policy_matched_query_5c00314b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.305-policy-simulation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.305-policy-simulation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_simulation_d2f33386/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_simulation_d2f33386.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_simulation_d2f33386.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_simulation_d2f33386.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.306-policy-dry-run`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.306-policy-dry-run.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_dry_run_956b585e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_dry_run_956b585e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_dry_run_956b585e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_dry_run_956b585e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.307-policy-diff`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.307-policy-diff.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_diff_bd719215/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_diff_bd719215.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_diff_bd719215.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_diff_bd719215.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.308-policy-change-preview`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.308-policy-change-preview.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_change_preview_66473577/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_change_preview_66473577.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_change_preview_66473577.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_change_preview_66473577.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.309-policy-test-harness`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.309-policy-test-harness.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_test_harness_dcadefbe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/policy_test_harness_dcadefbe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/policy_test_harness_dcadefbe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_policy_test_harness_dcadefbe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.310-policy-unit-test-format`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.310-policy-unit-test-format.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_unit_test_format_50c22f5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/policy_unit_test_format_50c22f5d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/policy_unit_test_format_50c22f5d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_policy_unit_test_format_50c22f5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.311-policy-deployment`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.311-policy-deployment.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_deployment_19aa7399/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_deployment_19aa7399.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_deployment_19aa7399.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_deployment_19aa7399.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.312-policy-atomic-reload`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.312-policy-atomic-reload.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_atomic_reload_edb329a5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_atomic_reload_edb329a5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_atomic_reload_edb329a5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_atomic_reload_edb329a5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.313-policy-rollback`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.313-policy-rollback.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_rollback_64bfa36f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/policy_rollback_64bfa36f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/policy_rollback_64bfa36f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_policy_rollback_64bfa36f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.314-policy-backup-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.314-policy-backup-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_backup_boundary_8aec8196/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_backup_boundary_8aec8196.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_backup_boundary_8aec8196.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_backup_boundary_8aec8196.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.315-policy-migration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.315-policy-migration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_migration_b05ad0e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_migration_b05ad0e5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_migration_b05ad0e5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_migration_b05ad0e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.316-policy-version-compatibility`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.316-policy-version-compatibility.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_version_compatibility_e8398b0d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_version_compatibility_e8398b0d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_version_compatibility_e8398b0d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_version_compatibility_e8398b0d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.317-policy-hot-reload`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.317-policy-hot-reload.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_hot_reload_471ee98e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_hot_reload_471ee98e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_hot_reload_471ee98e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_hot_reload_471ee98e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.318-policy-reload-failure`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.318-policy-reload-failure.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_reload_failure_fe0cb7fa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_reload_failure_fe0cb7fa.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_reload_failure_fe0cb7fa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_reload_failure_fe0cb7fa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.319-policy-corruption-detection`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.319-policy-corruption-detection.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_corruption_detection_087c73f1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_corruption_detection_087c73f1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_corruption_detection_087c73f1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_corruption_detection_087c73f1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.320-policy-corruption-recovery`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.320-policy-corruption-recovery.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_corruption_recovery_d22a8290/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/policy_corruption_recovery_d22a8290.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/policy_corruption_recovery_d22a8290.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_policy_corruption_recovery_d22a8290.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.321-fail-closed-versus-degraded-behavior`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.321-fail-closed-versus-degraded-behavior.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/fail_closed_versus_degraded_behavior_b0ba1ded/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/fail_closed_versus_degraded_behavior_b0ba1ded.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/fail_closed_versus_degraded_behavior_b0ba1ded.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_fail_closed_versus_degraded_behavior_b0ba1ded.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.322-read-only-degraded-mode`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.322-read-only-degraded-mode.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/read_only_degraded_mode_8bd9fa65/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/read_only_degraded_mode_8bd9fa65.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/read_only_degraded_mode_8bd9fa65.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_read_only_degraded_mode_8bd9fa65.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.323-safe-mode`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.323-safe-mode.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/safe_mode_25c529d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/safe_mode_25c529d2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/safe_mode_25c529d2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_safe_mode_25c529d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.324-emergency-quiescence`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.324-emergency-quiescence.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/emergency_quiescence_92f409fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/emergency_quiescence_92f409fe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/emergency_quiescence_92f409fe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_emergency_quiescence_92f409fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.325-policy-service-lifecycle`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.325-policy-service-lifecycle.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_service_lifecycle_ab20cd47/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_service_lifecycle_ab20cd47.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_service_lifecycle_ab20cd47.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_service_lifecycle_ab20cd47.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.326-policy-daemon-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.326-policy-daemon-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_daemon_boundary_547da825/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_daemon_boundary_547da825.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_daemon_boundary_547da825.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_daemon_boundary_547da825.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.327-policy-ipc`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.327-policy-ipc.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_ipc_19353d75/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_ipc_19353d75.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_ipc_19353d75.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_ipc_19353d75.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.328-policy-ipc-schema`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.328-policy-ipc-schema.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_ipc_schema_ef467654/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_ipc_schema_ef467654.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_ipc_schema_ef467654.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_ipc_schema_ef467654.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.329-policy-client-api`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.329-policy-client-api.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_client_api_04ddcb4f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_client_api_04ddcb4f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_client_api_04ddcb4f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_client_api_04ddcb4f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.330-policy-capability-discovery`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.330-policy-capability-discovery.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_capability_discovery_5e356925/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_capability_discovery_5e356925.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_capability_discovery_5e356925.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_capability_discovery_5e356925.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.331-policy-cache`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.331-policy-cache.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_cache_11b7502a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_cache_11b7502a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_cache_11b7502a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_cache_11b7502a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.332-policy-cache-invalidation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.332-policy-cache-invalidation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_cache_invalidation_d0d72444/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_cache_invalidation_d0d72444.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_cache_invalidation_d0d72444.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_cache_invalidation_d0d72444.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.333-policy-cache-freshness`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.333-policy-cache-freshness.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_cache_freshness_aac42c2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_cache_freshness_aac42c2e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_cache_freshness_aac42c2e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_cache_freshness_aac42c2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.334-policy-performance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.334-policy-performance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_performance_63efd8fd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_performance_63efd8fd.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_performance_63efd8fd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_performance_63efd8fd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.335-policy-latency-budget`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.335-policy-latency-budget.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_latency_budget_2eb04062/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_latency_budget_2eb04062.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_latency_budget_2eb04062.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_latency_budget_2eb04062.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.336-policy-memory-bounds`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.336-policy-memory-bounds.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_memory_bounds_4c2e10c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_memory_bounds_4c2e10c5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_memory_bounds_4c2e10c5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_memory_bounds_4c2e10c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.337-policy-concurrency`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.337-policy-concurrency.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_concurrency_5f8e9294/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_concurrency_5f8e9294.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_concurrency_5f8e9294.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_concurrency_5f8e9294.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.338-policy-thread-safety`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.338-policy-thread-safety.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_thread_safety_6a1aba81/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_thread_safety_6a1aba81.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_thread_safety_6a1aba81.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_thread_safety_6a1aba81.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.339-policy-cancellation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.339-policy-cancellation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_cancellation_850cfd6c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_cancellation_850cfd6c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_cancellation_850cfd6c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_cancellation_850cfd6c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.340-policy-timeout`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.340-policy-timeout.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_timeout_3e9c052f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_timeout_3e9c052f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_timeout_3e9c052f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_timeout_3e9c052f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.341-policy-backpressure`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.341-policy-backpressure.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_backpressure_ef3b4fbd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_backpressure_ef3b4fbd.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_backpressure_ef3b4fbd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_backpressure_ef3b4fbd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.342-policy-observability`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.342-policy-observability.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_observability_11bc24b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_observability_11bc24b7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_observability_11bc24b7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_observability_11bc24b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.343-policy-metrics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.343-policy-metrics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_metrics_782bffa6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_metrics_782bffa6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_metrics_782bffa6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_metrics_782bffa6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.344-policy-tracing`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.344-policy-tracing.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_tracing_a3339d44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_tracing_a3339d44.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_tracing_a3339d44.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_tracing_a3339d44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.345-policy-audit-log`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.345-policy-audit-log.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_audit_log_cf99bd4f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/policy_audit_log_cf99bd4f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/policy_audit_log_cf99bd4f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_policy_audit_log_cf99bd4f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.346-secret-safe-policy-logs`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.346-secret-safe-policy-logs.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/secret_safe_policy_logs_ccfdd4d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/secret_safe_policy_logs_ccfdd4d2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/secret_safe_policy_logs_ccfdd4d2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_secret_safe_policy_logs_ccfdd4d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.347-policy-decision-history`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.347-policy-decision-history.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_decision_history_a40038af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_history_a40038af.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_decision_history_a40038af.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_decision_history_a40038af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.348-policy-statistics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.348-policy-statistics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_statistics_c5061d84/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_statistics_c5061d84.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_statistics_c5061d84.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_statistics_c5061d84.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.349-policy-denial-statistics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.349-policy-denial-statistics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_denial_statistics_66b8a326/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_denial_statistics_66b8a326.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_denial_statistics_66b8a326.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_denial_statistics_66b8a326.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.350-policy-clarification-statistics`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.350-policy-clarification-statistics.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_clarification_statistics_2545b9b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_clarification_statistics_2545b9b7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_clarification_statistics_2545b9b7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_clarification_statistics_2545b9b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.351-policy-false-positive-feedback`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.351-policy-false-positive-feedback.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_false_positive_feedback_dc1d42da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_false_positive_feedback_dc1d42da.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_false_positive_feedback_dc1d42da.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_false_positive_feedback_dc1d42da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.352-policy-false-negative-feedback`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.352-policy-false-negative-feedback.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_false_negative_feedback_82b0549a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_false_negative_feedback_82b0549a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_false_negative_feedback_82b0549a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_false_negative_feedback_82b0549a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.353-feedback-does-not-override-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.353-feedback-does-not-override-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/feedback_does_not_override_policy_9073fc26/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/feedback_does_not_override_policy_9073fc26.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/feedback_does_not_override_policy_9073fc26.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_feedback_does_not_override_policy_9073fc26.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.354-policy-calibration-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.354-policy-calibration-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_calibration_boundary_06f00ec1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_calibration_boundary_06f00ec1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_calibration_boundary_06f00ec1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_calibration_boundary_06f00ec1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.355-semantic-policy-suggestion-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.355-semantic-policy-suggestion-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/semantic_policy_suggestion_boundary_e59e8d94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/semantic_policy_suggestion_boundary_e59e8d94.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/semantic_policy_suggestion_boundary_e59e8d94.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_semantic_policy_suggestion_boundary_e59e8d94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.356-bitnet-policy-explanation-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.356-bitnet-policy-explanation-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/bitnet_policy_explanation_boundary_2d0c603c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/bitnet_policy_explanation_boundary_2d0c603c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/bitnet_policy_explanation_boundary_2d0c603c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_bitnet_policy_explanation_boundary_2d0c603c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.357-gordon-policy-consultation-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.357-gordon-policy-consultation-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gordon_policy_consultation_boundary_710f638f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gordon_policy_consultation_boundary_710f638f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gordon_policy_consultation_boundary_710f638f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gordon_policy_consultation_boundary_710f638f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.358-gordon-policy-recommendation-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.358-gordon-policy-recommendation-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gordon_policy_recommendation_boundary_5ce46079/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gordon_policy_recommendation_boundary_5ce46079.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gordon_policy_recommendation_boundary_5ce46079.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gordon_policy_recommendation_boundary_5ce46079.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.359-gordon-cannot-grant-policy-exception`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.359-gordon-cannot-grant-policy-exception.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gordon_cannot_grant_policy_exception_7e5ca355/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gordon_cannot_grant_policy_exception_7e5ca355.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gordon_cannot_grant_policy_exception_7e5ca355.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gordon_cannot_grant_policy_exception_7e5ca355.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.360-bitnet-cannot-grant-policy-exception`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.360-bitnet-cannot-grant-policy-exception.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/bitnet_cannot_grant_policy_exception_8d4bf9f5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/bitnet_cannot_grant_policy_exception_8d4bf9f5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/bitnet_cannot_grant_policy_exception_8d4bf9f5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_bitnet_cannot_grant_policy_exception_8d4bf9f5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.361-model-output-cannot-alter-active-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.361-model-output-cannot-alter-active-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/model_output_cannot_alter_active_policy_265d7cb7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/model_output_cannot_alter_active_policy_265d7cb7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/model_output_cannot_alter_active_policy_265d7cb7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_model_output_cannot_alter_active_policy_265d7cb7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.362-natural-language-policy-edit-request`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.362-natural-language-policy-edit-request.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/natural_language_policy_edit_request_febad22b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/natural_language_policy_edit_request_febad22b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/natural_language_policy_edit_request_febad22b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_natural_language_policy_edit_request_febad22b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.363-policy-edit-authorization`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.363-policy-edit-authorization.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_edit_authorization_7b21c03e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_authorization_7b21c03e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_authorization_7b21c03e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_edit_authorization_7b21c03e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.364-policy-edit-contextual-legitimacy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.364-policy-edit-contextual-legitimacy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_edit_contextual_legitimacy_a8830304/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_contextual_legitimacy_a8830304.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_contextual_legitimacy_a8830304.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_edit_contextual_legitimacy_a8830304.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.365-policy-edit-plan-preview`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.365-policy-edit-plan-preview.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_edit_plan_preview_b7ec9416/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_plan_preview_b7ec9416.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_plan_preview_b7ec9416.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_edit_plan_preview_b7ec9416.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.366-policy-edit-confirmation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.366-policy-edit-confirmation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_edit_confirmation_c515de3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_confirmation_c515de3a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_edit_confirmation_c515de3a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_edit_confirmation_c515de3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.367-policy-edit-rollback`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.367-policy-edit-rollback.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_edit_rollback_7658facc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/policy_edit_rollback_7658facc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/policy_edit_rollback_7658facc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_policy_edit_rollback_7658facc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.368-no-silent-self-modifying-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.368-no-silent-self-modifying-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/no_silent_self_modifying_policy_79510143/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/no_silent_self_modifying_policy_79510143.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/no_silent_self_modifying_policy_79510143.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_no_silent_self_modifying_policy_79510143.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.369-coding-agent-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.369-coding-agent-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/coding_agent_policy_3725e3d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/coding_agent_policy_3725e3d6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/coding_agent_policy_3725e3d6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_coding_agent_policy_3725e3d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.370-agent-filesystem-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.370-agent-filesystem-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_filesystem_policy_f3c11835/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_filesystem_policy_f3c11835.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_filesystem_policy_f3c11835.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_filesystem_policy_f3c11835.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.371-agent-process-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.371-agent-process-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_process_policy_a54dd4b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_process_policy_a54dd4b1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_process_policy_a54dd4b1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_process_policy_a54dd4b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.372-agent-network-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.372-agent-network-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_network_policy_f832718e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_network_policy_f832718e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_network_policy_f832718e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_network_policy_f832718e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.373-agent-package-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.373-agent-package-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_package_policy_885964af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_package_policy_885964af.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_package_policy_885964af.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_package_policy_885964af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.374-agent-service-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.374-agent-service-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_service_policy_3acba439/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_service_policy_3acba439.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_service_policy_3acba439.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_service_policy_3acba439.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.375-agent-repository-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.375-agent-repository-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_repository_policy_2d91cb19/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_repository_policy_2d91cb19.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_repository_policy_2d91cb19.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_repository_policy_2d91cb19.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.376-agent-destructive-operation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.376-agent-destructive-operation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_destructive_operation_policy_2ad9f7c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_destructive_operation_policy_2ad9f7c2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_destructive_operation_policy_2ad9f7c2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_destructive_operation_policy_2ad9f7c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.377-agent-secret-access-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.377-agent-secret-access-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_secret_access_policy_c8842aa5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_secret_access_policy_c8842aa5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_secret_access_policy_c8842aa5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_secret_access_policy_c8842aa5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.378-agent-external-upload-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.378-agent-external-upload-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_external_upload_policy_12c2f98a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_external_upload_policy_12c2f98a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_external_upload_policy_12c2f98a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_external_upload_policy_12c2f98a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.379-agent-shell-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.379-agent-shell-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_shell_boundary_0a279cc7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/agent_shell_boundary_0a279cc7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/agent_shell_boundary_0a279cc7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_agent_shell_boundary_0a279cc7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.380-automation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.380-automation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/automation_policy_fddd2803/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/automation_policy_fddd2803.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/automation_policy_fddd2803.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_automation_policy_fddd2803.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.381-scheduled-task-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.381-scheduled-task-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/scheduled_task_policy_f5e6a324/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/scheduled_task_policy_f5e6a324.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/scheduled_task_policy_f5e6a324.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_scheduled_task_policy_f5e6a324.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.382-recurring-task-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.382-recurring-task-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/recurring_task_policy_f4faf8f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/recurring_task_policy_f4faf8f2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/recurring_task_policy_f4faf8f2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_recurring_task_policy_f4faf8f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.383-condition-watch-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.383-condition-watch-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/condition_watch_policy_cc984649/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/condition_watch_policy_cc984649.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/condition_watch_policy_cc984649.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_condition_watch_policy_cc984649.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.384-unattended-mutation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.384-unattended-mutation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/unattended_mutation_policy_9525bad3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/unattended_mutation_policy_9525bad3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/unattended_mutation_policy_9525bad3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_unattended_mutation_policy_9525bad3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.385-persistent-automation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.385-persistent-automation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/persistent_automation_policy_652c06a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/persistent_automation_policy_652c06a7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/persistent_automation_policy_652c06a7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_persistent_automation_policy_652c06a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.386-automation-external-communication-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.386-automation-external-communication-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/automation_external_communication_policy_54f14c76/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/automation_external_communication_policy_54f14c76.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/automation_external_communication_policy_54f14c76.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_automation_external_communication_policy_54f14c76.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.387-automation-secret-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.387-automation-secret-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/automation_secret_policy_1484f2b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/automation_secret_policy_1484f2b5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/automation_secret_policy_1484f2b5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_automation_secret_policy_1484f2b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.388-workflow-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.388-workflow-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_policy_4f2fdcd2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workflow_policy_4f2fdcd2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workflow_policy_4f2fdcd2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workflow_policy_4f2fdcd2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.389-workflow-child-task-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.389-workflow-child-task-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_child_task_policy_21607961/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workflow_child_task_policy_21607961.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workflow_child_task_policy_21607961.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workflow_child_task_policy_21607961.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.390-workflow-authority-inheritance`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.390-workflow-authority-inheritance.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_authority_inheritance_0fb67838/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_authority_inheritance_0fb67838.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_authority_inheritance_0fb67838.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_workflow_authority_inheritance_0fb67838.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.391-workflow-authority-narrowing`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.391-workflow-authority-narrowing.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_authority_narrowing_e40a2390/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_authority_narrowing_e40a2390.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/workflow_authority_narrowing_e40a2390.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_workflow_authority_narrowing_e40a2390.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.392-workflow-fan-out-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.392-workflow-fan-out-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_fan_out_policy_42f82acb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workflow_fan_out_policy_42f82acb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workflow_fan_out_policy_42f82acb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workflow_fan_out_policy_42f82acb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.393-workflow-retry-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.393-workflow-retry-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_retry_policy_1355cd92/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workflow_retry_policy_1355cd92.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workflow_retry_policy_1355cd92.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workflow_retry_policy_1355cd92.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.394-workflow-compensation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.394-workflow-compensation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_compensation_policy_de763ad1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/workflow_compensation_policy_de763ad1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/workflow_compensation_policy_de763ad1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_workflow_compensation_policy_de763ad1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.395-workflow-dynamic-task-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.395-workflow-dynamic-task-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_dynamic_task_policy_4a81a47e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/workflow_dynamic_task_policy_4a81a47e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/workflow_dynamic_task_policy_4a81a47e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_workflow_dynamic_task_policy_4a81a47e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.396-cross-workflow-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.396-cross-workflow-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cross_workflow_policy_8f2c678a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cross_workflow_policy_8f2c678a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cross_workflow_policy_8f2c678a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cross_workflow_policy_8f2c678a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.397-cross-session-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.397-cross-session-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cross_session_policy_509bef22/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cross_session_policy_509bef22.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cross_session_policy_509bef22.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cross_session_policy_509bef22.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.398-cross-user-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.398-cross-user-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cross_user_policy_564dd98f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cross_user_policy_564dd98f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cross_user_policy_564dd98f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cross_user_policy_564dd98f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.399-multi-user-isolation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.399-multi-user-isolation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/multi_user_isolation_44d8ee9f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/multi_user_isolation_44d8ee9f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/multi_user_isolation_44d8ee9f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_multi_user_isolation_44d8ee9f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.400-identity-transition-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.400-identity-transition-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/identity_transition_policy_f1df75e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/identity_transition_policy_f1df75e0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/identity_transition_policy_f1df75e0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_identity_transition_policy_f1df75e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.401-sudo-boundary-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.401-sudo-boundary-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/sudo_boundary_policy_beea8a38/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/sudo_boundary_policy_beea8a38.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/sudo_boundary_policy_beea8a38.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_sudo_boundary_policy_beea8a38.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.402-polkit-boundary-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.402-polkit-boundary-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/polkit_boundary_policy_251c0cfe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/polkit_boundary_policy_251c0cfe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/polkit_boundary_policy_251c0cfe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_polkit_boundary_policy_251c0cfe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.403-privileged-helper-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.403-privileged-helper-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/privileged_helper_policy_ba53be40/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/privileged_helper_policy_ba53be40.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/privileged_helper_policy_ba53be40.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_privileged_helper_policy_ba53be40.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.404-d-bus-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.404-d-bus-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/d_bus_action_policy_7268dea1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/d_bus_action_policy_7268dea1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/d_bus_action_policy_7268dea1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_d_bus_action_policy_7268dea1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.405-systemd-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.405-systemd-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/systemd_action_policy_f00bf075/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/systemd_action_policy_f00bf075.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/systemd_action_policy_f00bf075.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_systemd_action_policy_f00bf075.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.406-network-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.406-network-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/network_action_policy_4f1db2c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/network_action_policy_4f1db2c4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/network_action_policy_4f1db2c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_network_action_policy_4f1db2c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.407-firewall-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.407-firewall-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/firewall_action_policy_771ea472/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/firewall_action_policy_771ea472.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/firewall_action_policy_771ea472.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_firewall_action_policy_771ea472.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.408-storage-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.408-storage-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/storage_action_policy_6b87f1ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/storage_action_policy_6b87f1ce.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/storage_action_policy_6b87f1ce.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_storage_action_policy_6b87f1ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.409-package-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.409-package-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/package_action_policy_5668df59/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/package_action_policy_5668df59.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/package_action_policy_5668df59.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_package_action_policy_5668df59.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.410-configuration-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.410-configuration-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/configuration_action_policy_31c698c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/configuration_action_policy_31c698c4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/configuration_action_policy_31c698c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_configuration_action_policy_31c698c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.411-gpu-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.411-gpu-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gpu_action_policy_86d980d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gpu_action_policy_86d980d8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gpu_action_policy_86d980d8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gpu_action_policy_86d980d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.412-process-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.412-process-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/process_action_policy_281dfe74/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/process_action_policy_281dfe74.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/process_action_policy_281dfe74.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_process_action_policy_281dfe74.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.413-service-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.413-service-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/service_action_policy_5978a36b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/service_action_policy_5978a36b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/service_action_policy_5978a36b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_service_action_policy_5978a36b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.414-user-identity-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.414-user-identity-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/user_identity_action_policy_e2621047/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/user_identity_action_policy_e2621047.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/user_identity_action_policy_e2621047.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_user_identity_action_policy_e2621047.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.415-development-environment-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.415-development-environment-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/development_environment_action_policy_2c37d956/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/development_environment_action_policy_2c37d956.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/development_environment_action_policy_2c37d956.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_development_environment_action_policy_2c37d956.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.416-shell-terminal-action-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.416-shell-terminal-action-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/shell_terminal_action_policy_9b380d6c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/shell_terminal_action_policy_9b380d6c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/shell_terminal_action_policy_9b380d6c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_shell_terminal_action_policy_9b380d6c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.417-read-only-inspection-baseline-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.417-read-only-inspection-baseline-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/read_only_inspection_baseline_policy_e90a5d09/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/read_only_inspection_baseline_policy_e90a5d09.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/read_only_inspection_baseline_policy_e90a5d09.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_read_only_inspection_baseline_policy_e90a5d09.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.418-system-diagnosis-baseline-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.418-system-diagnosis-baseline-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_diagnosis_baseline_policy_c870361d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/system_diagnosis_baseline_policy_c870361d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/system_diagnosis_baseline_policy_c870361d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_system_diagnosis_baseline_policy_c870361d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.419-system-repair-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.419-system-repair-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_repair_policy_d6687eab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/system_repair_policy_d6687eab.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/system_repair_policy_d6687eab.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_system_repair_policy_d6687eab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.420-system-optimization-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.420-system-optimization-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_optimization_policy_572d6013/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/system_optimization_policy_572d6013.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/system_optimization_policy_572d6013.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_system_optimization_policy_572d6013.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.421-system-adaptation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.421-system-adaptation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_adaptation_policy_603533ef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/system_adaptation_policy_603533ef.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/system_adaptation_policy_603533ef.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_system_adaptation_policy_603533ef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.422-system-update-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.422-system-update-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/system_update_policy_e5f9fe6e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/system_update_policy_e5f9fe6e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/system_update_policy_e5f9fe6e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_system_update_policy_e5f9fe6e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.423-kernel-update-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.423-kernel-update-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/kernel_update_policy_7cb4c279/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/kernel_update_policy_7cb4c279.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/kernel_update_policy_7cb4c279.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_kernel_update_policy_7cb4c279.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.424-driver-update-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.424-driver-update-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/driver_update_policy_52b6c20a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/driver_update_policy_52b6c20a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/driver_update_policy_52b6c20a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_driver_update_policy_52b6c20a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.425-reboot-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.425-reboot-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/reboot_policy_de0b6d52/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/reboot_policy_de0b6d52.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/reboot_policy_de0b6d52.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_reboot_policy_de0b6d52.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.426-shutdown-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.426-shutdown-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/shutdown_policy_9f69ad58/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/shutdown_policy_9f69ad58.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/shutdown_policy_9f69ad58.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_shutdown_policy_9f69ad58.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.427-suspend-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.427-suspend-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/suspend_policy_8567419c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/suspend_policy_8567419c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/suspend_policy_8567419c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_suspend_policy_8567419c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.428-filesystem-mount-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.428-filesystem-mount-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/filesystem_mount_policy_73c4b8b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/filesystem_mount_policy_73c4b8b0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/filesystem_mount_policy_73c4b8b0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_filesystem_mount_policy_73c4b8b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.429-filesystem-unmount-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.429-filesystem-unmount-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/filesystem_unmount_policy_ede16ae1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/filesystem_unmount_policy_ede16ae1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/filesystem_unmount_policy_ede16ae1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_filesystem_unmount_policy_ede16ae1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.430-luks-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.430-luks-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/luks_policy_ff5fc016/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/luks_policy_ff5fc016.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/luks_policy_ff5fc016.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_luks_policy_ff5fc016.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.431-raid-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.431-raid-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/raid_policy_ac030425/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/raid_policy_ac030425.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/raid_policy_ac030425.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_raid_policy_ac030425.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.432-network-interface-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.432-network-interface-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/network_interface_policy_086107f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/network_interface_policy_086107f2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/network_interface_policy_086107f2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_network_interface_policy_086107f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.433-route-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.433-route-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/route_policy_014f2018/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/route_policy_014f2018.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/route_policy_014f2018.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_route_policy_014f2018.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.434-dns-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.434-dns-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/dns_policy_e4307b0e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/dns_policy_e4307b0e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/dns_policy_e4307b0e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_dns_policy_e4307b0e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.435-firewall-rule-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.435-firewall-rule-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/firewall_rule_policy_e188f286/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/firewall_rule_policy_e188f286.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/firewall_rule_policy_e188f286.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_firewall_rule_policy_e188f286.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.436-ssh-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.436-ssh-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/ssh_policy_403d56d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/ssh_policy_403d56d2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/ssh_policy_403d56d2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_ssh_policy_403d56d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.437-container-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.437-container-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/container_policy_7f5bb4b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/container_policy_7f5bb4b7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/container_policy_7f5bb4b7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_container_policy_7f5bb4b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.438-docker-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.438-docker-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/docker_policy_bb747167/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/docker_policy_bb747167.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/docker_policy_bb747167.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_docker_policy_bb747167.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.439-model-server-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.439-model-server-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/model_server_policy_0003712d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/model_server_policy_0003712d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/model_server_policy_0003712d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_model_server_policy_0003712d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.440-ai-inference-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.440-ai-inference-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/ai_inference_policy_99b25cc5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/ai_inference_policy_99b25cc5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/ai_inference_policy_99b25cc5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_ai_inference_policy_99b25cc5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.441-gpu-power-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.441-gpu-power-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gpu_power_policy_3e32a31b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gpu_power_policy_3e32a31b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gpu_power_policy_3e32a31b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gpu_power_policy_3e32a31b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.442-gpu-reset-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.442-gpu-reset-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gpu_reset_policy_0b3eaa47/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/gpu_reset_policy_0b3eaa47.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/gpu_reset_policy_0b3eaa47.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_gpu_reset_policy_0b3eaa47.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.443-process-termination-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.443-process-termination-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/process_termination_policy_dd3059f8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/process_termination_policy_dd3059f8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/process_termination_policy_dd3059f8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_process_termination_policy_dd3059f8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.444-service-restart-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.444-service-restart-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/service_restart_policy_7963be78/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/service_restart_policy_7963be78.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/service_restart_policy_7963be78.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_service_restart_policy_7963be78.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.445-package-install-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.445-package-install-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/package_install_policy_724ec853/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/package_install_policy_724ec853.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/package_install_policy_724ec853.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_package_install_policy_724ec853.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.446-package-removal-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.446-package-removal-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/package_removal_policy_e2d2df7f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/package_removal_policy_e2d2df7f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/package_removal_policy_e2d2df7f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_package_removal_policy_e2d2df7f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.447-autoremove-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.447-autoremove-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/autoremove_policy_0a322bbe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/autoremove_policy_0a322bbe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/autoremove_policy_0a322bbe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_autoremove_policy_0a322bbe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.448-configuration-edit-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.448-configuration-edit-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/configuration_edit_policy_f46f850d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/configuration_edit_policy_f46f850d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/configuration_edit_policy_f46f850d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_configuration_edit_policy_f46f850d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.449-user-creation-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.449-user-creation-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/user_creation_policy_5a6003e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/user_creation_policy_5a6003e7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/user_creation_policy_5a6003e7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_user_creation_policy_5a6003e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.450-user-deletion-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.450-user-deletion-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/user_deletion_policy_526d619f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/user_deletion_policy_526d619f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/user_deletion_policy_526d619f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_user_deletion_policy_526d619f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.451-credential-rotation-task-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.451-credential-rotation-task-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/credential_rotation_task_policy_4245ed18/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/credential_rotation_task_policy_4245ed18.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/credential_rotation_task_policy_4245ed18.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_credential_rotation_task_policy_4245ed18.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.452-secret-material-boundary-tests`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.452-secret-material-boundary-tests.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/secret_material_boundary_tests_368615f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/secret_material_boundary_tests_368615f0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/secret_material_boundary_tests_368615f0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_secret_material_boundary_tests_368615f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.453-cli-policy-inspect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.453-cli-policy-inspect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_policy_inspect_e61e0d9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_inspect_e61e0d9d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_inspect_e61e0d9d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cli_policy_inspect_e61e0d9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.454-cli-task-inspect`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.454-cli-task-inspect.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_task_inspect_5ff85a0a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/cli_task_inspect_5ff85a0a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/cli_task_inspect_5ff85a0a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_cli_task_inspect_5ff85a0a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.455-cli-policy-evaluate`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.455-cli-policy-evaluate.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_policy_evaluate_3448cfee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_evaluate_3448cfee.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_evaluate_3448cfee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cli_policy_evaluate_3448cfee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.456-cli-policy-explain`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.456-cli-policy-explain.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_policy_explain_4cf5e0ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_explain_4cf5e0ee.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_explain_4cf5e0ee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cli_policy_explain_4cf5e0ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.457-cli-policy-simulate`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.457-cli-policy-simulate.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_policy_simulate_6a458930/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_simulate_6a458930.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_simulate_6a458930.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cli_policy_simulate_6a458930.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.458-cli-policy-diff`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.458-cli-policy-diff.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_policy_diff_5ddadf2d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_diff_5ddadf2d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_diff_5ddadf2d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cli_policy_diff_5ddadf2d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.459-cli-policy-validate`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.459-cli-policy-validate.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_policy_validate_20f9dade/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_validate_20f9dade.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cli_policy_validate_20f9dade.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cli_policy_validate_20f9dade.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.460-cli-task-plan`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.460-cli-task-plan.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_task_plan_c3e3a8c0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/cli_task_plan_c3e3a8c0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/cli_task_plan_c3e3a8c0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_cli_task_plan_c3e3a8c0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.461-cli-task-authorize-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.461-cli-task-authorize-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_task_authorize_boundary_bd7166e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/cli_task_authorize_boundary_bd7166e8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/cli_task_authorize_boundary_bd7166e8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_cli_task_authorize_boundary_bd7166e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.462-cli-task-execute-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.462-cli-task-execute-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_task_execute_boundary_f85f3bbf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/execution/cli_task_execute_boundary_f85f3bbf.hpp`, `src/runtime/os-task-policy-system/subtask_targets/execution/cli_task_execute_boundary_f85f3bbf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/execution/test_cli_task_execute_boundary_f85f3bbf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.463-cli-task-history`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.463-cli-task-history.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/cli_task_history_e37de2a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/cli_task_history_e37de2a2.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/cli_task_history_e37de2a2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_cli_task_history_e37de2a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.464-phase-25-panel-policy-overview`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.464-phase-25-panel-policy-overview.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_policy_overview_b313377e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_overview_b313377e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_overview_b313377e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_panel_policy_overview_b313377e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.465-panel-active-task-view`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.465-panel-active-task-view.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_active_task_view_d721a3c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/panel_active_task_view_d721a3c9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/panel_active_task_view_d721a3c9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_panel_active_task_view_d721a3c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.466-panel-policy-decision-view`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.466-panel-policy-decision-view.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_policy_decision_view_f2aef4c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_decision_view_f2aef4c8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_decision_view_f2aef4c8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_panel_policy_decision_view_f2aef4c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.467-panel-policy-explanation-view`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.467-panel-policy-explanation-view.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_policy_explanation_view_b6290b6f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_explanation_view_b6290b6f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_explanation_view_b6290b6f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_panel_policy_explanation_view_b6290b6f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.468-panel-task-history-view`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.468-panel-task-history-view.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_task_history_view_8c7eb699/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/panel_task_history_view_8c7eb699.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/panel_task_history_view_8c7eb699.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_panel_task_history_view_8c7eb699.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.469-panel-policy-editor-boundary`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.469-panel-policy-editor-boundary.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_policy_editor_boundary_983f2fa5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_editor_boundary_983f2fa5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_editor_boundary_983f2fa5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_panel_policy_editor_boundary_983f2fa5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.470-panel-policy-simulation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.470-panel-policy-simulation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_policy_simulation_4d39420a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_simulation_4d39420a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/panel_policy_simulation_4d39420a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_panel_policy_simulation_4d39420a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.471-panel-break-glass-surface`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.471-panel-break-glass-surface.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/panel_break_glass_surface_72209c35/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/panel_break_glass_surface_72209c35.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/panel_break_glass_surface_72209c35.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_panel_break_glass_surface_72209c35.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.472-operator-notification-policy`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.472-operator-notification-policy.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/operator_notification_policy_d6ffab3c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/operator_notification_policy_d6ffab3c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/operator_notification_policy_d6ffab3c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_operator_notification_policy_d6ffab3c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.473-policy-denial-ux`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.473-policy-denial-ux.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_denial_ux_8b2ab775/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_denial_ux_8b2ab775.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_denial_ux_8b2ab775.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_denial_ux_8b2ab775.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.474-policy-clarification-ux`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.474-policy-clarification-ux.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_clarification_ux_ebce4f5f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_clarification_ux_ebce4f5f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_clarification_ux_ebce4f5f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_clarification_ux_ebce4f5f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.475-policy-justification-ux`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.475-policy-justification-ux.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_justification_ux_b75746c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_justification_ux_b75746c9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_justification_ux_b75746c9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_justification_ux_b75746c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.476-policy-confirmation-ux`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.476-policy-confirmation-ux.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_confirmation_ux_ed34ba12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_confirmation_ux_ed34ba12.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_confirmation_ux_ed34ba12.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_confirmation_ux_ed34ba12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.477-policy-conflict-ux`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.477-policy-conflict-ux.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_conflict_ux_00125ddb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_ux_00125ddb.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_conflict_ux_00125ddb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_conflict_ux_00125ddb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.478-policy-unknown-ux`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.478-policy-unknown-ux.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_unknown_ux_384b2dc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_unknown_ux_384b2dc3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_unknown_ux_384b2dc3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_unknown_ux_384b2dc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.479-policy-documentation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.479-policy-documentation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_documentation_02ec7e69/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_documentation_02ec7e69.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_documentation_02ec7e69.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_documentation_02ec7e69.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.480-task-policy-documentation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.480-task-policy-documentation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_policy_documentation_ff492465/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/task_policy_documentation_ff492465.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/task_policy_documentation_ff492465.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_task_policy_documentation_ff492465.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.481-policy-authoring-guide`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.481-policy-authoring-guide.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_authoring_guide_4a47cece/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_authoring_guide_4a47cece.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_authoring_guide_4a47cece.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_authoring_guide_4a47cece.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.482-policy-security-guide`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.482-policy-security-guide.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_security_guide_83a3f725/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_security_guide_83a3f725.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_security_guide_83a3f725.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_security_guide_83a3f725.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.483-policy-troubleshooting`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.483-policy-troubleshooting.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_troubleshooting_c76b8ee7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/policy_troubleshooting_c76b8ee7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/policy_troubleshooting_c76b8ee7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_policy_troubleshooting_c76b8ee7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.484-taskwarrior-policy-documentation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.484-taskwarrior-policy-documentation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/taskwarrior_policy_documentation_67d0de5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_policy_documentation_67d0de5d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/taskwarrior_policy_documentation_67d0de5d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_taskwarrior_policy_documentation_67d0de5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.485-agent-policy-documentation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.485-agent-policy-documentation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_policy_documentation_06409004/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agent_policy_documentation_06409004.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agent_policy_documentation_06409004.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agent_policy_documentation_06409004.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.486-automation-policy-documentation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.486-automation-policy-documentation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/automation_policy_documentation_eafe6936/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/automation_policy_documentation_eafe6936.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/automation_policy_documentation_eafe6936.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_automation_policy_documentation_eafe6936.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.487-end-to-end-read-only-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.487-end-to-end-read-only-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_read_only_task_601f7d6b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_read_only_task_601f7d6b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_read_only_task_601f7d6b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_read_only_task_601f7d6b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.488-end-to-end-mutating-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.488-end-to-end-mutating-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_mutating_task_b68fa31f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_mutating_task_b68fa31f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_mutating_task_b68fa31f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_mutating_task_b68fa31f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.489-end-to-end-scheduled-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.489-end-to-end-scheduled-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_scheduled_task_32937dbe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/planning/end_to_end_scheduled_task_32937dbe.hpp`, `src/runtime/os-task-policy-system/subtask_targets/planning/end_to_end_scheduled_task_32937dbe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/planning/test_end_to_end_scheduled_task_32937dbe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.490-end-to-end-workflow-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.490-end-to-end-workflow-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_workflow_task_75c7a1e6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_workflow_task_75c7a1e6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_workflow_task_75c7a1e6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_workflow_task_75c7a1e6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.491-end-to-end-ask-originated-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.491-end-to-end-ask-originated-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_ask_originated_task_fa2041f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_ask_originated_task_fa2041f0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_ask_originated_task_fa2041f0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_ask_originated_task_fa2041f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.492-end-to-end-taskwarrior-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.492-end-to-end-taskwarrior-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_taskwarrior_task_d6a259a6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_taskwarrior_task_d6a259a6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_taskwarrior_task_d6a259a6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_taskwarrior_task_d6a259a6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.493-end-to-end-agent-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.493-end-to-end-agent-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_agent_task_3a32d2c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_agent_task_3a32d2c8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_agent_task_3a32d2c8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_agent_task_3a32d2c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.494-end-to-end-denied-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.494-end-to-end-denied-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_denied_task_f6e54b30/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_denied_task_f6e54b30.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_denied_task_f6e54b30.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_denied_task_f6e54b30.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.495-end-to-end-justification-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.495-end-to-end-justification-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_justification_task_03faae5f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_justification_task_03faae5f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_justification_task_03faae5f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_justification_task_03faae5f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.496-end-to-end-break-glass-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.496-end-to-end-break-glass-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_break_glass_task_4b0c9409/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_break_glass_task_4b0c9409.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/end_to_end_break_glass_task_4b0c9409.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_end_to_end_break_glass_task_4b0c9409.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.497-end-to-end-rollback-task`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.497-end-to-end-rollback-task.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/end_to_end_rollback_task_e8fe4aca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/recovery/end_to_end_rollback_task_e8fe4aca.hpp`, `src/runtime/os-task-policy-system/subtask_targets/recovery/end_to_end_rollback_task_e8fe4aca.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/recovery/test_end_to_end_rollback_task_e8fe4aca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.498-fork-bomb-policy-adversarial-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.498-fork-bomb-policy-adversarial-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/fork_bomb_policy_adversarial_test_ae940c98/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/fork_bomb_policy_adversarial_test_ae940c98.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/fork_bomb_policy_adversarial_test_ae940c98.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_fork_bomb_policy_adversarial_test_ae940c98.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.499-natural-language-fork-bomb-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.499-natural-language-fork-bomb-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/natural_language_fork_bomb_policy_test_5508267b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/natural_language_fork_bomb_policy_test_5508267b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/natural_language_fork_bomb_policy_test_5508267b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_natural_language_fork_bomb_policy_test_5508267b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.500-port-plus-log-export-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.500-port-plus-log-export-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/port_plus_log_export_policy_test_d4ca561d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/port_plus_log_export_policy_test_d4ca561d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/port_plus_log_export_policy_test_d4ca561d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_port_plus_log_export_policy_test_d4ca561d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.501-secret-plus-network-egress-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.501-secret-plus-network-egress-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/secret_plus_network_egress_test_c90d1db3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/secret_plus_network_egress_test_c90d1db3.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/secret_plus_network_egress_test_c90d1db3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_secret_plus_network_egress_test_c90d1db3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.502-task-splitting-exfiltration-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.502-task-splitting-exfiltration-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/task_splitting_exfiltration_test_e5e39bf5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/task_splitting_exfiltration_test_e5e39bf5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/task_splitting_exfiltration_test_e5e39bf5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_task_splitting_exfiltration_test_e5e39bf5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.503-workflow-decomposition-bypass-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.503-workflow-decomposition-bypass-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/workflow_decomposition_bypass_test_4d2a7b50/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/workflow_decomposition_bypass_test_4d2a7b50.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/workflow_decomposition_bypass_test_4d2a7b50.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_workflow_decomposition_bypass_test_4d2a7b50.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.504-delegation-laundering-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.504-delegation-laundering-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/delegation_laundering_test_ce189b8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/delegation_laundering_test_ce189b8d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/delegation_laundering_test_ce189b8d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_delegation_laundering_test_ce189b8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.505-context-laundering-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.505-context-laundering-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/context_laundering_test_e1f44f12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/context_laundering_test_e1f44f12.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/context_laundering_test_e1f44f12.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_context_laundering_test_e1f44f12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.506-authority-laundering-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.506-authority-laundering-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/authority_laundering_test_a90800ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/authority_laundering_test_a90800ab.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/authority_laundering_test_a90800ab.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_authority_laundering_test_a90800ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.507-stale-policy-decision-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.507-stale-policy-decision-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/stale_policy_decision_test_015ca0ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/stale_policy_decision_test_015ca0ea.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/stale_policy_decision_test_015ca0ea.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_stale_policy_decision_test_015ca0ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.508-changed-plan-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.508-changed-plan-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/changed_plan_policy_test_74cbf09e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/changed_plan_policy_test_74cbf09e.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/changed_plan_policy_test_74cbf09e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_changed_plan_policy_test_74cbf09e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.509-changed-destination-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.509-changed-destination-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/changed_destination_policy_test_e20b0c99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/changed_destination_policy_test_e20b0c99.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/changed_destination_policy_test_e20b0c99.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_changed_destination_policy_test_e20b0c99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.510-changed-requester-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.510-changed-requester-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/changed_requester_policy_test_c6e8db1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/changed_requester_policy_test_c6e8db1a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/changed_requester_policy_test_c6e8db1a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_changed_requester_policy_test_c6e8db1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.511-policy-conflict-adversarial-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.511-policy-conflict-adversarial-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_conflict_adversarial_test_70ee67e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/policy_conflict_adversarial_test_70ee67e0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/policy_conflict_adversarial_test_70ee67e0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_policy_conflict_adversarial_test_70ee67e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.512-policy-injection-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.512-policy-injection-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_injection_test_98830baa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/policy_injection_test_98830baa.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/policy_injection_test_98830baa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_policy_injection_test_98830baa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.513-malformed-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.513-malformed-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/malformed_policy_test_d700f300/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/malformed_policy_test_d700f300.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/malformed_policy_test_d700f300.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_malformed_policy_test_d700f300.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.514-policy-dos-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.514-policy-dos-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/policy_dos_test_69c2d8ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/policy_dos_test_69c2d8ee.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/policy_dos_test_69c2d8ee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_policy_dos_test_69c2d8ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.515-semantic-policy-manipulation-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.515-semantic-policy-manipulation-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/semantic_policy_manipulation_test_5ba90465/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/semantic_policy_manipulation_test_5ba90465.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/semantic_policy_manipulation_test_5ba90465.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_semantic_policy_manipulation_test_5ba90465.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.516-gordon-exception-manipulation-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.516-gordon-exception-manipulation-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/gordon_exception_manipulation_test_aaa43b0b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/gordon_exception_manipulation_test_aaa43b0b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/gordon_exception_manipulation_test_aaa43b0b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_gordon_exception_manipulation_test_aaa43b0b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.517-bitnet-exception-manipulation-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.517-bitnet-exception-manipulation-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/bitnet_exception_manipulation_test_0d6ea9bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/bitnet_exception_manipulation_test_0d6ea9bf.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/bitnet_exception_manipulation_test_0d6ea9bf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_bitnet_exception_manipulation_test_0d6ea9bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.518-agent-bypass-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.518-agent-bypass-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agent_bypass_test_788df34c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/agent_bypass_test_788df34c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/agent_bypass_test_788df34c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_agent_bypass_test_788df34c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.519-direct-shell-bypass-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.519-direct-shell-bypass-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/direct_shell_bypass_test_011ae819/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/direct_shell_bypass_test_011ae819.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/direct_shell_bypass_test_011ae819.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_direct_shell_bypass_test_011ae819.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.520-direct-privileged-helper-bypass-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.520-direct-privileged-helper-bypass-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/direct_privileged_helper_bypass_test_1617cd7f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/direct_privileged_helper_bypass_test_1617cd7f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/direct_privileged_helper_bypass_test_1617cd7f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_direct_privileged_helper_bypass_test_1617cd7f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.521-phase-45-bypass-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.521-phase-45-bypass-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/bypass_test_f93b3553/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/bypass_test_f93b3553.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/bypass_test_f93b3553.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_bypass_test_f93b3553.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.522-fail-open-adversarial-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.522-fail-open-adversarial-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/fail_open_adversarial_test_5798dada/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/fail_open_adversarial_test_5798dada.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/fail_open_adversarial_test_5798dada.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_fail_open_adversarial_test_5798dada.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.523-crash-restart-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.523-crash-restart-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/crash_restart_policy_test_abac0ad8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/crash_restart_policy_test_abac0ad8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/crash_restart_policy_test_abac0ad8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_crash_restart_policy_test_abac0ad8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.524-reboot-policy-continuity-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.524-reboot-policy-continuity-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/reboot_policy_continuity_test_b5662759/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/reboot_policy_continuity_test_b5662759.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/reboot_policy_continuity_test_b5662759.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_reboot_policy_continuity_test_b5662759.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.525-concurrent-policy-reload-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.525-concurrent-policy-reload-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/concurrent_policy_reload_test_ed2772e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/concurrent_policy_reload_test_ed2772e0.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/concurrent_policy_reload_test_ed2772e0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_concurrent_policy_reload_test_ed2772e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.526-concurrent-task-evaluation-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.526-concurrent-task-evaluation-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/concurrent_task_evaluation_test_8358faae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/concurrent_task_evaluation_test_8358faae.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/concurrent_task_evaluation_test_8358faae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_concurrent_task_evaluation_test_8358faae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.527-toctou-policy-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.527-toctou-policy-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/toctou_policy_test_d02e5183/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/toctou_policy_test_d02e5183.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/toctou_policy_test_d02e5183.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_toctou_policy_test_d02e5183.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.528-performance-regression-test`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.528-performance-regression-test.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/performance_regression_test_1f62798b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/performance_regression_test_1f62798b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/performance_regression_test_1f62798b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_performance_regression_test_1f62798b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.529-repository-source-tree-normalization`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.529-repository-source-tree-normalization.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/repository_source_tree_normalization_bfc19ee4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/repository_source_tree_normalization_bfc19ee4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/repository_source_tree_normalization_bfc19ee4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_repository_source_tree_normalization_bfc19ee4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.530-existing-policy-code-migration`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.530-existing-policy-code-migration.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/existing_policy_code_migration_50bca583/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/existing_policy_code_migration_50bca583.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/existing_policy_code_migration_50bca583.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_existing_policy_code_migration_50bca583.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.531-duplicate-policy-engine-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.531-duplicate-policy-engine-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/duplicate_policy_engine_audit_fd16e184/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_policy_engine_audit_fd16e184.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_policy_engine_audit_fd16e184.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_duplicate_policy_engine_audit_fd16e184.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.532-duplicate-task-gate-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.532-duplicate-task-gate-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/duplicate_task_gate_audit_ed943c22/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_task_gate_audit_ed943c22.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_task_gate_audit_ed943c22.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_duplicate_task_gate_audit_ed943c22.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.533-duplicate-authorization-heuristic-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.533-duplicate-authorization-heuristic-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/duplicate_authorization_heuristic_audit_f154ed8a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_authorization_heuristic_audit_f154ed8a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_authorization_heuristic_audit_f154ed8a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_duplicate_authorization_heuristic_audit_f154ed8a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.534-duplicate-safety-rule-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.534-duplicate-safety-rule-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/duplicate_safety_rule_audit_23c660ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_safety_rule_audit_23c660ed.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/duplicate_safety_rule_audit_23c660ed.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_duplicate_safety_rule_audit_23c660ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.535-direct-domain-policy-bypass-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.535-direct-domain-policy-bypass-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/direct_domain_policy_bypass_audit_8cf44580/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/direct_domain_policy_bypass_audit_8cf44580.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/direct_domain_policy_bypass_audit_8cf44580.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_direct_domain_policy_bypass_audit_8cf44580.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.536-direct-workflow-policy-bypass-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.536-direct-workflow-policy-bypass-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/direct_workflow_policy_bypass_audit_cf419ef9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/direct_workflow_policy_bypass_audit_cf419ef9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/direct_workflow_policy_bypass_audit_cf419ef9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_direct_workflow_policy_bypass_audit_cf419ef9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.537-direct-ask-policy-bypass-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.537-direct-ask-policy-bypass-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/direct_ask_policy_bypass_audit_7e6cf595/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/direct_ask_policy_bypass_audit_7e6cf595.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/direct_ask_policy_bypass_audit_7e6cf595.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_direct_ask_policy_bypass_audit_7e6cf595.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.538-direct-automation-policy-bypass-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.538-direct-automation-policy-bypass-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/direct_automation_policy_bypass_audit_84d747a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/direct_automation_policy_bypass_audit_84d747a4.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/direct_automation_policy_bypass_audit_84d747a4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_direct_automation_policy_bypass_audit_84d747a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.539-stale-python-policy-ownership-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.539-stale-python-policy-ownership-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/stale_python_policy_ownership_audit_a1865b40/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/stale_python_policy_ownership_audit_a1865b40.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/stale_python_policy_ownership_audit_a1865b40.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_stale_python_policy_ownership_audit_a1865b40.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.540-remaining-python-boundary-inventory`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.540-remaining-python-boundary-inventory.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/remaining_python_boundary_inventory_9159473d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/remaining_python_boundary_inventory_9159473d.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/remaining_python_boundary_inventory_9159473d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_remaining_python_boundary_inventory_9159473d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.541-c-first-policy-contract-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.541-c-first-policy-contract-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/c_first_policy_contract_audit_4c478943/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/c_first_policy_contract_audit_4c478943.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/c_first_policy_contract_audit_4c478943.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_c_first_policy_contract_audit_4c478943.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.542-agents-md-task-policy-contract`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.542-agents-md-task-policy-contract.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agents_md_task_policy_contract_25285dcd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agents_md_task_policy_contract_25285dcd.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agents_md_task_policy_contract_25285dcd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agents_md_task_policy_contract_25285dcd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.543-agents-md-no-authority-amplification-contract`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.543-agents-md-no-authority-amplification-contract.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agents_md_no_authority_amplification_contract_35e046b9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/contracts/agents_md_no_authority_amplification_contract_35e046b9.hpp`, `src/runtime/os-task-policy-system/subtask_targets/contracts/agents_md_no_authority_amplification_contract_35e046b9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/contracts/test_agents_md_no_authority_amplification_contract_35e046b9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.544-agents-md-data-flow-policy-contract`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.544-agents-md-data-flow-policy-contract.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agents_md_data_flow_policy_contract_9dcc982a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agents_md_data_flow_policy_contract_9dcc982a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agents_md_data_flow_policy_contract_9dcc982a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agents_md_data_flow_policy_contract_9dcc982a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.545-agents-md-fail-safe-policy-contract`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.545-agents-md-fail-safe-policy-contract.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/agents_md_fail_safe_policy_contract_6a448f4f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/agents_md_fail_safe_policy_contract_6a448f4f.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/agents_md_fail_safe_policy_contract_6a448f4f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_agents_md_fail_safe_policy_contract_6a448f4f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.546-recursive-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.546-recursive-rediscovery-pass-one.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/recursive_rediscovery_pass_one_b5effa9a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/resolution/recursive_rediscovery_pass_one_b5effa9a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/resolution/recursive_rediscovery_pass_one_b5effa9a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/resolution/test_recursive_rediscovery_pass_one_b5effa9a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.547-resolve-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.547-resolve-rediscovery-pass-one.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/resolve_rediscovery_pass_one_c9f35ebc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/resolution/resolve_rediscovery_pass_one_c9f35ebc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/resolution/resolve_rediscovery_pass_one_c9f35ebc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/resolution/test_resolve_rediscovery_pass_one_c9f35ebc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.548-recursive-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.548-recursive-rediscovery-pass-two.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/recursive_rediscovery_pass_two_ce66cd5b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/resolution/recursive_rediscovery_pass_two_ce66cd5b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/resolution/recursive_rediscovery_pass_two_ce66cd5b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/resolution/test_recursive_rediscovery_pass_two_ce66cd5b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.549-resolve-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.549-resolve-rediscovery-pass-two.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/resolve_rediscovery_pass_two_b1105be8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/resolution/resolve_rediscovery_pass_two_b1105be8.hpp`, `src/runtime/os-task-policy-system/subtask_targets/resolution/resolve_rediscovery_pass_two_b1105be8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/resolution/test_resolve_rediscovery_pass_two_b1105be8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.550-adversarial-policy-bypass-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.550-adversarial-policy-bypass-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adversarial_policy_bypass_audit_fac5f6d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_policy_bypass_audit_fac5f6d5.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_policy_bypass_audit_fac5f6d5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_adversarial_policy_bypass_audit_fac5f6d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.551-adversarial-delegation-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.551-adversarial-delegation-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adversarial_delegation_audit_499bc5c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_delegation_audit_499bc5c1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_delegation_audit_499bc5c1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_adversarial_delegation_audit_499bc5c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.552-adversarial-task-splitting-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.552-adversarial-task-splitting-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adversarial_task_splitting_audit_7969fb0c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_task_splitting_audit_7969fb0c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_task_splitting_audit_7969fb0c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_adversarial_task_splitting_audit_7969fb0c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.553-adversarial-data-flow-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.553-adversarial-data-flow-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adversarial_data_flow_audit_a95ca30c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_data_flow_audit_a95ca30c.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_data_flow_audit_a95ca30c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_adversarial_data_flow_audit_a95ca30c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.554-adversarial-resource-exhaustion-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.554-adversarial-resource-exhaustion-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adversarial_resource_exhaustion_audit_86710213/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_resource_exhaustion_audit_86710213.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_resource_exhaustion_audit_86710213.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_adversarial_resource_exhaustion_audit_86710213.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.555-adversarial-semantic-influence-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.555-adversarial-semantic-influence-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adversarial_semantic_influence_audit_4600d0c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_semantic_influence_audit_4600d0c1.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_semantic_influence_audit_4600d0c1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_adversarial_semantic_influence_audit_4600d0c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.556-adversarial-fail-open-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.556-adversarial-fail-open-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/adversarial_fail_open_audit_fb3db204/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_fail_open_audit_fb3db204.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/adversarial_fail_open_audit_fb3db204.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_adversarial_fail_open_audit_fb3db204.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.557-final-native-build`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.557-final-native-build.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_native_build_2f4f92c6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/final_native_build_2f4f92c6.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/final_native_build_2f4f92c6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_final_native_build_2f4f92c6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.558-final-unit-tests`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.558-final-unit-tests.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_unit_tests_c32e8417/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/final_unit_tests_c32e8417.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/final_unit_tests_c32e8417.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_final_unit_tests_c32e8417.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.559-final-integration-tests`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.559-final-integration-tests.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_integration_tests_d62068bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/final_integration_tests_d62068bf.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/final_integration_tests_d62068bf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_final_integration_tests_d62068bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.560-final-end-to-end-tests`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.560-final-end-to-end-tests.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_end_to_end_tests_9a06f104/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/final_end_to_end_tests_9a06f104.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/final_end_to_end_tests_9a06f104.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_final_end_to_end_tests_9a06f104.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.561-final-adversarial-suite`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.561-final-adversarial-suite.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_adversarial_suite_cb1796dd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/final_adversarial_suite_cb1796dd.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/final_adversarial_suite_cb1796dd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_final_adversarial_suite_cb1796dd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.562-final-performance-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.562-final-performance-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_performance_validation_047d6325/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/final_performance_validation_047d6325.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/final_performance_validation_047d6325.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_final_performance_validation_047d6325.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.563-final-policy-corpus-validation`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.563-final-policy-corpus-validation.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_policy_corpus_validation_ba4a7263/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/final_policy_corpus_validation_ba4a7263.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/final_policy_corpus_validation_ba4a7263.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_final_policy_corpus_validation_ba4a7263.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.564-final-source-tree-audit`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.564-final-source-tree-audit.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_source_tree_audit_1cb03214/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/verification/final_source_tree_audit_1cb03214.hpp`, `src/runtime/os-task-policy-system/subtask_targets/verification/final_source_tree_audit_1cb03214.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/verification/test_final_source_tree_audit_1cb03214.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.565-final-production-call-graph-trace`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.565-final-production-call-graph-trace.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_production_call_graph_trace_679608cc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/observability/final_production_call_graph_trace_679608cc.hpp`, `src/runtime/os-task-policy-system/subtask_targets/observability/final_production_call_graph_trace_679608cc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/observability/test_final_production_call_graph_trace_679608cc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.566-final-policy-decision-path-trace`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.566-final-policy-decision-path-trace.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_policy_decision_path_trace_d9887e6a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/security/final_policy_decision_path_trace_d9887e6a.hpp`, `src/runtime/os-task-policy-system/subtask_targets/security/final_policy_decision_path_trace_d9887e6a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/security/test_final_policy_decision_path_trace_d9887e6a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.567-final-authority-graph`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.567-final-authority-graph.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_authority_graph_648cc859/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/final_authority_graph_648cc859.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/final_authority_graph_648cc859.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_final_authority_graph_648cc859.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.568-final-remaining-python-inventory`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.568-final-remaining-python-inventory.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_remaining_python_inventory_d8468b83/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/final_remaining_python_inventory_d8468b83.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/final_remaining_python_inventory_d8468b83.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_final_remaining_python_inventory_d8468b83.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.569-final-fixed-point-rediscovery`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.569-final-fixed-point-rediscovery.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/final_fixed_point_rediscovery_7f47d5f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/resolution/final_fixed_point_rediscovery_7f47d5f7.hpp`, `src/runtime/os-task-policy-system/subtask_targets/resolution/final_fixed_point_rediscovery_7f47d5f7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/resolution/test_final_fixed_point_rediscovery_7f47d5f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `47.570-phase-47-closure-and-future-handoff`
- **Source:** `.phases/phases/phase-47-os-task-policy-system/prompts/47.570-phase-47-closure-and-future-handoff.md`
- **Structural package:** `src/runtime/os-task-policy-system/subtask_packages/verification/closure_and_future_handoff_d94c642b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/os-task-policy-system/subtask_targets/requirements/closure_and_future_handoff_d94c642b.hpp`, `src/runtime/os-task-policy-system/subtask_targets/requirements/closure_and_future_handoff_d94c642b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/os-task-policy-system/requirements/test_closure_and_future_handoff_d94c642b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

