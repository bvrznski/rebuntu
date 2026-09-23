# Phase 44 — Adaptive Workstation System — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-44-adaptive-workstation-system/`
- Primary prompt location: `.phases/phases/phase-44-adaptive-workstation-system/prompts/`
- Prompt/specification Markdown files currently present: **335**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 335 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_44` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 44 — Adaptive Workstation System
- Phase 44 Index
- Normative architecture
- Full executable prompts
- Phase 44 Agent Handoff
- Phase 44.251 — Semantic profile suggestion
- Objective
- Repository-first execution
- Authority and safety invariants
- Adaptive behavior requirements
- Implementation requirements
- Validation

## Structural skeleton / canonical destination
- Canonical skeleton: `src/domains/adaptive-workstation-system/`
- Structural files: `src/domains/adaptive-workstation-system/component.hpp`, `src/domains/adaptive-workstation-system/component.cpp`, `src/domains/adaptive-workstation-system/IMPLEMENTATION.json`
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

- Structural skeleton materialized at `src/domains/adaptive-workstation-system/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/adaptive-workstation-system/model/`
- `src/domains/adaptive-workstation-system/contracts/`
- `src/domains/adaptive-workstation-system/integration/`
- `src/domains/adaptive-workstation-system/verification/`
- `src/domains/adaptive-workstation-system/lifecycle/`
- `src/domains/adaptive-workstation-system/state/`
- `src/domains/adaptive-workstation-system/execution/`
- `src/domains/adaptive-workstation-system/transactions/`
- `src/domains/adaptive-workstation-system/events/`
- `src/domains/adaptive-workstation-system/scheduling/`
- `src/domains/adaptive-workstation-system/recovery/`
- `src/domains/adaptive-workstation-system/principals/`
- `src/domains/adaptive-workstation-system/groups/`
- `src/domains/adaptive-workstation-system/roles/`
- `src/domains/adaptive-workstation-system/resolution/`
- `src/domains/adaptive-workstation-system/authorization/`
- `src/domains/adaptive-workstation-system/credentials/`
- `src/domains/adaptive-workstation-system/policy/`



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

### `44.000-foundation-and-repository-archaeology`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.000-foundation-and-repository-archaeology.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/foundation_and_repository_archaeology_d1aa1c6b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/foundation_and_repository_archaeology_d1aa1c6b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/foundation_and_repository_archaeology_d1aa1c6b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_foundation_and_repository_archaeology_d1aa1c6b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.001-existing-adaptive-capability-inventory`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.001-existing-adaptive-capability-inventory.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/existing_adaptive_capability_inventory_693ce5e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/existing_adaptive_capability_inventory_693ce5e7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/existing_adaptive_capability_inventory_693ce5e7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_existing_adaptive_capability_inventory_693ce5e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.002-adaptation-ownership-map`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.002-adaptation-ownership-map.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_ownership_map_0edfb0d0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_ownership_map_0edfb0d0.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_ownership_map_0edfb0d0.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_ownership_map_0edfb0d0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.003-canonical-c-adaptive-architecture`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.003-canonical-c-adaptive-architecture.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/canonical_c_adaptive_architecture_fa64bae1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/canonical_c_adaptive_architecture_fa64bae1.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/canonical_c_adaptive_architecture_fa64bae1.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_canonical_c_adaptive_architecture_fa64bae1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.004-adaptive-artifact-strong-types`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.004-adaptive-artifact-strong-types.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_artifact_strong_types_99a22a1e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/adaptive_artifact_strong_types_99a22a1e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/adaptive_artifact_strong_types_99a22a1e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_adaptive_artifact_strong_types_99a22a1e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.005-goal-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.005-goal-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/goal_model_4b242925/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/goal_model_4b242925.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/goal_model_4b242925.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_goal_model_4b242925.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.006-operator-preference-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.006-operator-preference-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/operator_preference_model_4805e1a6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/operator_preference_model_4805e1a6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/operator_preference_model_4805e1a6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_operator_preference_model_4805e1a6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.007-context-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.007-context-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/context_model_58d7833a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/context_model_58d7833a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/context_model_58d7833a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_context_model_58d7833a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.008-adaptive-policy-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.008-adaptive-policy-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_policy_model_b5707af1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/adaptive_policy_model_b5707af1.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/adaptive_policy_model_b5707af1.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_adaptive_policy_model_b5707af1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.009-candidate-adaptation-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.009-candidate-adaptation-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/candidate_adaptation_model_82d2eaf0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/candidate_adaptation_model_82d2eaf0.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/candidate_adaptation_model_82d2eaf0.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_candidate_adaptation_model_82d2eaf0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.010-applied-adaptation-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.010-applied-adaptation-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/applied_adaptation_model_a50dabb3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/applied_adaptation_model_a50dabb3.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/applied_adaptation_model_a50dabb3.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_applied_adaptation_model_a50dabb3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.011-outcome-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.011-outcome-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/outcome_model_293c6dc7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/outcome_model_293c6dc7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/outcome_model_293c6dc7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_outcome_model_293c6dc7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.012-experiment-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.012-experiment-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_model_16387313/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/experiment_model_16387313.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/experiment_model_16387313.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_experiment_model_16387313.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.013-adaptation-provenance`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.013-adaptation-provenance.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_provenance_e9e7635d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_provenance_e9e7635d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_provenance_e9e7635d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_provenance_e9e7635d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.014-adaptation-epistemic-metadata`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.014-adaptation-epistemic-metadata.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_epistemic_metadata_ed5381d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_epistemic_metadata_ed5381d1.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_epistemic_metadata_ed5381d1.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_epistemic_metadata_ed5381d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.015-adaptation-lifecycle-state-machine`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.015-adaptation-lifecycle-state-machine.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_lifecycle_state_machine_ad44f6ef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/adaptation_lifecycle_state_machine_ad44f6ef.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/adaptation_lifecycle_state_machine_ad44f6ef.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_adaptation_lifecycle_state_machine_ad44f6ef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.016-policy-scope-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.016-policy-scope-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_scope_model_918a2f4c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/policy_scope_model_918a2f4c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/policy_scope_model_918a2f4c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_policy_scope_model_918a2f4c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.017-policy-authorization-levels`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.017-policy-authorization-levels.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_authorization_levels_59d3a816/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/policy_authorization_levels_59d3a816.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/policy_authorization_levels_59d3a816.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_policy_authorization_levels_59d3a816.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.018-policy-expiry`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.018-policy-expiry.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_expiry_3fcba894/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/policy_expiry_3fcba894.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/policy_expiry_3fcba894.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_policy_expiry_3fcba894.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.019-policy-conflict-resolution`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.019-policy-conflict-resolution.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_conflict_resolution_1b415668/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/policy_conflict_resolution_1b415668.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/policy_conflict_resolution_1b415668.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_policy_conflict_resolution_1b415668.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.020-policy-precedence`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.020-policy-precedence.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_precedence_d9cb863d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/policy_precedence_d9cb863d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/policy_precedence_d9cb863d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_policy_precedence_d9cb863d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.021-policy-composition`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.021-policy-composition.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_composition_740e6bd3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/policy_composition_740e6bd3.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/policy_composition_740e6bd3.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_policy_composition_740e6bd3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.022-global-adaptation-enable-disable`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.022-global-adaptation-enable-disable.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/global_adaptation_enable_disable_4f569844/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/global_adaptation_enable_disable_4f569844.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/global_adaptation_enable_disable_4f569844.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_global_adaptation_enable_disable_4f569844.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.023-adaptive-safe-mode`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.023-adaptive-safe-mode.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_safe_mode_1f3b1206/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptive_safe_mode_1f3b1206.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptive_safe_mode_1f3b1206.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptive_safe_mode_1f3b1206.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.024-emergency-adaptation-freeze`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.024-emergency-adaptation-freeze.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/emergency_adaptation_freeze_43e4480e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/emergency_adaptation_freeze_43e4480e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/emergency_adaptation_freeze_43e4480e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_emergency_adaptation_freeze_43e4480e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.025-manual-only-mode`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.025-manual-only-mode.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/manual_only_mode_43432fb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/manual_only_mode_43432fb9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/manual_only_mode_43432fb9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_manual_only_mode_43432fb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.026-recommend-only-mode`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.026-recommend-only-mode.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/recommend_only_mode_73ccfd09/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/recommend_only_mode_73ccfd09.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/recommend_only_mode_73ccfd09.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_recommend_only_mode_73ccfd09.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.027-policy-authorized-automatic-mode`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.027-policy-authorized-automatic-mode.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_authorized_automatic_mode_9963df00/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/policy_authorized_automatic_mode_9963df00.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/policy_authorized_automatic_mode_9963df00.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_policy_authorized_automatic_mode_9963df00.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.028-context-detection-foundation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.028-context-detection-foundation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/context_detection_foundation_9bcca919/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_detection_foundation_9bcca919.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_detection_foundation_9bcca919.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_context_detection_foundation_9bcca919.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.029-context-confidence-semantics`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.029-context-confidence-semantics.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/context_confidence_semantics_f83bfb9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_confidence_semantics_f83bfb9b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_confidence_semantics_f83bfb9b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_context_confidence_semantics_f83bfb9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.030-context-transition-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.030-context-transition-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/context_transition_handling_e82346de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/context_transition_handling_e82346de.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/context_transition_handling_e82346de.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_context_transition_handling_e82346de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.031-context-hysteresis`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.031-context-hysteresis.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/context_hysteresis_d2bc0c04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_hysteresis_d2bc0c04.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_hysteresis_d2bc0c04.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_context_hysteresis_d2bc0c04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.032-context-debounce-and-cooldown`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.032-context-debounce-and-cooldown.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/context_debounce_and_cooldown_31c5d443/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_debounce_and_cooldown_31c5d443.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_debounce_and_cooldown_31c5d443.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_context_debounce_and_cooldown_31c5d443.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.033-profile-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.033-profile-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/profile_model_0f2f72b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/profile_model_0f2f72b0.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/profile_model_0f2f72b0.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_profile_model_0f2f72b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.034-profile-composition`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.034-profile-composition.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/profile_composition_9e583411/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_composition_9e583411.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_composition_9e583411.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_profile_composition_9e583411.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.035-profile-inheritance`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.035-profile-inheritance.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/profile_inheritance_e3c3bd38/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_inheritance_e3c3bd38.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_inheritance_e3c3bd38.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_profile_inheritance_e3c3bd38.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.036-profile-conflict-resolution`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.036-profile-conflict-resolution.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/profile_conflict_resolution_7c1ffbb2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_conflict_resolution_7c1ffbb2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_conflict_resolution_7c1ffbb2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_profile_conflict_resolution_7c1ffbb2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.037-profile-activation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.037-profile-activation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/profile_activation_5028b6d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_activation_5028b6d7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_activation_5028b6d7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_profile_activation_5028b6d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.038-profile-deactivation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.038-profile-deactivation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/profile_deactivation_ef50f537/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_deactivation_ef50f537.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/profile_deactivation_ef50f537.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_profile_deactivation_ef50f537.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.039-profile-transition-safety`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.039-profile-transition-safety.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/profile_transition_safety_2a37f011/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/profile_transition_safety_2a37f011.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/profile_transition_safety_2a37f011.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_profile_transition_safety_2a37f011.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.040-development-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.040-development-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/development_profile_5e2d61db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/development_profile_5e2d61db.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/development_profile_5e2d61db.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_development_profile_5e2d61db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.041-ai-inference-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.041-ai-inference-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/ai_inference_profile_8e8a753e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/ai_inference_profile_8e8a753e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/ai_inference_profile_8e8a753e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_ai_inference_profile_8e8a753e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.042-gaming-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.042-gaming-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/gaming_profile_59251880/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/gaming_profile_59251880.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/gaming_profile_59251880.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_gaming_profile_59251880.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.043-interactive-desktop-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.043-interactive-desktop-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/interactive_desktop_profile_2ee552ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/interactive_desktop_profile_2ee552ba.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/interactive_desktop_profile_2ee552ba.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_interactive_desktop_profile_2ee552ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.044-background-idle-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.044-background-idle-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/background_idle_profile_4ad09e47/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/background_idle_profile_4ad09e47.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/background_idle_profile_4ad09e47.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_background_idle_profile_4ad09e47.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.045-maintenance-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.045-maintenance-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/maintenance_profile_c9fcb0a6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/maintenance_profile_c9fcb0a6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/maintenance_profile_c9fcb0a6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_maintenance_profile_c9fcb0a6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.046-power-efficiency-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.046-power-efficiency-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/power_efficiency_profile_67616bbf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/power_efficiency_profile_67616bbf.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/power_efficiency_profile_67616bbf.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_power_efficiency_profile_67616bbf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.047-performance-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.047-performance-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/performance_profile_2b5356f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/performance_profile_2b5356f4.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/performance_profile_2b5356f4.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_performance_profile_2b5356f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.048-thermal-constrained-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.048-thermal-constrained-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/thermal_constrained_profile_72f61e53/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/thermal_constrained_profile_72f61e53.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/thermal_constrained_profile_72f61e53.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_thermal_constrained_profile_72f61e53.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.049-noise-sensitive-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.049-noise-sensitive-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/noise_sensitive_profile_aed9f680/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/noise_sensitive_profile_aed9f680.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/noise_sensitive_profile_aed9f680.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_noise_sensitive_profile_aed9f680.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.050-custom-operator-profile`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.050-custom-operator-profile.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/custom_operator_profile_d9d3d5e2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/custom_operator_profile_d9d3d5e2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/custom_operator_profile_d9d3d5e2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_custom_operator_profile_d9d3d5e2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.051-phase-39-adaptation-history-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.051-phase-39-adaptation-history-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_history_integration_0757eff1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/adaptation_history_integration_0757eff1.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/adaptation_history_integration_0757eff1.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_adaptation_history_integration_0757eff1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.052-phase-42-impact-graph-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.052-phase-42-impact-graph-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/impact_graph_integration_d86a9360/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/impact_graph_integration_d86a9360.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/impact_graph_integration_d86a9360.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_impact_graph_integration_d86a9360.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.053-phase-43-candidate-adaptation-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.053-phase-43-candidate-adaptation-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/candidate_adaptation_integration_edc6ebe5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/candidate_adaptation_integration_edc6ebe5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/candidate_adaptation_integration_edc6ebe5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_candidate_adaptation_integration_edc6ebe5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.054-phase-40-typed-plan-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.054-phase-40-typed-plan-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/typed_plan_integration_96e508ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/typed_plan_integration_96e508ba.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/typed_plan_integration_96e508ba.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_typed_plan_integration_96e508ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.055-phase-41-adaptive-workflow-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.055-phase-41-adaptive-workflow-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_workflow_integration_8815c2cd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/adaptive_workflow_integration_8815c2cd.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/adaptive_workflow_integration_8815c2cd.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_adaptive_workflow_integration_8815c2cd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.056-domain-owner-re-observation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.056-domain-owner-re-observation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/domain_owner_re_observation_4b834a29/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/domain_owner_re_observation_4b834a29.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/domain_owner_re_observation_4b834a29.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_domain_owner_re_observation_4b834a29.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.057-pre-adaptation-snapshot`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.057-pre-adaptation-snapshot.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/pre_adaptation_snapshot_2b09b7d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/persistence/pre_adaptation_snapshot_2b09b7d6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/persistence/pre_adaptation_snapshot_2b09b7d6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/persistence/test_pre_adaptation_snapshot_2b09b7d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.058-pre-adaptation-validation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.058-pre-adaptation-validation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/pre_adaptation_validation_bac44b1e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/pre_adaptation_validation_bac44b1e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/pre_adaptation_validation_bac44b1e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_pre_adaptation_validation_bac44b1e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.059-adaptation-plan-construction`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.059-adaptation-plan-construction.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_plan_construction_d579c7db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/planning/adaptation_plan_construction_d579c7db.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/planning/adaptation_plan_construction_d579c7db.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/planning/test_adaptation_plan_construction_d579c7db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.060-adaptation-preview`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.060-adaptation-preview.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_preview_397202be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_preview_397202be.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_preview_397202be.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_preview_397202be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.061-expected-effect-representation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.061-expected-effect-representation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/expected_effect_representation_930fe68d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/expected_effect_representation_930fe68d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/expected_effect_representation_930fe68d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_expected_effect_representation_930fe68d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.062-risk-representation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.062-risk-representation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/risk_representation_2838bf08/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/risk_representation_2838bf08.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/risk_representation_2838bf08.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_risk_representation_2838bf08.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.063-reversibility-classification`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.063-reversibility-classification.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/reversibility_classification_4718002d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/reversibility_classification_4718002d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/reversibility_classification_4718002d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_reversibility_classification_4718002d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.064-rollback-plan-construction`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.064-rollback-plan-construction.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/rollback_plan_construction_b47ecd6b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/rollback_plan_construction_b47ecd6b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/rollback_plan_construction_b47ecd6b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_rollback_plan_construction_b47ecd6b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.065-rollback-validation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.065-rollback-validation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/rollback_validation_32f4c6a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/rollback_validation_32f4c6a9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/rollback_validation_32f4c6a9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_rollback_validation_32f4c6a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.066-authorization-handoff`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.066-authorization-handoff.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/authorization_handoff_8def461b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/authorization_handoff_8def461b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/authorization_handoff_8def461b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_authorization_handoff_8def461b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.067-execution-coordination`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.067-execution-coordination.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/execution_coordination_9597cd7f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/execution/execution_coordination_9597cd7f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/execution/execution_coordination_9597cd7f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/execution/test_execution_coordination_9597cd7f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.068-post-change-verification`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.068-post-change-verification.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/post_change_verification_3219eaa5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/post_change_verification_3219eaa5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/post_change_verification_3219eaa5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_post_change_verification_3219eaa5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.069-outcome-measurement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.069-outcome-measurement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/outcome_measurement_bc941578/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_measurement_bc941578.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_measurement_bc941578.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_outcome_measurement_bc941578.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.070-outcome-observation-window`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.070-outcome-observation-window.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/outcome_observation_window_7efc5973/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/outcome_observation_window_7efc5973.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/outcome_observation_window_7efc5973.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_outcome_observation_window_7efc5973.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.071-outcome-attribution-restraint`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.071-outcome-attribution-restraint.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/outcome_attribution_restraint_c9819804/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_attribution_restraint_c9819804.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_attribution_restraint_c9819804.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_outcome_attribution_restraint_c9819804.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.072-outcome-comparison-to-baseline`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.072-outcome-comparison-to-baseline.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/outcome_comparison_to_baseline_96f66c76/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_comparison_to_baseline_96f66c76.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_comparison_to_baseline_96f66c76.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_outcome_comparison_to_baseline_96f66c76.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.073-success-criteria`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.073-success-criteria.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/success_criteria_95452dcd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/success_criteria_95452dcd.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/success_criteria_95452dcd.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_success_criteria_95452dcd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.074-failure-criteria`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.074-failure-criteria.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/failure_criteria_caf3b952/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/failure_criteria_caf3b952.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/failure_criteria_caf3b952.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_failure_criteria_caf3b952.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.075-abort-criteria`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.075-abort-criteria.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/abort_criteria_e331329f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/abort_criteria_e331329f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/abort_criteria_e331329f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_abort_criteria_e331329f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.076-automatic-rollback-criteria`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.076-automatic-rollback-criteria.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/automatic_rollback_criteria_dab1c4d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/automatic_rollback_criteria_dab1c4d5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/automatic_rollback_criteria_dab1c4d5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_automatic_rollback_criteria_dab1c4d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.077-manual-rollback`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.077-manual-rollback.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/manual_rollback_99dddf8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/manual_rollback_99dddf8d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/manual_rollback_99dddf8d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_manual_rollback_99dddf8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.078-rollback-verification`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.078-rollback-verification.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/rollback_verification_8b4d05a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/rollback_verification_8b4d05a9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/rollback_verification_8b4d05a9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_rollback_verification_8b4d05a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.079-partial-rollback-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.079-partial-rollback-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/partial_rollback_handling_ab241209/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/partial_rollback_handling_ab241209.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/partial_rollback_handling_ab241209.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_partial_rollback_handling_ab241209.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.080-ambiguous-outcome-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.080-ambiguous-outcome-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/ambiguous_outcome_handling_b31e250d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/ambiguous_outcome_handling_b31e250d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/ambiguous_outcome_handling_b31e250d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_ambiguous_outcome_handling_b31e250d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.081-unknown-outcome-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.081-unknown-outcome-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/unknown_outcome_handling_2349659d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/unknown_outcome_handling_2349659d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/unknown_outcome_handling_2349659d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_unknown_outcome_handling_2349659d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.082-experiment-foundation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.082-experiment-foundation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_foundation_67de9364/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_foundation_67de9364.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_foundation_67de9364.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_experiment_foundation_67de9364.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.083-experiment-hypothesis`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.083-experiment-hypothesis.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_hypothesis_cbcf3de5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_hypothesis_cbcf3de5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_hypothesis_cbcf3de5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_experiment_hypothesis_cbcf3de5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.084-experiment-baseline`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.084-experiment-baseline.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_baseline_73a101b9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_baseline_73a101b9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_baseline_73a101b9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_experiment_baseline_73a101b9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.085-experiment-control-variables`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.085-experiment-control-variables.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_control_variables_4044d1c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_control_variables_4044d1c3.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_control_variables_4044d1c3.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_experiment_control_variables_4044d1c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.086-experiment-bounded-scope`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.086-experiment-bounded-scope.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_bounded_scope_db489777/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_bounded_scope_db489777.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_bounded_scope_db489777.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_experiment_bounded_scope_db489777.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.087-experiment-duration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.087-experiment-duration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_duration_3873a2bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_duration_3873a2bf.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_duration_3873a2bf.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_experiment_duration_3873a2bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.088-experiment-stop-conditions`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.088-experiment-stop-conditions.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_stop_conditions_f959ee10/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/experiment_stop_conditions_f959ee10.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/experiment_stop_conditions_f959ee10.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_experiment_stop_conditions_f959ee10.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.089-experiment-rollback`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.089-experiment-rollback.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_rollback_a805c41f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/experiment_rollback_a805c41f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/experiment_rollback_a805c41f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_experiment_rollback_a805c41f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.090-experiment-result-recording`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.090-experiment-result-recording.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/experiment_result_recording_772d06c6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_result_recording_772d06c6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/experiment_result_recording_772d06c6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_experiment_result_recording_772d06c6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.091-a-b-comparison-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.091-a-b-comparison-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/a_b_comparison_boundary_a70113fb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/a_b_comparison_boundary_a70113fb.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/a_b_comparison_boundary_a70113fb.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_a_b_comparison_boundary_a70113fb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.092-multi-armed-optimization-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.092-multi-armed-optimization-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/multi_armed_optimization_boundary_942ba04e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/multi_armed_optimization_boundary_942ba04e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/multi_armed_optimization_boundary_942ba04e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_multi_armed_optimization_boundary_942ba04e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.093-safe-parameter-search`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.093-safe-parameter-search.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/safe_parameter_search_d3fbe139/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/resolution/safe_parameter_search_d3fbe139.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/resolution/safe_parameter_search_d3fbe139.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/resolution/test_safe_parameter_search_d3fbe139.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.094-parameter-bounds`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.094-parameter-bounds.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/parameter_bounds_b761daf6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/parameter_bounds_b761daf6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/parameter_bounds_b761daf6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_parameter_bounds_b761daf6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.095-parameter-step-size-policy`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.095-parameter-step-size-policy.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/parameter_step_size_policy_7a3d3d28/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/parameter_step_size_policy_7a3d3d28.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/parameter_step_size_policy_7a3d3d28.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_parameter_step_size_policy_7a3d3d28.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.096-optimization-convergence`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.096-optimization-convergence.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/optimization_convergence_5d000a93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/optimization_convergence_5d000a93.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/optimization_convergence_5d000a93.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_optimization_convergence_5d000a93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.097-optimization-oscillation-detection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.097-optimization-oscillation-detection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/optimization_oscillation_detection_8b56c659/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/optimization_oscillation_detection_8b56c659.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/optimization_oscillation_detection_8b56c659.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_optimization_oscillation_detection_8b56c659.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.098-optimization-cooldown`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.098-optimization-cooldown.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/optimization_cooldown_259c5456/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/optimization_cooldown_259c5456.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/optimization_cooldown_259c5456.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_optimization_cooldown_259c5456.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.099-anti-thrashing-controls`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.099-anti-thrashing-controls.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/anti_thrashing_controls_46b3e4ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/anti_thrashing_controls_46b3e4ea.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/anti_thrashing_controls_46b3e4ea.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_anti_thrashing_controls_46b3e4ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.100-preference-learning-foundation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.100-preference-learning-foundation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/preference_learning_foundation_13233c3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_learning_foundation_13233c3f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_learning_foundation_13233c3f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_preference_learning_foundation_13233c3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.101-explicit-operator-feedback`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.101-explicit-operator-feedback.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/explicit_operator_feedback_3059b1c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/explicit_operator_feedback_3059b1c8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/explicit_operator_feedback_3059b1c8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_explicit_operator_feedback_3059b1c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.102-accepted-adaptation-feedback`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.102-accepted-adaptation-feedback.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/accepted_adaptation_feedback_16773051/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/accepted_adaptation_feedback_16773051.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/accepted_adaptation_feedback_16773051.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_accepted_adaptation_feedback_16773051.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.103-rejected-adaptation-feedback`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.103-rejected-adaptation-feedback.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/rejected_adaptation_feedback_3510140f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/rejected_adaptation_feedback_3510140f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/rejected_adaptation_feedback_3510140f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_rejected_adaptation_feedback_3510140f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.104-manual-override-learning`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.104-manual-override-learning.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/manual_override_learning_28239156/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/manual_override_learning_28239156.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/manual_override_learning_28239156.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_manual_override_learning_28239156.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.105-preference-provenance`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.105-preference-provenance.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/preference_provenance_4e08a36f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_provenance_4e08a36f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_provenance_4e08a36f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_preference_provenance_4e08a36f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.106-preference-confidence`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.106-preference-confidence.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/preference_confidence_bf3dacb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_confidence_bf3dacb9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_confidence_bf3dacb9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_preference_confidence_bf3dacb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.107-preference-decay`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.107-preference-decay.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/preference_decay_76f64d2d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_decay_76f64d2d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_decay_76f64d2d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_preference_decay_76f64d2d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.108-preference-reset`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.108-preference-reset.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/preference_reset_379dfd22/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_reset_379dfd22.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_reset_379dfd22.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_preference_reset_379dfd22.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.109-preference-export-and-inspection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.109-preference-export-and-inspection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/preference_export_and_inspection_8f2e5f37/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_export_and_inspection_8f2e5f37.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/preference_export_and_inspection_8f2e5f37.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_preference_export_and_inspection_8f2e5f37.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.110-factual-knowledge-versus-preference-separation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.110-factual-knowledge-versus-preference-separation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/factual_knowledge_versus_preference_separation_354f2917/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/factual_knowledge_versus_preference_separation_354f2917.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/factual_knowledge_versus_preference_separation_354f2917.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_factual_knowledge_versus_preference_separation_354f2917.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.111-outcome-learning-foundation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.111-outcome-learning-foundation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/outcome_learning_foundation_503b06e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_learning_foundation_503b06e5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/outcome_learning_foundation_503b06e5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_outcome_learning_foundation_503b06e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.112-verified-outcome-dataset`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.112-verified-outcome-dataset.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/verified_outcome_dataset_0520c8ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/verified_outcome_dataset_0520c8ca.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/verified_outcome_dataset_0520c8ca.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_verified_outcome_dataset_0520c8ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.113-adaptation-effectiveness-history`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.113-adaptation-effectiveness-history.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_effectiveness_history_e3faad5f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_effectiveness_history_e3faad5f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_effectiveness_history_e3faad5f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_effectiveness_history_e3faad5f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.114-context-specific-effectiveness`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.114-context-specific-effectiveness.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/context_specific_effectiveness_75ca9051/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_specific_effectiveness_75ca9051.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/context_specific_effectiveness_75ca9051.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_context_specific_effectiveness_75ca9051.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.115-regression-detection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.115-regression-detection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/regression_detection_01f1f2a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/regression_detection_01f1f2a4.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/regression_detection_01f1f2a4.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_regression_detection_01f1f2a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.116-adaptation-invalidation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.116-adaptation-invalidation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_invalidation_c80fc15e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_invalidation_c80fc15e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_invalidation_c80fc15e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_invalidation_c80fc15e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.117-stale-learned-policy-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.117-stale-learned-policy-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/stale_learned_policy_handling_86468e5c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/stale_learned_policy_handling_86468e5c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/stale_learned_policy_handling_86468e5c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_stale_learned_policy_handling_86468e5c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.118-learning-rollback`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.118-learning-rollback.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/learning_rollback_78bfd5a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/learning_rollback_78bfd5a2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/learning_rollback_78bfd5a2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_learning_rollback_78bfd5a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.119-online-learning-safety-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.119-online-learning-safety-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/online_learning_safety_boundary_a74b8607/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/online_learning_safety_boundary_a74b8607.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/online_learning_safety_boundary_a74b8607.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_online_learning_safety_boundary_a74b8607.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.120-semantic-learning-provider-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.120-semantic-learning-provider-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_learning_provider_boundary_9a170f1d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/semantic_learning_provider_boundary_9a170f1d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/semantic_learning_provider_boundary_9a170f1d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_semantic_learning_provider_boundary_9a170f1d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.121-cpu-topology-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.121-cpu-topology-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cpu_topology_adaptation_091c9fb0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/cpu_topology_adaptation_091c9fb0.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/cpu_topology_adaptation_091c9fb0.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_cpu_topology_adaptation_091c9fb0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.122-cpu-affinity-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.122-cpu-affinity-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cpu_affinity_adaptation_e0578d42/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/cpu_affinity_adaptation_e0578d42.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/cpu_affinity_adaptation_e0578d42.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_cpu_affinity_adaptation_e0578d42.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.123-cpu-frequency-policy-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.123-cpu-frequency-policy-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cpu_frequency_policy_boundary_ef014ffa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/cpu_frequency_policy_boundary_ef014ffa.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/cpu_frequency_policy_boundary_ef014ffa.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_cpu_frequency_policy_boundary_ef014ffa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.124-smt-policy-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.124-smt-policy-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/smt_policy_boundary_040b88aa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/smt_policy_boundary_040b88aa.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/smt_policy_boundary_040b88aa.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_smt_policy_boundary_040b88aa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.125-numa-placement-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.125-numa-placement-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/numa_placement_adaptation_afae5be6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/numa_placement_adaptation_afae5be6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/numa_placement_adaptation_afae5be6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_numa_placement_adaptation_afae5be6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.126-memory-pressure-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.126-memory-pressure-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/memory_pressure_adaptation_63a1cd53/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/memory_pressure_adaptation_63a1cd53.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/memory_pressure_adaptation_63a1cd53.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_memory_pressure_adaptation_63a1cd53.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.127-memory-locality-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.127-memory-locality-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/memory_locality_adaptation_eb0b45d3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/memory_locality_adaptation_eb0b45d3.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/memory_locality_adaptation_eb0b45d3.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_memory_locality_adaptation_eb0b45d3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.128-huge-page-policy-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.128-huge-page-policy-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/huge_page_policy_boundary_24bc01fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/huge_page_policy_boundary_24bc01fc.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/huge_page_policy_boundary_24bc01fc.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_huge_page_policy_boundary_24bc01fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.129-gpu-identity-safe-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.129-gpu-identity-safe-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/gpu_identity_safe_adaptation_35cf298f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/gpu_identity_safe_adaptation_35cf298f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/gpu_identity_safe_adaptation_35cf298f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_gpu_identity_safe_adaptation_35cf298f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.130-gpu-workload-placement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.130-gpu-workload-placement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/gpu_workload_placement_bb3cec27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_workload_placement_bb3cec27.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_workload_placement_bb3cec27.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_gpu_workload_placement_bb3cec27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.131-gpu-vram-pressure-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.131-gpu-vram-pressure-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/gpu_vram_pressure_adaptation_0265bd09/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_vram_pressure_adaptation_0265bd09.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_vram_pressure_adaptation_0265bd09.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_gpu_vram_pressure_adaptation_0265bd09.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.132-gpu-power-limit-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.132-gpu-power-limit-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/gpu_power_limit_adaptation_b3a2252a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_power_limit_adaptation_b3a2252a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_power_limit_adaptation_b3a2252a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_gpu_power_limit_adaptation_b3a2252a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.133-gpu-clock-policy-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.133-gpu-clock-policy-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/gpu_clock_policy_boundary_26324d93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/gpu_clock_policy_boundary_26324d93.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/gpu_clock_policy_boundary_26324d93.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_gpu_clock_policy_boundary_26324d93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.134-gpu-display-role-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.134-gpu-display-role-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/gpu_display_role_protection_7f996bc7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_display_role_protection_7f996bc7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/gpu_display_role_protection_7f996bc7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_gpu_display_role_protection_7f996bc7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.135-multi-gpu-workload-balancing`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.135-multi-gpu-workload-balancing.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/multi_gpu_workload_balancing_19b97649/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/multi_gpu_workload_balancing_19b97649.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/multi_gpu_workload_balancing_19b97649.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_multi_gpu_workload_balancing_19b97649.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.136-ai-model-placement-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.136-ai-model-placement-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/ai_model_placement_adaptation_e36ca9ef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/ai_model_placement_adaptation_e36ca9ef.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/ai_model_placement_adaptation_e36ca9ef.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_ai_model_placement_adaptation_e36ca9ef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.137-inference-concurrency-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.137-inference-concurrency-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/inference_concurrency_adaptation_e8ae64bd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/inference_concurrency_adaptation_e8ae64bd.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/inference_concurrency_adaptation_e8ae64bd.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_inference_concurrency_adaptation_e8ae64bd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.138-inference-context-resource-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.138-inference-context-resource-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/inference_context_resource_adaptation_4aad6dde/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/inference_context_resource_adaptation_4aad6dde.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/inference_context_resource_adaptation_4aad6dde.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_inference_context_resource_adaptation_4aad6dde.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.139-storage-i-o-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.139-storage-i-o-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/storage_i_o_adaptation_3bfe9e49/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/storage_i_o_adaptation_3bfe9e49.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/storage_i_o_adaptation_3bfe9e49.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_storage_i_o_adaptation_3bfe9e49.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.140-storage-workload-placement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.140-storage-workload-placement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/storage_workload_placement_4d2fd8d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/storage_workload_placement_4d2fd8d9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/storage_workload_placement_4d2fd8d9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_storage_workload_placement_4d2fd8d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.141-filesystem-cache-pressure-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.141-filesystem-cache-pressure-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/filesystem_cache_pressure_adaptation_a57475e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/persistence/filesystem_cache_pressure_adaptation_a57475e8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/persistence/filesystem_cache_pressure_adaptation_a57475e8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/persistence/test_filesystem_cache_pressure_adaptation_a57475e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.142-network-workload-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.142-network-workload-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/network_workload_adaptation_5d277984/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/network_workload_adaptation_5d277984.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/network_workload_adaptation_5d277984.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_network_workload_adaptation_5d277984.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.143-network-route-policy-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.143-network-route-policy-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/network_route_policy_boundary_6453da44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/network_route_policy_boundary_6453da44.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/network_route_policy_boundary_6453da44.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_network_route_policy_boundary_6453da44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.144-bandwidth-contention-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.144-bandwidth-contention-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/bandwidth_contention_adaptation_e8f71c3d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/bandwidth_contention_adaptation_e8f71c3d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/bandwidth_contention_adaptation_e8f71c3d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_bandwidth_contention_adaptation_e8f71c3d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.145-service-workload-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.145-service-workload-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/service_workload_adaptation_69da35ad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/service_workload_adaptation_69da35ad.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/service_workload_adaptation_69da35ad.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_service_workload_adaptation_69da35ad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.146-service-resource-limit-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.146-service-resource-limit-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/service_resource_limit_adaptation_1bb36021/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/service_resource_limit_adaptation_1bb36021.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/service_resource_limit_adaptation_1bb36021.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_service_resource_limit_adaptation_1bb36021.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.147-process-priority-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.147-process-priority-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/process_priority_adaptation_a5e2c517/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/process_priority_adaptation_a5e2c517.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/process_priority_adaptation_a5e2c517.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_process_priority_adaptation_a5e2c517.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.148-workload-scheduling-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.148-workload-scheduling-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/workload_scheduling_adaptation_a4b20909/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/workload_scheduling_adaptation_a4b20909.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/workload_scheduling_adaptation_a4b20909.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_workload_scheduling_adaptation_a4b20909.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.149-phase-29-workload-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.149-phase-29-workload-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/workload_integration_95b565b6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/workload_integration_95b565b6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/workload_integration_95b565b6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_workload_integration_95b565b6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.150-phase-30-resource-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.150-phase-30-resource-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/resource_integration_33001e9f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/resource_integration_33001e9f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/resource_integration_33001e9f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_resource_integration_33001e9f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.151-phase-31-service-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.151-phase-31-service-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/service_integration_8755d4b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/service_integration_8755d4b7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/service_integration_8755d4b7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_service_integration_8755d4b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.152-phase-32-storage-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.152-phase-32-storage-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/storage_integration_372181c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/storage_integration_372181c2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/storage_integration_372181c2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_storage_integration_372181c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.153-phase-33-network-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.153-phase-33-network-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/network_integration_7ff2cbe6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/network_integration_7ff2cbe6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/network_integration_7ff2cbe6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_network_integration_7ff2cbe6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.154-phase-34-accelerator-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.154-phase-34-accelerator-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/accelerator_integration_4dec03c6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/accelerator_integration_4dec03c6.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/accelerator_integration_4dec03c6.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_accelerator_integration_4dec03c6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.155-phase-35-software-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.155-phase-35-software-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/software_integration_c1160796/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/software_integration_c1160796.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/software_integration_c1160796.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_software_integration_c1160796.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.156-phase-36-configuration-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.156-phase-36-configuration-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/configuration_integration_c3a7a57b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/configuration_integration_c3a7a57b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/configuration_integration_c3a7a57b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_configuration_integration_c3a7a57b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.157-phase-37-secrets-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.157-phase-37-secrets-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/secrets_boundary_518d46d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/secrets_boundary_518d46d2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/secrets_boundary_518d46d2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_secrets_boundary_518d46d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.158-phase-38-identity-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.158-phase-38-identity-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/identity_boundary_bc1530e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/identity_boundary_bc1530e8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/identity_boundary_bc1530e8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_identity_boundary_bc1530e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.159-development-environment-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.159-development-environment-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/development_environment_adaptation_bb2fc6ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/development_environment_adaptation_bb2fc6ec.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/development_environment_adaptation_bb2fc6ec.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_development_environment_adaptation_bb2fc6ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.160-toolchain-profile-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.160-toolchain-profile-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/toolchain_profile_adaptation_4c31cd5e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/toolchain_profile_adaptation_4c31cd5e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/toolchain_profile_adaptation_4c31cd5e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_toolchain_profile_adaptation_4c31cd5e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.161-build-parallelism-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.161-build-parallelism-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/build_parallelism_adaptation_529a9c0c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/build_parallelism_adaptation_529a9c0c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/build_parallelism_adaptation_529a9c0c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_build_parallelism_adaptation_529a9c0c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.162-container-resource-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.162-container-resource-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/container_resource_adaptation_d9f5d443/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/container_resource_adaptation_d9f5d443.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/container_resource_adaptation_d9f5d443.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_container_resource_adaptation_d9f5d443.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.163-terminal-and-shell-profile-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.163-terminal-and-shell-profile-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/terminal_and_shell_profile_adaptation_1497edf4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/terminal_and_shell_profile_adaptation_1497edf4.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/terminal_and_shell_profile_adaptation_1497edf4.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_terminal_and_shell_profile_adaptation_1497edf4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.164-package-update-timing-recommendation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.164-package-update-timing-recommendation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/package_update_timing_recommendation_ac9d8250/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/package_update_timing_recommendation_ac9d8250.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/package_update_timing_recommendation_ac9d8250.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_package_update_timing_recommendation_ac9d8250.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.165-maintenance-window-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.165-maintenance-window-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/maintenance_window_adaptation_ff75d0ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/maintenance_window_adaptation_ff75d0ab.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/maintenance_window_adaptation_ff75d0ab.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_maintenance_window_adaptation_ff75d0ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.166-reboot-timing-recommendation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.166-reboot-timing-recommendation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/reboot_timing_recommendation_6b2040b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/reboot_timing_recommendation_6b2040b2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/reboot_timing_recommendation_6b2040b2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_reboot_timing_recommendation_6b2040b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.167-background-task-scheduling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.167-background-task-scheduling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/background_task_scheduling_dba892ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/background_task_scheduling_dba892ce.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/background_task_scheduling_dba892ce.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_background_task_scheduling_dba892ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.168-power-state-awareness`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.168-power-state-awareness.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/power_state_awareness_fb707d5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/power_state_awareness_fb707d5d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/power_state_awareness_fb707d5d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_power_state_awareness_fb707d5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.169-thermal-telemetry-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.169-thermal-telemetry-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/thermal_telemetry_integration_fcfca58d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/thermal_telemetry_integration_fcfca58d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/thermal_telemetry_integration_fcfca58d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_thermal_telemetry_integration_fcfca58d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.170-thermal-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.170-thermal-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/thermal_adaptation_06c7caf7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/thermal_adaptation_06c7caf7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/thermal_adaptation_06c7caf7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_thermal_adaptation_06c7caf7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.171-fan-control-authority-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.171-fan-control-authority-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/fan_control_authority_boundary_1e7c57de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/fan_control_authority_boundary_1e7c57de.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/fan_control_authority_boundary_1e7c57de.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_fan_control_authority_boundary_1e7c57de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.172-power-telemetry-integration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.172-power-telemetry-integration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/power_telemetry_integration_d8ea8e53/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/power_telemetry_integration_d8ea8e53.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/power_telemetry_integration_d8ea8e53.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_power_telemetry_integration_d8ea8e53.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.173-power-budget-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.173-power-budget-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/power_budget_adaptation_40241494/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/power_budget_adaptation_40241494.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/power_budget_adaptation_40241494.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_power_budget_adaptation_40241494.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.174-energy-efficiency-measurement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.174-energy-efficiency-measurement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/energy_efficiency_measurement_f7df56f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/energy_efficiency_measurement_f7df56f0.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/energy_efficiency_measurement_f7df56f0.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_energy_efficiency_measurement_f7df56f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.175-interactive-latency-measurement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.175-interactive-latency-measurement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/interactive_latency_measurement_8b9c0529/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/interactive_latency_measurement_8b9c0529.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/interactive_latency_measurement_8b9c0529.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_interactive_latency_measurement_8b9c0529.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.176-throughput-measurement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.176-throughput-measurement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/throughput_measurement_629e4b5e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/throughput_measurement_629e4b5e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/throughput_measurement_629e4b5e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_throughput_measurement_629e4b5e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.177-responsiveness-measurement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.177-responsiveness-measurement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/responsiveness_measurement_3593498c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/responsiveness_measurement_3593498c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/responsiveness_measurement_3593498c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_responsiveness_measurement_3593498c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.178-workload-completion-measurement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.178-workload-completion-measurement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/workload_completion_measurement_27001fb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/workload_completion_measurement_27001fb9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/workload_completion_measurement_27001fb9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_workload_completion_measurement_27001fb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.179-user-interruption-cost-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.179-user-interruption-cost-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/user_interruption_cost_model_c84ddf99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/user_interruption_cost_model_c84ddf99.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/user_interruption_cost_model_c84ddf99.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_user_interruption_cost_model_c84ddf99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.180-resource-contention-measurement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.180-resource-contention-measurement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/resource_contention_measurement_67704b9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/resource_contention_measurement_67704b9d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/resource_contention_measurement_67704b9d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_resource_contention_measurement_67704b9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.181-adaptive-metric-registry`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.181-adaptive-metric-registry.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_metric_registry_856e5405/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/adaptive_metric_registry_856e5405.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/adaptive_metric_registry_856e5405.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_adaptive_metric_registry_856e5405.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.182-metric-normalization`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.182-metric-normalization.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/metric_normalization_d8380560/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_normalization_d8380560.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_normalization_d8380560.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_metric_normalization_d8380560.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.183-metric-provenance`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.183-metric-provenance.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/metric_provenance_32d6560b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_provenance_32d6560b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_provenance_32d6560b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_metric_provenance_32d6560b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.184-metric-freshness`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.184-metric-freshness.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/metric_freshness_95c2e7b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_freshness_95c2e7b5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_freshness_95c2e7b5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_metric_freshness_95c2e7b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.185-metric-uncertainty`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.185-metric-uncertainty.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/metric_uncertainty_661b590f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_uncertainty_661b590f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/metric_uncertainty_661b590f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_metric_uncertainty_661b590f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.186-composite-objective-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.186-composite-objective-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/composite_objective_model_b47b806a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/composite_objective_model_b47b806a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/composite_objective_model_b47b806a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_composite_objective_model_b47b806a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.187-multi-objective-tradeoff-representation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.187-multi-objective-tradeoff-representation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/multi_objective_tradeoff_representation_45f23244/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/multi_objective_tradeoff_representation_45f23244.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/multi_objective_tradeoff_representation_45f23244.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_multi_objective_tradeoff_representation_45f23244.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.188-operator-objective-weighting`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.188-operator-objective-weighting.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/operator_objective_weighting_8e9b4a21/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/operator_objective_weighting_8e9b4a21.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/operator_objective_weighting_8e9b4a21.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_operator_objective_weighting_8e9b4a21.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.189-objective-conflict-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.189-objective-conflict-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/objective_conflict_handling_ee92fb74/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/objective_conflict_handling_ee92fb74.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/objective_conflict_handling_ee92fb74.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_objective_conflict_handling_ee92fb74.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.190-hard-constraints-versus-soft-goals`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.190-hard-constraints-versus-soft-goals.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/hard_constraints_versus_soft_goals_3ca4097c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/hard_constraints_versus_soft_goals_3ca4097c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/hard_constraints_versus_soft_goals_3ca4097c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_hard_constraints_versus_soft_goals_3ca4097c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.191-constraint-validation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.191-constraint-validation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/constraint_validation_108d7055/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/constraint_validation_108d7055.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/constraint_validation_108d7055.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_constraint_validation_108d7055.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.192-constraint-violation-rollback`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.192-constraint-violation-rollback.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/constraint_violation_rollback_9cea08ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/constraint_violation_rollback_9cea08ce.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/constraint_violation_rollback_9cea08ce.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_constraint_violation_rollback_9cea08ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.193-change-budget`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.193-change-budget.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/change_budget_76837772/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/change_budget_76837772.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/change_budget_76837772.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_change_budget_76837772.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.194-resource-budget`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.194-resource-budget.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/resource_budget_d9bfc7e2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/resource_budget_d9bfc7e2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/resource_budget_d9bfc7e2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_resource_budget_d9bfc7e2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.195-risk-budget`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.195-risk-budget.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/risk_budget_0ca1782f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/risk_budget_0ca1782f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/risk_budget_0ca1782f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_risk_budget_0ca1782f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.196-adaptation-frequency-budget`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.196-adaptation-frequency-budget.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_frequency_budget_1a612306/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_frequency_budget_1a612306.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_frequency_budget_1a612306.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_frequency_budget_1a612306.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.197-per-domain-mutation-budget`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.197-per-domain-mutation-budget.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/per_domain_mutation_budget_1d0ec460/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/execution/per_domain_mutation_budget_1d0ec460.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/execution/per_domain_mutation_budget_1d0ec460.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/execution/test_per_domain_mutation_budget_1d0ec460.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.198-automatic-action-allowlist`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.198-automatic-action-allowlist.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/automatic_action_allowlist_f0bf698f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/automatic_action_allowlist_f0bf698f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/automatic_action_allowlist_f0bf698f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_automatic_action_allowlist_f0bf698f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.199-automatic-action-denylist`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.199-automatic-action-denylist.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/automatic_action_denylist_19ce3f3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/automatic_action_denylist_19ce3f3f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/automatic_action_denylist_19ce3f3f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_automatic_action_denylist_19ce3f3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.200-protected-resource-registry`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.200-protected-resource-registry.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/protected_resource_registry_119051bc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/protected_resource_registry_119051bc.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/protected_resource_registry_119051bc.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_protected_resource_registry_119051bc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.201-protected-maintenance-path`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.201-protected-maintenance-path.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/protected_maintenance_path_1a2ebd82/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/protected_maintenance_path_1a2ebd82.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/protected_maintenance_path_1a2ebd82.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_protected_maintenance_path_1a2ebd82.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.202-boot-safety-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.202-boot-safety-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/boot_safety_protection_742f57bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/boot_safety_protection_742f57bf.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/boot_safety_protection_742f57bf.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_boot_safety_protection_742f57bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.203-storage-integrity-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.203-storage-integrity-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/storage_integrity_protection_6b05bed2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/storage_integrity_protection_6b05bed2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/storage_integrity_protection_6b05bed2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_storage_integrity_protection_6b05bed2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.204-network-access-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.204-network-access-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/network_access_protection_5361f582/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/network_access_protection_5361f582.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/network_access_protection_5361f582.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_network_access_protection_5361f582.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.205-ssh-access-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.205-ssh-access-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/ssh_access_protection_a0f9f1ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/ssh_access_protection_a0f9f1ed.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/ssh_access_protection_a0f9f1ed.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_ssh_access_protection_a0f9f1ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.206-graphical-session-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.206-graphical-session-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/graphical_session_protection_35655e88/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/graphical_session_protection_35655e88.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/graphical_session_protection_35655e88.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_graphical_session_protection_35655e88.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.207-security-control-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.207-security-control-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/security_control_protection_e7819834/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/security_control_protection_e7819834.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/security_control_protection_e7819834.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_security_control_protection_e7819834.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.208-package-trust-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.208-package-trust-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/package_trust_protection_9c1ad578/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/package_trust_protection_9c1ad578.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/package_trust_protection_9c1ad578.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_package_trust_protection_9c1ad578.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.209-rebuntu-control-plane-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.209-rebuntu-control-plane-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/rebuntu_control_plane_protection_bf56394d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/planning/rebuntu_control_plane_protection_bf56394d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/planning/rebuntu_control_plane_protection_bf56394d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/planning/test_rebuntu_control_plane_protection_bf56394d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.210-failure-domain-isolation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.210-failure-domain-isolation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/failure_domain_isolation_7acddda3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/failure_domain_isolation_7acddda3.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/failure_domain_isolation_7acddda3.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_failure_domain_isolation_7acddda3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.211-blast-radius-estimation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.211-blast-radius-estimation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/blast_radius_estimation_2542b36f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/blast_radius_estimation_2542b36f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/blast_radius_estimation_2542b36f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_blast_radius_estimation_2542b36f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.212-change-impact-preflight`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.212-change-impact-preflight.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/change_impact_preflight_b8afa152/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/change_impact_preflight_b8afa152.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/change_impact_preflight_b8afa152.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_change_impact_preflight_b8afa152.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.213-concurrent-adaptation-coordination`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.213-concurrent-adaptation-coordination.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/concurrent_adaptation_coordination_1bf8a2a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/concurrent_adaptation_coordination_1bf8a2a3.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/concurrent_adaptation_coordination_1bf8a2a3.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_concurrent_adaptation_coordination_1bf8a2a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.214-adaptation-locking`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.214-adaptation-locking.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_locking_7aa43c98/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_locking_7aa43c98.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_locking_7aa43c98.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_locking_7aa43c98.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.215-race-and-toctou-protection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.215-race-and-toctou-protection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/race_and_toctou_protection_feb6450e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/race_and_toctou_protection_feb6450e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/race_and_toctou_protection_feb6450e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_race_and_toctou_protection_feb6450e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.216-external-change-detection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.216-external-change-detection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/external_change_detection_f87e7600/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/external_change_detection_f87e7600.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/external_change_detection_f87e7600.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_external_change_detection_f87e7600.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.217-operator-change-detection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.217-operator-change-detection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/operator_change_detection_1e2f1f81/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/operator_change_detection_1e2f1f81.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/operator_change_detection_1e2f1f81.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_operator_change_detection_1e2f1f81.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.218-drift-during-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.218-drift-during-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/drift_during_adaptation_c24e21c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/drift_during_adaptation_c24e21c5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/drift_during_adaptation_c24e21c5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_drift_during_adaptation_c24e21c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.219-adaptation-reconciliation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.219-adaptation-reconciliation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_reconciliation_a320cfe9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_reconciliation_a320cfe9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_reconciliation_a320cfe9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_reconciliation_a320cfe9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.220-crash-recovery`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.220-crash-recovery.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/crash_recovery_d54b5d37/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/crash_recovery_d54b5d37.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/crash_recovery_d54b5d37.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_crash_recovery_d54b5d37.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.221-daemon-restart-recovery`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.221-daemon-restart-recovery.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/daemon_restart_recovery_bc0480a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/daemon_restart_recovery_bc0480a8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/daemon_restart_recovery_bc0480a8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_daemon_restart_recovery_bc0480a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.222-reboot-continuity`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.222-reboot-continuity.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/reboot_continuity_e0f86a0a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/reboot_continuity_e0f86a0a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/reboot_continuity_e0f86a0a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_reboot_continuity_e0f86a0a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.223-interrupted-adaptation-recovery`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.223-interrupted-adaptation-recovery.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/interrupted_adaptation_recovery_beb8a11a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/interrupted_adaptation_recovery_beb8a11a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/interrupted_adaptation_recovery_beb8a11a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_interrupted_adaptation_recovery_beb8a11a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.224-interrupted-rollback-recovery`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.224-interrupted-rollback-recovery.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/interrupted_rollback_recovery_22c1f203/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/interrupted_rollback_recovery_22c1f203.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/interrupted_rollback_recovery_22c1f203.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_interrupted_rollback_recovery_22c1f203.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.225-durable-adaptive-state`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.225-durable-adaptive-state.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/durable_adaptive_state_05856844/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/durable_adaptive_state_05856844.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/durable_adaptive_state_05856844.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_durable_adaptive_state_05856844.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.226-idempotent-recovery-operations`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.226-idempotent-recovery-operations.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/idempotent_recovery_operations_b9854163/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/idempotent_recovery_operations_b9854163.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/idempotent_recovery_operations_b9854163.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_idempotent_recovery_operations_b9854163.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.227-adaptive-event-recording`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.227-adaptive-event-recording.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_event_recording_35ff462f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptive_event_recording_35ff462f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptive_event_recording_35ff462f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptive_event_recording_35ff462f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.228-adaptive-audit-trail`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.228-adaptive-audit-trail.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_audit_trail_6fa76812/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/adaptive_audit_trail_6fa76812.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/adaptive_audit_trail_6fa76812.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_adaptive_audit_trail_6fa76812.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.229-adaptive-observability`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.229-adaptive-observability.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_observability_faa438c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/adaptive_observability_faa438c4.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/adaptive_observability_faa438c4.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_adaptive_observability_faa438c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.230-adaptive-metrics-telemetry`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.230-adaptive-metrics-telemetry.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_metrics_telemetry_d5f41e2c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/adaptive_metrics_telemetry_d5f41e2c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/adaptive_metrics_telemetry_d5f41e2c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_adaptive_metrics_telemetry_d5f41e2c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.231-cli-adaptation-inspection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.231-cli-adaptation-inspection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cli_adaptation_inspection_cb01e151/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/cli_adaptation_inspection_cb01e151.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/cli_adaptation_inspection_cb01e151.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_cli_adaptation_inspection_cb01e151.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.232-cli-recommendation-inspection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.232-cli-recommendation-inspection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cli_recommendation_inspection_dfaf5198/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/cli_recommendation_inspection_dfaf5198.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/cli_recommendation_inspection_dfaf5198.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_cli_recommendation_inspection_dfaf5198.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.233-cli-policy-inspection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.233-cli-policy-inspection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cli_policy_inspection_9bef1aac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/cli_policy_inspection_9bef1aac.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/cli_policy_inspection_9bef1aac.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_cli_policy_inspection_9bef1aac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.234-cli-freeze-and-resume`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.234-cli-freeze-and-resume.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cli_freeze_and_resume_3211e03b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/cli_freeze_and_resume_3211e03b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/cli_freeze_and_resume_3211e03b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_cli_freeze_and_resume_3211e03b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.235-cli-rollback-control`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.235-cli-rollback-control.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/cli_rollback_control_70b6a464/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/cli_rollback_control_70b6a464.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/cli_rollback_control_70b6a464.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_cli_rollback_control_70b6a464.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.236-phase-25-panel-adaptive-overview`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.236-phase-25-panel-adaptive-overview.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_adaptive_overview_a50af584/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_adaptive_overview_a50af584.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_adaptive_overview_a50af584.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_panel_adaptive_overview_a50af584.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.237-panel-active-goal-view`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.237-panel-active-goal-view.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_active_goal_view_53c0ed92/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_active_goal_view_53c0ed92.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_active_goal_view_53c0ed92.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_panel_active_goal_view_53c0ed92.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.238-panel-recommendation-view`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.238-panel-recommendation-view.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_recommendation_view_2aba144b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_recommendation_view_2aba144b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_recommendation_view_2aba144b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_panel_recommendation_view_2aba144b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.239-panel-adaptation-history-view`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.239-panel-adaptation-history-view.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_adaptation_history_view_80ebec1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_adaptation_history_view_80ebec1f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_adaptation_history_view_80ebec1f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_panel_adaptation_history_view_80ebec1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.240-panel-outcome-view`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.240-panel-outcome-view.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_outcome_view_07f75d5c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_outcome_view_07f75d5c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_outcome_view_07f75d5c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_panel_outcome_view_07f75d5c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.241-panel-policy-view`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.241-panel-policy-view.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_policy_view_0788e9af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/panel_policy_view_0788e9af.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/panel_policy_view_0788e9af.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_panel_policy_view_0788e9af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.242-panel-rollback-surface`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.242-panel-rollback-surface.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_rollback_surface_69a7f567/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/panel_rollback_surface_69a7f567.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/panel_rollback_surface_69a7f567.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_panel_rollback_surface_69a7f567.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.243-panel-safe-mode-controls`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.243-panel-safe-mode-controls.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/panel_safe_mode_controls_32e0ad23/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_safe_mode_controls_32e0ad23.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/panel_safe_mode_controls_32e0ad23.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_panel_safe_mode_controls_32e0ad23.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.244-explain-why-adapted`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.244-explain-why-adapted.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/explain_why_adapted_eb11140c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_why_adapted_eb11140c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_why_adapted_eb11140c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_explain_why_adapted_eb11140c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.245-explain-why-not-adapted`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.245-explain-why-not-adapted.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/explain_why_not_adapted_d694eee7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_why_not_adapted_d694eee7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_why_not_adapted_d694eee7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_explain_why_not_adapted_d694eee7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.246-explain-expected-effect`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.246-explain-expected-effect.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/explain_expected_effect_83e32391/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_expected_effect_83e32391.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_expected_effect_83e32391.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_explain_expected_effect_83e32391.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.247-explain-measured-outcome`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.247-explain-measured-outcome.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/explain_measured_outcome_d741de27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_measured_outcome_d741de27.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/observability/explain_measured_outcome_d741de27.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/observability/test_explain_measured_outcome_d741de27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.248-explain-rollback-reason`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.248-explain-rollback-reason.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/explain_rollback_reason_a12d603e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/recovery/explain_rollback_reason_a12d603e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/recovery/explain_rollback_reason_a12d603e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/recovery/test_explain_rollback_reason_a12d603e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.249-semantic-explanation-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.249-semantic-explanation-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_explanation_boundary_d317a03a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/planning/semantic_explanation_boundary_d317a03a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/planning/semantic_explanation_boundary_d317a03a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/planning/test_semantic_explanation_boundary_d317a03a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.250-semantic-candidate-generation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.250-semantic-candidate-generation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_candidate_generation_5d08844c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_candidate_generation_5d08844c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_candidate_generation_5d08844c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_semantic_candidate_generation_5d08844c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.251-semantic-profile-suggestion`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.251-semantic-profile-suggestion.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_profile_suggestion_39cace06/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_profile_suggestion_39cace06.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_profile_suggestion_39cace06.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_semantic_profile_suggestion_39cace06.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.252-semantic-objective-interpretation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.252-semantic-objective-interpretation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_objective_interpretation_a977b7a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_objective_interpretation_a977b7a8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_objective_interpretation_a977b7a8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_semantic_objective_interpretation_a977b7a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.253-semantic-output-validation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.253-semantic-output-validation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_output_validation_fb21aca1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_output_validation_fb21aca1.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_output_validation_fb21aca1.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_semantic_output_validation_fb21aca1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.254-semantic-no-authority-enforcement`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.254-semantic-no-authority-enforcement.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_no_authority_enforcement_777fe3b3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_no_authority_enforcement_777fe3b3.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/semantic_no_authority_enforcement_777fe3b3.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_semantic_no_authority_enforcement_777fe3b3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.255-prompt-injection-resistance`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.255-prompt-injection-resistance.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/prompt_injection_resistance_7b66fad5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/prompt_injection_resistance_7b66fad5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/prompt_injection_resistance_7b66fad5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_prompt_injection_resistance_7b66fad5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.256-untrusted-telemetry-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.256-untrusted-telemetry-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/untrusted_telemetry_handling_2105b480/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/untrusted_telemetry_handling_2105b480.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/untrusted_telemetry_handling_2105b480.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_untrusted_telemetry_handling_2105b480.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.257-untrusted-configuration-handling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.257-untrusted-configuration-handling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/untrusted_configuration_handling_9b6b256b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/untrusted_configuration_handling_9b6b256b.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/untrusted_configuration_handling_9b6b256b.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_untrusted_configuration_handling_9b6b256b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.258-secret-exfiltration-resistance`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.258-secret-exfiltration-resistance.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/secret_exfiltration_resistance_c8ed56d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/secret_exfiltration_resistance_c8ed56d4.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/secret_exfiltration_resistance_c8ed56d4.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_secret_exfiltration_resistance_c8ed56d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.259-authorization-bypass-resistance`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.259-authorization-bypass-resistance.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/authorization_bypass_resistance_d5e2b0cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/security/authorization_bypass_resistance_d5e2b0cf.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/security/authorization_bypass_resistance_d5e2b0cf.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/security/test_authorization_bypass_resistance_d5e2b0cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.260-no-arbitrary-shell-authority`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.260-no-arbitrary-shell-authority.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/no_arbitrary_shell_authority_3299471a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/no_arbitrary_shell_authority_3299471a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/no_arbitrary_shell_authority_3299471a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_no_arbitrary_shell_authority_3299471a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.261-deterministic-fallback-without-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.261-deterministic-fallback-without-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/deterministic_fallback_without_model_73ea2150/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/deterministic_fallback_without_model_73ea2150.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/deterministic_fallback_without_model_73ea2150.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_deterministic_fallback_without_model_73ea2150.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.262-provider-outage-degradation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.262-provider-outage-degradation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/provider_outage_degradation_c560c24a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/integration/provider_outage_degradation_c560c24a.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/integration/provider_outage_degradation_c560c24a.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/integration/test_provider_outage_degradation_c560c24a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.263-resource-exhaustion-degradation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.263-resource-exhaustion-degradation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/resource_exhaustion_degradation_d72884ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/resource_exhaustion_degradation_d72884ae.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/resource_exhaustion_degradation_d72884ae.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_resource_exhaustion_degradation_d72884ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.264-low-confidence-behavior`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.264-low-confidence-behavior.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/low_confidence_behavior_b75e41a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/low_confidence_behavior_b75e41a7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/low_confidence_behavior_b75e41a7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_low_confidence_behavior_b75e41a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.265-insufficient-evidence-behavior`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.265-insufficient-evidence-behavior.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/insufficient_evidence_behavior_4edf4937/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/insufficient_evidence_behavior_4edf4937.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/insufficient_evidence_behavior_4edf4937.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_insufficient_evidence_behavior_4edf4937.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.266-conflicting-evidence-behavior`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.266-conflicting-evidence-behavior.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/conflicting_evidence_behavior_51420ea2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/conflicting_evidence_behavior_51420ea2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/conflicting_evidence_behavior_51420ea2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_conflicting_evidence_behavior_51420ea2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.267-simulation-interface`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.267-simulation-interface.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/simulation_interface_44e2a386/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/simulation_interface_44e2a386.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/simulation_interface_44e2a386.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_simulation_interface_44e2a386.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.268-dry-run-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.268-dry-run-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/dry_run_adaptation_3cefd622/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/dry_run_adaptation_3cefd622.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/dry_run_adaptation_3cefd622.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_dry_run_adaptation_3cefd622.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.269-counterfactual-estimation-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.269-counterfactual-estimation-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/counterfactual_estimation_boundary_f02deb09/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/counterfactual_estimation_boundary_f02deb09.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/counterfactual_estimation_boundary_f02deb09.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_counterfactual_estimation_boundary_f02deb09.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.270-historical-replay-evaluation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.270-historical-replay-evaluation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/historical_replay_evaluation_7d174ebb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/historical_replay_evaluation_7d174ebb.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/historical_replay_evaluation_7d174ebb.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_historical_replay_evaluation_7d174ebb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.271-shadow-mode-adaptation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.271-shadow-mode-adaptation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/shadow_mode_adaptation_60bd124c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/shadow_mode_adaptation_60bd124c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/shadow_mode_adaptation_60bd124c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_shadow_mode_adaptation_60bd124c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.272-canary-adaptation-boundary`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.272-canary-adaptation-boundary.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/canary_adaptation_boundary_dd132b27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/canary_adaptation_boundary_dd132b27.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/canary_adaptation_boundary_dd132b27.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_canary_adaptation_boundary_dd132b27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.273-staged-rollout-on-local-resources`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.273-staged-rollout-on-local-resources.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/staged_rollout_on_local_resources_ecd475aa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/staged_rollout_on_local_resources_ecd475aa.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/staged_rollout_on_local_resources_ecd475aa.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_staged_rollout_on_local_resources_ecd475aa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.274-adaptation-calibration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.274-adaptation-calibration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptation_calibration_f0b2b543/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_calibration_f0b2b543.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptation_calibration_f0b2b543.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptation_calibration_f0b2b543.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.275-prediction-versus-outcome-calibration`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.275-prediction-versus-outcome-calibration.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/prediction_versus_outcome_calibration_1c7207eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/prediction_versus_outcome_calibration_1c7207eb.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/prediction_versus_outcome_calibration_1c7207eb.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_prediction_versus_outcome_calibration_1c7207eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.276-false-positive-adaptation-analysis`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.276-false-positive-adaptation-analysis.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/false_positive_adaptation_analysis_075afee8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/false_positive_adaptation_analysis_075afee8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/false_positive_adaptation_analysis_075afee8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_false_positive_adaptation_analysis_075afee8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.277-false-negative-adaptation-analysis`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.277-false-negative-adaptation-analysis.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/false_negative_adaptation_analysis_18fb5366/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/false_negative_adaptation_analysis_18fb5366.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/false_negative_adaptation_analysis_18fb5366.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_false_negative_adaptation_analysis_18fb5366.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.278-over-adaptation-detection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.278-over-adaptation-detection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/over_adaptation_detection_648d6817/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/over_adaptation_detection_648d6817.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/over_adaptation_detection_648d6817.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_over_adaptation_detection_648d6817.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.279-under-adaptation-detection`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.279-under-adaptation-detection.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/under_adaptation_detection_aa0d81fa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/under_adaptation_detection_aa0d81fa.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/under_adaptation_detection_aa0d81fa.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_under_adaptation_detection_aa0d81fa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.280-oscillation-adversarial-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.280-oscillation-adversarial-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/oscillation_adversarial_tests_3c21678d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/oscillation_adversarial_tests_3c21678d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/oscillation_adversarial_tests_3c21678d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_oscillation_adversarial_tests_3c21678d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.281-feedback-loop-adversarial-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.281-feedback-loop-adversarial-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/feedback_loop_adversarial_tests_66b8341e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/feedback_loop_adversarial_tests_66b8341e.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/feedback_loop_adversarial_tests_66b8341e.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_feedback_loop_adversarial_tests_66b8341e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.282-rollback-adversarial-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.282-rollback-adversarial-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/rollback_adversarial_tests_7578d7d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/rollback_adversarial_tests_7578d7d2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/rollback_adversarial_tests_7578d7d2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_rollback_adversarial_tests_7578d7d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.283-authorization-adversarial-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.283-authorization-adversarial-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/authorization_adversarial_tests_80e49bcf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/authorization_adversarial_tests_80e49bcf.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/authorization_adversarial_tests_80e49bcf.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_authorization_adversarial_tests_80e49bcf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.284-protected-resource-adversarial-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.284-protected-resource-adversarial-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/protected_resource_adversarial_tests_03f910a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/protected_resource_adversarial_tests_03f910a9.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/protected_resource_adversarial_tests_03f910a9.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_protected_resource_adversarial_tests_03f910a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.285-resource-contention-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.285-resource-contention-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/resource_contention_tests_d4dd9cab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/resource_contention_tests_d4dd9cab.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/resource_contention_tests_d4dd9cab.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_resource_contention_tests_d4dd9cab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.286-multi-gpu-adaptation-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.286-multi-gpu-adaptation-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/multi_gpu_adaptation_tests_b15f0a46/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/multi_gpu_adaptation_tests_b15f0a46.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/multi_gpu_adaptation_tests_b15f0a46.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_multi_gpu_adaptation_tests_b15f0a46.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.287-numa-adaptation-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.287-numa-adaptation-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/numa_adaptation_tests_4845d918/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/numa_adaptation_tests_4845d918.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/numa_adaptation_tests_4845d918.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_numa_adaptation_tests_4845d918.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.288-network-continuity-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.288-network-continuity-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/network_continuity_tests_665530d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/network_continuity_tests_665530d7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/network_continuity_tests_665530d7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_network_continuity_tests_665530d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.289-storage-safety-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.289-storage-safety-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/storage_safety_tests_60d5f37f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/storage_safety_tests_60d5f37f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/storage_safety_tests_60d5f37f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_storage_safety_tests_60d5f37f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.290-graphical-session-continuity-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.290-graphical-session-continuity-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/graphical_session_continuity_tests_0f6ac5ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/graphical_session_continuity_tests_0f6ac5ee.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/graphical_session_continuity_tests_0f6ac5ee.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_graphical_session_continuity_tests_0f6ac5ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.291-crash-restart-reboot-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.291-crash-restart-reboot-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/crash_restart_reboot_tests_8cb4b6c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/crash_restart_reboot_tests_8cb4b6c4.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/crash_restart_reboot_tests_8cb4b6c4.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_crash_restart_reboot_tests_8cb4b6c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.292-concurrent-mutation-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.292-concurrent-mutation-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/concurrent_mutation_tests_7e17c04c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/concurrent_mutation_tests_7e17c04c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/concurrent_mutation_tests_7e17c04c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_concurrent_mutation_tests_7e17c04c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.293-external-drift-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.293-external-drift-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/external_drift_tests_d469a8f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/external_drift_tests_d469a8f0.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/external_drift_tests_d469a8f0.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_external_drift_tests_d469a8f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.294-semantic-provider-failure-tests`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.294-semantic-provider-failure-tests.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/semantic_provider_failure_tests_910f3b9c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/semantic_provider_failure_tests_910f3b9c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/semantic_provider_failure_tests_910f3b9c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_semantic_provider_failure_tests_910f3b9c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.295-end-to-end-development-scenario`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.295-end-to-end-development-scenario.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/end_to_end_development_scenario_ec850acc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_development_scenario_ec850acc.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_development_scenario_ec850acc.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_end_to_end_development_scenario_ec850acc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.296-end-to-end-ai-inference-scenario`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.296-end-to-end-ai-inference-scenario.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/end_to_end_ai_inference_scenario_0361c37d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_ai_inference_scenario_0361c37d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_ai_inference_scenario_0361c37d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_end_to_end_ai_inference_scenario_0361c37d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.297-end-to-end-gaming-scenario`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.297-end-to-end-gaming-scenario.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/end_to_end_gaming_scenario_6e9d6e0f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_gaming_scenario_6e9d6e0f.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_gaming_scenario_6e9d6e0f.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_end_to_end_gaming_scenario_6e9d6e0f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.298-end-to-end-maintenance-scenario`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.298-end-to-end-maintenance-scenario.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/end_to_end_maintenance_scenario_2be9642d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_maintenance_scenario_2be9642d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_maintenance_scenario_2be9642d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_end_to_end_maintenance_scenario_2be9642d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.299-end-to-end-degraded-mode-scenario`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.299-end-to-end-degraded-mode-scenario.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/end_to_end_degraded_mode_scenario_dddd2883/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_degraded_mode_scenario_dddd2883.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/end_to_end_degraded_mode_scenario_dddd2883.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_end_to_end_degraded_mode_scenario_dddd2883.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.300-performance-profiling`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.300-performance-profiling.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/performance_profiling_e3e561f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/performance_profiling_e3e561f7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/performance_profiling_e3e561f7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_performance_profiling_e3e561f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.301-adaptive-runtime-overhead`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.301-adaptive-runtime-overhead.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adaptive_runtime_overhead_c67a6b02/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptive_runtime_overhead_c67a6b02.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/adaptive_runtime_overhead_c67a6b02.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_adaptive_runtime_overhead_c67a6b02.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.302-memory-and-state-bounds`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.302-memory-and-state-bounds.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/memory_and_state_bounds_f140834d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/memory_and_state_bounds_f140834d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/lifecycle/memory_and_state_bounds_f140834d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/lifecycle/test_memory_and_state_bounds_f140834d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.303-scalability-validation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.303-scalability-validation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/scalability_validation_1bbd08d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/scalability_validation_1bbd08d5.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/scalability_validation_1bbd08d5.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_scalability_validation_1bbd08d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.304-configuration-model`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.304-configuration-model.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/configuration_model_c4614244/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/configuration_model_c4614244.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/configuration_model_c4614244.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_configuration_model_c4614244.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.305-feature-capability-discovery`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.305-feature-capability-discovery.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/feature_capability_discovery_36e3eb2c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/resolution/feature_capability_discovery_36e3eb2c.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/resolution/feature_capability_discovery_36e3eb2c.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/resolution/test_feature_capability_discovery_36e3eb2c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.306-documentation-reconciliation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.306-documentation-reconciliation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/documentation_reconciliation_40b01dc8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/documentation_reconciliation_40b01dc8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/documentation_reconciliation_40b01dc8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_documentation_reconciliation_40b01dc8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.307-architecture-reconciliation`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.307-architecture-reconciliation.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/architecture_reconciliation_226c94d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/architecture_reconciliation_226c94d2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/architecture_reconciliation_226c94d2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_architecture_reconciliation_226c94d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.308-agents-md-permanent-adaptive-contract`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.308-agents-md-permanent-adaptive-contract.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/agents_md_permanent_adaptive_contract_92efadad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/contracts/agents_md_permanent_adaptive_contract_92efadad.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/contracts/agents_md_permanent_adaptive_contract_92efadad.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/contracts/test_agents_md_permanent_adaptive_contract_92efadad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.309-repository-wide-recursive-rediscovery`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.309-repository-wide-recursive-rediscovery.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/repository_wide_recursive_rediscovery_4e336ad7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/resolution/repository_wide_recursive_rediscovery_4e336ad7.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/resolution/repository_wide_recursive_rediscovery_4e336ad7.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/resolution/test_repository_wide_recursive_rediscovery_4e336ad7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.310-duplicate-tuning-authority-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.310-duplicate-tuning-authority-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/duplicate_tuning_authority_audit_3fe4af07/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/duplicate_tuning_authority_audit_3fe4af07.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/duplicate_tuning_authority_audit_3fe4af07.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_duplicate_tuning_authority_audit_3fe4af07.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.311-remaining-python-boundary-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.311-remaining-python-boundary-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/remaining_python_boundary_audit_31813662/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/remaining_python_boundary_audit_31813662.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/remaining_python_boundary_audit_31813662.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_remaining_python_boundary_audit_31813662.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.312-policy-authority-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.312-policy-authority-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/policy_authority_audit_f3c5c4b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/policy_authority_audit_f3c5c4b2.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/policy_authority_audit_f3c5c4b2.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_policy_authority_audit_f3c5c4b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.313-outcome-grounding-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.313-outcome-grounding-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/outcome_grounding_audit_549f0ea1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/outcome_grounding_audit_549f0ea1.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/outcome_grounding_audit_549f0ea1.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_outcome_grounding_audit_549f0ea1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.314-learning-safety-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.314-learning-safety-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/learning_safety_audit_c43766f8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/learning_safety_audit_c43766f8.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/learning_safety_audit_c43766f8.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_learning_safety_audit_c43766f8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.315-protected-resource-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.315-protected-resource-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/protected_resource_audit_6e9a51b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/protected_resource_audit_6e9a51b4.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/protected_resource_audit_6e9a51b4.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_protected_resource_audit_6e9a51b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.316-rollback-completeness-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.316-rollback-completeness-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/rollback_completeness_audit_6bf4766d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/rollback_completeness_audit_6bf4766d.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/rollback_completeness_audit_6bf4766d.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_rollback_completeness_audit_6bf4766d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.317-adversarial-self-modification-audit`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.317-adversarial-self-modification-audit.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/adversarial_self_modification_audit_4df3f4d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/verification/adversarial_self_modification_audit_4df3f4d1.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/verification/adversarial_self_modification_audit_4df3f4d1.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/verification/test_adversarial_self_modification_audit_4df3f4d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.318-final-fixed-point-rediscovery`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.318-final-fixed-point-rediscovery.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/final_fixed_point_rediscovery_6e9e1bef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/resolution/final_fixed_point_rediscovery_6e9e1bef.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/resolution/final_fixed_point_rediscovery_6e9e1bef.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/resolution/test_final_fixed_point_rediscovery_6e9e1bef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `44.319-phase-44-closure-and-phase-45-handoff`
- **Source:** `.phases/phases/phase-44-adaptive-workstation-system/prompts/44.319-phase-44-closure-and-phase-45-handoff.md`
- **Structural package:** `src/domains/adaptive-workstation-system/subtask_packages/verification/closure_and_phase_45_handoff_0b5b9eec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/adaptive-workstation-system/subtask_targets/requirements/closure_and_phase_45_handoff_0b5b9eec.hpp`, `src/domains/adaptive-workstation-system/subtask_targets/requirements/closure_and_phase_45_handoff_0b5b9eec.cpp`
- **Structural test target:** `tests/structural-closure/domains/adaptive-workstation-system/requirements/test_closure_and_phase_45_handoff_0b5b9eec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

