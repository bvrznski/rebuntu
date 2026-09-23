# Phase 27 — Terminal Management — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-27-terminal-management/`
- Primary prompt location: `.phases/phases/phase-27-terminal-management/prompts/`
- Prompt/specification Markdown files currently present: **38**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 38 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_27` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 27: Terminal Management
- Layout
- Prompt Index
- Agent Handoff — Phase 27
- Phase 27.6 — Interactive Shell Launch Policy
- Mission
- Non-negotiable architecture and invariants
- Phase-specific implementation requirements
- Required implementation method
- 1. Repository and live-state discovery
- 2. Canonical ownership
- 3. Typed provider-neutral contracts

## Structural skeleton / canonical destination
- Canonical skeleton: `src/domains/terminal-management/`
- Structural files: `src/domains/terminal-management/component.hpp`, `src/domains/terminal-management/component.cpp`, `src/domains/terminal-management/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/terminal/README.md`
- `src/domains/terminal/capabilities/README.md`
- `src/domains/terminal/capabilities/contract.hpp`
- `src/domains/terminal/integration/README.md`
- `src/domains/terminal/integration/contract.hpp`
- `src/domains/terminal/model/README.md`
- `src/domains/terminal/model/contract.hpp`
- `src/domains/terminal/presentation/README.md`
- `src/domains/terminal/presentation/contract.hpp`
- `src/domains/terminal/profiles/README.md`
- `src/domains/terminal/profiles/contract.hpp`
- `src/domains/terminal/sessions/README.md`

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

- Structural skeleton materialized at `src/domains/terminal-management/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/terminal-management/model/`
- `src/domains/terminal-management/contracts/`
- `src/domains/terminal-management/integration/`
- `src/domains/terminal-management/verification/`
- `src/domains/terminal-management/lifecycle/`
- `src/domains/terminal-management/state/`
- `src/domains/terminal-management/execution/`
- `src/domains/terminal-management/transactions/`
- `src/domains/terminal-management/events/`
- `src/domains/terminal-management/scheduling/`
- `src/domains/terminal-management/recovery/`
- `src/domains/terminal-management/principals/`
- `src/domains/terminal-management/groups/`
- `src/domains/terminal-management/roles/`
- `src/domains/terminal-management/resolution/`
- `src/domains/terminal-management/authorization/`
- `src/domains/terminal-management/credentials/`
- `src/domains/terminal-management/policy/`



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

### `27.0-terminal-management-system-foundation`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.0-terminal-management-system-foundation.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_management_system_foundation_ef417643/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/terminal_management_system_foundation_ef417643.hpp`, `src/domains/terminal-management/subtask_targets/requirements/terminal_management_system_foundation_ef417643.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_terminal_management_system_foundation_ef417643.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.1-terminal-domain-model`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.1-terminal-domain-model.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_domain_model_de9b9568/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/contracts/terminal_domain_model_de9b9568.hpp`, `src/domains/terminal-management/subtask_targets/contracts/terminal_domain_model_de9b9568.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/contracts/test_terminal_domain_model_de9b9568.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.10-terminal-capability-detection`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.10-terminal-capability-detection.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_capability_detection_8b2fc931/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/terminal_capability_detection_8b2fc931.hpp`, `src/domains/terminal-management/subtask_targets/requirements/terminal_capability_detection_8b2fc931.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_terminal_capability_detection_8b2fc931.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.11-term-environment-semantics`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.11-term-environment-semantics.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/term_environment_semantics_9b4081ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/term_environment_semantics_9b4081ce.hpp`, `src/domains/terminal-management/subtask_targets/requirements/term_environment_semantics_9b4081ce.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_term_environment_semantics_9b4081ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.12-font-configuration-management`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.12-font-configuration-management.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/font_configuration_management_7676ad6a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/font_configuration_management_7676ad6a.hpp`, `src/domains/terminal-management/subtask_targets/requirements/font_configuration_management_7676ad6a.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_font_configuration_management_7676ad6a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.13-verified-glyph-compatibility-policy`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.13-verified-glyph-compatibility-policy.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/verified_glyph_compatibility_policy_6e598e31/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/security/verified_glyph_compatibility_policy_6e598e31.hpp`, `src/domains/terminal-management/subtask_targets/security/verified_glyph_compatibility_policy_6e598e31.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/security/test_verified_glyph_compatibility_policy_6e598e31.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.14-palette-color-capability-management`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.14-palette-color-capability-management.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/palette_color_capability_management_2ce86269/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/palette_color_capability_management_2ce86269.hpp`, `src/domains/terminal-management/subtask_targets/requirements/palette_color_capability_management_2ce86269.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_palette_color_capability_management_2ce86269.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.15-terminal-visual-profile`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.15-terminal-visual-profile.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_visual_profile_5ac41b65/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/terminal_visual_profile_5ac41b65.hpp`, `src/domains/terminal-management/subtask_targets/requirements/terminal_visual_profile_5ac41b65.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_terminal_visual_profile_5ac41b65.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.16-window-tab-behavior`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.16-window-tab-behavior.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/window_tab_behavior_f3b59f16/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/window_tab_behavior_f3b59f16.hpp`, `src/domains/terminal-management/subtask_targets/requirements/window_tab_behavior_f3b59f16.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_window_tab_behavior_f3b59f16.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.17-copy-paste-clipboard-boundary`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.17-copy-paste-clipboard-boundary.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/copy_paste_clipboard_boundary_bfd874c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/copy_paste_clipboard_boundary_bfd874c3.hpp`, `src/domains/terminal-management/subtask_targets/requirements/copy_paste_clipboard_boundary_bfd874c3.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_copy_paste_clipboard_boundary_bfd874c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.18-bracketed-paste-safety`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.18-bracketed-paste-safety.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/bracketed_paste_safety_e5c819a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/bracketed_paste_safety_e5c819a9.hpp`, `src/domains/terminal-management/subtask_targets/requirements/bracketed_paste_safety_e5c819a9.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_bracketed_paste_safety_e5c819a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.19-osc-escape-sequence-security`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.19-osc-escape-sequence-security.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/osc_escape_sequence_security_bf5af8cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/security/osc_escape_sequence_security_bf5af8cb.hpp`, `src/domains/terminal-management/subtask_targets/security/osc_escape_sequence_security_bf5af8cb.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/security/test_osc_escape_sequence_security_bf5af8cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.2-terminal-provider-discovery`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.2-terminal-provider-discovery.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_provider_discovery_a981540b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/integration/terminal_provider_discovery_a981540b.hpp`, `src/domains/terminal-management/subtask_targets/integration/terminal_provider_discovery_a981540b.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/integration/test_terminal_provider_discovery_a981540b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.20-remote-terminal-ssh-semantics`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.20-remote-terminal-ssh-semantics.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/remote_terminal_ssh_semantics_2d43cc0f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/remote_terminal_ssh_semantics_2d43cc0f.hpp`, `src/domains/terminal-management/subtask_targets/requirements/remote_terminal_ssh_semantics_2d43cc0f.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_remote_terminal_ssh_semantics_2d43cc0f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.21-terminal-configuration-ownership-drift`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.21-terminal-configuration-ownership-drift.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_configuration_ownership_drift_9219f9d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/terminal_configuration_ownership_drift_9219f9d4.hpp`, `src/domains/terminal-management/subtask_targets/requirements/terminal_configuration_ownership_drift_9219f9d4.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_terminal_configuration_ownership_drift_9219f9d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.22-terminal-health-diagnostics`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.22-terminal-health-diagnostics.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_health_diagnostics_7780fb5e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/observability/terminal_health_diagnostics_7780fb5e.hpp`, `src/domains/terminal-management/subtask_targets/observability/terminal_health_diagnostics_7780fb5e.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/observability/test_terminal_health_diagnostics_7780fb5e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.23-terminal-recovery-conservative-fallback`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.23-terminal-recovery-conservative-fallback.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_recovery_conservative_fallback_139ba540/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/recovery/terminal_recovery_conservative_fallback_139ba540.hpp`, `src/domains/terminal-management/subtask_targets/recovery/terminal_recovery_conservative_fallback_139ba540.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/recovery/test_terminal_recovery_conservative_fallback_139ba540.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.24-backup-restore-rollback`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.24-backup-restore-rollback.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/backup_restore_rollback_00ac3357/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/recovery/backup_restore_rollback_00ac3357.hpp`, `src/domains/terminal-management/subtask_targets/recovery/backup_restore_rollback_00ac3357.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/recovery/test_backup_restore_rollback_00ac3357.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.25-terminal-management-cli`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.25-terminal-management-cli.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_management_cli_7b5ff666/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/terminal_management_cli_7b5ff666.hpp`, `src/domains/terminal-management/subtask_targets/requirements/terminal_management_cli_7b5ff666.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_terminal_management_cli_7b5ff666.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.26-phase-25-panel-integration-api`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.26-phase-25-panel-integration-api.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/panel_integration_api_0f311d8b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/integration/panel_integration_api_0f311d8b.hpp`, `src/domains/terminal-management/subtask_targets/integration/panel_integration_api_0f311d8b.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/integration/test_panel_integration_api_0f311d8b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.27-phase-26-shell-integration-boundary`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.27-phase-26-shell-integration-boundary.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/shell_integration_boundary_45f179fb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/integration/shell_integration_boundary_45f179fb.hpp`, `src/domains/terminal-management/subtask_targets/integration/shell_integration_boundary_45f179fb.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/integration/test_shell_integration_boundary_45f179fb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.28-frontend-independence-future-providers`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.28-frontend-independence-future-providers.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/frontend_independence_future_providers_8c3c803c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/integration/frontend_independence_future_providers_8c3c803c.hpp`, `src/domains/terminal-management/subtask_targets/integration/frontend_independence_future_providers_8c3c803c.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/integration/test_frontend_independence_future_providers_8c3c803c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.29-security-privacy-exposure-audit`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.29-security-privacy-exposure-audit.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/security_privacy_exposure_audit_fe844d90/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/verification/security_privacy_exposure_audit_fe844d90.hpp`, `src/domains/terminal-management/subtask_targets/verification/security_privacy_exposure_audit_fe844d90.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/verification/test_security_privacy_exposure_audit_fe844d90.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.3-gnome-terminal-provider-adapter`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.3-gnome-terminal-provider-adapter.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/gnome_terminal_provider_adapter_0b2cc21e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/integration/gnome_terminal_provider_adapter_0b2cc21e.hpp`, `src/domains/terminal-management/subtask_targets/integration/gnome_terminal_provider_adapter_0b2cc21e.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/integration/test_gnome_terminal_provider_adapter_0b2cc21e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.30-failure-injection-recovery-testing`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.30-failure-injection-recovery-testing.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/failure_injection_recovery_testing_cd892311/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/verification/failure_injection_recovery_testing_cd892311.hpp`, `src/domains/terminal-management/subtask_targets/verification/failure_injection_recovery_testing_cd892311.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/verification/test_failure_injection_recovery_testing_cd892311.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.31-terminal-management-system-closure-readiness-gate`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.31-terminal-management-system-closure-readiness-gate.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_management_system_closure_readiness_gate_f74a70b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/terminal_management_system_closure_readiness_gate_f74a70b2.hpp`, `src/domains/terminal-management/subtask_targets/requirements/terminal_management_system_closure_readiness_gate_f74a70b2.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_terminal_management_system_closure_readiness_gate_f74a70b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.4-terminal-profile-registry`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.4-terminal-profile-registry.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_profile_registry_d22d76fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/terminal_profile_registry_d22d76fc.hpp`, `src/domains/terminal-management/subtask_targets/requirements/terminal_profile_registry_d22d76fc.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_terminal_profile_registry_d22d76fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.5-terminal-profile-lifecycle`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.5-terminal-profile-lifecycle.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_profile_lifecycle_7f1a89d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/lifecycle/terminal_profile_lifecycle_7f1a89d7.hpp`, `src/domains/terminal-management/subtask_targets/lifecycle/terminal_profile_lifecycle_7f1a89d7.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/lifecycle/test_terminal_profile_lifecycle_7f1a89d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.6-interactive-shell-launch-policy`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.6-interactive-shell-launch-policy.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/interactive_shell_launch_policy_727c94d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/security/interactive_shell_launch_policy_727c94d5.hpp`, `src/domains/terminal-management/subtask_targets/security/interactive_shell_launch_policy_727c94d5.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/security/test_interactive_shell_launch_policy_727c94d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.7-bash-console-launch-boundary`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.7-bash-console-launch-boundary.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/bash_console_launch_boundary_07e29e4e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/requirements/bash_console_launch_boundary_07e29e4e.hpp`, `src/domains/terminal-management/subtask_targets/requirements/bash_console_launch_boundary_07e29e4e.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/requirements/test_bash_console_launch_boundary_07e29e4e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.8-tty-pty-context-model`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.8-tty-pty-context-model.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/tty_pty_context_model_5472cd97/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/contracts/tty_pty_context_model_5472cd97.hpp`, `src/domains/terminal-management/subtask_targets/contracts/tty_pty_context_model_5472cd97.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/contracts/test_tty_pty_context_model_5472cd97.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `27.9-terminal-session-identity`
- **Source:** `.phases/phases/phase-27-terminal-management/prompts/27.9-terminal-session-identity.md`
- **Structural package:** `src/domains/terminal-management/subtask_packages/verification/terminal_session_identity_eb8213dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/terminal-management/subtask_targets/contracts/terminal_session_identity_eb8213dc.hpp`, `src/domains/terminal-management/subtask_targets/contracts/terminal_session_identity_eb8213dc.cpp`
- **Structural test target:** `tests/structural-closure/domains/terminal-management/contracts/test_terminal_session_identity_eb8213dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

