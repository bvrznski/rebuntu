# Phase 25 — System Control Panel — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-25-system-control-panel/`
- Primary prompt location: `.phases/phases/phase-25-system-control-panel/prompts/`
- Prompt/specification Markdown files currently present: **34**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 34 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_25` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 25: System Control Panel
- Layout
- Prompt Index
- Agent Handoff — Phase 25
- Phase 25.22 — Privilege Boundary & Root Helper Architecture
- Mission
- Mandatory Architectural Rules
- Completion Evidence
- IMPLEMENTATION LANGUAGE OVERRIDE
- Phase 25.5 — Process Inspection & Control
- Phase 25.21 — Performance, Refresh & Event Architecture
- Phase 25.9 — Package & Repository Management

## Structural skeleton / canonical destination
- Canonical skeleton: `src/operator/system-control-panel/`
- Structural files: `src/operator/system-control-panel/component.hpp`, `src/operator/system-control-panel/component.cpp`, `src/operator/system-control-panel/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/control/README.md`
- `src/control/change_sets/README.md`
- `src/control/change_sets/contract.hpp`
- `src/control/checkpoints/README.md`
- `src/control/checkpoints/contract.hpp`
- `src/control/convergence/README.md`
- `src/control/convergence/contract.hpp`
- `src/control/domain_controller.hpp`
- `src/control/drift/README.md`
- `src/control/drift/contract.hpp`
- `src/control/homeostasis/README.md`
- `src/control/homeostasis/contract.hpp`

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

- Structural skeleton materialized at `src/operator/system-control-panel/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/operator/system-control-panel/model/`
- `src/operator/system-control-panel/contracts/`
- `src/operator/system-control-panel/integration/`
- `src/operator/system-control-panel/verification/`
- `src/operator/system-control-panel/lifecycle/`
- `src/operator/system-control-panel/state/`
- `src/operator/system-control-panel/execution/`
- `src/operator/system-control-panel/transactions/`
- `src/operator/system-control-panel/events/`
- `src/operator/system-control-panel/scheduling/`
- `src/operator/system-control-panel/recovery/`
- `src/operator/system-control-panel/identity/`
- `src/operator/system-control-panel/inventory/`
- `src/operator/system-control-panel/relationships/`
- `src/operator/system-control-panel/resources/`
- `src/operator/system-control-panel/placement/`
- `src/operator/system-control-panel/desired_state/`
- `src/operator/system-control-panel/operations/`



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

### `25.0-system-control-panel-foundation`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.0-system-control-panel-foundation.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/system_control_panel_foundation_7d91e634/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/system_control_panel_foundation_7d91e634.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/system_control_panel_foundation_7d91e634.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_system_control_panel_foundation_7d91e634.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.1-panel-domain-model-and-typed-control-api`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.1-panel-domain-model-and-typed-control-api.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/panel_domain_model_and_typed_control_api_83dc3ef5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/contracts/panel_domain_model_and_typed_control_api_83dc3ef5.hpp`, `src/operator/system-control-panel/subtask_targets/contracts/panel_domain_model_and_typed_control_api_83dc3ef5.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/contracts/test_panel_domain_model_and_typed_control_api_83dc3ef5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.10-kernel,-driver-and-dkms-management`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.10-kernel,-driver-and-dkms-management.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/kernel_driver_and_dkms_management_8f5cf02f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/kernel_driver_and_dkms_management_8f5cf02f.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/kernel_driver_and_dkms_management_8f5cf02f.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_kernel_driver_and_dkms_management_8f5cf02f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.11-containers-and-docker`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.11-containers-and-docker.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/containers_and_docker_fb0e6216/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/containers_and_docker_fb0e6216.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/containers_and_docker_fb0e6216.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_containers_and_docker_fb0e6216.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.12-logs-and-evidence-explorer`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.12-logs-and-evidence-explorer.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/logs_and_evidence_explorer_35197d13/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/verification/logs_and_evidence_explorer_35197d13.hpp`, `src/operator/system-control-panel/subtask_targets/verification/logs_and_evidence_explorer_35197d13.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/verification/test_logs_and_evidence_explorer_35197d13.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.13-semantic-analysis-and-hypothesis-view`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.13-semantic-analysis-and-hypothesis-view.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/semantic_analysis_and_hypothesis_view_b0c23e4a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/semantic_analysis_and_hypothesis_view_b0c23e4a.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/semantic_analysis_and_hypothesis_view_b0c23e4a.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_semantic_analysis_and_hypothesis_view_b0c23e4a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.14-security-and-exposure-view`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.14-security-and-exposure-view.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/security_and_exposure_view_ff6020c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/security/security_and_exposure_view_ff6020c2.hpp`, `src/operator/system-control-panel/subtask_targets/security/security_and_exposure_view_ff6020c2.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/security/test_security_and_exposure_view_ff6020c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.15-updates-and-evergreen-evolution-center`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.15-updates-and-evergreen-evolution-center.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/updates_and_evergreen_evolution_center_2f244b51/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/updates_and_evergreen_evolution_center_2f244b51.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/updates_and_evergreen_evolution_center_2f244b51.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_updates_and_evergreen_evolution_center_2f244b51.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.16-recovery-and-rollback-center`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.16-recovery-and-rollback-center.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/recovery_and_rollback_center_77aad223/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/recovery/recovery_and_rollback_center_77aad223.hpp`, `src/operator/system-control-panel/subtask_targets/recovery/recovery_and_rollback_center_77aad223.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/recovery/test_recovery_and_rollback_center_77aad223.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.17-unified-action-planning-and-authorization-ux`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.17-unified-action-planning-and-authorization-ux.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/unified_action_planning_and_authorization_ux_093aadde/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/security/unified_action_planning_and_authorization_ux_093aadde.hpp`, `src/operator/system-control-panel/subtask_targets/security/unified_action_planning_and_authorization_ux_093aadde.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/security/test_unified_action_planning_and_authorization_ux_093aadde.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.18-execution-progress,-verification-and-audit-trail`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.18-execution-progress,-verification-and-audit-trail.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/execution_progress_verification_and_audit_trail_643ec7f5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/verification/execution_progress_verification_and_audit_trail_643ec7f5.hpp`, `src/operator/system-control-panel/subtask_targets/verification/execution_progress_verification_and_audit_trail_643ec7f5.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/verification/test_execution_progress_verification_and_audit_trail_643ec7f5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.19-search,-command-palette-and-cross-system-navigation`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.19-search,-command-palette-and-cross-system-navigation.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/search_command_palette_and_cross_system_navigation_30aa3d94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/execution/search_command_palette_and_cross_system_navigation_30aa3d94.hpp`, `src/operator/system-control-panel/subtask_targets/execution/search_command_palette_and_cross_system_navigation_30aa3d94.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/execution/test_search_command_palette_and_cross_system_navigation_30aa3d94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.2-tui-runtime,-navigation-and-layout`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.2-tui-runtime,-navigation-and-layout.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/tui_runtime_navigation_and_layout_d04ce818/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/tui_runtime_navigation_and_layout_d04ce818.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/tui_runtime_navigation_and_layout_d04ce818.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_tui_runtime_navigation_and_layout_d04ce818.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.20-contextual-help-and-explainability`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.20-contextual-help-and-explainability.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/contextual_help_and_explainability_e1511012/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/observability/contextual_help_and_explainability_e1511012.hpp`, `src/operator/system-control-panel/subtask_targets/observability/contextual_help_and_explainability_e1511012.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/observability/test_contextual_help_and_explainability_e1511012.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.21-performance,-refresh-and-event-architecture`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.21-performance,-refresh-and-event-architecture.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/performance_refresh_and_event_architecture_565d3f9f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/performance_refresh_and_event_architecture_565d3f9f.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/performance_refresh_and_event_architecture_565d3f9f.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_performance_refresh_and_event_architecture_565d3f9f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.22-privilege-boundary-and-root-helper-architecture`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.22-privilege-boundary-and-root-helper-architecture.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/privilege_boundary_and_root_helper_architecture_aadd9ee0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/security/privilege_boundary_and_root_helper_architecture_aadd9ee0.hpp`, `src/operator/system-control-panel/subtask_targets/security/privilege_boundary_and_root_helper_architecture_aadd9ee0.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/security/test_privilege_boundary_and_root_helper_architecture_aadd9ee0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.23-panel-configuration-and-personalization`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.23-panel-configuration-and-personalization.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/panel_configuration_and_personalization_d57ef430/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/panel_configuration_and_personalization_d57ef430.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/panel_configuration_and_personalization_d57ef430.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_panel_configuration_and_personalization_d57ef430.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.24-frontend-independence-and-future-gui-api-readiness`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.24-frontend-independence-and-future-gui-api-readiness.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/frontend_independence_and_future_gui_api_readiness_2259ef63/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/contracts/frontend_independence_and_future_gui_api_readiness_2259ef63.hpp`, `src/operator/system-control-panel/subtask_targets/contracts/frontend_independence_and_future_gui_api_readiness_2259ef63.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/contracts/test_frontend_independence_and_future_gui_api_readiness_2259ef63.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.25-failure-injection-and-safety-testing`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.25-failure-injection-and-safety-testing.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/failure_injection_and_safety_testing_9cb48805/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/verification/failure_injection_and_safety_testing_9cb48805.hpp`, `src/operator/system-control-panel/subtask_targets/verification/failure_injection_and_safety_testing_9cb48805.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/verification/test_failure_injection_and_safety_testing_9cb48805.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.26-cross-phase-integration-audit`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.26-cross-phase-integration-audit.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/cross_phase_integration_audit_7f879f39/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/verification/cross_phase_integration_audit_7f879f39.hpp`, `src/operator/system-control-panel/subtask_targets/verification/cross_phase_integration_audit_7f879f39.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/verification/test_cross_phase_integration_audit_7f879f39.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.27-system-control-panel-closure-and-readiness-gate`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.27-system-control-panel-closure-and-readiness-gate.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/system_control_panel_closure_and_readiness_gate_37168a7e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/system_control_panel_closure_and_readiness_gate_37168a7e.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/system_control_panel_closure_and_readiness_gate_37168a7e.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_system_control_panel_closure_and_readiness_gate_37168a7e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.3-system-overview-and-health-dashboard`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.3-system-overview-and-health-dashboard.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/system_overview_and_health_dashboard_9464d791/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/system_overview_and_health_dashboard_9464d791.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/system_overview_and_health_dashboard_9464d791.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_system_overview_and_health_dashboard_9464d791.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.4-hardware-and-sensor-control-surface`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.4-hardware-and-sensor-control-surface.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/hardware_and_sensor_control_surface_b183cb55/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/hardware_and_sensor_control_surface_b183cb55.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/hardware_and_sensor_control_surface_b183cb55.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_hardware_and_sensor_control_surface_b183cb55.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.5-process-inspection-and-control`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.5-process-inspection-and-control.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/process_inspection_and_control_205f5677/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/process_inspection_and_control_205f5677.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/process_inspection_and_control_205f5677.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_process_inspection_and_control_205f5677.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.6-systemd-services-and-units`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.6-systemd-services-and-units.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/systemd_services_and_units_3e18e05d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/systemd_services_and_units_3e18e05d.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/systemd_services_and_units_3e18e05d.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_systemd_services_and_units_3e18e05d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.7-storage,-filesystems-and-mounts`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.7-storage,-filesystems-and-mounts.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/storage_filesystems_and_mounts_81e60fe9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/storage_filesystems_and_mounts_81e60fe9.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/storage_filesystems_and_mounts_81e60fe9.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_storage_filesystems_and_mounts_81e60fe9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.8-network-control-surface`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.8-network-control-surface.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/network_control_surface_8fe73692/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/network_control_surface_8fe73692.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/network_control_surface_8fe73692.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_network_control_surface_8fe73692.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `25.9-package-and-repository-management`
- **Source:** `.phases/phases/phase-25-system-control-panel/prompts/25.9-package-and-repository-management.md`
- **Structural package:** `src/operator/system-control-panel/subtask_packages/verification/package_and_repository_management_573a3d33/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/system-control-panel/subtask_targets/requirements/package_and_repository_management_573a3d33.hpp`, `src/operator/system-control-panel/subtask_targets/requirements/package_and_repository_management_573a3d33.cpp`
- **Structural test target:** `tests/structural-closure/operator/system-control-panel/requirements/test_package_and_repository_management_573a3d33.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

