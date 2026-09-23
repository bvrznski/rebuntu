# Phase 26 — Shell Management — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-26-shell-management/`
- Primary prompt location: `.phases/phases/phase-26-shell-management/prompts/`
- Prompt/specification Markdown files currently present: **37**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 37 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_26` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 26: Shell Management
- Layout
- Prompt Index
- Agent Handoff — Phase 26
- Phase 26.8 — FZF-Coupled History Navigation
- Mission
- Non-negotiable architecture and invariants
- Phase-specific implementation requirements
- Required implementation method
- 1. Discover before designing
- 2. Establish canonical ownership
- 3. Typed shell-management contracts

## Structural skeleton / canonical destination
- Canonical skeleton: `src/domains/shell-management/`
- Structural files: `src/domains/shell-management/component.hpp`, `src/domains/shell-management/component.cpp`, `src/domains/shell-management/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/shell/README.md`
- `src/domains/shell/commands/README.md`
- `src/domains/shell/commands/contract.hpp`
- `src/domains/shell/completion/README.md`
- `src/domains/shell/completion/contract.hpp`
- `src/domains/shell/desired_state/README.md`
- `src/domains/shell/desired_state/contract.hpp`
- `src/domains/shell/environments/README.md`
- `src/domains/shell/environments/contract.hpp`
- `src/domains/shell/history/README.md`
- `src/domains/shell/history/contract.hpp`
- `src/domains/shell/language.hpp`

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

- Structural skeleton materialized at `src/domains/shell-management/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/shell-management/model/`
- `src/domains/shell-management/contracts/`
- `src/domains/shell-management/integration/`
- `src/domains/shell-management/verification/`
- `src/domains/shell-management/lifecycle/`
- `src/domains/shell-management/state/`
- `src/domains/shell-management/execution/`
- `src/domains/shell-management/transactions/`
- `src/domains/shell-management/events/`
- `src/domains/shell-management/scheduling/`
- `src/domains/shell-management/recovery/`
- `src/domains/shell-management/principals/`
- `src/domains/shell-management/groups/`
- `src/domains/shell-management/roles/`
- `src/domains/shell-management/resolution/`
- `src/domains/shell-management/authorization/`
- `src/domains/shell-management/credentials/`
- `src/domains/shell-management/policy/`



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

### `26.0-shell-management-system-foundation`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.0-shell-management-system-foundation.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_management_system_foundation_865be993/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/shell_management_system_foundation_865be993.hpp`, `src/domains/shell-management/subtask_targets/requirements/shell_management_system_foundation_865be993.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_shell_management_system_foundation_865be993.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.1-shell-context-session-model`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.1-shell-context-session-model.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_context_session_model_b2a3b54f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/contracts/shell_context_session_model_b2a3b54f.hpp`, `src/domains/shell-management/subtask_targets/contracts/shell_context_session_model_b2a3b54f.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/contracts/test_shell_context_session_model_b2a3b54f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.10-directory-project-aware-command-memory`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.10-directory-project-aware-command-memory.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/directory_project_aware_command_memory_52189eb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/execution/directory_project_aware_command_memory_52189eb9.hpp`, `src/domains/shell-management/subtask_targets/execution/directory_project_aware_command_memory_52189eb9.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/execution/test_directory_project_aware_command_memory_52189eb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.11-command-metadata-exit-state-duration`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.11-command-metadata-exit-state-duration.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/command_metadata_exit_state_duration_1b7c94f1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/execution/command_metadata_exit_state_duration_1b7c94f1.hpp`, `src/domains/shell-management/subtask_targets/execution/command_metadata_exit_state_duration_1b7c94f1.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/execution/test_command_metadata_exit_state_duration_1b7c94f1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.12-shell-session-management`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.12-shell-session-management.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_session_management_1278712d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/shell_session_management_1278712d.hpp`, `src/domains/shell-management/subtask_targets/requirements/shell_session_management_1278712d.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_shell_session_management_1278712d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.13-environment-path-state-management`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.13-environment-path-state-management.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/environment_path_state_management_7bc784ac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/lifecycle/environment_path_state_management_7bc784ac.hpp`, `src/domains/shell-management/subtask_targets/lifecycle/environment_path_state_management_7bc784ac.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/lifecycle/test_environment_path_state_management_7bc784ac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.14-alias-abbreviation-function-management`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.14-alias-abbreviation-function-management.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/alias_abbreviation_function_management_0b6554a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/alias_abbreviation_function_management_0b6554a9.hpp`, `src/domains/shell-management/subtask_targets/requirements/alias_abbreviation_function_management_0b6554a9.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_alias_abbreviation_function_management_0b6554a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.15-fish-plugin-oh-my-fish-management`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.15-fish-plugin-oh-my-fish-management.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/fish_plugin_oh_my_fish_management_318f5cea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/fish_plugin_oh_my_fish_management_318f5cea.hpp`, `src/domains/shell-management/subtask_targets/requirements/fish_plugin_oh_my_fish_management_318f5cea.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_fish_plugin_oh_my_fish_management_318f5cea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.16-cli-tool-integration-registry`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.16-cli-tool-integration-registry.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/cli_tool_integration_registry_34c231b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/integration/cli_tool_integration_registry_34c231b1.hpp`, `src/domains/shell-management/subtask_targets/integration/cli_tool_integration_registry_34c231b1.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/integration/test_cli_tool_integration_registry_34c231b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.17-shell-configuration-registry-ownership`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.17-shell-configuration-registry-ownership.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_configuration_registry_ownership_99dc4aa8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/shell_configuration_registry_ownership_99dc4aa8.hpp`, `src/domains/shell-management/subtask_targets/requirements/shell_configuration_registry_ownership_99dc4aa8.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_shell_configuration_registry_ownership_99dc4aa8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.18-shell-configuration-drift-detection`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.18-shell-configuration-drift-detection.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_configuration_drift_detection_e4231768/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/shell_configuration_drift_detection_e4231768.hpp`, `src/domains/shell-management/subtask_targets/requirements/shell_configuration_drift_detection_e4231768.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_shell_configuration_drift_detection_e4231768.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.19-shell-health-diagnostics`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.19-shell-health-diagnostics.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_health_diagnostics_6d9329c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/observability/shell_health_diagnostics_6d9329c4.hpp`, `src/domains/shell-management/subtask_targets/observability/shell_health_diagnostics_6d9329c4.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/observability/test_shell_health_diagnostics_6d9329c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.2-command-lifecycle-execution-context-capture`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.2-command-lifecycle-execution-context-capture.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/command_lifecycle_execution_context_capture_99b387eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/execution/command_lifecycle_execution_context_capture_99b387eb.hpp`, `src/domains/shell-management/subtask_targets/execution/command_lifecycle_execution_context_capture_99b387eb.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/execution/test_command_lifecycle_execution_context_capture_99b387eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.20-shell-recovery-safe-mode-console`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.20-shell-recovery-safe-mode-console.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_recovery_safe_mode_console_a8b327b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/recovery/shell_recovery_safe_mode_console_a8b327b5.hpp`, `src/domains/shell-management/subtask_targets/recovery/shell_recovery_safe_mode_console_a8b327b5.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/recovery/test_shell_recovery_safe_mode_console_a8b327b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.21-backup-snapshot-rollback`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.21-backup-snapshot-rollback.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/backup_snapshot_rollback_30a81bb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/recovery/backup_snapshot_rollback_30a81bb9.hpp`, `src/domains/shell-management/subtask_targets/recovery/backup_snapshot_rollback_30a81bb9.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/recovery/test_backup_snapshot_rollback_30a81bb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.22-search-inspection-explainability`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.22-search-inspection-explainability.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/search_inspection_explainability_c568da58/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/observability/search_inspection_explainability_c568da58.hpp`, `src/domains/shell-management/subtask_targets/observability/search_inspection_explainability_c568da58.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/observability/test_search_inspection_explainability_c568da58.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.23-shell-management-cli`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.23-shell-management-cli.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_management_cli_999ef644/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/shell_management_cli_999ef644.hpp`, `src/domains/shell-management/subtask_targets/requirements/shell_management_cli_999ef644.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_shell_management_cli_999ef644.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.24-panel-integration-api`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.24-panel-integration-api.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/panel_integration_api_8ee39a51/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/integration/panel_integration_api_8ee39a51.hpp`, `src/domains/shell-management/subtask_targets/integration/panel_integration_api_8ee39a51.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/integration/test_panel_integration_api_8ee39a51.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.25-privacy-secrets-sensitive-command-handling`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.25-privacy-secrets-sensitive-command-handling.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/privacy_secrets_sensitive_command_handling_5e2be00a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/security/privacy_secrets_sensitive_command_handling_5e2be00a.hpp`, `src/domains/shell-management/subtask_targets/security/privacy_secrets_sensitive_command_handling_5e2be00a.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/security/test_privacy_secrets_sensitive_command_handling_5e2be00a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.26-performance-retention-database-maintenance`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.26-performance-retention-database-maintenance.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/performance_retention_database_maintenance_7d860829/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/persistence/performance_retention_database_maintenance_7d860829.hpp`, `src/domains/shell-management/subtask_targets/persistence/performance_retention_database_maintenance_7d860829.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/persistence/test_performance_retention_database_maintenance_7d860829.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.27-cross-shell-bash-compatibility-boundary`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.27-cross-shell-bash-compatibility-boundary.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/cross_shell_bash_compatibility_boundary_3633c14a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/cross_shell_bash_compatibility_boundary_3633c14a.hpp`, `src/domains/shell-management/subtask_targets/requirements/cross_shell_bash_compatibility_boundary_3633c14a.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_cross_shell_bash_compatibility_boundary_3633c14a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.28-failure-injection-recovery-testing`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.28-failure-injection-recovery-testing.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/failure_injection_recovery_testing_8308147a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/verification/failure_injection_recovery_testing_8308147a.hpp`, `src/domains/shell-management/subtask_targets/verification/failure_injection_recovery_testing_8308147a.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/verification/test_failure_injection_recovery_testing_8308147a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.29-cross-phase-integration-audit`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.29-cross-phase-integration-audit.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/cross_phase_integration_audit_22b3e4a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/verification/cross_phase_integration_audit_22b3e4a8.hpp`, `src/domains/shell-management/subtask_targets/verification/cross_phase_integration_audit_22b3e4a8.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/verification/test_cross_phase_integration_audit_22b3e4a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.3-unified-history-backend`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.3-unified-history-backend.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/unified_history_backend_583bc84f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/unified_history_backend_583bc84f.hpp`, `src/domains/shell-management/subtask_targets/requirements/unified_history_backend_583bc84f.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_unified_history_backend_583bc84f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.30-shell-management-system-closure-readiness-gate`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.30-shell-management-system-closure-readiness-gate.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/shell_management_system_closure_readiness_gate_bcf53eb1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/shell_management_system_closure_readiness_gate_bcf53eb1.hpp`, `src/domains/shell-management/subtask_targets/requirements/shell_management_system_closure_readiness_gate_bcf53eb1.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_shell_management_system_closure_readiness_gate_bcf53eb1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.4-system-vs-virtual-environment-history-separation`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.4-system-vs-virtual-environment-history-separation.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/system_vs_virtual_environment_history_separation_722c3357/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/system_vs_virtual_environment_history_separation_722c3357.hpp`, `src/domains/shell-management/subtask_targets/requirements/system_vs_virtual_environment_history_separation_722c3357.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_system_vs_virtual_environment_history_separation_722c3357.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.5-virtual-environment-identity-lifecycle-tracking`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.5-virtual-environment-identity-lifecycle-tracking.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/virtual_environment_identity_lifecycle_tracking_3c620cb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/lifecycle/virtual_environment_identity_lifecycle_tracking_3c620cb9.hpp`, `src/domains/shell-management/subtask_targets/lifecycle/virtual_environment_identity_lifecycle_tracking_3c620cb9.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/lifecycle/test_virtual_environment_identity_lifecycle_tracking_3c620cb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.6-contextual-history-search-retrieval`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.6-contextual-history-search-retrieval.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/contextual_history_search_retrieval_8df462cd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/resolution/contextual_history_search_retrieval_8df462cd.hpp`, `src/domains/shell-management/subtask_targets/resolution/contextual_history_search_retrieval_8df462cd.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/resolution/test_contextual_history_search_retrieval_8df462cd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.7-interactive-history-manager`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.7-interactive-history-manager.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/interactive_history_manager_dbaa89e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/interactive_history_manager_dbaa89e5.hpp`, `src/domains/shell-management/subtask_targets/requirements/interactive_history_manager_dbaa89e5.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_interactive_history_manager_dbaa89e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.8-fzf-coupled-history-navigation`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.8-fzf-coupled-history-navigation.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/fzf_coupled_history_navigation_b509b15c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/requirements/fzf_coupled_history_navigation_b509b15c.hpp`, `src/domains/shell-management/subtask_targets/requirements/fzf_coupled_history_navigation_b509b15c.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/requirements/test_fzf_coupled_history_navigation_b509b15c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `26.9-atuin-integration-backend-abstraction`
- **Source:** `.phases/phases/phase-26-shell-management/prompts/26.9-atuin-integration-backend-abstraction.md`
- **Structural package:** `src/domains/shell-management/subtask_packages/verification/atuin_integration_backend_abstraction_1d4d107c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/shell-management/subtask_targets/integration/atuin_integration_backend_abstraction_1d4d107c.hpp`, `src/domains/shell-management/subtask_targets/integration/atuin_integration_backend_abstraction_1d4d107c.cpp`
- **Structural test target:** `tests/structural-closure/domains/shell-management/integration/test_atuin_integration_backend_abstraction_1d4d107c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

