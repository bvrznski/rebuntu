# Phase 32 — Storage Management — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-32-storage-management/`
- Primary prompt location: `.phases/phases/phase-32-storage-management/prompts/`
- Prompt/specification Markdown files currently present: **63**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 63 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_32` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 32: Storage Management
- Layout
- Prompt Index
- Agent Handoff — Phase 32
- Phase 32.24 — Mount / Unmount Lifecycle
- Mission
- Non-negotiable architecture and invariants
- Phase-specific implementation requirements
- Required implementation method
- 1. Repository-first discovery
- 2. Structured provider evidence
- 3. Whole-stack resolution

## Structural skeleton / canonical destination
- Canonical skeleton: `src/domains/storage-management/`
- Structural files: `src/domains/storage-management/component.hpp`, `src/domains/storage-management/component.cpp`, `src/domains/storage-management/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/storage/README.md`
- `src/domains/storage/block_devices/README.md`
- `src/domains/storage/block_devices/contract.hpp`
- `src/domains/storage/capacity/README.md`
- `src/domains/storage/capacity/contract.hpp`
- `src/domains/storage/dependencies/README.md`
- `src/domains/storage/dependencies/contract.hpp`
- `src/domains/storage/desired_state/README.md`
- `src/domains/storage/desired_state/contract.hpp`
- `src/domains/storage/encryption/README.md`
- `src/domains/storage/encryption/contract.hpp`
- `src/domains/storage/filesystems/README.md`

### Existing test evidence
- `tests/native/test_config_storage.cpp`
- `tests/rebuntu/test_storage_reconciliation.cpp`

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

- Structural skeleton materialized at `src/domains/storage-management/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/storage-management/model/`
- `src/domains/storage-management/contracts/`
- `src/domains/storage-management/integration/`
- `src/domains/storage-management/verification/`
- `src/domains/storage-management/lifecycle/`
- `src/domains/storage-management/state/`
- `src/domains/storage-management/execution/`
- `src/domains/storage-management/transactions/`
- `src/domains/storage-management/events/`
- `src/domains/storage-management/scheduling/`
- `src/domains/storage-management/recovery/`
- `src/domains/storage-management/sources/`
- `src/domains/storage-management/resolution/`
- `src/domains/storage-management/diff/`
- `src/domains/storage-management/desired_state/`
- `src/domains/storage-management/validation/`
- `src/domains/storage-management/application/`
- `src/domains/storage-management/rollback/`



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

### `32.0-storage-management-system-foundation`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.0-storage-management-system-foundation.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_management_system_foundation_b263596e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/storage_management_system_foundation_b263596e.hpp`, `src/domains/storage-management/subtask_targets/requirements/storage_management_system_foundation_b263596e.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_storage_management_system_foundation_b263596e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.1-storage-domain-model`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.1-storage-domain-model.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_domain_model_4963b0d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/contracts/storage_domain_model_4963b0d2.hpp`, `src/domains/storage-management/subtask_targets/contracts/storage_domain_model_4963b0d2.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/contracts/test_storage_domain_model_4963b0d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.10-storage-stack-relationship-model`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.10-storage-stack-relationship-model.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_stack_relationship_model_3c1c5361/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/contracts/storage_stack_relationship_model_3c1c5361.hpp`, `src/domains/storage-management/subtask_targets/contracts/storage_stack_relationship_model_3c1c5361.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/contracts/test_storage_stack_relationship_model_3c1c5361.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.11-stable-storage-references`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.11-stable-storage-references.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/stable_storage_references_5f56e18b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/stable_storage_references_5f56e18b.hpp`, `src/domains/storage-management/subtask_targets/requirements/stable_storage_references_5f56e18b.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_stable_storage_references_5f56e18b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.12-block-device-inventory`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.12-block-device-inventory.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/block_device_inventory_b91cf40d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/block_device_inventory_b91cf40d.hpp`, `src/domains/storage-management/subtask_targets/requirements/block_device_inventory_b91cf40d.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_block_device_inventory_b91cf40d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.13-filesystem-inventory`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.13-filesystem-inventory.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/filesystem_inventory_2277eca2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/filesystem_inventory_2277eca2.hpp`, `src/domains/storage-management/subtask_targets/requirements/filesystem_inventory_2277eca2.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_filesystem_inventory_2277eca2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.14-mount-inventory`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.14-mount-inventory.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/mount_inventory_306f0dbb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/mount_inventory_306f0dbb.hpp`, `src/domains/storage-management/subtask_targets/requirements/mount_inventory_306f0dbb.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_mount_inventory_306f0dbb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.15-capacity-free-space-allocation-semantics`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.15-capacity-free-space-allocation-semantics.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/capacity_free_space_allocation_semantics_b04ff226/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/capacity_free_space_allocation_semantics_b04ff226.hpp`, `src/domains/storage-management/subtask_targets/requirements/capacity_free_space_allocation_semantics_b04ff226.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_capacity_free_space_allocation_semantics_b04ff226.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.16-storage-health-evidence`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.16-storage-health-evidence.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_health_evidence_16ca3ddd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/verification/storage_health_evidence_16ca3ddd.hpp`, `src/domains/storage-management/subtask_targets/verification/storage_health_evidence_16ca3ddd.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/verification/test_storage_health_evidence_16ca3ddd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.17-smart-nvme-health-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.17-smart-nvme-health-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/smart_nvme_health_integration_078b8593/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/smart_nvme_health_integration_078b8593.hpp`, `src/domains/storage-management/subtask_targets/integration/smart_nvme_health_integration_078b8593.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_smart_nvme_health_integration_078b8593.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.18-storage-i-o-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.18-storage-i-o-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_i_o_integration_8348a92a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/storage_i_o_integration_8348a92a.hpp`, `src/domains/storage-management/subtask_targets/integration/storage_i_o_integration_8348a92a.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_storage_i_o_integration_8348a92a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.19-storage-topology-dependency-analysis`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.19-storage-topology-dependency-analysis.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_topology_dependency_analysis_80b9cfe3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/observability/storage_topology_dependency_analysis_80b9cfe3.hpp`, `src/domains/storage-management/subtask_targets/observability/storage_topology_dependency_analysis_80b9cfe3.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/observability/test_storage_topology_dependency_analysis_80b9cfe3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.2-storage-provider-discovery`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.2-storage-provider-discovery.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_provider_discovery_4103c939/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/storage_provider_discovery_4103c939.hpp`, `src/domains/storage-management/subtask_targets/integration/storage_provider_discovery_4103c939.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_storage_provider_discovery_4103c939.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.20-root-boot-efi-protection`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.20-root-boot-efi-protection.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/root_boot_efi_protection_2fa92c38/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/root_boot_efi_protection_2fa92c38.hpp`, `src/domains/storage-management/subtask_targets/requirements/root_boot_efi_protection_2fa92c38.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_root_boot_efi_protection_2fa92c38.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.21-home-storage-protection`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.21-home-storage-protection.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/home_storage_protection_c17a150d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/home_storage_protection_c17a150d.hpp`, `src/domains/storage-management/subtask_targets/requirements/home_storage_protection_c17a150d.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_home_storage_protection_c17a150d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.22-active-workload-storage-protection`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.22-active-workload-storage-protection.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/active_workload_storage_protection_27fed36d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/active_workload_storage_protection_27fed36d.hpp`, `src/domains/storage-management/subtask_targets/requirements/active_workload_storage_protection_27fed36d.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_active_workload_storage_protection_27fed36d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.23-mount-planning`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.23-mount-planning.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/mount_planning_d223b45a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/planning/mount_planning_d223b45a.hpp`, `src/domains/storage-management/subtask_targets/planning/mount_planning_d223b45a.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/planning/test_mount_planning_d223b45a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.24-mount-unmount-lifecycle`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.24-mount-unmount-lifecycle.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/mount_unmount_lifecycle_e3db66ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/lifecycle/mount_unmount_lifecycle_e3db66ec.hpp`, `src/domains/storage-management/subtask_targets/lifecycle/mount_unmount_lifecycle_e3db66ec.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/lifecycle/test_mount_unmount_lifecycle_e3db66ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.25-persistent-mount-configuration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.25-persistent-mount-configuration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/persistent_mount_configuration_b0d2bf56/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/persistence/persistent_mount_configuration_b0d2bf56.hpp`, `src/domains/storage-management/subtask_targets/persistence/persistent_mount_configuration_b0d2bf56.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/persistence/test_persistent_mount_configuration_b0d2bf56.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.26-fstab-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.26-fstab-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/fstab_integration_d09389e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/fstab_integration_d09389e3.hpp`, `src/domains/storage-management/subtask_targets/integration/fstab_integration_d09389e3.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_fstab_integration_d09389e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.27-automount-systemd-mount-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.27-automount-systemd-mount-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/automount_systemd_mount_integration_8ebee582/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/automount_systemd_mount_integration_8ebee582.hpp`, `src/domains/storage-management/subtask_targets/integration/automount_systemd_mount_integration_8ebee582.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_automount_systemd_mount_integration_8ebee582.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.28-removable-hotplug-storage`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.28-removable-hotplug-storage.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/removable_hotplug_storage_c9c81a37/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/removable_hotplug_storage_c9c81a37.hpp`, `src/domains/storage-management/subtask_targets/requirements/removable_hotplug_storage_c9c81a37.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_removable_hotplug_storage_c9c81a37.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.29-storage-permission-ownership-context`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.29-storage-permission-ownership-context.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_permission_ownership_context_5f073305/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/security/storage_permission_ownership_context_5f073305.hpp`, `src/domains/storage-management/subtask_targets/security/storage_permission_ownership_context_5f073305.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/security/test_storage_permission_ownership_context_5f073305.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.3-physical-device-identity`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.3-physical-device-identity.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/physical_device_identity_54c0c157/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/contracts/physical_device_identity_54c0c157.hpp`, `src/domains/storage-management/subtask_targets/contracts/physical_device_identity_54c0c157.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/contracts/test_physical_device_identity_54c0c157.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.30-filesystem-check-boundary`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.30-filesystem-check-boundary.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/filesystem_check_boundary_631757d0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/filesystem_check_boundary_631757d0.hpp`, `src/domains/storage-management/subtask_targets/requirements/filesystem_check_boundary_631757d0.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_filesystem_check_boundary_631757d0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.31-filesystem-resize-boundary`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.31-filesystem-resize-boundary.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/filesystem_resize_boundary_2534fe26/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/filesystem_resize_boundary_2534fe26.hpp`, `src/domains/storage-management/subtask_targets/requirements/filesystem_resize_boundary_2534fe26.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_filesystem_resize_boundary_2534fe26.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.32-partition-resize-boundary`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.32-partition-resize-boundary.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/partition_resize_boundary_39515309/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/partition_resize_boundary_39515309.hpp`, `src/domains/storage-management/subtask_targets/requirements/partition_resize_boundary_39515309.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_partition_resize_boundary_39515309.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.33-encrypted-volume-lifecycle`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.33-encrypted-volume-lifecycle.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/encrypted_volume_lifecycle_0baf2cd9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/lifecycle/encrypted_volume_lifecycle_0baf2cd9.hpp`, `src/domains/storage-management/subtask_targets/lifecycle/encrypted_volume_lifecycle_0baf2cd9.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/lifecycle/test_encrypted_volume_lifecycle_0baf2cd9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.34-raid-lifecycle-boundary`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.34-raid-lifecycle-boundary.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/raid_lifecycle_boundary_813b0a08/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/lifecycle/raid_lifecycle_boundary_813b0a08.hpp`, `src/domains/storage-management/subtask_targets/lifecycle/raid_lifecycle_boundary_813b0a08.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/lifecycle/test_raid_lifecycle_boundary_813b0a08.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.35-snapshot-discovery-semantics`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.35-snapshot-discovery-semantics.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/snapshot_discovery_semantics_ced26ac7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/resolution/snapshot_discovery_semantics_ced26ac7.hpp`, `src/domains/storage-management/subtask_targets/resolution/snapshot_discovery_semantics_ced26ac7.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/resolution/test_snapshot_discovery_semantics_ced26ac7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.36-snapshot-vs-backup-separation`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.36-snapshot-vs-backup-separation.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/snapshot_vs_backup_separation_dfd4946a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/persistence/snapshot_vs_backup_separation_dfd4946a.hpp`, `src/domains/storage-management/subtask_targets/persistence/snapshot_vs_backup_separation_dfd4946a.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/persistence/test_snapshot_vs_backup_separation_dfd4946a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.37-backup-integration-boundary`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.37-backup-integration-boundary.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/backup_integration_boundary_f5f4b0ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/backup_integration_boundary_f5f4b0ba.hpp`, `src/domains/storage-management/subtask_targets/integration/backup_integration_boundary_f5f4b0ba.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_backup_integration_boundary_f5f4b0ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.38-storage-change-planning`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.38-storage-change-planning.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_change_planning_05cc97da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/planning/storage_change_planning_05cc97da.hpp`, `src/domains/storage-management/subtask_targets/planning/storage_change_planning_05cc97da.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/planning/test_storage_change_planning_05cc97da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.39-destructive-action-classification`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.39-destructive-action-classification.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/destructive_action_classification_1dbacbd5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/destructive_action_classification_1dbacbd5.hpp`, `src/domains/storage-management/subtask_targets/requirements/destructive_action_classification_1dbacbd5.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_destructive_action_classification_1dbacbd5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.4-partition-table-partition-model`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.4-partition-table-partition-model.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/partition_table_partition_model_04891c3e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/contracts/partition_table_partition_model_04891c3e.hpp`, `src/domains/storage-management/subtask_targets/contracts/partition_table_partition_model_04891c3e.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/contracts/test_partition_table_partition_model_04891c3e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.40-format-reformat-safety-boundary`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.40-format-reformat-safety-boundary.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/format_reformat_safety_boundary_e8d4e057/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/format_reformat_safety_boundary_e8d4e057.hpp`, `src/domains/storage-management/subtask_targets/requirements/format_reformat_safety_boundary_e8d4e057.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_format_reformat_safety_boundary_e8d4e057.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.41-partition-table-mutation-safety`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.41-partition-table-mutation-safety.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/partition_table_mutation_safety_0904be94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/execution/partition_table_mutation_safety_0904be94.hpp`, `src/domains/storage-management/subtask_targets/execution/partition_table_mutation_safety_0904be94.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/execution/test_partition_table_mutation_safety_0904be94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.42-data-migration-planning`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.42-data-migration-planning.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/data_migration_planning_45fa1421/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/data_migration_planning_45fa1421.hpp`, `src/domains/storage-management/subtask_targets/integration/data_migration_planning_45fa1421.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_data_migration_planning_45fa1421.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.43-home-migration-support`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.43-home-migration-support.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/home_migration_support_36261a23/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/home_migration_support_36261a23.hpp`, `src/domains/storage-management/subtask_targets/integration/home_migration_support_36261a23.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_home_migration_support_36261a23.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.44-storage-recovery-rollback`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.44-storage-recovery-rollback.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_recovery_rollback_421963bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/recovery/storage_recovery_rollback_421963bb.hpp`, `src/domains/storage-management/subtask_targets/recovery/storage_recovery_rollback_421963bb.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/recovery/test_storage_recovery_rollback_421963bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.45-boot-recovery-for-storage-changes`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.45-boot-recovery-for-storage-changes.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/boot_recovery_for_storage_changes_44f167a6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/recovery/boot_recovery_for_storage_changes_44f167a6.hpp`, `src/domains/storage-management/subtask_targets/recovery/boot_recovery_for_storage_changes_44f167a6.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/recovery/test_boot_recovery_for_storage_changes_44f167a6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.46-storage-drift-detection`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.46-storage-drift-detection.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_drift_detection_3c4dabee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/storage_drift_detection_3c4dabee.hpp`, `src/domains/storage-management/subtask_targets/requirements/storage_drift_detection_3c4dabee.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_storage_drift_detection_3c4dabee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.47-storage-management-cli`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.47-storage-management-cli.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_management_cli_cfdfdab8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/storage_management_cli_cfdfdab8.hpp`, `src/domains/storage-management/subtask_targets/requirements/storage_management_cli_cfdfdab8.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_storage_management_cli_cfdfdab8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.48-phase-25-panel-integration-api`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.48-phase-25-panel-integration-api.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/panel_integration_api_8db3626b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/panel_integration_api_8db3626b.hpp`, `src/domains/storage-management/subtask_targets/integration/panel_integration_api_8db3626b.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_panel_integration_api_8db3626b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.49-phase-29-workload-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.49-phase-29-workload-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/workload_integration_3c034e81/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/workload_integration_3c034e81.hpp`, `src/domains/storage-management/subtask_targets/integration/workload_integration_3c034e81.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_workload_integration_3c034e81.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.5-device-mapper-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.5-device-mapper-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/device_mapper_integration_a04c3cd2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/device_mapper_integration_a04c3cd2.hpp`, `src/domains/storage-management/subtask_targets/integration/device_mapper_integration_a04c3cd2.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_device_mapper_integration_a04c3cd2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.50-phase-30-resource-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.50-phase-30-resource-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/resource_integration_3037cb7e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/resource_integration_3037cb7e.hpp`, `src/domains/storage-management/subtask_targets/integration/resource_integration_3037cb7e.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_resource_integration_3037cb7e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.51-phase-31-service-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.51-phase-31-service-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/service_integration_769935f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/service_integration_769935f9.hpp`, `src/domains/storage-management/subtask_targets/integration/service_integration_769935f9.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_service_integration_769935f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.52-phase-36-configuration-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.52-phase-36-configuration-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/configuration_integration_47a8e249/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/configuration_integration_47a8e249.hpp`, `src/domains/storage-management/subtask_targets/integration/configuration_integration_47a8e249.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_configuration_integration_47a8e249.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.53-phase-37-secrets-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.53-phase-37-secrets-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/secrets_integration_acceca0f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/security/secrets_integration_acceca0f.hpp`, `src/domains/storage-management/subtask_targets/security/secrets_integration_acceca0f.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/security/test_secrets_integration_acceca0f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.54-phase-39-timeline-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.54-phase-39-timeline-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/timeline_integration_b6d64fa8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/timeline_integration_b6d64fa8.hpp`, `src/domains/storage-management/subtask_targets/integration/timeline_integration_b6d64fa8.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_timeline_integration_b6d64fa8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.55-failure-injection-disposable-storage-testing`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.55-failure-injection-disposable-storage-testing.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/failure_injection_disposable_storage_testing_d40c1d44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/verification/failure_injection_disposable_storage_testing_d40c1d44.hpp`, `src/domains/storage-management/subtask_targets/verification/failure_injection_disposable_storage_testing_d40c1d44.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/verification/test_failure_injection_disposable_storage_testing_d40c1d44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.56-storage-management-system-closure-readiness-gate`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.56-storage-management-system-closure-readiness-gate.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/storage_management_system_closure_readiness_gate_876aa5a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/requirements/storage_management_system_closure_readiness_gate_876aa5a2.hpp`, `src/domains/storage-management/subtask_targets/requirements/storage_management_system_closure_readiness_gate_876aa5a2.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/requirements/test_storage_management_system_closure_readiness_gate_876aa5a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.6-software-raid-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.6-software-raid-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/software_raid_integration_bce836ff/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/software_raid_integration_bce836ff.hpp`, `src/domains/storage-management/subtask_targets/integration/software_raid_integration_bce836ff.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_software_raid_integration_bce836ff.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.7-luks-encrypted-storage-integration`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.7-luks-encrypted-storage-integration.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/luks_encrypted_storage_integration_51c77bd2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/integration/luks_encrypted_storage_integration_51c77bd2.hpp`, `src/domains/storage-management/subtask_targets/integration/luks_encrypted_storage_integration_51c77bd2.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/integration/test_luks_encrypted_storage_integration_51c77bd2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.8-filesystem-identity-capabilities`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.8-filesystem-identity-capabilities.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/filesystem_identity_capabilities_62c1a129/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/contracts/filesystem_identity_capabilities_62c1a129.hpp`, `src/domains/storage-management/subtask_targets/contracts/filesystem_identity_capabilities_62c1a129.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/contracts/test_filesystem_identity_capabilities_62c1a129.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `32.9-mount-identity-state`
- **Source:** `.phases/phases/phase-32-storage-management/prompts/32.9-mount-identity-state.md`
- **Structural package:** `src/domains/storage-management/subtask_packages/verification/mount_identity_state_83959bde/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/storage-management/subtask_targets/lifecycle/mount_identity_state_83959bde.hpp`, `src/domains/storage-management/subtask_targets/lifecycle/mount_identity_state_83959bde.cpp`
- **Structural test target:** `tests/structural-closure/domains/storage-management/lifecycle/test_mount_identity_state_83959bde.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

