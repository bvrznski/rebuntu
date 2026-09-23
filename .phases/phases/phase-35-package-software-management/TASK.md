# Phase 35 — Package Software Management — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-35-package-software-management/`
- Primary prompt location: `.phases/phases/phase-35-package-software-management/prompts/`
- Prompt/specification Markdown files currently present: **70**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 70 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_35` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 35: Package Software Management
- Layout
- Prompt Index
- Agent Handoff — Phase 35
- Phase 35.27 — Snap Provider Integration
- Mission
- Non-negotiable architecture and invariants
- Phase-specific implementation requirements
- Required implementation method
- Global acceptance gate
- Required final report for Phase 35.27
- IMPLEMENTATION LANGUAGE OVERRIDE

## Structural skeleton / canonical destination
- Canonical skeleton: `src/domains/package-software-management/`
- Structural files: `src/domains/package-software-management/component.hpp`, `src/domains/package-software-management/component.cpp`, `src/domains/package-software-management/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/software/packages/README.md`
- `src/domains/software/packages/contract.hpp`
- `src/domains/software/README.md`
- `src/domains/software/dependencies/README.md`
- `src/domains/software/dependencies/contract.hpp`
- `src/domains/software/desired_state/README.md`
- `src/domains/software/desired_state/contract.hpp`
- `src/domains/software/dpkg.hpp`
- `src/domains/software/model/README.md`
- `src/domains/software/model/contract.hpp`
- `src/domains/software/native/dpkg.cpp`
- `src/domains/software/recovery/README.md`

### Existing test evidence
- `tests/native/test_packages.cpp`

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

- Structural skeleton materialized at `src/domains/package-software-management/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/package-software-management/model/`
- `src/domains/package-software-management/contracts/`
- `src/domains/package-software-management/integration/`
- `src/domains/package-software-management/verification/`
- `src/domains/package-software-management/lifecycle/`
- `src/domains/package-software-management/state/`
- `src/domains/package-software-management/execution/`
- `src/domains/package-software-management/transactions/`
- `src/domains/package-software-management/events/`
- `src/domains/package-software-management/scheduling/`
- `src/domains/package-software-management/recovery/`
- `src/domains/package-software-management/identity/`
- `src/domains/package-software-management/inventory/`
- `src/domains/package-software-management/repositories/`
- `src/domains/package-software-management/dependencies/`
- `src/domains/package-software-management/desired_state/`
- `src/domains/package-software-management/rollback/`
- `src/domains/package-software-management/sources/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

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

### `35.0-package-software-management-system-foundation`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.0-package-software-management-system-foundation.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_software_management_system_foundation_c7bac8bd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/package_software_management_system_foundation_c7bac8bd.hpp`, `src/domains/package-software-management/subtask_targets/requirements/package_software_management_system_foundation_c7bac8bd.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_package_software_management_system_foundation_c7bac8bd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.1-software-domain-model`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.1-software-domain-model.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_domain_model_e4305262/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/contracts/software_domain_model_e4305262.hpp`, `src/domains/package-software-management/subtask_targets/contracts/software_domain_model_e4305262.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/contracts/test_software_domain_model_e4305262.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.10-installed-vs-available-version-semantics`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.10-installed-vs-available-version-semantics.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/installed_vs_available_version_semantics_2f6f7126/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/installed_vs_available_version_semantics_2f6f7126.hpp`, `src/domains/package-software-management/subtask_targets/requirements/installed_vs_available_version_semantics_2f6f7126.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_installed_vs_available_version_semantics_2f6f7126.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.11-package-dependency-evidence`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.11-package-dependency-evidence.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_dependency_evidence_ede49b5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/verification/package_dependency_evidence_ede49b5d.hpp`, `src/domains/package-software-management/subtask_targets/verification/package_dependency_evidence_ede49b5d.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/verification/test_package_dependency_evidence_ede49b5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.12-native-dependency-resolution-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.12-native-dependency-resolution-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/native_dependency_resolution_boundary_bc736fee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/native_dependency_resolution_boundary_bc736fee.hpp`, `src/domains/package-software-management/subtask_targets/requirements/native_dependency_resolution_boundary_bc736fee.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_native_dependency_resolution_boundary_bc736fee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.13-package-install-planning`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.13-package-install-planning.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_install_planning_4191ecf4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/planning/package_install_planning_4191ecf4.hpp`, `src/domains/package-software-management/subtask_targets/planning/package_install_planning_4191ecf4.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/planning/test_package_install_planning_4191ecf4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.14-package-upgrade-planning`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.14-package-upgrade-planning.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_upgrade_planning_166e09fb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/planning/package_upgrade_planning_166e09fb.hpp`, `src/domains/package-software-management/subtask_targets/planning/package_upgrade_planning_166e09fb.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/planning/test_package_upgrade_planning_166e09fb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.15-package-removal-planning`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.15-package-removal-planning.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_removal_planning_6f5cce1c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/planning/package_removal_planning_6f5cce1c.hpp`, `src/domains/package-software-management/subtask_targets/planning/package_removal_planning_6f5cce1c.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/planning/test_package_removal_planning_6f5cce1c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.16-purge-semantics-safety-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.16-purge-semantics-safety-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/purge_semantics_safety_boundary_6e0d1d65/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/purge_semantics_safety_boundary_6e0d1d65.hpp`, `src/domains/package-software-management/subtask_targets/requirements/purge_semantics_safety_boundary_6e0d1d65.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_purge_semantics_safety_boundary_6e0d1d65.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.17-autoremove-safety-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.17-autoremove-safety-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/autoremove_safety_boundary_aa565d91/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/autoremove_safety_boundary_aa565d91.hpp`, `src/domains/package-software-management/subtask_targets/requirements/autoremove_safety_boundary_aa565d91.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_autoremove_safety_boundary_aa565d91.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.18-package-hold-pin-preference-semantics`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.18-package-hold-pin-preference-semantics.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_hold_pin_preference_semantics_044474db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/package_hold_pin_preference_semantics_044474db.hpp`, `src/domains/package-software-management/subtask_targets/requirements/package_hold_pin_preference_semantics_044474db.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_package_hold_pin_preference_semantics_044474db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.19-package-configuration-state`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.19-package-configuration-state.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_configuration_state_961f58f8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/lifecycle/package_configuration_state_961f58f8.hpp`, `src/domains/package-software-management/subtask_targets/lifecycle/package_configuration_state_961f58f8.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/lifecycle/test_package_configuration_state_961f58f8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.2-package-provider-discovery`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.2-package-provider-discovery.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_provider_discovery_73a6b04a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/package_provider_discovery_73a6b04a.hpp`, `src/domains/package-software-management/subtask_targets/integration/package_provider_discovery_73a6b04a.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_package_provider_discovery_73a6b04a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.20-conffile-conflict-handling`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.20-conffile-conflict-handling.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/conffile_conflict_handling_e384ae37/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/conffile_conflict_handling_e384ae37.hpp`, `src/domains/package-software-management/subtask_targets/requirements/conffile_conflict_handling_e384ae37.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_conffile_conflict_handling_e384ae37.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.21-package-transaction-model`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.21-package-transaction-model.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_transaction_model_f5ac5296/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/contracts/package_transaction_model_f5ac5296.hpp`, `src/domains/package-software-management/subtask_targets/contracts/package_transaction_model_f5ac5296.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/contracts/test_package_transaction_model_f5ac5296.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.22-package-transaction-verification`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.22-package-transaction-verification.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_transaction_verification_76f99bdd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/verification/package_transaction_verification_76f99bdd.hpp`, `src/domains/package-software-management/subtask_targets/verification/package_transaction_verification_76f99bdd.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/verification/test_package_transaction_verification_76f99bdd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.23-interrupted-dpkg-apt-recovery`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.23-interrupted-dpkg-apt-recovery.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/interrupted_dpkg_apt_recovery_3da77451/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/recovery/interrupted_dpkg_apt_recovery_3da77451.hpp`, `src/domains/package-software-management/subtask_targets/recovery/interrupted_dpkg_apt_recovery_3da77451.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/recovery/test_interrupted_dpkg_apt_recovery_3da77451.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.24-flatpak-provider-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.24-flatpak-provider-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/flatpak_provider_integration_6c616fbc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/flatpak_provider_integration_6c616fbc.hpp`, `src/domains/package-software-management/subtask_targets/integration/flatpak_provider_integration_6c616fbc.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_flatpak_provider_integration_6c616fbc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.25-flatpak-remote-ref-model`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.25-flatpak-remote-ref-model.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/flatpak_remote_ref_model_9bba534a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/contracts/flatpak_remote_ref_model_9bba534a.hpp`, `src/domains/package-software-management/subtask_targets/contracts/flatpak_remote_ref_model_9bba534a.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/contracts/test_flatpak_remote_ref_model_9bba534a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.26-flatpak-permission-evidence`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.26-flatpak-permission-evidence.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/flatpak_permission_evidence_0ba474c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/verification/flatpak_permission_evidence_0ba474c9.hpp`, `src/domains/package-software-management/subtask_targets/verification/flatpak_permission_evidence_0ba474c9.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/verification/test_flatpak_permission_evidence_0ba474c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.27-snap-provider-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.27-snap-provider-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/snap_provider_integration_beadf0dd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/snap_provider_integration_beadf0dd.hpp`, `src/domains/package-software-management/subtask_targets/integration/snap_provider_integration_beadf0dd.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_snap_provider_integration_beadf0dd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.28-standalone-software-discovery`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.28-standalone-software-discovery.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/standalone_software_discovery_bc5f8b71/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/resolution/standalone_software_discovery_bc5f8b71.hpp`, `src/domains/package-software-management/subtask_targets/resolution/standalone_software_discovery_bc5f8b71.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/resolution/test_standalone_software_discovery_bc5f8b71.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.29-local-manual-package-discovery`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.29-local-manual-package-discovery.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/local_manual_package_discovery_6bf5ee56/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/resolution/local_manual_package_discovery_6bf5ee56.hpp`, `src/domains/package-software-management/subtask_targets/resolution/local_manual_package_discovery_6bf5ee56.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/resolution/test_local_manual_package_discovery_6bf5ee56.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.3-installed-package-identity`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.3-installed-package-identity.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/installed_package_identity_8e0d8a6b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/contracts/installed_package_identity_8e0d8a6b.hpp`, `src/domains/package-software-management/subtask_targets/contracts/installed_package_identity_8e0d8a6b.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/contracts/test_installed_package_identity_8e0d8a6b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.30-executable-provenance-resolution`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.30-executable-provenance-resolution.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/executable_provenance_resolution_ad22aef3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/execution/executable_provenance_resolution_ad22aef3.hpp`, `src/domains/package-software-management/subtask_targets/execution/executable_provenance_resolution_ad22aef3.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/execution/test_executable_provenance_resolution_ad22aef3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.31-desktop-application-discovery`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.31-desktop-application-discovery.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/desktop_application_discovery_99e9fe4b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/resolution/desktop_application_discovery_99e9fe4b.hpp`, `src/domains/package-software-management/subtask_targets/resolution/desktop_application_discovery_99e9fe4b.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/resolution/test_desktop_application_discovery_99e9fe4b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.32-duplicate-application-detection`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.32-duplicate-application-detection.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/duplicate_application_detection_195cb14b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/duplicate_application_detection_195cb14b.hpp`, `src/domains/package-software-management/subtask_targets/requirements/duplicate_application_detection_195cb14b.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_duplicate_application_detection_195cb14b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.33-duplicate-installation-analysis`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.33-duplicate-installation-analysis.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/duplicate_installation_analysis_910d9c84/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/duplicate_installation_analysis_910d9c84.hpp`, `src/domains/package-software-management/subtask_targets/requirements/duplicate_installation_analysis_910d9c84.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_duplicate_installation_analysis_910d9c84.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.34-software-ownership-origin`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.34-software-ownership-origin.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_ownership_origin_76ccb09c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/software_ownership_origin_76ccb09c.hpp`, `src/domains/package-software-management/subtask_targets/requirements/software_ownership_origin_76ccb09c.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_software_ownership_origin_76ccb09c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.35-package-file-ownership-evidence`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.35-package-file-ownership-evidence.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_file_ownership_evidence_71c0edbc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/verification/package_file_ownership_evidence_71c0edbc.hpp`, `src/domains/package-software-management/subtask_targets/verification/package_file_ownership_evidence_71c0edbc.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/verification/test_package_file_ownership_evidence_71c0edbc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.36-software-dependency-impact-analysis`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.36-software-dependency-impact-analysis.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_dependency_impact_analysis_ad097edb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/software_dependency_impact_analysis_ad097edb.hpp`, `src/domains/package-software-management/subtask_targets/requirements/software_dependency_impact_analysis_ad097edb.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_software_dependency_impact_analysis_ad097edb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.37-running-workload-impact-analysis`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.37-running-workload-impact-analysis.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/running_workload_impact_analysis_63200b58/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/running_workload_impact_analysis_63200b58.hpp`, `src/domains/package-software-management/subtask_targets/requirements/running_workload_impact_analysis_63200b58.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_running_workload_impact_analysis_63200b58.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.38-service-impact-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.38-service-impact-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/service_impact_integration_1203169f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/service_impact_integration_1203169f.hpp`, `src/domains/package-software-management/subtask_targets/integration/service_impact_integration_1203169f.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_service_impact_integration_1203169f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.39-kernel-driver-package-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.39-kernel-driver-package-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/kernel_driver_package_boundary_f50ec7fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/kernel_driver_package_boundary_f50ec7fc.hpp`, `src/domains/package-software-management/subtask_targets/requirements/kernel_driver_package_boundary_f50ec7fc.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_kernel_driver_package_boundary_f50ec7fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.4-application-vs-package-vs-executable-model`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.4-application-vs-package-vs-executable-model.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/application_vs_package_vs_executable_model_c7a4f4e6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/execution/application_vs_package_vs_executable_model_c7a4f4e6.hpp`, `src/domains/package-software-management/subtask_targets/execution/application_vs_package_vs_executable_model_c7a4f4e6.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/execution/test_application_vs_package_vs_executable_model_c7a4f4e6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.40-development-dependency-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.40-development-dependency-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/development_dependency_boundary_239b430d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/development_dependency_boundary_239b430d.hpp`, `src/domains/package-software-management/subtask_targets/requirements/development_dependency_boundary_239b430d.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_development_dependency_boundary_239b430d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.41-container-software-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.41-container-software-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/container_software_boundary_7cbb079e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/container_software_boundary_7cbb079e.hpp`, `src/domains/package-software-management/subtask_targets/requirements/container_software_boundary_7cbb079e.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_container_software_boundary_7cbb079e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.42-software-configuration-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.42-software-configuration-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_configuration_boundary_7f00ffa1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/software_configuration_boundary_7f00ffa1.hpp`, `src/domains/package-software-management/subtask_targets/requirements/software_configuration_boundary_7f00ffa1.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_software_configuration_boundary_7f00ffa1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.43-package-cache-download-semantics`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.43-package-cache-download-semantics.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_cache_download_semantics_53e801fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/persistence/package_cache_download_semantics_53e801fc.hpp`, `src/domains/package-software-management/subtask_targets/persistence/package_cache_download_semantics_53e801fc.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/persistence/test_package_cache_download_semantics_53e801fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.44-package-cleanup-safety`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.44-package-cleanup-safety.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_cleanup_safety_bbec0a57/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/package_cleanup_safety_bbec0a57.hpp`, `src/domains/package-software-management/subtask_targets/requirements/package_cleanup_safety_bbec0a57.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_package_cleanup_safety_bbec0a57.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.45-repository-change-planning`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.45-repository-change-planning.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/repository_change_planning_23c2796d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/planning/repository_change_planning_23c2796d.hpp`, `src/domains/package-software-management/subtask_targets/planning/repository_change_planning_23c2796d.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/planning/test_repository_change_planning_23c2796d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.46-software-change-planning`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.46-software-change-planning.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_change_planning_b8567ecf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/planning/software_change_planning_b8567ecf.hpp`, `src/domains/package-software-management/subtask_targets/planning/software_change_planning_b8567ecf.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/planning/test_software_change_planning_b8567ecf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.47-software-mutation-authorization`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.47-software-mutation-authorization.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_mutation_authorization_b5d193ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/security/software_mutation_authorization_b5d193ca.hpp`, `src/domains/package-software-management/subtask_targets/security/software_mutation_authorization_b5d193ca.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/security/test_software_mutation_authorization_b5d193ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.48-package-manager-locking-concurrency`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.48-package-manager-locking-concurrency.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_manager_locking_concurrency_1a820842/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/package_manager_locking_concurrency_1a820842.hpp`, `src/domains/package-software-management/subtask_targets/requirements/package_manager_locking_concurrency_1a820842.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_package_manager_locking_concurrency_1a820842.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.49-offline-partial-network-behavior`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.49-offline-partial-network-behavior.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/offline_partial_network_behavior_ff877626/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/offline_partial_network_behavior_ff877626.hpp`, `src/domains/package-software-management/subtask_targets/requirements/offline_partial_network_behavior_ff877626.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_offline_partial_network_behavior_ff877626.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.5-apt-dpkg-provider-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.5-apt-dpkg-provider-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/apt_dpkg_provider_integration_7bf69e01/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/apt_dpkg_provider_integration_7bf69e01.hpp`, `src/domains/package-software-management/subtask_targets/integration/apt_dpkg_provider_integration_7bf69e01.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_apt_dpkg_provider_integration_7bf69e01.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.50-software-drift-detection`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.50-software-drift-detection.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_drift_detection_f92be092/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/software_drift_detection_f92be092.hpp`, `src/domains/package-software-management/subtask_targets/requirements/software_drift_detection_f92be092.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_software_drift_detection_f92be092.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.51-software-health-diagnostics`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.51-software-health-diagnostics.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_health_diagnostics_1ee0a297/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/observability/software_health_diagnostics_1ee0a297.hpp`, `src/domains/package-software-management/subtask_targets/observability/software_health_diagnostics_1ee0a297.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/observability/test_software_health_diagnostics_1ee0a297.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.52-software-management-cli`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.52-software-management-cli.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/software_management_cli_d0b45396/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/software_management_cli_d0b45396.hpp`, `src/domains/package-software-management/subtask_targets/requirements/software_management_cli_d0b45396.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_software_management_cli_d0b45396.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.53-phase-25-panel-integration-api`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.53-phase-25-panel-integration-api.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/panel_integration_api_1ed6e86b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/panel_integration_api_1ed6e86b.hpp`, `src/domains/package-software-management/subtask_targets/integration/panel_integration_api_1ed6e86b.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_panel_integration_api_1ed6e86b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.54-phase-24-platform-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.54-phase-24-platform-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/platform_integration_2bbba88f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/platform_integration_2bbba88f.hpp`, `src/domains/package-software-management/subtask_targets/integration/platform_integration_2bbba88f.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_platform_integration_2bbba88f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.55-phase-28-development-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.55-phase-28-development-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/development_integration_b9b7bd38/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/development_integration_b9b7bd38.hpp`, `src/domains/package-software-management/subtask_targets/integration/development_integration_b9b7bd38.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_development_integration_b9b7bd38.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.56-phase-29-workload-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.56-phase-29-workload-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/workload_integration_b5aa155f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/workload_integration_b5aa155f.hpp`, `src/domains/package-software-management/subtask_targets/integration/workload_integration_b5aa155f.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_workload_integration_b5aa155f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.57-phase-31-service-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.57-phase-31-service-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/service_integration_66998557/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/service_integration_66998557.hpp`, `src/domains/package-software-management/subtask_targets/integration/service_integration_66998557.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_service_integration_66998557.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.58-phase-36-configuration-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.58-phase-36-configuration-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/configuration_integration_d4a7b743/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/configuration_integration_d4a7b743.hpp`, `src/domains/package-software-management/subtask_targets/integration/configuration_integration_d4a7b743.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_configuration_integration_d4a7b743.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.59-phase-37-secrets-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.59-phase-37-secrets-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/secrets_integration_22b87bee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/security/secrets_integration_22b87bee.hpp`, `src/domains/package-software-management/subtask_targets/security/secrets_integration_22b87bee.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/security/test_secrets_integration_22b87bee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.6-apt-repository-discovery`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.6-apt-repository-discovery.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/apt_repository_discovery_ef4af6f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/resolution/apt_repository_discovery_ef4af6f2.hpp`, `src/domains/package-software-management/subtask_targets/resolution/apt_repository_discovery_ef4af6f2.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/resolution/test_apt_repository_discovery_ef4af6f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.60-phase-39-timeline-integration`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.60-phase-39-timeline-integration.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/timeline_integration_59ea7d64/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/timeline_integration_59ea7d64.hpp`, `src/domains/package-software-management/subtask_targets/integration/timeline_integration_59ea7d64.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_timeline_integration_59ea7d64.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.61-cross-provider-software-inventory`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.61-cross-provider-software-inventory.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/cross_provider_software_inventory_6da3fa9a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/integration/cross_provider_software_inventory_6da3fa9a.hpp`, `src/domains/package-software-management/subtask_targets/integration/cross_provider_software_inventory_6da3fa9a.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/integration/test_cross_provider_software_inventory_6da3fa9a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.62-failure-injection-disposable-package-testing`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.62-failure-injection-disposable-package-testing.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/failure_injection_disposable_package_testing_3b02d46a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/verification/failure_injection_disposable_package_testing_3b02d46a.hpp`, `src/domains/package-software-management/subtask_targets/verification/failure_injection_disposable_package_testing_3b02d46a.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/verification/test_failure_injection_disposable_package_testing_3b02d46a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.63-package-software-management-system-closure-readiness-gate`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.63-package-software-management-system-closure-readiness-gate.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_software_management_system_closure_readiness_gate_c1bd6a91/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/package_software_management_system_closure_readiness_gate_c1bd6a91.hpp`, `src/domains/package-software-management/subtask_targets/requirements/package_software_management_system_closure_readiness_gate_c1bd6a91.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_package_software_management_system_closure_readiness_gate_c1bd6a91.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.7-apt-source-configuration-provenance`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.7-apt-source-configuration-provenance.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/apt_source_configuration_provenance_71338fdf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/requirements/apt_source_configuration_provenance_71338fdf.hpp`, `src/domains/package-software-management/subtask_targets/requirements/apt_source_configuration_provenance_71338fdf.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/requirements/test_apt_source_configuration_provenance_71338fdf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.8-repository-trust-signature-boundary`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.8-repository-trust-signature-boundary.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/repository_trust_signature_boundary_b26bca72/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/security/repository_trust_signature_boundary_b26bca72.hpp`, `src/domains/package-software-management/subtask_targets/security/repository_trust_signature_boundary_b26bca72.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/security/test_repository_trust_signature_boundary_b26bca72.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `35.9-package-candidate-version-model`
- **Source:** `.phases/phases/phase-35-package-software-management/prompts/35.9-package-candidate-version-model.md`
- **Structural package:** `src/domains/package-software-management/subtask_packages/verification/package_candidate_version_model_9d60ade5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/package-software-management/subtask_targets/contracts/package_candidate_version_model_9d60ade5.hpp`, `src/domains/package-software-management/subtask_targets/contracts/package_candidate_version_model_9d60ade5.cpp`
- **Structural test target:** `tests/structural-closure/domains/package-software-management/contracts/test_package_candidate_version_model_9d60ade5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

