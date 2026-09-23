# Phase 31 — Service Management — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-31-service-management/`
- Primary prompt location: `.phases/phases/phase-31-service-management/prompts/`
- Prompt/specification Markdown files currently present: **55**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 55 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_31` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 31: Service Management
- Layout
- Prompt Index
- Agent Handoff — Phase 31
- Phase 31.38 — Rebuntu Control Plane Protection
- Mission
- Non-negotiable architecture and invariants
- Phase-specific implementation requirements
- Required implementation method
- Global acceptance gate
- Required final report for Phase 31.38
- IMPLEMENTATION LANGUAGE OVERRIDE

## Structural skeleton / canonical destination
- Canonical skeleton: `src/domains/service-management/`
- Structural files: `src/domains/service-management/component.hpp`, `src/domains/service-management/component.cpp`, `src/domains/service-management/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/services/reconciliation/service_controller.cpp`
- `src/domains/services/reconciliation/service_controller.hpp`
- `src/semantics/native/service.cpp`
- `src/semantics/service.hpp`

### Existing test evidence
- `tests/rebuntu/service_reconciliation_test.cpp`

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

- Structural skeleton materialized at `src/domains/service-management/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/service-management/model/`
- `src/domains/service-management/contracts/`
- `src/domains/service-management/integration/`
- `src/domains/service-management/verification/`
- `src/domains/service-management/lifecycle/`
- `src/domains/service-management/state/`
- `src/domains/service-management/execution/`
- `src/domains/service-management/transactions/`
- `src/domains/service-management/events/`
- `src/domains/service-management/scheduling/`
- `src/domains/service-management/recovery/`
- `src/domains/service-management/identity/`
- `src/domains/service-management/inventory/`
- `src/domains/service-management/dependencies/`
- `src/domains/service-management/desired_state/`
- `src/domains/service-management/operations/`
- `src/domains/service-management/principals/`
- `src/domains/service-management/groups/`



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

### `31.0-service-management-system-foundation`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.0-service-management-system-foundation.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_management_system_foundation_028e9645/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/service_management_system_foundation_028e9645.hpp`, `src/domains/service-management/subtask_targets/requirements/service_management_system_foundation_028e9645.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_service_management_system_foundation_028e9645.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.1-service-domain-model`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.1-service-domain-model.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_domain_model_0ef8bed7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/contracts/service_domain_model_0ef8bed7.hpp`, `src/domains/service-management/subtask_targets/contracts/service_domain_model_0ef8bed7.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/contracts/test_service_domain_model_0ef8bed7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.10-service-configuration-provenance`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.10-service-configuration-provenance.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_configuration_provenance_ab1f6756/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/service_configuration_provenance_ab1f6756.hpp`, `src/domains/service-management/subtask_targets/requirements/service_configuration_provenance_ab1f6756.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_service_configuration_provenance_ab1f6756.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.11-unit-file-drop-in-discovery`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.11-unit-file-drop-in-discovery.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/unit_file_drop_in_discovery_d7473232/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/resolution/unit_file_drop_in_discovery_d7473232.hpp`, `src/domains/service-management/subtask_targets/resolution/unit_file_drop_in_discovery_d7473232.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/resolution/test_unit_file_drop_in_discovery_d7473232.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.12-enablement-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.12-enablement-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/enablement_semantics_0e1db215/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/lifecycle/enablement_semantics_0e1db215.hpp`, `src/domains/service-management/subtask_targets/lifecycle/enablement_semantics_0e1db215.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/lifecycle/test_enablement_semantics_0e1db215.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.13-activation-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.13-activation-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/activation_semantics_2a11ae15/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/activation_semantics_2a11ae15.hpp`, `src/domains/service-management/subtask_targets/requirements/activation_semantics_2a11ae15.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_activation_semantics_2a11ae15.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.14-start-stop-restart-lifecycle-model`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.14-start-stop-restart-lifecycle-model.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/start_stop_restart_lifecycle_model_a35d1bb0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/recovery/start_stop_restart_lifecycle_model_a35d1bb0.hpp`, `src/domains/service-management/subtask_targets/recovery/start_stop_restart_lifecycle_model_a35d1bb0.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/recovery/test_start_stop_restart_lifecycle_model_a35d1bb0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.15-reload-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.15-reload-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/reload_semantics_36460426/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/reload_semantics_36460426.hpp`, `src/domains/service-management/subtask_targets/requirements/reload_semantics_36460426.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_reload_semantics_36460426.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.16-daemon-reload-boundary`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.16-daemon-reload-boundary.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/daemon_reload_boundary_91251f80/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/daemon_reload_boundary_91251f80.hpp`, `src/domains/service-management/subtask_targets/requirements/daemon_reload_boundary_91251f80.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_daemon_reload_boundary_91251f80.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.17-service-dependency-model`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.17-service-dependency-model.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_dependency_model_30467cfb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/contracts/service_dependency_model_30467cfb.hpp`, `src/domains/service-management/subtask_targets/contracts/service_dependency_model_30467cfb.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/contracts/test_service_dependency_model_30467cfb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.18-ordering-vs-requirement-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.18-ordering-vs-requirement-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/ordering_vs_requirement_semantics_b8d57491/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/ordering_vs_requirement_semantics_b8d57491.hpp`, `src/domains/service-management/subtask_targets/requirements/ordering_vs_requirement_semantics_b8d57491.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_ordering_vs_requirement_semantics_b8d57491.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.19-socket-activation-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.19-socket-activation-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/socket_activation_integration_2b0b1c5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/socket_activation_integration_2b0b1c5d.hpp`, `src/domains/service-management/subtask_targets/integration/socket_activation_integration_2b0b1c5d.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_socket_activation_integration_2b0b1c5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.2-service-provider-discovery`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.2-service-provider-discovery.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_provider_discovery_c0d24ae1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/service_provider_discovery_c0d24ae1.hpp`, `src/domains/service-management/subtask_targets/integration/service_provider_discovery_c0d24ae1.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_service_provider_discovery_c0d24ae1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.20-timer-activation-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.20-timer-activation-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/timer_activation_integration_d433a4c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/timer_activation_integration_d433a4c2.hpp`, `src/domains/service-management/subtask_targets/integration/timer_activation_integration_d433a4c2.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_timer_activation_integration_d433a4c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.21-path-device-bus-activation-context`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.21-path-device-bus-activation-context.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/path_device_bus_activation_context_2ef6c981/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/path_device_bus_activation_context_2ef6c981.hpp`, `src/domains/service-management/subtask_targets/requirements/path_device_bus_activation_context_2ef6c981.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_path_device_bus_activation_context_2ef6c981.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.22-template-instance-unit-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.22-template-instance-unit-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/template_instance_unit_semantics_377c62bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/template_instance_unit_semantics_377c62bb.hpp`, `src/domains/service-management/subtask_targets/requirements/template_instance_unit_semantics_377c62bb.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_template_instance_unit_semantics_377c62bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.23-transient-units-scopes`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.23-transient-units-scopes.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/transient_units_scopes_dc7490a6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/transient_units_scopes_dc7490a6.hpp`, `src/domains/service-management/subtask_targets/requirements/transient_units_scopes_dc7490a6.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_transient_units_scopes_dc7490a6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.24-service-process-workload-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.24-service-process-workload-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_process_workload_integration_5530843d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/service_process_workload_integration_5530843d.hpp`, `src/domains/service-management/subtask_targets/integration/service_process_workload_integration_5530843d.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_service_process_workload_integration_5530843d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.25-service-resource-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.25-service-resource-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_resource_integration_96743fae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/service_resource_integration_96743fae.hpp`, `src/domains/service-management/subtask_targets/integration/service_resource_integration_96743fae.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_service_resource_integration_96743fae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.26-service-user-identity-context`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.26-service-user-identity-context.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_user_identity_context_62aaf4b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/contracts/service_user_identity_context_62aaf4b1.hpp`, `src/domains/service-management/subtask_targets/contracts/service_user_identity_context_62aaf4b1.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/contracts/test_service_user_identity_context_62aaf4b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.27-service-environment-secret-boundary`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.27-service-environment-secret-boundary.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_environment_secret_boundary_26eb7b26/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/security/service_environment_secret_boundary_26eb7b26.hpp`, `src/domains/service-management/subtask_targets/security/service_environment_secret_boundary_26eb7b26.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/security/test_service_environment_secret_boundary_26eb7b26.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.28-service-logging-journal-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.28-service-logging-journal-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_logging_journal_integration_7840b7a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/service_logging_journal_integration_7840b7a8.hpp`, `src/domains/service-management/subtask_targets/integration/service_logging_journal_integration_7840b7a8.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_service_logging_journal_integration_7840b7a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.29-service-health-model`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.29-service-health-model.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_health_model_a1c30814/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/contracts/service_health_model_a1c30814.hpp`, `src/domains/service-management/subtask_targets/contracts/service_health_model_a1c30814.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/contracts/test_service_health_model_a1c30814.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.3-systemd-provider-adapter`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.3-systemd-provider-adapter.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/systemd_provider_adapter_c19488f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/systemd_provider_adapter_c19488f2.hpp`, `src/domains/service-management/subtask_targets/integration/systemd_provider_adapter_c19488f2.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_systemd_provider_adapter_c19488f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.30-readiness-vs-liveness-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.30-readiness-vs-liveness-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/readiness_vs_liveness_semantics_fdfda29d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/readiness_vs_liveness_semantics_fdfda29d.hpp`, `src/domains/service-management/subtask_targets/requirements/readiness_vs_liveness_semantics_fdfda29d.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_readiness_vs_liveness_semantics_fdfda29d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.31-failure-restart-policy-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.31-failure-restart-policy-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/failure_restart_policy_semantics_e5b621b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/recovery/failure_restart_policy_semantics_e5b621b4.hpp`, `src/domains/service-management/subtask_targets/recovery/failure_restart_policy_semantics_e5b621b4.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/recovery/test_failure_restart_policy_semantics_e5b621b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.32-crash-loop-detection`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.32-crash-loop-detection.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/crash_loop_detection_12125b68/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/recovery/crash_loop_detection_12125b68.hpp`, `src/domains/service-management/subtask_targets/recovery/crash_loop_detection_12125b68.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/recovery/test_crash_loop_detection_12125b68.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.33-service-dependency-impact-analysis`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.33-service-dependency-impact-analysis.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_dependency_impact_analysis_a79a9e20/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/service_dependency_impact_analysis_a79a9e20.hpp`, `src/domains/service-management/subtask_targets/requirements/service_dependency_impact_analysis_a79a9e20.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_service_dependency_impact_analysis_a79a9e20.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.34-service-change-planning`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.34-service-change-planning.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_change_planning_6cc97a18/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/planning/service_change_planning_6cc97a18.hpp`, `src/domains/service-management/subtask_targets/planning/service_change_planning_6cc97a18.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/planning/test_service_change_planning_6cc97a18.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.35-service-lifecycle-authorization`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.35-service-lifecycle-authorization.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_lifecycle_authorization_e02c57ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/security/service_lifecycle_authorization_e02c57ab.hpp`, `src/domains/service-management/subtask_targets/security/service_lifecycle_authorization_e02c57ab.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/security/test_service_lifecycle_authorization_e02c57ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.36-protected-critical-services`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.36-protected-critical-services.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/protected_critical_services_0aa627e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/protected_critical_services_0aa627e7.hpp`, `src/domains/service-management/subtask_targets/requirements/protected_critical_services_0aa627e7.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_protected_critical_services_0aa627e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.37-desktop-operator-session-protection`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.37-desktop-operator-session-protection.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/desktop_operator_session_protection_468d0390/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/desktop_operator_session_protection_468d0390.hpp`, `src/domains/service-management/subtask_targets/requirements/desktop_operator_session_protection_468d0390.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_desktop_operator_session_protection_468d0390.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.38-rebuntu-control-plane-protection`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.38-rebuntu-control-plane-protection.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/rebuntu_control_plane_protection_834eec54/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/planning/rebuntu_control_plane_protection_834eec54.hpp`, `src/domains/service-management/subtask_targets/planning/rebuntu_control_plane_protection_834eec54.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/planning/test_rebuntu_control_plane_protection_834eec54.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.39-service-configuration-mutation`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.39-service-configuration-mutation.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_configuration_mutation_8d8aa0be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/execution/service_configuration_mutation_8d8aa0be.hpp`, `src/domains/service-management/subtask_targets/execution/service_configuration_mutation_8d8aa0be.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/execution/test_service_configuration_mutation_8d8aa0be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.4-system-vs-user-service-managers`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.4-system-vs-user-service-managers.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/system_vs_user_service_managers_4b086705/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/system_vs_user_service_managers_4b086705.hpp`, `src/domains/service-management/subtask_targets/requirements/system_vs_user_service_managers_4b086705.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_system_vs_user_service_managers_4b086705.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.40-drop-in-first-configuration-policy`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.40-drop-in-first-configuration-policy.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/drop_in_first_configuration_policy_cebb23d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/security/drop_in_first_configuration_policy_cebb23d6.hpp`, `src/domains/service-management/subtask_targets/security/drop_in_first_configuration_policy_cebb23d6.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/security/test_drop_in_first_configuration_policy_cebb23d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.41-service-recovery-rollback`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.41-service-recovery-rollback.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_recovery_rollback_e743c0e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/recovery/service_recovery_rollback_e743c0e4.hpp`, `src/domains/service-management/subtask_targets/recovery/service_recovery_rollback_e743c0e4.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/recovery/test_service_recovery_rollback_e743c0e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.42-boot-time-service-analysis`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.42-boot-time-service-analysis.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/boot_time_service_analysis_1750934a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/boot_time_service_analysis_1750934a.hpp`, `src/domains/service-management/subtask_targets/requirements/boot_time_service_analysis_1750934a.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_boot_time_service_analysis_1750934a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.43-service-management-cli`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.43-service-management-cli.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_management_cli_0bdb7d0b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/service_management_cli_0bdb7d0b.hpp`, `src/domains/service-management/subtask_targets/requirements/service_management_cli_0bdb7d0b.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_service_management_cli_0bdb7d0b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.44-phase-25-panel-integration-api`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.44-phase-25-panel-integration-api.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/panel_integration_api_461e63e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/panel_integration_api_461e63e7.hpp`, `src/domains/service-management/subtask_targets/integration/panel_integration_api_461e63e7.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_panel_integration_api_461e63e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.45-phase-29-process-workload-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.45-phase-29-process-workload-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/process_workload_integration_86339ed1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/process_workload_integration_86339ed1.hpp`, `src/domains/service-management/subtask_targets/integration/process_workload_integration_86339ed1.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_process_workload_integration_86339ed1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.46-phase-30-resource-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.46-phase-30-resource-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/resource_integration_6f3a35b6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/resource_integration_6f3a35b6.hpp`, `src/domains/service-management/subtask_targets/integration/resource_integration_6f3a35b6.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_resource_integration_6f3a35b6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.47-phase-39-timeline-integration`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.47-phase-39-timeline-integration.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/timeline_integration_2416e901/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/integration/timeline_integration_2416e901.hpp`, `src/domains/service-management/subtask_targets/integration/timeline_integration_2416e901.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/integration/test_timeline_integration_2416e901.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.48-service-management-system-closure-readiness-gate`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.48-service-management-system-closure-readiness-gate.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_management_system_closure_readiness_gate_3fca62a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/requirements/service_management_system_closure_readiness_gate_3fca62a4.hpp`, `src/domains/service-management/subtask_targets/requirements/service_management_system_closure_readiness_gate_3fca62a4.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/requirements/test_service_management_system_closure_readiness_gate_3fca62a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.5-unit-identity-stable-references`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.5-unit-identity-stable-references.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/unit_identity_stable_references_80418c2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/contracts/unit_identity_stable_references_80418c2e.hpp`, `src/domains/service-management/subtask_targets/contracts/unit_identity_stable_references_80418c2e.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/contracts/test_unit_identity_stable_references_80418c2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.6-unit-type-semantics`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.6-unit-type-semantics.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/unit_type_semantics_8c349403/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/contracts/unit_type_semantics_8c349403.hpp`, `src/domains/service-management/subtask_targets/contracts/unit_type_semantics_8c349403.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/contracts/test_unit_type_semantics_8c349403.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.7-service-discovery-inventory`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.7-service-discovery-inventory.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_discovery_inventory_0eea86c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/resolution/service_discovery_inventory_0eea86c8.hpp`, `src/domains/service-management/subtask_targets/resolution/service_discovery_inventory_0eea86c8.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/resolution/test_service_discovery_inventory_0eea86c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.8-loaded-enabled-running-healthy-separation`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.8-loaded-enabled-running-healthy-separation.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/loaded_enabled_running_healthy_separation_27454d78/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/lifecycle/loaded_enabled_running_healthy_separation_27454d78.hpp`, `src/domains/service-management/subtask_targets/lifecycle/loaded_enabled_running_healthy_separation_27454d78.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/lifecycle/test_loaded_enabled_running_healthy_separation_27454d78.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `31.9-service-state-observation`
- **Source:** `.phases/phases/phase-31-service-management/prompts/31.9-service-state-observation.md`
- **Structural package:** `src/domains/service-management/subtask_packages/verification/service_state_observation_a2b1728e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/service-management/subtask_targets/observability/service_state_observation_a2b1728e.hpp`, `src/domains/service-management/subtask_targets/observability/service_state_observation_a2b1728e.cpp`
- **Structural test target:** `tests/structural-closure/domains/service-management/observability/test_service_state_observation_a2b1728e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

