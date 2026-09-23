# Phase 29 — Process Workload Management — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-29-process-workload-management/`
- Primary prompt location: `.phases/phases/phase-29-process-workload-management/prompts/`
- Prompt/specification Markdown files currently present: **54**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 54 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_29` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 29: Process Workload Management
- Layout
- Prompt Index
- Agent Handoff — Phase 29
- Phase 29.42 — Process & Workload Management CLI
- Mission
- Non-negotiable architecture and invariants
- Phase-specific implementation requirements
- Required implementation method
- 1. Repository-first discovery
- 2. Linux/provider evidence
- 3. Stable identity and race discipline

## Structural skeleton / canonical destination
- Canonical skeleton: `src/domains/process-workload-management/`
- Structural files: `src/domains/process-workload-management/component.hpp`, `src/domains/process-workload-management/component.cpp`, `src/domains/process-workload-management/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/processes/reconciliation/process_controller.cpp`
- `src/domains/processes/reconciliation/process_controller.hpp`
- `src/providers/linux/procfs/process_provider.hpp`
- `src/system/shell/sources/processes/test_processes.sh`

### Existing test evidence
- `tests/rebuntu/test_process_reconciliation.cpp`

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

- Structural skeleton materialized at `src/domains/process-workload-management/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/process-workload-management/model/`
- `src/domains/process-workload-management/contracts/`
- `src/domains/process-workload-management/integration/`
- `src/domains/process-workload-management/verification/`
- `src/domains/process-workload-management/lifecycle/`
- `src/domains/process-workload-management/state/`
- `src/domains/process-workload-management/execution/`
- `src/domains/process-workload-management/transactions/`
- `src/domains/process-workload-management/events/`
- `src/domains/process-workload-management/scheduling/`
- `src/domains/process-workload-management/recovery/`
- `src/domains/process-workload-management/identity/`
- `src/domains/process-workload-management/inventory/`
- `src/domains/process-workload-management/relationships/`
- `src/domains/process-workload-management/resources/`
- `src/domains/process-workload-management/placement/`
- `src/domains/process-workload-management/desired_state/`
- `src/domains/process-workload-management/operations/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

## DOMAIN CONTROL SPINE INTEGRATION I

Implementation pass: services/processes/storage → shared reconciliation pipeline.

Implemented evidence:
- `src/control/reconciliation/bindings/domain_bindings.hpp`
- `src/control/reconciliation/bindings/domain_bindings.cpp`
- `src/control/reconciliation/pipeline/pipeline.hpp`
- `src/control/reconciliation/pipeline/pipeline.cpp`
- `tests/rebuntu/test_domain_pipeline_bindings.cpp`

Behavior now exercised through one common control path:
- authoritative domain observation through typed Linux providers;
- domain-specific plan synthesis;
- policy authorization boundary;
- typed `NativeOperation` execution;
- re-observation and convergence verification;
- service/systemd, process/procfs, and storage/filesystem bindings;
- process state is normalized semantically while retaining `raw_state`, avoiding leakage of procfs single-letter state into desired-state semantics.

Verification:
- `DOMAIN_PIPELINE_BINDINGS_PASS` with C++20 and `-Wall -Wextra -Wpedantic -Werror`.
- Existing process reconciliation regression test remains passing.

Remaining work:
- Do not treat this shared spine as completion of this phase. Read all phase prompts and implement phase-specific requirements.
- Extend policy from the test allow-policy to real security/policy decisions where required.
- Add transaction/recovery integration around domain mutations and richer failure evidence.
- Add further domain bindings only through typed native providers; never reproduce Linux mechanics.

Ledger rule: this section is implementation evidence, not an automatic maturity upgrade. Re-evaluate depth against the phase prompts before changing its score.


## MASS IMPLEMENTATION PASS — DOMAIN SEMANTICS + SYNTHESIS\n\nImplemented and verified in this pass:\n- canonical domain semantic model: stable identity, native authority/provenance, resources, relationships/topology, capabilities, requirements, desired state, operations and health;\n- concrete profiles/models for services, processes, storage, networking, software, configuration, identity and accelerators;\n- semantic projection adapter for reconciliation observations;\n- capability-aware typed operation synthesis;\n- requirement resolution and health aggregation;\n- tests: `test_domain_semantic_models.cpp`, `test_semantic_projection.cpp`, `test_domain_synthesis.cpp`, compiled with C++20 + `-Wall -Wextra -Wpedantic -Werror`.\n\nImplementation depth note: this is real reusable behavior and integration evidence, but does NOT by itself complete this phase. Phase-specific prompts, provider-specific execution, failure paths and E2E acceptance criteria remain authoritative. Native Linux mechanisms remain the source of truth.\n

## MASS IMPLEMENTATION IV / SATURATION — transactional convergence + cross-domain coordination

**Verified implementation evidence:**
- `src/domains/common/reconciliation/domain_reconciler.hpp`: transaction-journaled reconcile lifecycle, deterministic checkpoints, bounded authoritative re-observation/replan, verified commit, failure rollback, rollback-failure reporting, dry-run/already-converged handling.
- `src/core/transactions/journal.hpp`: validated transaction state machine with explicit replanning/rolling-back terminal semantics and timestamped evidence entries.
- `src/control/reconciliation/coordination/cross_domain.hpp`: deterministic dependency-ordered cross-domain reconciliation, missing-dependency/cycle rejection, stop-on-nonconvergence and reverse-order compensation of already converged domains.
- `tests/rebuntu/test_saturation_v.cpp`: strict executable coverage for replan-to-convergence, transactional rollback, cross-domain rollback ordering and cycle rejection.

**Executed test evidence:** `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/rebuntu/test_saturation_v.cpp` -> `REPLAN_CONVERGENCE_PASS`, `TRANSACTION_ROLLBACK_PASS`, `CROSS_DOMAIN_ROLLBACK_PASS`, `CROSS_DOMAIN_CYCLE_PASS`. Regression strict builds also executed: `DOMAIN_SEMANTIC_MODELS_PASS`, `DOMAIN_SYNTHESIS_PASS`, `TREE_DEEPENING_II_SATURATION_PASS`.

**Native Authority compliance:** no Linux mechanism is reimplemented. Mutations remain typed `NativeOperation`s routed toward native providers; convergence is accepted only after authoritative re-observation. Cross-domain coordination composes Rebuntu semantics and compensation, not systemd/procfs/Netlink/filesystem/package/NSS/PAM/GPU mechanics.

**Remaining work / maturity:** this pass is concrete implementation evidence but is not phase-completion evidence. Provider-specific durable checkpoints, crash-resume persistence, policy/authorization wiring, real-machine E2E tests and full source-prompt closure remain where applicable. Existing depth is not automatically raised solely by this shared pass.

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `29.0-process-workload-management-system-foundation`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.0-process-workload-management-system-foundation.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_workload_management_system_foundation_cbe99f31/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/process_workload_management_system_foundation_cbe99f31.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/process_workload_management_system_foundation_cbe99f31.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_process_workload_management_system_foundation_cbe99f31.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.1-process-domain-model`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.1-process-domain-model.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_domain_model_dfc1b4c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/contracts/process_domain_model_dfc1b4c2.hpp`, `src/domains/process-workload-management/subtask_targets/contracts/process_domain_model_dfc1b4c2.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/contracts/test_process_domain_model_dfc1b4c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.10-process-session-tty-context`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.10-process-session-tty-context.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_session_tty_context_a1f43299/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/process_session_tty_context_a1f43299.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/process_session_tty_context_a1f43299.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_process_session_tty_context_a1f43299.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.11-process-resource-observation`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.11-process-resource-observation.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_resource_observation_260ecf95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/observability/process_resource_observation_260ecf95.hpp`, `src/domains/process-workload-management/subtask_targets/observability/process_resource_observation_260ecf95.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/observability/test_process_resource_observation_260ecf95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.12-process-open-resource-evidence`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.12-process-open-resource-evidence.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_open_resource_evidence_21be2802/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/verification/process_open_resource_evidence_21be2802.hpp`, `src/domains/process-workload-management/subtask_targets/verification/process_open_resource_evidence_21be2802.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/verification/test_process_open_resource_evidence_21be2802.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.13-process-namespace-container-context`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.13-process-namespace-container-context.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_namespace_container_context_ab294040/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/process_namespace_container_context_ab294040.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/process_namespace_container_context_ab294040.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_process_namespace_container_context_ab294040.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.14-process-group-session-semantics`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.14-process-group-session-semantics.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_group_session_semantics_0e7dc1a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/process_group_session_semantics_0e7dc1a9.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/process_group_session_semantics_0e7dc1a9.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_process_group_session_semantics_0e7dc1a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.15-workload-domain-model`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.15-workload-domain-model.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/workload_domain_model_ed9dfbe6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/contracts/workload_domain_model_ed9dfbe6.hpp`, `src/domains/process-workload-management/subtask_targets/contracts/workload_domain_model_ed9dfbe6.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/contracts/test_workload_domain_model_ed9dfbe6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.16-workload-identity`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.16-workload-identity.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/workload_identity_55996d44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/contracts/workload_identity_55996d44.hpp`, `src/domains/process-workload-management/subtask_targets/contracts/workload_identity_55996d44.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/contracts/test_workload_identity_55996d44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.17-workload-membership-evidence`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.17-workload-membership-evidence.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/workload_membership_evidence_689f70f5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/verification/workload_membership_evidence_689f70f5.hpp`, `src/domains/process-workload-management/subtask_targets/verification/workload_membership_evidence_689f70f5.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/verification/test_workload_membership_evidence_689f70f5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.18-workload-discovery`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.18-workload-discovery.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/workload_discovery_80255e90/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/resolution/workload_discovery_80255e90.hpp`, `src/domains/process-workload-management/subtask_targets/resolution/workload_discovery_80255e90.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/resolution/test_workload_discovery_80255e90.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.19-workload-hierarchy-composition`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.19-workload-hierarchy-composition.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/workload_hierarchy_composition_53953c36/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/workload_hierarchy_composition_53953c36.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/workload_hierarchy_composition_53953c36.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_workload_hierarchy_composition_53953c36.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.2-stable-process-identity`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.2-stable-process-identity.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/stable_process_identity_d71d1b71/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/contracts/stable_process_identity_d71d1b71.hpp`, `src/domains/process-workload-management/subtask_targets/contracts/stable_process_identity_d71d1b71.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/contracts/test_stable_process_identity_d71d1b71.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.20-workload-classification`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.20-workload-classification.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/workload_classification_19fb9d69/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/workload_classification_19fb9d69.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/workload_classification_19fb9d69.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_workload_classification_19fb9d69.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.21-workload-priority-protection`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.21-workload-priority-protection.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/workload_priority_protection_f55bccfb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/workload_priority_protection_f55bccfb.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/workload_priority_protection_f55bccfb.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_workload_priority_protection_f55bccfb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.22-foreground-interactive-workload-protection`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.22-foreground-interactive-workload-protection.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/foreground_interactive_workload_protection_57e0d400/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/foreground_interactive_workload_protection_57e0d400.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/foreground_interactive_workload_protection_57e0d400.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_foreground_interactive_workload_protection_57e0d400.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.23-desktop-display-critical-protection`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.23-desktop-display-critical-protection.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/desktop_display_critical_protection_33288cb0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/desktop_display_critical_protection_33288cb0.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/desktop_display_critical_protection_33288cb0.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_desktop_display_critical_protection_33288cb0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.24-rebuntu-control-plane-protection`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.24-rebuntu-control-plane-protection.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/rebuntu_control_plane_protection_68e7f876/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/planning/rebuntu_control_plane_protection_68e7f876.hpp`, `src/domains/process-workload-management/subtask_targets/planning/rebuntu_control_plane_protection_68e7f876.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/planning/test_rebuntu_control_plane_protection_68e7f876.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.25-service-workload-integration`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.25-service-workload-integration.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/service_workload_integration_c0fc3ef6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/integration/service_workload_integration_c0fc3ef6.hpp`, `src/domains/process-workload-management/subtask_targets/integration/service_workload_integration_c0fc3ef6.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/integration/test_service_workload_integration_c0fc3ef6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.26-development-workload-integration`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.26-development-workload-integration.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/development_workload_integration_c67b852a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/integration/development_workload_integration_c67b852a.hpp`, `src/domains/process-workload-management/subtask_targets/integration/development_workload_integration_c67b852a.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/integration/test_development_workload_integration_c67b852a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.27-container-workload-integration`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.27-container-workload-integration.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/container_workload_integration_498418bc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/integration/container_workload_integration_498418bc.hpp`, `src/domains/process-workload-management/subtask_targets/integration/container_workload_integration_498418bc.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/integration/test_container_workload_integration_498418bc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.28-gpu-accelerator-workload-integration`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.28-gpu-accelerator-workload-integration.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/gpu_accelerator_workload_integration_20c508e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/integration/gpu_accelerator_workload_integration_20c508e3.hpp`, `src/domains/process-workload-management/subtask_targets/integration/gpu_accelerator_workload_integration_20c508e3.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/integration/test_gpu_accelerator_workload_integration_20c508e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.29-lifecycle-action-model`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.29-lifecycle-action-model.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/lifecycle_action_model_f4a89bab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/lifecycle/lifecycle_action_model_f4a89bab.hpp`, `src/domains/process-workload-management/subtask_targets/lifecycle/lifecycle_action_model_f4a89bab.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/lifecycle/test_lifecycle_action_model_f4a89bab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.3-process-discovery-provider`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.3-process-discovery-provider.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_discovery_provider_5ec5003b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/integration/process_discovery_provider_5ec5003b.hpp`, `src/domains/process-workload-management/subtask_targets/integration/process_discovery_provider_5ec5003b.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/integration/test_process_discovery_provider_5ec5003b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.30-graceful-stop-semantics`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.30-graceful-stop-semantics.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/graceful_stop_semantics_577124b9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/lifecycle/graceful_stop_semantics_577124b9.hpp`, `src/domains/process-workload-management/subtask_targets/lifecycle/graceful_stop_semantics_577124b9.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/lifecycle/test_graceful_stop_semantics_577124b9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.31-signal-delivery-planning`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.31-signal-delivery-planning.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/signal_delivery_planning_a8986ef8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/planning/signal_delivery_planning_a8986ef8.hpp`, `src/domains/process-workload-management/subtask_targets/planning/signal_delivery_planning_a8986ef8.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/planning/test_signal_delivery_planning_a8986ef8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.32-termination-escalation-policy`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.32-termination-escalation-policy.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/termination_escalation_policy_09090291/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/security/termination_escalation_policy_09090291.hpp`, `src/domains/process-workload-management/subtask_targets/security/termination_escalation_policy_09090291.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/security/test_termination_escalation_policy_09090291.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.33-suspend-resume-semantics`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.33-suspend-resume-semantics.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/suspend_resume_semantics_97263b70/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/recovery/suspend_resume_semantics_97263b70.hpp`, `src/domains/process-workload-management/subtask_targets/recovery/suspend_resume_semantics_97263b70.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/recovery/test_suspend_resume_semantics_97263b70.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.34-bulk-action-safety`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.34-bulk-action-safety.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/bulk_action_safety_94c5c11e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/bulk_action_safety_94c5c11e.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/bulk_action_safety_94c5c11e.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_bulk_action_safety_94c5c11e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.35-dependency-impact-analysis`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.35-dependency-impact-analysis.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/dependency_impact_analysis_78e9e117/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/dependency_impact_analysis_78e9e117.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/dependency_impact_analysis_78e9e117.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_dependency_impact_analysis_78e9e117.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.36-race-safe-target-revalidation`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.36-race-safe-target-revalidation.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/race_safe_target_revalidation_375ac9d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/race_safe_target_revalidation_375ac9d7.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/race_safe_target_revalidation_375ac9d7.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_race_safe_target_revalidation_375ac9d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.37-process-exit-zombie-handling`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.37-process-exit-zombie-handling.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_exit_zombie_handling_92a140d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/process_exit_zombie_handling_92a140d9.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/process_exit_zombie_handling_92a140d9.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_process_exit_zombie_handling_92a140d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.38-orphan-reparenting-semantics`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.38-orphan-reparenting-semantics.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/orphan_reparenting_semantics_c0d310a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/orphan_reparenting_semantics_c0d310a2.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/orphan_reparenting_semantics_c0d310a2.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_orphan_reparenting_semantics_c0d310a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.39-runaway-process-diagnostics`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.39-runaway-process-diagnostics.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/runaway_process_diagnostics_b7c430e1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/observability/runaway_process_diagnostics_b7c430e1.hpp`, `src/domains/process-workload-management/subtask_targets/observability/runaway_process_diagnostics_b7c430e1.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/observability/test_runaway_process_diagnostics_b7c430e1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.4-process-lifecycle-observation`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.4-process-lifecycle-observation.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_lifecycle_observation_08330dee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/observability/process_lifecycle_observation_08330dee.hpp`, `src/domains/process-workload-management/subtask_targets/observability/process_lifecycle_observation_08330dee.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/observability/test_process_lifecycle_observation_08330dee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.40-stuck-unresponsive-workload-diagnostics`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.40-stuck-unresponsive-workload-diagnostics.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/stuck_unresponsive_workload_diagnostics_526aa6ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/observability/stuck_unresponsive_workload_diagnostics_526aa6ea.hpp`, `src/domains/process-workload-management/subtask_targets/observability/stuck_unresponsive_workload_diagnostics_526aa6ea.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/observability/test_stuck_unresponsive_workload_diagnostics_526aa6ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.41-process-workload-search-explainability`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.41-process-workload-search-explainability.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_workload_search_explainability_b34206f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/observability/process_workload_search_explainability_b34206f0.hpp`, `src/domains/process-workload-management/subtask_targets/observability/process_workload_search_explainability_b34206f0.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/observability/test_process_workload_search_explainability_b34206f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.42-process-workload-management-cli`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.42-process-workload-management-cli.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_workload_management_cli_661fc4ad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/process_workload_management_cli_661fc4ad.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/process_workload_management_cli_661fc4ad.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_process_workload_management_cli_661fc4ad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.43-phase-25-panel-integration-api`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.43-phase-25-panel-integration-api.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/panel_integration_api_12afff40/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/integration/panel_integration_api_12afff40.hpp`, `src/domains/process-workload-management/subtask_targets/integration/panel_integration_api_12afff40.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/integration/test_panel_integration_api_12afff40.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.44-event-timeline-integration`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.44-event-timeline-integration.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/event_timeline_integration_8a44b319/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/integration/event_timeline_integration_8a44b319.hpp`, `src/domains/process-workload-management/subtask_targets/integration/event_timeline_integration_8a44b319.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/integration/test_event_timeline_integration_8a44b319.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.45-failure-injection-race-testing`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.45-failure-injection-race-testing.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/failure_injection_race_testing_9058ab1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/verification/failure_injection_race_testing_9058ab1a.hpp`, `src/domains/process-workload-management/subtask_targets/verification/failure_injection_race_testing_9058ab1a.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/verification/test_failure_injection_race_testing_9058ab1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.46-cross-phase-ownership-safety-audit`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.46-cross-phase-ownership-safety-audit.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/cross_phase_ownership_safety_audit_e397980c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/verification/cross_phase_ownership_safety_audit_e397980c.hpp`, `src/domains/process-workload-management/subtask_targets/verification/cross_phase_ownership_safety_audit_e397980c.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/verification/test_cross_phase_ownership_safety_audit_e397980c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.47-process-workload-management-system-closure-readiness-gate`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.47-process-workload-management-system-closure-readiness-gate.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_workload_management_system_closure_readiness_gate_5b489b70/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/process_workload_management_system_closure_readiness_gate_5b489b70.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/process_workload_management_system_closure_readiness_gate_5b489b70.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_process_workload_management_system_closure_readiness_gate_5b489b70.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.5-parent-child-process-relationships`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.5-parent-child-process-relationships.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/parent_child_process_relationships_c21db9dd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/requirements/parent_child_process_relationships_c21db9dd.hpp`, `src/domains/process-workload-management/subtask_targets/requirements/parent_child_process_relationships_c21db9dd.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/requirements/test_parent_child_process_relationships_c21db9dd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.6-process-tree-forest-model`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.6-process-tree-forest-model.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_tree_forest_model_9f08b51f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/contracts/process_tree_forest_model_9f08b51f.hpp`, `src/domains/process-workload-management/subtask_targets/contracts/process_tree_forest_model_9f08b51f.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/contracts/test_process_tree_forest_model_9f08b51f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.7-process-state-semantics`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.7-process-state-semantics.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_state_semantics_f56c30ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/lifecycle/process_state_semantics_f56c30ae.hpp`, `src/domains/process-workload-management/subtask_targets/lifecycle/process_state_semantics_f56c30ae.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/lifecycle/test_process_state_semantics_f56c30ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.8-process-command-executable-provenance`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.8-process-command-executable-provenance.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_command_executable_provenance_038d6019/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/execution/process_command_executable_provenance_038d6019.hpp`, `src/domains/process-workload-management/subtask_targets/execution/process_command_executable_provenance_038d6019.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/execution/test_process_command_executable_provenance_038d6019.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `29.9-process-user-identity-context`
- **Source:** `.phases/phases/phase-29-process-workload-management/prompts/29.9-process-user-identity-context.md`
- **Structural package:** `src/domains/process-workload-management/subtask_packages/verification/process_user_identity_context_c8b595d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/process-workload-management/subtask_targets/contracts/process_user_identity_context_c8b595d4.hpp`, `src/domains/process-workload-management/subtask_targets/contracts/process_user_identity_context_c8b595d4.cpp`
- **Structural test target:** `tests/structural-closure/domains/process-workload-management/contracts/test_process_user_identity_context_c8b595d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

