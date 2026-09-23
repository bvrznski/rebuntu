# Phase 45 — Unified Control Plane — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-45-unified-control-plane/`
- Primary prompt location: `.phases/phases/phase-45-unified-control-plane/prompts/`
- Prompt/specification Markdown files currently present: **368**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 368 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_45` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 45 — Unified Control Plane
- Required execution
- Phase 45 Index
- Normative architecture
- Full executable prompts
- Phase 45 Agent Handoff
- Phase 45.343 — Final production-path trace
- Objective
- Repository-first execution
- Fundamental authority model
- Typed-control requirements
- Safety and resilience

## Structural skeleton / canonical destination
- Canonical skeleton: `src/runtime/unified-control-plane/`
- Structural files: `src/runtime/unified-control-plane/component.hpp`, `src/runtime/unified-control-plane/component.cpp`, `src/runtime/unified-control-plane/IMPLEMENTATION.json`
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

- Structural skeleton materialized at `src/runtime/unified-control-plane/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/runtime/unified-control-plane/model/`
- `src/runtime/unified-control-plane/contracts/`
- `src/runtime/unified-control-plane/integration/`
- `src/runtime/unified-control-plane/verification/`
- `src/runtime/unified-control-plane/lifecycle/`
- `src/runtime/unified-control-plane/state/`
- `src/runtime/unified-control-plane/execution/`
- `src/runtime/unified-control-plane/transactions/`
- `src/runtime/unified-control-plane/events/`
- `src/runtime/unified-control-plane/scheduling/`
- `src/runtime/unified-control-plane/recovery/`
- `src/runtime/unified-control-plane/principals/`
- `src/runtime/unified-control-plane/groups/`
- `src/runtime/unified-control-plane/roles/`
- `src/runtime/unified-control-plane/resolution/`
- `src/runtime/unified-control-plane/authorization/`
- `src/runtime/unified-control-plane/credentials/`
- `src/runtime/unified-control-plane/policy/`



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

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `45.000-foundation-and-repository-archaeology`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.000-foundation-and-repository-archaeology.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/foundation_and_repository_archaeology_43a40a35/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/foundation_and_repository_archaeology_43a40a35.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/foundation_and_repository_archaeology_43a40a35.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_foundation_and_repository_archaeology_43a40a35.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.001-control-plane-inventory`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.001-control-plane-inventory.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_inventory_1f39aa55/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_inventory_1f39aa55.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_inventory_1f39aa55.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_inventory_1f39aa55.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.002-authority-ownership-map`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.002-authority-ownership-map.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authority_ownership_map_d1d197f8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/authority_ownership_map_d1d197f8.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/authority_ownership_map_d1d197f8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_authority_ownership_map_d1d197f8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.003-cross-phase-contract-inventory`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.003-cross-phase-contract-inventory.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cross_phase_contract_inventory_a540da59/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/cross_phase_contract_inventory_a540da59.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/cross_phase_contract_inventory_a540da59.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_cross_phase_contract_inventory_a540da59.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.004-canonical-c-control-plane-architecture`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.004-canonical-c-control-plane-architecture.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/canonical_c_control_plane_architecture_4f89a106/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/canonical_c_control_plane_architecture_4f89a106.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/canonical_c_control_plane_architecture_4f89a106.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_canonical_c_control_plane_architecture_4f89a106.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.005-control-plane-strong-types`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.005-control-plane-strong-types.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_strong_types_a0b00474/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_strong_types_a0b00474.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_strong_types_a0b00474.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_strong_types_a0b00474.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.006-entity-and-capability-references`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.006-entity-and-capability-references.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/entity_and_capability_references_a1d1d84c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/entity_and_capability_references_a1d1d84c.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/entity_and_capability_references_a1d1d84c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_entity_and_capability_references_a1d1d84c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.007-typed-intent-envelope`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.007-typed-intent-envelope.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/typed_intent_envelope_130f20ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/typed_intent_envelope_130f20ed.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/typed_intent_envelope_130f20ed.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_typed_intent_envelope_130f20ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.008-intent-provenance`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.008-intent-provenance.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/intent_provenance_1822f2cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/intent_provenance_1822f2cb.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/intent_provenance_1822f2cb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_intent_provenance_1822f2cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.009-intent-lifecycle`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.009-intent-lifecycle.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/intent_lifecycle_4b948082/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/lifecycle/intent_lifecycle_4b948082.hpp`, `src/runtime/unified-control-plane/subtask_targets/lifecycle/intent_lifecycle_4b948082.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/lifecycle/test_intent_lifecycle_4b948082.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.010-capability-registry`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.010-capability-registry.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/capability_registry_f8c6474d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/capability_registry_f8c6474d.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/capability_registry_f8c6474d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_capability_registry_f8c6474d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.011-capability-discovery`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.011-capability-discovery.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/capability_discovery_b2e083c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/capability_discovery_b2e083c4.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/capability_discovery_b2e083c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_capability_discovery_b2e083c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.012-capability-metadata`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.012-capability-metadata.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/capability_metadata_cbfbe0e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/capability_metadata_cbfbe0e0.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/capability_metadata_cbfbe0e0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_capability_metadata_cbfbe0e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.013-capability-applicability`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.013-capability-applicability.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/capability_applicability_90a5795a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/capability_applicability_90a5795a.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/capability_applicability_90a5795a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_capability_applicability_90a5795a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.014-capability-versioning`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.014-capability-versioning.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/capability_versioning_7b9e1a91/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/capability_versioning_7b9e1a91.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/capability_versioning_7b9e1a91.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_capability_versioning_7b9e1a91.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.015-domain-owner-routing`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.015-domain-owner-routing.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/domain_owner_routing_ac9d76cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/domain_owner_routing_ac9d76cb.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/domain_owner_routing_ac9d76cb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_domain_owner_routing_ac9d76cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.016-provider-routing`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.016-provider-routing.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_routing_b9ad0fae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_routing_b9ad0fae.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_routing_b9ad0fae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_routing_b9ad0fae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.017-provider-capability-negotiation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.017-provider-capability-negotiation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_capability_negotiation_73984eb5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_capability_negotiation_73984eb5.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_capability_negotiation_73984eb5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_capability_negotiation_73984eb5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.018-provider-health`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.018-provider-health.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_health_68eb4185/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_health_68eb4185.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_health_68eb4185.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_health_68eb4185.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.019-provider-fallback-semantics`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.019-provider-fallback-semantics.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_fallback_semantics_8365dbe4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_fallback_semantics_8365dbe4.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_fallback_semantics_8365dbe4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_fallback_semantics_8365dbe4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.020-observation-request-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.020-observation-request-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/observation_request_model_97715c20/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/observation_request_model_97715c20.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/observation_request_model_97715c20.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_observation_request_model_97715c20.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.021-observation-result-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.021-observation-result-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/observation_result_model_9b8f762a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/observation_result_model_9b8f762a.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/observation_result_model_9b8f762a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_observation_result_model_9b8f762a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.022-observation-freshness`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.022-observation-freshness.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/observation_freshness_495c5091/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/observation_freshness_495c5091.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/observation_freshness_495c5091.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_observation_freshness_495c5091.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.023-observation-provenance`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.023-observation-provenance.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/observation_provenance_42013b4c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/observation_provenance_42013b4c.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/observation_provenance_42013b4c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_observation_provenance_42013b4c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.024-authoritative-re-observation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.024-authoritative-re-observation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authoritative_re_observation_0158b267/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/authoritative_re_observation_0158b267.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/authoritative_re_observation_0158b267.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_authoritative_re_observation_0158b267.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.025-plan-request-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.025-plan-request-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_request_model_3e1f0542/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_request_model_3e1f0542.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_request_model_3e1f0542.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_request_model_3e1f0542.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.026-typed-plan-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.026-typed-plan-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/typed_plan_model_95608a79/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/typed_plan_model_95608a79.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/typed_plan_model_95608a79.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_typed_plan_model_95608a79.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.027-plan-step-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.027-plan-step-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_step_model_4de0a9ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_step_model_4de0a9ee.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_step_model_4de0a9ee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_step_model_4de0a9ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.028-plan-dependency-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.028-plan-dependency-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_dependency_model_9805b3c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_dependency_model_9805b3c2.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_dependency_model_9805b3c2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_dependency_model_9805b3c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.029-plan-preconditions`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.029-plan-preconditions.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_preconditions_7aacc721/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_preconditions_7aacc721.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_preconditions_7aacc721.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_preconditions_7aacc721.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.030-plan-postconditions`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.030-plan-postconditions.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_postconditions_2ff843a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/plan_postconditions_2ff843a1.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/plan_postconditions_2ff843a1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_plan_postconditions_2ff843a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.031-plan-invariants`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.031-plan-invariants.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_invariants_81ad4f48/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_invariants_81ad4f48.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_invariants_81ad4f48.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_invariants_81ad4f48.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.032-plan-risk-metadata`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.032-plan-risk-metadata.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_risk_metadata_c9bb99c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_risk_metadata_c9bb99c4.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_risk_metadata_c9bb99c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_risk_metadata_c9bb99c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.033-plan-reversibility-metadata`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.033-plan-reversibility-metadata.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_reversibility_metadata_c4a8f920/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_reversibility_metadata_c4a8f920.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_reversibility_metadata_c4a8f920.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_reversibility_metadata_c4a8f920.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.034-plan-preview`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.034-plan-preview.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_preview_9561039d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_preview_9561039d.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_preview_9561039d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_preview_9561039d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.035-plan-explanation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.035-plan-explanation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_explanation_66fb4a22/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_explanation_66fb4a22.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_explanation_66fb4a22.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_explanation_66fb4a22.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.036-plan-normalization`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.036-plan-normalization.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_normalization_7aa9f852/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_normalization_7aa9f852.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_normalization_7aa9f852.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_normalization_7aa9f852.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.037-plan-validation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.037-plan-validation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_validation_045f02d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/plan_validation_045f02d7.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/plan_validation_045f02d7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_plan_validation_045f02d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.038-cross-domain-plan-composition`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.038-cross-domain-plan-composition.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cross_domain_plan_composition_026b738f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/cross_domain_plan_composition_026b738f.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/cross_domain_plan_composition_026b738f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_cross_domain_plan_composition_026b738f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.039-cross-domain-dependency-ordering`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.039-cross-domain-dependency-ordering.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cross_domain_dependency_ordering_c8dc3fd6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/cross_domain_dependency_ordering_c8dc3fd6.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/cross_domain_dependency_ordering_c8dc3fd6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_cross_domain_dependency_ordering_c8dc3fd6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.040-cross-domain-partial-failure-semantics`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.040-cross-domain-partial-failure-semantics.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cross_domain_partial_failure_semantics_4c3c59f3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/cross_domain_partial_failure_semantics_4c3c59f3.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/cross_domain_partial_failure_semantics_4c3c59f3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_cross_domain_partial_failure_semantics_4c3c59f3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.041-authorization-request-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.041-authorization-request-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_request_model_0165608f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/authorization_request_model_0165608f.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/authorization_request_model_0165608f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_authorization_request_model_0165608f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.042-authorization-decision-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.042-authorization-decision-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_decision_model_fd0bcb46/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/authorization_decision_model_fd0bcb46.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/authorization_decision_model_fd0bcb46.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_authorization_decision_model_fd0bcb46.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.043-authorization-provenance`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.043-authorization-provenance.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_provenance_846a95c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/authorization_provenance_846a95c4.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/authorization_provenance_846a95c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_authorization_provenance_846a95c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.044-authorization-expiry`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.044-authorization-expiry.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_expiry_1ed225e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/authorization_expiry_1ed225e8.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/authorization_expiry_1ed225e8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_authorization_expiry_1ed225e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.045-authorization-scope`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.045-authorization-scope.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_scope_55077718/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/authorization_scope_55077718.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/authorization_scope_55077718.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_authorization_scope_55077718.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.046-authorization-revalidation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.046-authorization-revalidation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_revalidation_a3e59f58/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/authorization_revalidation_a3e59f58.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/authorization_revalidation_a3e59f58.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_authorization_revalidation_a3e59f58.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.047-least-privilege-execution`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.047-least-privilege-execution.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/least_privilege_execution_58d7ac7d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/least_privilege_execution_58d7ac7d.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/least_privilege_execution_58d7ac7d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_least_privilege_execution_58d7ac7d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.048-privilege-helper-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.048-privilege-helper-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/privilege_helper_integration_ce4b9d1b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/privilege_helper_integration_ce4b9d1b.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/privilege_helper_integration_ce4b9d1b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_privilege_helper_integration_ce4b9d1b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.049-typed-privileged-ipc`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.049-typed-privileged-ipc.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/typed_privileged_ipc_0e81e7ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/typed_privileged_ipc_0e81e7ea.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/typed_privileged_ipc_0e81e7ea.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_typed_privileged_ipc_0e81e7ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.050-execution-request-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.050-execution-request-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_request_model_064d88f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/execution_request_model_064d88f4.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/execution_request_model_064d88f4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_execution_request_model_064d88f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.051-execution-attempt-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.051-execution-attempt-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_attempt_model_fce369a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/execution_attempt_model_fce369a1.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/execution_attempt_model_fce369a1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_execution_attempt_model_fce369a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.052-execution-result-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.052-execution-result-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_result_model_6e6374c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/execution_result_model_6e6374c8.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/execution_result_model_6e6374c8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_execution_result_model_6e6374c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.053-execution-cancellation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.053-execution-cancellation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_cancellation_37b277f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/execution_cancellation_37b277f9.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/execution_cancellation_37b277f9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_execution_cancellation_37b277f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.054-execution-timeout`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.054-execution-timeout.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_timeout_f981c543/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/execution_timeout_f981c543.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/execution_timeout_f981c543.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_execution_timeout_f981c543.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.055-execution-idempotency`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.055-execution-idempotency.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_idempotency_c80ed521/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/execution_idempotency_c80ed521.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/execution_idempotency_c80ed521.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_execution_idempotency_c80ed521.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.056-execution-deduplication`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.056-execution-deduplication.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_deduplication_1e97ccc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/execution_deduplication_1e97ccc3.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/execution_deduplication_1e97ccc3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_execution_deduplication_1e97ccc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.057-verification-request-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.057-verification-request-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/verification_request_model_c29a66ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/verification_request_model_c29a66ee.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/verification_request_model_c29a66ee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_verification_request_model_c29a66ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.058-verification-result-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.058-verification-result-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/verification_result_model_1fc67a4a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/verification_result_model_1fc67a4a.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/verification_result_model_1fc67a4a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_verification_result_model_1fc67a4a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.059-verification-freshness`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.059-verification-freshness.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/verification_freshness_481fa4b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/verification_freshness_481fa4b2.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/verification_freshness_481fa4b2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_verification_freshness_481fa4b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.060-verification-failure`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.060-verification-failure.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/verification_failure_01064c60/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/verification_failure_01064c60.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/verification_failure_01064c60.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_verification_failure_01064c60.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.061-unknown-verification-handling`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.061-unknown-verification-handling.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unknown_verification_handling_d76a6e6e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/unknown_verification_handling_d76a6e6e.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/unknown_verification_handling_d76a6e6e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_unknown_verification_handling_d76a6e6e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.062-postcondition-verification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.062-postcondition-verification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/postcondition_verification_b813a370/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/postcondition_verification_b813a370.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/postcondition_verification_b813a370.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_postcondition_verification_b813a370.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.063-rollback-eligibility`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.063-rollback-eligibility.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/rollback_eligibility_bf42ca1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/rollback_eligibility_bf42ca1f.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/rollback_eligibility_bf42ca1f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_rollback_eligibility_bf42ca1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.064-rollback-plan`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.064-rollback-plan.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/rollback_plan_50c1299f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/rollback_plan_50c1299f.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/rollback_plan_50c1299f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_rollback_plan_50c1299f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.065-rollback-execution`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.065-rollback-execution.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/rollback_execution_208758fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/rollback_execution_208758fe.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/rollback_execution_208758fe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_rollback_execution_208758fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.066-rollback-verification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.066-rollback-verification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/rollback_verification_1c08b97d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/rollback_verification_1c08b97d.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/rollback_verification_1c08b97d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_rollback_verification_1c08b97d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.067-compensation-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.067-compensation-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/compensation_model_8b01dd32/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/compensation_model_8b01dd32.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/compensation_model_8b01dd32.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_compensation_model_8b01dd32.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.068-compensation-ordering`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.068-compensation-ordering.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/compensation_ordering_cb4ee4a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/compensation_ordering_cb4ee4a1.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/compensation_ordering_cb4ee4a1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_compensation_ordering_cb4ee4a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.069-compensation-failure`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.069-compensation-failure.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/compensation_failure_46d43e0b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/compensation_failure_46d43e0b.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/compensation_failure_46d43e0b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_compensation_failure_46d43e0b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.070-partial-success-representation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.070-partial-success-representation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/partial_success_representation_f565dfb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/partial_success_representation_f565dfb9.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/partial_success_representation_f565dfb9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_partial_success_representation_f565dfb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.071-ambiguous-outcome-representation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.071-ambiguous-outcome-representation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/ambiguous_outcome_representation_b845db90/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/ambiguous_outcome_representation_b845db90.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/ambiguous_outcome_representation_b845db90.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_ambiguous_outcome_representation_b845db90.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.072-crash-reconciliation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.072-crash-reconciliation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/crash_reconciliation_1efc5b99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/crash_reconciliation_1efc5b99.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/crash_reconciliation_1efc5b99.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_crash_reconciliation_1efc5b99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.073-daemon-restart-reconciliation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.073-daemon-restart-reconciliation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/daemon_restart_reconciliation_f0e46080/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/daemon_restart_reconciliation_f0e46080.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/daemon_restart_reconciliation_f0e46080.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_daemon_restart_reconciliation_f0e46080.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.074-reboot-continuity`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.074-reboot-continuity.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/reboot_continuity_76a50444/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/reboot_continuity_76a50444.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/reboot_continuity_76a50444.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_reboot_continuity_76a50444.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.075-interrupted-operation-recovery`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.075-interrupted-operation-recovery.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/interrupted_operation_recovery_f83f7b60/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/interrupted_operation_recovery_f83f7b60.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/interrupted_operation_recovery_f83f7b60.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_interrupted_operation_recovery_f83f7b60.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.076-durable-operation-journal`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.076-durable-operation-journal.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/durable_operation_journal_3ad2431e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/durable_operation_journal_3ad2431e.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/durable_operation_journal_3ad2431e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_durable_operation_journal_3ad2431e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.077-operation-checkpointing`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.077-operation-checkpointing.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/operation_checkpointing_2583b983/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/operation_checkpointing_2583b983.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/operation_checkpointing_2583b983.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_operation_checkpointing_2583b983.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.078-control-plane-state-machine`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.078-control-plane-state-machine.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_state_machine_c589e915/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_state_machine_c589e915.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_state_machine_c589e915.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_state_machine_c589e915.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.079-control-plane-event-bus`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.079-control-plane-event-bus.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_event_bus_bb3b85de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_event_bus_bb3b85de.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_event_bus_bb3b85de.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_event_bus_bb3b85de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.080-bounded-concurrency`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.080-bounded-concurrency.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/bounded_concurrency_9abdf45c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/bounded_concurrency_9abdf45c.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/bounded_concurrency_9abdf45c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_bounded_concurrency_9abdf45c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.081-backpressure`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.081-backpressure.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/backpressure_d0ef322d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/backpressure_d0ef322d.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/backpressure_d0ef322d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_backpressure_d0ef322d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.082-priority-and-fairness`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.082-priority-and-fairness.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/priority_and_fairness_d1872d08/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/priority_and_fairness_d1872d08.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/priority_and_fairness_d1872d08.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_priority_and_fairness_d1872d08.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.083-cancellation-propagation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.083-cancellation-propagation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cancellation_propagation_04f7cc50/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/cancellation_propagation_04f7cc50.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/cancellation_propagation_04f7cc50.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_cancellation_propagation_04f7cc50.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.084-deadline-propagation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.084-deadline-propagation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/deadline_propagation_363cc522/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/deadline_propagation_363cc522.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/deadline_propagation_363cc522.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_deadline_propagation_363cc522.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.085-phase-29-workload-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.085-phase-29-workload-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/workload_integration_d24d412c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/workload_integration_d24d412c.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/workload_integration_d24d412c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_workload_integration_d24d412c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.086-phase-30-resource-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.086-phase-30-resource-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/resource_integration_13716984/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/resource_integration_13716984.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/resource_integration_13716984.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_resource_integration_13716984.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.087-resource-admission-control`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.087-resource-admission-control.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/resource_admission_control_b40a8976/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/resource_admission_control_b40a8976.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/resource_admission_control_b40a8976.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_resource_admission_control_b40a8976.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.088-resource-reservation-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.088-resource-reservation-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/resource_reservation_integration_ae74c24f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/resource_reservation_integration_ae74c24f.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/resource_reservation_integration_ae74c24f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_resource_reservation_integration_ae74c24f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.089-protected-resource-registry`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.089-protected-resource-registry.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/protected_resource_registry_0fe82d4f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/protected_resource_registry_0fe82d4f.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/protected_resource_registry_0fe82d4f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_protected_resource_registry_0fe82d4f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.090-protected-maintenance-path`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.090-protected-maintenance-path.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/protected_maintenance_path_83fc5f0b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/protected_maintenance_path_83fc5f0b.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/protected_maintenance_path_83fc5f0b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_protected_maintenance_path_83fc5f0b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.091-boot-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.091-boot-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/boot_protection_a9cd65e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/boot_protection_a9cd65e4.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/boot_protection_a9cd65e4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_boot_protection_a9cd65e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.092-storage-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.092-storage-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/storage_protection_9ac12d73/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/storage_protection_9ac12d73.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/storage_protection_9ac12d73.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_storage_protection_9ac12d73.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.093-network-access-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.093-network-access-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/network_access_protection_2f5ed670/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/network_access_protection_2f5ed670.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/network_access_protection_2f5ed670.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_network_access_protection_2f5ed670.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.094-ssh-maintenance-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.094-ssh-maintenance-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/ssh_maintenance_protection_3a1d9fd5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/ssh_maintenance_protection_3a1d9fd5.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/ssh_maintenance_protection_3a1d9fd5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_ssh_maintenance_protection_3a1d9fd5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.095-graphical-session-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.095-graphical-session-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/graphical_session_protection_6e8e385c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/graphical_session_protection_6e8e385c.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/graphical_session_protection_6e8e385c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_graphical_session_protection_6e8e385c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.096-security-control-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.096-security-control-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/security_control_protection_9a1caeac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/security_control_protection_9a1caeac.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/security_control_protection_9a1caeac.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_security_control_protection_9a1caeac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.097-package-trust-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.097-package-trust-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/package_trust_protection_4b88f8c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/package_trust_protection_4b88f8c8.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/package_trust_protection_4b88f8c8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_package_trust_protection_4b88f8c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.098-rebuntu-self-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.098-rebuntu-self-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/rebuntu_self_protection_ffc58c10/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/rebuntu_self_protection_ffc58c10.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/rebuntu_self_protection_ffc58c10.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_rebuntu_self_protection_ffc58c10.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.099-phase-31-service-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.099-phase-31-service-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/service_integration_5f777bbc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/service_integration_5f777bbc.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/service_integration_5f777bbc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_service_integration_5f777bbc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.100-phase-32-storage-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.100-phase-32-storage-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/storage_integration_3a311442/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/storage_integration_3a311442.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/storage_integration_3a311442.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_storage_integration_3a311442.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.101-phase-33-network-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.101-phase-33-network-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/network_integration_2029dbbd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/network_integration_2029dbbd.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/network_integration_2029dbbd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_network_integration_2029dbbd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.102-phase-34-gpu-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.102-phase-34-gpu-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/gpu_integration_f07914b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/gpu_integration_f07914b1.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/gpu_integration_f07914b1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_gpu_integration_f07914b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.103-phase-35-package-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.103-phase-35-package-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/package_integration_16d0a7c7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/package_integration_16d0a7c7.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/package_integration_16d0a7c7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_package_integration_16d0a7c7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.104-phase-36-configuration-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.104-phase-36-configuration-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/configuration_integration_1a40ce65/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/configuration_integration_1a40ce65.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/configuration_integration_1a40ce65.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_configuration_integration_1a40ce65.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.105-phase-37-secrets-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.105-phase-37-secrets-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/secrets_integration_ce0d33c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/secrets_integration_ce0d33c1.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/secrets_integration_ce0d33c1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_secrets_integration_ce0d33c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.106-phase-38-identity-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.106-phase-38-identity-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/identity_integration_411d0c1d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/identity_integration_411d0c1d.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/identity_integration_411d0c1d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_identity_integration_411d0c1d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.107-phase-39-event-recording`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.107-phase-39-event-recording.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/event_recording_e7b97183/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/event_recording_e7b97183.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/event_recording_e7b97183.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_event_recording_e7b97183.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.108-phase-40-search-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.108-phase-40-search-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/search_integration_350076cd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/search_integration_350076cd.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/search_integration_350076cd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_search_integration_350076cd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.109-phase-40-command-reconciliation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.109-phase-40-command-reconciliation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/command_reconciliation_dc1544de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/command_reconciliation_dc1544de.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/command_reconciliation_dc1544de.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_command_reconciliation_dc1544de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.110-phase-41-workflow-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.110-phase-41-workflow-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/workflow_integration_65ce0384/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/workflow_integration_65ce0384.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/workflow_integration_65ce0384.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_workflow_integration_65ce0384.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.111-phase-42-graph-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.111-phase-42-graph-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/graph_integration_383af44f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/graph_integration_383af44f.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/graph_integration_383af44f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_graph_integration_383af44f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.112-phase-43-intelligence-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.112-phase-43-intelligence-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/intelligence_integration_55dcecf1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/intelligence_integration_55dcecf1.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/intelligence_integration_55dcecf1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_intelligence_integration_55dcecf1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.113-phase-44-adaptation-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.113-phase-44-adaptation-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adaptation_integration_0a073c1e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/adaptation_integration_0a073c1e.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/adaptation_integration_0a073c1e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_adaptation_integration_0a073c1e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.114-earlier-phase-capability-reconciliation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.114-earlier-phase-capability-reconciliation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/earlier_phase_capability_reconciliation_597b18f8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/earlier_phase_capability_reconciliation_597b18f8.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/earlier_phase_capability_reconciliation_597b18f8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_earlier_phase_capability_reconciliation_597b18f8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.115-unified-capability-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.115-unified-capability-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_capability_api_20f55103/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/unified_capability_api_20f55103.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/unified_capability_api_20f55103.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_unified_capability_api_20f55103.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.116-unified-observation-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.116-unified-observation-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_observation_api_7a724bb3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/unified_observation_api_7a724bb3.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/unified_observation_api_7a724bb3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_unified_observation_api_7a724bb3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.117-unified-planning-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.117-unified-planning-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_planning_api_8b22b682/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/unified_planning_api_8b22b682.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/unified_planning_api_8b22b682.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_unified_planning_api_8b22b682.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.118-unified-validation-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.118-unified-validation-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_validation_api_23ac4c61/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/unified_validation_api_23ac4c61.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/unified_validation_api_23ac4c61.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_unified_validation_api_23ac4c61.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.119-unified-authorization-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.119-unified-authorization-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_authorization_api_fdb49ba3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/unified_authorization_api_fdb49ba3.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/unified_authorization_api_fdb49ba3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_unified_authorization_api_fdb49ba3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.120-unified-execution-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.120-unified-execution-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_execution_api_169af883/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/unified_execution_api_169af883.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/unified_execution_api_169af883.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_unified_execution_api_169af883.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.121-unified-verification-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.121-unified-verification-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_verification_api_34491cca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/unified_verification_api_34491cca.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/unified_verification_api_34491cca.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_unified_verification_api_34491cca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.122-unified-audit-api`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.122-unified-audit-api.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_audit_api_8342b597/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/unified_audit_api_8342b597.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/unified_audit_api_8342b597.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_unified_audit_api_8342b597.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.123-read-only-capability-path`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.123-read-only-capability-path.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/read_only_capability_path_e4d28baa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/read_only_capability_path_e4d28baa.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/read_only_capability_path_e4d28baa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_read_only_capability_path_e4d28baa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.124-mutating-capability-path`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.124-mutating-capability-path.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/mutating_capability_path_1e5ab4fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/mutating_capability_path_1e5ab4fc.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/mutating_capability_path_1e5ab4fc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_mutating_capability_path_1e5ab4fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.125-dry-run-path`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.125-dry-run-path.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/dry_run_path_641698c7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/dry_run_path_641698c7.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/dry_run_path_641698c7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_dry_run_path_641698c7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.126-explain-plan-path`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.126-explain-plan-path.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/explain_plan_path_e2c32112/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/explain_plan_path_e2c32112.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/explain_plan_path_e2c32112.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_explain_plan_path_e2c32112.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.127-simulation-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.127-simulation-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/simulation_boundary_90ab5fd9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/simulation_boundary_90ab5fd9.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/simulation_boundary_90ab5fd9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_simulation_boundary_90ab5fd9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.128-cli-control-plane-client`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.128-cli-control-plane-client.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_control_plane_client_463c9c4e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/cli_control_plane_client_463c9c4e.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/cli_control_plane_client_463c9c4e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_cli_control_plane_client_463c9c4e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.129-cli-capability-discovery`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.129-cli-capability-discovery.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_capability_discovery_d27823b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/cli_capability_discovery_d27823b4.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/cli_capability_discovery_d27823b4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_cli_capability_discovery_d27823b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.130-cli-inspect`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.130-cli-inspect.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_inspect_a83d760f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/cli_inspect_a83d760f.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/cli_inspect_a83d760f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_cli_inspect_a83d760f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.131-cli-plan`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.131-cli-plan.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_plan_471efa50/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/cli_plan_471efa50.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/cli_plan_471efa50.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_cli_plan_471efa50.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.132-cli-validate`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.132-cli-validate.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_validate_342c9666/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/cli_validate_342c9666.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/cli_validate_342c9666.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_cli_validate_342c9666.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.133-cli-authorize-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.133-cli-authorize-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_authorize_boundary_2ffd3c0d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/cli_authorize_boundary_2ffd3c0d.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/cli_authorize_boundary_2ffd3c0d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_cli_authorize_boundary_2ffd3c0d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.134-cli-execute`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.134-cli-execute.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_execute_ca1ab053/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/cli_execute_ca1ab053.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/cli_execute_ca1ab053.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_cli_execute_ca1ab053.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.135-cli-verify`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.135-cli-verify.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_verify_92d1e33a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/cli_verify_92d1e33a.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/cli_verify_92d1e33a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_cli_verify_92d1e33a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.136-cli-rollback`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.136-cli-rollback.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_rollback_216826b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/cli_rollback_216826b2.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/cli_rollback_216826b2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_cli_rollback_216826b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.137-cli-operation-history`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.137-cli-operation-history.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cli_operation_history_6c495cae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/cli_operation_history_6c495cae.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/cli_operation_history_6c495cae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_cli_operation_history_6c495cae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.138-phase-25-panel-control-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.138-phase-25-panel-control-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_control_integration_62c8f9e6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/panel_control_integration_62c8f9e6.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/panel_control_integration_62c8f9e6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_panel_control_integration_62c8f9e6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.139-panel-capability-browser`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.139-panel-capability-browser.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_capability_browser_86ded88e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/panel_capability_browser_86ded88e.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/panel_capability_browser_86ded88e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_panel_capability_browser_86ded88e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.140-panel-observation-view`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.140-panel-observation-view.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_observation_view_2b265ea8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/panel_observation_view_2b265ea8.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/panel_observation_view_2b265ea8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_panel_observation_view_2b265ea8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.141-panel-plan-preview`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.141-panel-plan-preview.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_plan_preview_88f6d718/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/panel_plan_preview_88f6d718.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/panel_plan_preview_88f6d718.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_panel_plan_preview_88f6d718.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.142-panel-authorization-surface`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.142-panel-authorization-surface.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_authorization_surface_305f497e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/panel_authorization_surface_305f497e.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/panel_authorization_surface_305f497e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_panel_authorization_surface_305f497e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.143-panel-execution-progress`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.143-panel-execution-progress.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_execution_progress_47c98aa2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/panel_execution_progress_47c98aa2.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/panel_execution_progress_47c98aa2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_panel_execution_progress_47c98aa2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.144-panel-verification-view`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.144-panel-verification-view.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_verification_view_a43dfacf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/panel_verification_view_a43dfacf.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/panel_verification_view_a43dfacf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_panel_verification_view_a43dfacf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.145-panel-rollback-surface`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.145-panel-rollback-surface.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_rollback_surface_7972451e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/panel_rollback_surface_7972451e.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/panel_rollback_surface_7972451e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_panel_rollback_surface_7972451e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.146-panel-operation-history`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.146-panel-operation-history.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/panel_operation_history_609d55fa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/panel_operation_history_609d55fa.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/panel_operation_history_609d55fa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_panel_operation_history_609d55fa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.147-fish-shell-integration-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.147-fish-shell-integration-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/fish_shell_integration_boundary_284a4714/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/fish_shell_integration_boundary_284a4714.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/fish_shell_integration_boundary_284a4714.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_fish_shell_integration_boundary_284a4714.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.148-bash-console-compatibility`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.148-bash-console-compatibility.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/bash_console_compatibility_388f94ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/bash_console_compatibility_388f94ed.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/bash_console_compatibility_388f94ed.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_bash_console_compatibility_388f94ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.149-coding-agent-control-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.149-coding-agent-control-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/coding_agent_control_boundary_3dfb7286/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/coding_agent_control_boundary_3dfb7286.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/coding_agent_control_boundary_3dfb7286.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_coding_agent_control_boundary_3dfb7286.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.150-automation-agent-control-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.150-automation-agent-control-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/automation_agent_control_boundary_71111222/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/automation_agent_control_boundary_71111222.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/automation_agent_control_boundary_71111222.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_automation_agent_control_boundary_71111222.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.151-no-arbitrary-shell-command-authority`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.151-no-arbitrary-shell-command-authority.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/no_arbitrary_shell_command_authority_422227f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/no_arbitrary_shell_command_authority_422227f7.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/no_arbitrary_shell_command_authority_422227f7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_no_arbitrary_shell_command_authority_422227f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.152-process-execution-compatibility-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.152-process-execution-compatibility-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/process_execution_compatibility_boundary_9fc24ede/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/process_execution_compatibility_boundary_9fc24ede.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/process_execution_compatibility_boundary_9fc24ede.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_process_execution_compatibility_boundary_9fc24ede.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.153-executable-argv-representation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.153-executable-argv-representation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/executable_argv_representation_3f97a58a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/executable_argv_representation_3f97a58a.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/executable_argv_representation_3f97a58a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_executable_argv_representation_3f97a58a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.154-environment-policy`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.154-environment-policy.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/environment_policy_053389ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/environment_policy_053389ec.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/environment_policy_053389ec.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_environment_policy_053389ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.155-working-directory-policy`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.155-working-directory-policy.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/working_directory_policy_ed0f7b35/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/working_directory_policy_ed0f7b35.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/working_directory_policy_ed0f7b35.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_working_directory_policy_ed0f7b35.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.156-output-capture-bounds`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.156-output-capture-bounds.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/output_capture_bounds_98fbdb00/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/output_capture_bounds_98fbdb00.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/output_capture_bounds_98fbdb00.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_output_capture_bounds_98fbdb00.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.157-command-timeout-policy`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.157-command-timeout-policy.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/command_timeout_policy_7a7b7fe4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/command_timeout_policy_7a7b7fe4.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/command_timeout_policy_7a7b7fe4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_command_timeout_policy_7a7b7fe4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.158-command-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.158-command-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/command_audit_fc047f5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/command_audit_fc047f5d.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/command_audit_fc047f5d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_command_audit_fc047f5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.159-d-bus-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.159-d-bus-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/d_bus_integration_646bae19/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/d_bus_integration_646bae19.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/d_bus_integration_646bae19.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_d_bus_integration_646bae19.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.160-systemd-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.160-systemd-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/systemd_integration_10e65d84/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/systemd_integration_10e65d84.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/systemd_integration_10e65d84.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_systemd_integration_10e65d84.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.161-udev-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.161-udev-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/udev_integration_5a138a1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/udev_integration_5a138a1a.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/udev_integration_5a138a1a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_udev_integration_5a138a1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.162-netlink-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.162-netlink-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/netlink_integration_475d509d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/netlink_integration_475d509d.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/netlink_integration_475d509d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_netlink_integration_475d509d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.163-procfs-sysfs-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.163-procfs-sysfs-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/procfs_sysfs_integration_791d328e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/procfs_sysfs_integration_791d328e.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/procfs_sysfs_integration_791d328e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_procfs_sysfs_integration_791d328e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.164-filesystem-native-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.164-filesystem-native-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/filesystem_native_integration_00a38303/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/filesystem_native_integration_00a38303.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/filesystem_native_integration_00a38303.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_filesystem_native_integration_00a38303.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.165-nvml-accelerator-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.165-nvml-accelerator-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/nvml_accelerator_integration_ed1bc743/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/nvml_accelerator_integration_ed1bc743.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/nvml_accelerator_integration_ed1bc743.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_nvml_accelerator_integration_ed1bc743.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.166-apt-dpkg-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.166-apt-dpkg-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/apt_dpkg_integration_be9c28b3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/apt_dpkg_integration_be9c28b3.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/apt_dpkg_integration_be9c28b3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_apt_dpkg_integration_be9c28b3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.167-networkmanager-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.167-networkmanager-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/networkmanager_integration_c8b99235/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/networkmanager_integration_c8b99235.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/networkmanager_integration_c8b99235.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_networkmanager_integration_c8b99235.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.168-firewall-provider-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.168-firewall-provider-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/firewall_provider_integration_c487cc76/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/firewall_provider_integration_c487cc76.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/firewall_provider_integration_c487cc76.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_firewall_provider_integration_c487cc76.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.169-nss-pam-logind-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.169-nss-pam-logind-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/nss_pam_logind_integration_3da48f99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/nss_pam_logind_integration_3da48f99.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/nss_pam_logind_integration_3da48f99.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_nss_pam_logind_integration_3da48f99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.170-polkit-integration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.170-polkit-integration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/polkit_integration_73d1e576/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/polkit_integration_73d1e576.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/polkit_integration_73d1e576.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_polkit_integration_73d1e576.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.171-native-provider-abstraction`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.171-native-provider-abstraction.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/native_provider_abstraction_05d6b687/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/native_provider_abstraction_05d6b687.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/native_provider_abstraction_05d6b687.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_native_provider_abstraction_05d6b687.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.172-provider-lifecycle`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.172-provider-lifecycle.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_lifecycle_fcdb2e5a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_lifecycle_fcdb2e5a.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_lifecycle_fcdb2e5a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_lifecycle_fcdb2e5a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.173-provider-discovery`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.173-provider-discovery.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_discovery_ac28d3d3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_discovery_ac28d3d3.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_discovery_ac28d3d3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_discovery_ac28d3d3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.174-provider-registration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.174-provider-registration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_registration_e7d5d851/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_registration_e7d5d851.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_registration_e7d5d851.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_registration_e7d5d851.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.175-provider-isolation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.175-provider-isolation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_isolation_ee379059/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_isolation_ee379059.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_isolation_ee379059.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_isolation_ee379059.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.176-provider-error-normalization`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.176-provider-error-normalization.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_error_normalization_3625d165/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_error_normalization_3625d165.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_error_normalization_3625d165.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_error_normalization_3625d165.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.177-provider-unknown-semantics`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.177-provider-unknown-semantics.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_unknown_semantics_3d653710/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_unknown_semantics_3d653710.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_unknown_semantics_3d653710.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_unknown_semantics_3d653710.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.178-provider-observability`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.178-provider-observability.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_observability_334809aa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_observability_334809aa.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_observability_334809aa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_observability_334809aa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.179-ipc-schema-versioning`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.179-ipc-schema-versioning.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/ipc_schema_versioning_47b26b39/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/ipc_schema_versioning_47b26b39.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/ipc_schema_versioning_47b26b39.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_ipc_schema_versioning_47b26b39.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.180-serialization-contracts`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.180-serialization-contracts.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/serialization_contracts_e5df3f89/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/serialization_contracts_e5df3f89.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/serialization_contracts_e5df3f89.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_serialization_contracts_e5df3f89.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.181-backward-compatibility-policy`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.181-backward-compatibility-policy.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/backward_compatibility_policy_1d74c37e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/backward_compatibility_policy_1d74c37e.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/backward_compatibility_policy_1d74c37e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_backward_compatibility_policy_1d74c37e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.182-control-plane-protocol-versioning`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.182-control-plane-protocol-versioning.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_protocol_versioning_a7692ca8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_protocol_versioning_a7692ca8.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_protocol_versioning_a7692ca8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_protocol_versioning_a7692ca8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.183-client-compatibility-negotiation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.183-client-compatibility-negotiation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/client_compatibility_negotiation_cd56262a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/client_compatibility_negotiation_cd56262a.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/client_compatibility_negotiation_cd56262a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_client_compatibility_negotiation_cd56262a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.184-feature-capability-negotiation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.184-feature-capability-negotiation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/feature_capability_negotiation_c77a9ced/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/feature_capability_negotiation_c77a9ced.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/feature_capability_negotiation_c77a9ced.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_feature_capability_negotiation_c77a9ced.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.185-schema-migration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.185-schema-migration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/schema_migration_50ec1df1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/schema_migration_50ec1df1.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/schema_migration_50ec1df1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_schema_migration_50ec1df1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.186-configuration-model`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.186-configuration-model.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/configuration_model_201b273c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/configuration_model_201b273c.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/configuration_model_201b273c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_configuration_model_201b273c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.187-runtime-feature-discovery`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.187-runtime-feature-discovery.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/runtime_feature_discovery_056996dd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/runtime_feature_discovery_056996dd.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/runtime_feature_discovery_056996dd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_runtime_feature_discovery_056996dd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.188-safe-mode`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.188-safe-mode.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/safe_mode_88c3a8d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/safe_mode_88c3a8d6.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/safe_mode_88c3a8d6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_safe_mode_88c3a8d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.189-emergency-quiescence`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.189-emergency-quiescence.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/emergency_quiescence_a5ef6186/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/emergency_quiescence_a5ef6186.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/emergency_quiescence_a5ef6186.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_emergency_quiescence_a5ef6186.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.190-read-only-emergency-mode`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.190-read-only-emergency-mode.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/read_only_emergency_mode_90ed45de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/read_only_emergency_mode_90ed45de.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/read_only_emergency_mode_90ed45de.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_read_only_emergency_mode_90ed45de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.191-control-plane-freeze`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.191-control-plane-freeze.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_freeze_4581ffe6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_freeze_4581ffe6.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_freeze_4581ffe6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_freeze_4581ffe6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.192-control-plane-resume`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.192-control-plane-resume.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_resume_8c4426ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/control_plane_resume_8c4426ba.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/control_plane_resume_8c4426ba.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_control_plane_resume_8c4426ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.193-recovery-console-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.193-recovery-console-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/recovery_console_boundary_a9bb1b6f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/recovery_console_boundary_a9bb1b6f.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/recovery_console_boundary_a9bb1b6f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_recovery_console_boundary_a9bb1b6f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.194-offline-inspection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.194-offline-inspection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/offline_inspection_6f5d62c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/offline_inspection_6f5d62c5.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/offline_inspection_6f5d62c5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_offline_inspection_6f5d62c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.195-degraded-provider-operation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.195-degraded-provider-operation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/degraded_provider_operation_c4930a9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/degraded_provider_operation_c4930a9d.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/degraded_provider_operation_c4930a9d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_degraded_provider_operation_c4930a9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.196-partial-subsystem-availability`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.196-partial-subsystem-availability.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/partial_subsystem_availability_e2cc13b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/partial_subsystem_availability_e2cc13b4.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/partial_subsystem_availability_e2cc13b4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_partial_subsystem_availability_e2cc13b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.197-semantic-provider-isolation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.197-semantic-provider-isolation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/semantic_provider_isolation_4f73ed9c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/semantic_provider_isolation_4f73ed9c.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/semantic_provider_isolation_4f73ed9c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_semantic_provider_isolation_4f73ed9c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.198-semantic-no-authority-enforcement`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.198-semantic-no-authority-enforcement.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/semantic_no_authority_enforcement_2f867784/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/semantic_no_authority_enforcement_2f867784.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/semantic_no_authority_enforcement_2f867784.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_semantic_no_authority_enforcement_2f867784.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.199-semantic-candidate-plan-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.199-semantic-candidate-plan-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/semantic_candidate_plan_boundary_a3cd0466/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/semantic_candidate_plan_boundary_a3cd0466.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/semantic_candidate_plan_boundary_a3cd0466.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_semantic_candidate_plan_boundary_a3cd0466.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.200-semantic-explanation-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.200-semantic-explanation-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/semantic_explanation_boundary_6b4a75cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/semantic_explanation_boundary_6b4a75cb.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/semantic_explanation_boundary_6b4a75cb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_semantic_explanation_boundary_6b4a75cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.201-prompt-injection-resistance`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.201-prompt-injection-resistance.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/prompt_injection_resistance_cb357d5e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/prompt_injection_resistance_cb357d5e.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/prompt_injection_resistance_cb357d5e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_prompt_injection_resistance_cb357d5e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.202-untrusted-output-handling`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.202-untrusted-output-handling.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/untrusted_output_handling_88419984/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/untrusted_output_handling_88419984.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/untrusted_output_handling_88419984.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_untrusted_output_handling_88419984.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.203-secret-exfiltration-resistance`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.203-secret-exfiltration-resistance.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/secret_exfiltration_resistance_43ce1932/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/secret_exfiltration_resistance_43ce1932.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/secret_exfiltration_resistance_43ce1932.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_secret_exfiltration_resistance_43ce1932.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.204-authorization-bypass-resistance`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.204-authorization-bypass-resistance.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_bypass_resistance_0da78316/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/authorization_bypass_resistance_0da78316.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/authorization_bypass_resistance_0da78316.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_authorization_bypass_resistance_0da78316.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.205-toctou-protection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.205-toctou-protection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/toctou_protection_85d473a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/toctou_protection_85d473a9.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/toctou_protection_85d473a9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_toctou_protection_85d473a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.206-race-condition-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.206-race-condition-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/race_condition_audit_e33fc76d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/race_condition_audit_e33fc76d.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/race_condition_audit_e33fc76d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_race_condition_audit_e33fc76d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.207-concurrent-mutation-locking`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.207-concurrent-mutation-locking.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/concurrent_mutation_locking_a834bca0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/concurrent_mutation_locking_a834bca0.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/concurrent_mutation_locking_a834bca0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_concurrent_mutation_locking_a834bca0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.208-external-change-detection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.208-external-change-detection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/external_change_detection_6c8e9169/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/external_change_detection_6c8e9169.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/external_change_detection_6c8e9169.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_external_change_detection_6c8e9169.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.209-drift-during-operation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.209-drift-during-operation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/drift_during_operation_da1b2324/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/drift_during_operation_da1b2324.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/drift_during_operation_da1b2324.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_drift_during_operation_da1b2324.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.210-reconciliation-after-drift`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.210-reconciliation-after-drift.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/reconciliation_after_drift_123d65c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/reconciliation_after_drift_123d65c5.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/reconciliation_after_drift_123d65c5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_reconciliation_after_drift_123d65c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.211-operation-conflict-detection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.211-operation-conflict-detection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/operation_conflict_detection_96d1d12e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/operation_conflict_detection_96d1d12e.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/operation_conflict_detection_96d1d12e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_operation_conflict_detection_96d1d12e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.212-conflict-resolution`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.212-conflict-resolution.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/conflict_resolution_2b492ea9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/conflict_resolution_2b492ea9.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/conflict_resolution_2b492ea9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_conflict_resolution_2b492ea9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.213-deadlock-prevention`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.213-deadlock-prevention.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/deadlock_prevention_918c8212/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/deadlock_prevention_918c8212.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/deadlock_prevention_918c8212.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_deadlock_prevention_918c8212.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.214-lock-ordering`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.214-lock-ordering.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/lock_ordering_551b8c1c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/lock_ordering_551b8c1c.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/lock_ordering_551b8c1c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_lock_ordering_551b8c1c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.215-distributed-lock-non-goal`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.215-distributed-lock-non-goal.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/distributed_lock_non_goal_3247589c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/distributed_lock_non_goal_3247589c.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/distributed_lock_non_goal_3247589c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_distributed_lock_non_goal_3247589c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.216-local-transaction-semantics`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.216-local-transaction-semantics.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/local_transaction_semantics_4ce8dd88/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/local_transaction_semantics_4ce8dd88.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/local_transaction_semantics_4ce8dd88.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_local_transaction_semantics_4ce8dd88.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.217-cross-domain-transaction-semantics`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.217-cross-domain-transaction-semantics.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cross_domain_transaction_semantics_9dcc9a98/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/cross_domain_transaction_semantics_9dcc9a98.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/cross_domain_transaction_semantics_9dcc9a98.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_cross_domain_transaction_semantics_9dcc9a98.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.218-no-false-acid-guarantees`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.218-no-false-acid-guarantees.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/no_false_acid_guarantees_af1e2f81/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/no_false_acid_guarantees_af1e2f81.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/no_false_acid_guarantees_af1e2f81.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_no_false_acid_guarantees_af1e2f81.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.219-audit-provenance-chain`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.219-audit-provenance-chain.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/audit_provenance_chain_877b845e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/audit_provenance_chain_877b845e.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/audit_provenance_chain_877b845e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_audit_provenance_chain_877b845e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.220-evidence-to-action-trace`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.220-evidence-to-action-trace.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/evidence_to_action_trace_cb3520d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/evidence_to_action_trace_cb3520d9.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/evidence_to_action_trace_cb3520d9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_evidence_to_action_trace_cb3520d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.221-phase-39-operation-timeline`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.221-phase-39-operation-timeline.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/operation_timeline_40b4110c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/operation_timeline_40b4110c.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/operation_timeline_40b4110c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_operation_timeline_40b4110c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.222-phase-42-operation-graph-links`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.222-phase-42-operation-graph-links.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/operation_graph_links_5a7b7428/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/operation_graph_links_5a7b7428.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/operation_graph_links_5a7b7428.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_operation_graph_links_5a7b7428.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.223-phase-43-explanation-links`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.223-phase-43-explanation-links.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/explanation_links_97f252e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/explanation_links_97f252e8.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/explanation_links_97f252e8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_explanation_links_97f252e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.224-phase-44-outcome-links`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.224-phase-44-outcome-links.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/outcome_links_016844db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/outcome_links_016844db.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/outcome_links_016844db.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_outcome_links_016844db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.225-structured-logging`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.225-structured-logging.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/structured_logging_706b4579/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/structured_logging_706b4579.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/structured_logging_706b4579.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_structured_logging_706b4579.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.226-secret-safe-logging`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.226-secret-safe-logging.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/secret_safe_logging_034de9e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/secret_safe_logging_034de9e8.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/secret_safe_logging_034de9e8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_secret_safe_logging_034de9e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.227-metrics`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.227-metrics.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/metrics_7f27d74b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/metrics_7f27d74b.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/metrics_7f27d74b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_metrics_7f27d74b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.228-tracing`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.228-tracing.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/tracing_d2d5d6e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/tracing_d2d5d6e0.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/tracing_d2d5d6e0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_tracing_d2d5d6e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.229-performance-telemetry`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.229-performance-telemetry.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/performance_telemetry_073b7b1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/performance_telemetry_073b7b1a.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/performance_telemetry_073b7b1a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_performance_telemetry_073b7b1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.230-control-plane-health`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.230-control-plane-health.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_health_4eb81b30/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_health_4eb81b30.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_health_4eb81b30.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_health_4eb81b30.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.231-self-diagnostics`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.231-self-diagnostics.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/self_diagnostics_26826444/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/self_diagnostics_26826444.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/self_diagnostics_26826444.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_self_diagnostics_26826444.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.232-watchdog-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.232-watchdog-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/watchdog_boundary_bf94ba31/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/watchdog_boundary_bf94ba31.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/watchdog_boundary_bf94ba31.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_watchdog_boundary_bf94ba31.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.233-startup-sequencing`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.233-startup-sequencing.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/startup_sequencing_834ff9fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/lifecycle/startup_sequencing_834ff9fc.hpp`, `src/runtime/unified-control-plane/subtask_targets/lifecycle/startup_sequencing_834ff9fc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/lifecycle/test_startup_sequencing_834ff9fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.234-shutdown-sequencing`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.234-shutdown-sequencing.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/shutdown_sequencing_8187168f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/shutdown_sequencing_8187168f.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/shutdown_sequencing_8187168f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_shutdown_sequencing_8187168f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.235-service-lifecycle`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.235-service-lifecycle.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/service_lifecycle_a16097bc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/lifecycle/service_lifecycle_a16097bc.hpp`, `src/runtime/unified-control-plane/subtask_targets/lifecycle/service_lifecycle_a16097bc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/lifecycle/test_service_lifecycle_a16097bc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.236-crash-handling`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.236-crash-handling.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/crash_handling_5a66a99d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/crash_handling_5a66a99d.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/crash_handling_5a66a99d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_crash_handling_5a66a99d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.237-core-dump-secret-safety`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.237-core-dump-secret-safety.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/core_dump_secret_safety_6059aacb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/core_dump_secret_safety_6059aacb.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/core_dump_secret_safety_6059aacb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_core_dump_secret_safety_6059aacb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.238-state-store-integrity`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.238-state-store-integrity.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/state_store_integrity_1c33ca5f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/lifecycle/state_store_integrity_1c33ca5f.hpp`, `src/runtime/unified-control-plane/subtask_targets/lifecycle/state_store_integrity_1c33ca5f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/lifecycle/test_state_store_integrity_1c33ca5f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.239-state-store-backup-boundary`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.239-state-store-backup-boundary.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/state_store_backup_boundary_351ca68e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/lifecycle/state_store_backup_boundary_351ca68e.hpp`, `src/runtime/unified-control-plane/subtask_targets/lifecycle/state_store_backup_boundary_351ca68e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/lifecycle/test_state_store_backup_boundary_351ca68e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.240-state-store-migration`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.240-state-store-migration.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/state_store_migration_44daed22/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/state_store_migration_44daed22.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/state_store_migration_44daed22.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_state_store_migration_44daed22.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.241-corruption-detection`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.241-corruption-detection.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/corruption_detection_af79f594/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/corruption_detection_af79f594.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/corruption_detection_af79f594.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_corruption_detection_af79f594.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.242-corruption-recovery`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.242-corruption-recovery.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/corruption_recovery_d103a035/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/corruption_recovery_d103a035.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/corruption_recovery_d103a035.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_corruption_recovery_d103a035.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.243-failure-injection-framework`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.243-failure-injection-framework.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/failure_injection_framework_33c558ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/failure_injection_framework_33c558ed.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/failure_injection_framework_33c558ed.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_failure_injection_framework_33c558ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.244-provider-failure-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.244-provider-failure-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_failure_tests_b9711174/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/provider_failure_tests_b9711174.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/provider_failure_tests_b9711174.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_provider_failure_tests_b9711174.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.245-authorization-denial-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.245-authorization-denial-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authorization_denial_tests_9e8ff012/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/authorization_denial_tests_9e8ff012.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/authorization_denial_tests_9e8ff012.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_authorization_denial_tests_9e8ff012.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.246-privilege-boundary-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.246-privilege-boundary-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/privilege_boundary_tests_3243928b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/privilege_boundary_tests_3243928b.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/privilege_boundary_tests_3243928b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_privilege_boundary_tests_3243928b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.247-plan-validation-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.247-plan-validation-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/plan_validation_tests_ff603413/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/plan_validation_tests_ff603413.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/plan_validation_tests_ff603413.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_plan_validation_tests_ff603413.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.248-execution-failure-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.248-execution-failure-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/execution_failure_tests_64a8c1a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/execution_failure_tests_64a8c1a2.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/execution_failure_tests_64a8c1a2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_execution_failure_tests_64a8c1a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.249-verification-failure-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.249-verification-failure-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/verification_failure_tests_3e3ec9f8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/verification_failure_tests_3e3ec9f8.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/verification_failure_tests_3e3ec9f8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_verification_failure_tests_3e3ec9f8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.250-rollback-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.250-rollback-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/rollback_tests_f774189f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/rollback_tests_f774189f.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/rollback_tests_f774189f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_rollback_tests_f774189f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.251-compensation-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.251-compensation-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/compensation_tests_11f8e999/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/compensation_tests_11f8e999.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/compensation_tests_11f8e999.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_compensation_tests_11f8e999.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.252-crash-restart-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.252-crash-restart-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/crash_restart_tests_5d6d6342/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/crash_restart_tests_5d6d6342.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/crash_restart_tests_5d6d6342.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_crash_restart_tests_5d6d6342.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.253-reboot-continuity-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.253-reboot-continuity-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/reboot_continuity_tests_d310ebea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/reboot_continuity_tests_d310ebea.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/reboot_continuity_tests_d310ebea.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_reboot_continuity_tests_d310ebea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.254-race-and-concurrency-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.254-race-and-concurrency-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/race_and_concurrency_tests_3868040d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/race_and_concurrency_tests_3868040d.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/race_and_concurrency_tests_3868040d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_race_and_concurrency_tests_3868040d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.255-toctou-adversarial-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.255-toctou-adversarial-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/toctou_adversarial_tests_befab08f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/toctou_adversarial_tests_befab08f.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/toctou_adversarial_tests_befab08f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_toctou_adversarial_tests_befab08f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.256-protected-resource-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.256-protected-resource-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/protected_resource_tests_12d2a5b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/protected_resource_tests_12d2a5b5.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/protected_resource_tests_12d2a5b5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_protected_resource_tests_12d2a5b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.257-secret-safety-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.257-secret-safety-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/secret_safety_tests_b6b4abf1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/secret_safety_tests_b6b4abf1.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/secret_safety_tests_b6b4abf1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_secret_safety_tests_b6b4abf1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.258-semantic-authority-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.258-semantic-authority-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/semantic_authority_tests_9a0c578e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/semantic_authority_tests_9a0c578e.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/semantic_authority_tests_9a0c578e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_semantic_authority_tests_9a0c578e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.259-shell-injection-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.259-shell-injection-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/shell_injection_tests_f6044312/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/shell_injection_tests_f6044312.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/shell_injection_tests_f6044312.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_shell_injection_tests_f6044312.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.260-ipc-fuzzing`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.260-ipc-fuzzing.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/ipc_fuzzing_a1716b64/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/ipc_fuzzing_a1716b64.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/ipc_fuzzing_a1716b64.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_ipc_fuzzing_a1716b64.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.261-schema-compatibility-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.261-schema-compatibility-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/schema_compatibility_tests_adf185a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/schema_compatibility_tests_adf185a8.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/schema_compatibility_tests_adf185a8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_schema_compatibility_tests_adf185a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.262-provider-contract-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.262-provider-contract-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_contract_tests_b134877b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/provider_contract_tests_b134877b.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/provider_contract_tests_b134877b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_provider_contract_tests_b134877b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.263-cross-domain-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.263-cross-domain-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/cross_domain_integration_tests_c5330e1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/cross_domain_integration_tests_c5330e1a.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/cross_domain_integration_tests_c5330e1a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_cross_domain_integration_tests_c5330e1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.264-phase-39-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.264-phase-39-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/integration_tests_77c803bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_77c803bb.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_77c803bb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_integration_tests_77c803bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.265-phase-40-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.265-phase-40-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/integration_tests_fc0635e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_fc0635e7.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_fc0635e7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_integration_tests_fc0635e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.266-phase-41-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.266-phase-41-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/integration_tests_6f48c098/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_6f48c098.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_6f48c098.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_integration_tests_6f48c098.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.267-phase-42-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.267-phase-42-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/integration_tests_ddfae3ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_ddfae3ae.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_ddfae3ae.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_integration_tests_ddfae3ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.268-phase-43-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.268-phase-43-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/integration_tests_6ee32ead/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_6ee32ead.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_6ee32ead.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_integration_tests_6ee32ead.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.269-phase-44-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.269-phase-44-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/integration_tests_92f66961/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_92f66961.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/integration_tests_92f66961.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_integration_tests_92f66961.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.270-end-to-end-read-only-scenario`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.270-end-to-end-read-only-scenario.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_read_only_scenario_66c2bb20/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_read_only_scenario_66c2bb20.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_read_only_scenario_66c2bb20.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_end_to_end_read_only_scenario_66c2bb20.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.271-end-to-end-single-domain-mutation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.271-end-to-end-single-domain-mutation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_single_domain_mutation_d1a49145/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/end_to_end_single_domain_mutation_d1a49145.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/end_to_end_single_domain_mutation_d1a49145.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_end_to_end_single_domain_mutation_d1a49145.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.272-end-to-end-cross-domain-mutation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.272-end-to-end-cross-domain-mutation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_cross_domain_mutation_495b9927/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/execution/end_to_end_cross_domain_mutation_495b9927.hpp`, `src/runtime/unified-control-plane/subtask_targets/execution/end_to_end_cross_domain_mutation_495b9927.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/execution/test_end_to_end_cross_domain_mutation_495b9927.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.273-end-to-end-rollback-scenario`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.273-end-to-end-rollback-scenario.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_rollback_scenario_d1f307fa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/end_to_end_rollback_scenario_d1f307fa.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/end_to_end_rollback_scenario_d1f307fa.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_end_to_end_rollback_scenario_d1f307fa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.274-end-to-end-partial-failure-scenario`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.274-end-to-end-partial-failure-scenario.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_partial_failure_scenario_373b9470/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_partial_failure_scenario_373b9470.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_partial_failure_scenario_373b9470.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_end_to_end_partial_failure_scenario_373b9470.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.275-end-to-end-recovery-scenario`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.275-end-to-end-recovery-scenario.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_recovery_scenario_bc20c5b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/end_to_end_recovery_scenario_bc20c5b4.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/end_to_end_recovery_scenario_bc20c5b4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_end_to_end_recovery_scenario_bc20c5b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.276-end-to-end-workflow-scenario`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.276-end-to-end-workflow-scenario.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_workflow_scenario_e636baf7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_workflow_scenario_e636baf7.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_workflow_scenario_e636baf7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_end_to_end_workflow_scenario_e636baf7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.277-end-to-end-intelligence-recommendation-scenario`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.277-end-to-end-intelligence-recommendation-scenario.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_intelligence_recommendation_scenario_91696d40/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_intelligence_recommendation_scenario_91696d40.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_intelligence_recommendation_scenario_91696d40.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_end_to_end_intelligence_recommendation_scenario_91696d40.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.278-end-to-end-adaptive-scenario`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.278-end-to-end-adaptive-scenario.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/end_to_end_adaptive_scenario_5e136519/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_adaptive_scenario_5e136519.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/end_to_end_adaptive_scenario_5e136519.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_end_to_end_adaptive_scenario_5e136519.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.279-performance-baseline`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.279-performance-baseline.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/performance_baseline_30b4e635/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/performance_baseline_30b4e635.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/performance_baseline_30b4e635.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_performance_baseline_30b4e635.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.280-latency-budget`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.280-latency-budget.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/latency_budget_0c4bc63d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/latency_budget_0c4bc63d.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/latency_budget_0c4bc63d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_latency_budget_0c4bc63d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.281-throughput-validation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.281-throughput-validation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/throughput_validation_e6676c8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/throughput_validation_e6676c8d.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/throughput_validation_e6676c8d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_throughput_validation_e6676c8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.282-memory-bounds`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.282-memory-bounds.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/memory_bounds_da378dd7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/memory_bounds_da378dd7.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/memory_bounds_da378dd7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_memory_bounds_da378dd7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.283-queue-bounds`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.283-queue-bounds.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/queue_bounds_4988a897/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/queue_bounds_4988a897.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/queue_bounds_4988a897.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_queue_bounds_4988a897.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.284-scalability-validation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.284-scalability-validation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/scalability_validation_ab895980/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/scalability_validation_ab895980.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/scalability_validation_ab895980.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_scalability_validation_ab895980.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.285-control-plane-overhead`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.285-control-plane-overhead.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/control_plane_overhead_64ae070e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_overhead_64ae070e.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/control_plane_overhead_64ae070e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_control_plane_overhead_64ae070e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.286-repository-source-tree-normalization`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.286-repository-source-tree-normalization.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/repository_source_tree_normalization_54e550f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/repository_source_tree_normalization_54e550f4.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/repository_source_tree_normalization_54e550f4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_repository_source_tree_normalization_54e550f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.287-c-prefix-migration-era-cleanup`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.287-c-prefix-migration-era-cleanup.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/c_prefix_migration_era_cleanup_70271b78/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/c_prefix_migration_era_cleanup_70271b78.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/c_prefix_migration_era_cleanup_70271b78.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_c_prefix_migration_era_cleanup_70271b78.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.288-legacy-python-runtime-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.288-legacy-python-runtime-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/legacy_python_runtime_audit_029a492c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/legacy_python_runtime_audit_029a492c.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/legacy_python_runtime_audit_029a492c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_legacy_python_runtime_audit_029a492c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.289-remaining-python-boundary-classification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.289-remaining-python-boundary-classification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/remaining_python_boundary_classification_c470cec2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/remaining_python_boundary_classification_c470cec2.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/remaining_python_boundary_classification_c470cec2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_remaining_python_boundary_classification_c470cec2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.290-duplicate-native-implementation-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.290-duplicate-native-implementation-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/duplicate_native_implementation_audit_2915ae42/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/duplicate_native_implementation_audit_2915ae42.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/duplicate_native_implementation_audit_2915ae42.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_duplicate_native_implementation_audit_2915ae42.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.291-duplicate-authority-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.291-duplicate-authority-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/duplicate_authority_audit_5aebe596/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/duplicate_authority_audit_5aebe596.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/duplicate_authority_audit_5aebe596.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_duplicate_authority_audit_5aebe596.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.292-direct-domain-bypass-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.292-direct-domain-bypass-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/direct_domain_bypass_audit_a67c414f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/direct_domain_bypass_audit_a67c414f.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/direct_domain_bypass_audit_a67c414f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_direct_domain_bypass_audit_a67c414f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.293-direct-privileged-call-bypass-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.293-direct-privileged-call-bypass-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/direct_privileged_call_bypass_audit_303736bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/direct_privileged_call_bypass_audit_303736bf.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/direct_privileged_call_bypass_audit_303736bf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_direct_privileged_call_bypass_audit_303736bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.294-direct-shell-execution-bypass-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.294-direct-shell-execution-bypass-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/direct_shell_execution_bypass_audit_2d51e85e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/direct_shell_execution_bypass_audit_2d51e85e.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/direct_shell_execution_bypass_audit_2d51e85e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_direct_shell_execution_bypass_audit_2d51e85e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.295-presentation-layer-mutation-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.295-presentation-layer-mutation-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/presentation_layer_mutation_audit_d16f2d9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/presentation_layer_mutation_audit_d16f2d9b.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/presentation_layer_mutation_audit_d16f2d9b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_presentation_layer_mutation_audit_d16f2d9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.296-workflow-bypass-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.296-workflow-bypass-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/workflow_bypass_audit_7e981494/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/workflow_bypass_audit_7e981494.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/workflow_bypass_audit_7e981494.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_workflow_bypass_audit_7e981494.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.297-intelligence-bypass-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.297-intelligence-bypass-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/intelligence_bypass_audit_2aa9fc0e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/intelligence_bypass_audit_2aa9fc0e.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/intelligence_bypass_audit_2aa9fc0e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_intelligence_bypass_audit_2aa9fc0e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.298-adaptive-bypass-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.298-adaptive-bypass-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adaptive_bypass_audit_425a648b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adaptive_bypass_audit_425a648b.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adaptive_bypass_audit_425a648b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adaptive_bypass_audit_425a648b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.299-stale-entrypoint-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.299-stale-entrypoint-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/stale_entrypoint_audit_6120183a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/stale_entrypoint_audit_6120183a.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/stale_entrypoint_audit_6120183a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_stale_entrypoint_audit_6120183a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.300-stale-caller-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.300-stale-caller-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/stale_caller_audit_ec6ac2c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/stale_caller_audit_ec6ac2c2.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/stale_caller_audit_ec6ac2c2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_stale_caller_audit_ec6ac2c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.301-stale-cmake-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.301-stale-cmake-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/stale_cmake_audit_ecba2a91/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/stale_cmake_audit_ecba2a91.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/stale_cmake_audit_ecba2a91.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_stale_cmake_audit_ecba2a91.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.302-stale-packaging-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.302-stale-packaging-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/stale_packaging_audit_26ae3e44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/stale_packaging_audit_26ae3e44.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/stale_packaging_audit_26ae3e44.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_stale_packaging_audit_26ae3e44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.303-stale-service-definition-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.303-stale-service-definition-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/stale_service_definition_audit_bcd83de9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/stale_service_definition_audit_bcd83de9.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/stale_service_definition_audit_bcd83de9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_stale_service_definition_audit_bcd83de9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.304-stale-documentation-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.304-stale-documentation-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/stale_documentation_audit_88121048/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/stale_documentation_audit_88121048.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/stale_documentation_audit_88121048.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_stale_documentation_audit_88121048.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.305-test-only-legacy-path-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.305-test-only-legacy-path-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/test_only_legacy_path_audit_51001975/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/test_only_legacy_path_audit_51001975.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/test_only_legacy_path_audit_51001975.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_test_only_legacy_path_audit_51001975.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.306-canonical-entrypoint-verification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.306-canonical-entrypoint-verification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/canonical_entrypoint_verification_e2aac08b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/canonical_entrypoint_verification_e2aac08b.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/canonical_entrypoint_verification_e2aac08b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_canonical_entrypoint_verification_e2aac08b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.307-production-call-graph-verification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.307-production-call-graph-verification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/production_call_graph_verification_61f4846e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/production_call_graph_verification_61f4846e.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/production_call_graph_verification_61f4846e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_production_call_graph_verification_61f4846e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.308-domain-owner-verification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.308-domain-owner-verification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/domain_owner_verification_1646a2a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/domain_owner_verification_1646a2a7.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/domain_owner_verification_1646a2a7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_domain_owner_verification_1646a2a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.309-authority-path-verification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.309-authority-path-verification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/authority_path_verification_cbda95b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/authority_path_verification_cbda95b1.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/authority_path_verification_cbda95b1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_authority_path_verification_cbda95b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.310-agents-md-hierarchy-reconciliation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.310-agents-md-hierarchy-reconciliation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/agents_md_hierarchy_reconciliation_bf071c8e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/agents_md_hierarchy_reconciliation_bf071c8e.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/agents_md_hierarchy_reconciliation_bf071c8e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_agents_md_hierarchy_reconciliation_bf071c8e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.311-agents-md-permanent-c-first-contract`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.311-agents-md-permanent-c-first-contract.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/agents_md_permanent_c_first_contract_54da3981/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/contracts/agents_md_permanent_c_first_contract_54da3981.hpp`, `src/runtime/unified-control-plane/subtask_targets/contracts/agents_md_permanent_c_first_contract_54da3981.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/contracts/test_agents_md_permanent_c_first_contract_54da3981.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.312-agents-md-control-plane-contract`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.312-agents-md-control-plane-contract.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/agents_md_control_plane_contract_0a5de2f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/agents_md_control_plane_contract_0a5de2f7.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/agents_md_control_plane_contract_0a5de2f7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_agents_md_control_plane_contract_0a5de2f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.313-architecture-documentation-reconciliation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.313-architecture-documentation-reconciliation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/architecture_documentation_reconciliation_4acac789/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/architecture_documentation_reconciliation_4acac789.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/architecture_documentation_reconciliation_4acac789.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_architecture_documentation_reconciliation_4acac789.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.314-operator-documentation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.314-operator-documentation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/operator_documentation_f5ec74b3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/operator_documentation_f5ec74b3.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/operator_documentation_f5ec74b3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_operator_documentation_f5ec74b3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.315-developer-documentation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.315-developer-documentation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/developer_documentation_f3a2bbe7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/developer_documentation_f3a2bbe7.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/developer_documentation_f3a2bbe7.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_developer_documentation_f3a2bbe7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.316-provider-authoring-documentation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.316-provider-authoring-documentation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/provider_authoring_documentation_6f705ef2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/integration/provider_authoring_documentation_6f705ef2.hpp`, `src/runtime/unified-control-plane/subtask_targets/integration/provider_authoring_documentation_6f705ef2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/integration/test_provider_authoring_documentation_6f705ef2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.317-capability-authoring-documentation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.317-capability-authoring-documentation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/capability_authoring_documentation_f22bb311/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/capability_authoring_documentation_f22bb311.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/capability_authoring_documentation_f22bb311.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_capability_authoring_documentation_f22bb311.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.318-recovery-documentation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.318-recovery-documentation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/recovery_documentation_e7d110b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/recovery/recovery_documentation_e7d110b5.hpp`, `src/runtime/unified-control-plane/subtask_targets/recovery/recovery_documentation_e7d110b5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/recovery/test_recovery_documentation_e7d110b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.319-security-documentation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.319-security-documentation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/security_documentation_a49f4faf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/security_documentation_a49f4faf.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/security_documentation_a49f4faf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_security_documentation_a49f4faf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.320-repository-wide-recursive-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.320-repository-wide-recursive-rediscovery-pass-one.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/repository_wide_recursive_rediscovery_pass_one_b467ce6f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/repository_wide_recursive_rediscovery_pass_one_b467ce6f.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/repository_wide_recursive_rediscovery_pass_one_b467ce6f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_repository_wide_recursive_rediscovery_pass_one_b467ce6f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.321-resolve-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.321-resolve-rediscovery-pass-one.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/resolve_rediscovery_pass_one_d49e73a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/resolve_rediscovery_pass_one_d49e73a3.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/resolve_rediscovery_pass_one_d49e73a3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_resolve_rediscovery_pass_one_d49e73a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.322-repository-wide-recursive-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.322-repository-wide-recursive-rediscovery-pass-two.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/repository_wide_recursive_rediscovery_pass_two_2f1d8f5b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/repository_wide_recursive_rediscovery_pass_two_2f1d8f5b.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/repository_wide_recursive_rediscovery_pass_two_2f1d8f5b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_repository_wide_recursive_rediscovery_pass_two_2f1d8f5b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.323-resolve-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.323-resolve-rediscovery-pass-two.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/resolve_rediscovery_pass_two_5e5f98ac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/resolve_rediscovery_pass_two_5e5f98ac.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/resolve_rediscovery_pass_two_5e5f98ac.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_resolve_rediscovery_pass_two_5e5f98ac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.324-fixed-point-confirmation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.324-fixed-point-confirmation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/fixed_point_confirmation_8332fb9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/fixed_point_confirmation_8332fb9d.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/fixed_point_confirmation_8332fb9d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_fixed_point_confirmation_8332fb9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.325-adversarial-authority-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.325-adversarial-authority-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_authority_audit_a266fcee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_authority_audit_a266fcee.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_authority_audit_a266fcee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_authority_audit_a266fcee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.326-adversarial-bypass-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.326-adversarial-bypass-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_bypass_audit_7d4b0be0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_bypass_audit_7d4b0be0.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_bypass_audit_7d4b0be0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_bypass_audit_7d4b0be0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.327-adversarial-duplicate-control-plane-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.327-adversarial-duplicate-control-plane-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_duplicate_control_plane_audit_ef7ad939/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_duplicate_control_plane_audit_ef7ad939.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_duplicate_control_plane_audit_ef7ad939.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_duplicate_control_plane_audit_ef7ad939.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.328-adversarial-python-ownership-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.328-adversarial-python-ownership-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_python_ownership_audit_91d28de4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_python_ownership_audit_91d28de4.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_python_ownership_audit_91d28de4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_python_ownership_audit_91d28de4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.329-adversarial-shell-authority-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.329-adversarial-shell-authority-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_shell_authority_audit_67a3cd37/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_shell_authority_audit_67a3cd37.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_shell_authority_audit_67a3cd37.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_shell_authority_audit_67a3cd37.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.330-adversarial-privilege-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.330-adversarial-privilege-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_privilege_audit_0448371a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_privilege_audit_0448371a.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_privilege_audit_0448371a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_privilege_audit_0448371a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.331-adversarial-recovery-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.331-adversarial-recovery-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_recovery_audit_18793b80/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_recovery_audit_18793b80.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_recovery_audit_18793b80.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_recovery_audit_18793b80.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.332-adversarial-unknown-semantics-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.332-adversarial-unknown-semantics-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/adversarial_unknown_semantics_audit_68351d7b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_unknown_semantics_audit_68351d7b.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/adversarial_unknown_semantics_audit_68351d7b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_adversarial_unknown_semantics_audit_68351d7b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.333-final-build`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.333-final-build.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_build_5b2f91cc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_build_5b2f91cc.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_build_5b2f91cc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_build_5b2f91cc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.334-final-unit-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.334-final-unit-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_unit_tests_1149c3ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/final_unit_tests_1149c3ab.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/final_unit_tests_1149c3ab.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_final_unit_tests_1149c3ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.335-final-integration-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.335-final-integration-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_integration_tests_71c0e296/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/final_integration_tests_71c0e296.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/final_integration_tests_71c0e296.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_final_integration_tests_71c0e296.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.336-final-end-to-end-tests`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.336-final-end-to-end-tests.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_end_to_end_tests_def6602c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/final_end_to_end_tests_def6602c.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/final_end_to_end_tests_def6602c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_final_end_to_end_tests_def6602c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.337-final-failure-injection-suite`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.337-final-failure-injection-suite.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_failure_injection_suite_81892cbf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_failure_injection_suite_81892cbf.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_failure_injection_suite_81892cbf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_failure_injection_suite_81892cbf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.338-final-performance-validation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.338-final-performance-validation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_performance_validation_d571e9cc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_performance_validation_d571e9cc.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_performance_validation_d571e9cc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_performance_validation_d571e9cc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.339-final-security-validation`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.339-final-security-validation.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_security_validation_3d4f4f27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/security/final_security_validation_3d4f4f27.hpp`, `src/runtime/unified-control-plane/subtask_targets/security/final_security_validation_3d4f4f27.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/security/test_final_security_validation_3d4f4f27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.340-final-source-tree-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.340-final-source-tree-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_source_tree_audit_137bd673/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/final_source_tree_audit_137bd673.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/final_source_tree_audit_137bd673.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_final_source_tree_audit_137bd673.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.341-final-documentation-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.341-final-documentation-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_documentation_audit_50de9f5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/final_documentation_audit_50de9f5d.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/final_documentation_audit_50de9f5d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_final_documentation_audit_50de9f5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.342-final-agents-md-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.342-final-agents-md-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_agents_md_audit_88602b39/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/final_agents_md_audit_88602b39.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/final_agents_md_audit_88602b39.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_final_agents_md_audit_88602b39.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.343-final-production-path-trace`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.343-final-production-path-trace.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_production_path_trace_ba82acc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/observability/final_production_path_trace_ba82acc3.hpp`, `src/runtime/unified-control-plane/subtask_targets/observability/final_production_path_trace_ba82acc3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/observability/test_final_production_path_trace_ba82acc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.344-final-authority-graph`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.344-final-authority-graph.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_authority_graph_ff12acc2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_authority_graph_ff12acc2.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_authority_graph_ff12acc2.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_authority_graph_ff12acc2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.345-final-remaining-python-inventory`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.345-final-remaining-python-inventory.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_remaining_python_inventory_fb76eb64/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_remaining_python_inventory_fb76eb64.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_remaining_python_inventory_fb76eb64.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_remaining_python_inventory_fb76eb64.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.346-final-retained-boundary-justification`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.346-final-retained-boundary-justification.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_retained_boundary_justification_9148dc18/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_retained_boundary_justification_9148dc18.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_retained_boundary_justification_9148dc18.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_retained_boundary_justification_9148dc18.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.347-final-obsolete-code-retirement`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.347-final-obsolete-code-retirement.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_obsolete_code_retirement_04233c3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_obsolete_code_retirement_04233c3f.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_obsolete_code_retirement_04233c3f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_obsolete_code_retirement_04233c3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.348-final-compatibility-shim-retirement`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.348-final-compatibility-shim-retirement.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_compatibility_shim_retirement_91f70f3e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/final_compatibility_shim_retirement_91f70f3e.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/final_compatibility_shim_retirement_91f70f3e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_final_compatibility_shim_retirement_91f70f3e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.349-final-migration-debt-audit`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.349-final-migration-debt-audit.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_migration_debt_audit_87ab142e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/verification/final_migration_debt_audit_87ab142e.hpp`, `src/runtime/unified-control-plane/subtask_targets/verification/final_migration_debt_audit_87ab142e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/verification/test_final_migration_debt_audit_87ab142e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.350-final-fixed-point-rediscovery`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.350-final-fixed-point-rediscovery.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/final_fixed_point_rediscovery_097cbda8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/resolution/final_fixed_point_rediscovery_097cbda8.hpp`, `src/runtime/unified-control-plane/subtask_targets/resolution/final_fixed_point_rediscovery_097cbda8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/resolution/test_final_fixed_point_rediscovery_097cbda8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.351-unified-control-plane-closure`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.351-unified-control-plane-closure.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/unified_control_plane_closure_60fc8d9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/planning/unified_control_plane_closure_60fc8d9b.hpp`, `src/runtime/unified-control-plane/subtask_targets/planning/unified_control_plane_closure_60fc8d9b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/planning/test_unified_control_plane_closure_60fc8d9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `45.352-rebuntu-architecture-closure-and-future-handoff`
- **Source:** `.phases/phases/phase-45-unified-control-plane/prompts/45.352-rebuntu-architecture-closure-and-future-handoff.md`
- **Structural package:** `src/runtime/unified-control-plane/subtask_packages/verification/rebuntu_architecture_closure_and_future_handoff_ee740a8c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/unified-control-plane/subtask_targets/requirements/rebuntu_architecture_closure_and_future_handoff_ee740a8c.hpp`, `src/runtime/unified-control-plane/subtask_targets/requirements/rebuntu_architecture_closure_and_future_handoff_ee740a8c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/unified-control-plane/requirements/test_rebuntu_architecture_closure_and_future_handoff_ee740a8c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`


## MASS IMPLEMENTATION XXII — Structural Skeleton Oversaturation
- Expanded canonical structural address space in `src/adapters`, `src/core`, `src/governance`, `src/interfaces`, `src/portability`, and `src/system`.
- Added explicit contracts/model/verification facets with local `AGENTS.md` boundaries and compilable skeleton tags.
- Evidence: `docs/reports/structural_saturation_xxii.md`, `docs/reports/structural_saturation_xxii.json`, `tools/materialize_structural_saturation.py`.
- Verification observed: `STRUCTURAL_HEADERS_STRICT_COMPILE_PASS`; phase-contract and subtask-ledger validators pass.
- **Maturity rule:** this is structural scaffolding only. It does not implement prompt behavior and does not raise this phase's depth. Future behavioral passes must replace/saturate these placement points with real integrated code and per-subtask evidence.
- Native Authority: compliant; no native Linux mechanism was reimplemented.

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

