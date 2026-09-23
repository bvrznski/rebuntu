# Phase 58 — Constraint Invariant Operational Contract — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-58-constraint-invariant-operational-contract/`
- Primary prompt location: `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/`
- Prompt/specification Markdown files currently present: **54**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 54 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_58` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 58 — Constraint, Invariant & Operational Contract System — FULL 2000+ LINE PROMPTS
- Rebuntu — Phase 58.32: Constraint-to-security boundary
- Mission
- Non-negotiable invariants
- Exhaustive repository discovery
- Execution stage 1: Repository archaeology
- Repository archaeology task matrix
- Execution stage 2: Semantic contracts
- Semantic contracts task matrix
- Execution stage 3: Architecture integration
- Architecture integration task matrix
- Execution stage 4: Deterministic implementation

## Structural skeleton / canonical destination
- Canonical skeleton: `src/semantics/constraint-invariant-operational-contract/`
- Structural files: `src/semantics/constraint-invariant-operational-contract/component.hpp`, `src/semantics/constraint-invariant-operational-contract/component.cpp`, `src/semantics/constraint-invariant-operational-contract/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** SKELETON
- **Implementation depth:** **1/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- No implementation evidence was matched automatically; inspect `src/` before concluding that the requirement is absent.

### Existing test evidence
- `tests/native/test_runtime_contracts.cpp`
- `tests/native/test_contracts.cpp`

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

- Structural skeleton materialized at `src/semantics/constraint-invariant-operational-contract/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/semantics/constraint-invariant-operational-contract/model/`
- `src/semantics/constraint-invariant-operational-contract/contracts/`
- `src/semantics/constraint-invariant-operational-contract/integration/`
- `src/semantics/constraint-invariant-operational-contract/verification/`
- `src/semantics/constraint-invariant-operational-contract/lifecycle/`
- `src/semantics/constraint-invariant-operational-contract/state/`
- `src/semantics/constraint-invariant-operational-contract/execution/`
- `src/semantics/constraint-invariant-operational-contract/transactions/`
- `src/semantics/constraint-invariant-operational-contract/events/`
- `src/semantics/constraint-invariant-operational-contract/scheduling/`
- `src/semantics/constraint-invariant-operational-contract/recovery/`
- `src/semantics/constraint-invariant-operational-contract/principals/`
- `src/semantics/constraint-invariant-operational-contract/groups/`
- `src/semantics/constraint-invariant-operational-contract/roles/`
- `src/semantics/constraint-invariant-operational-contract/resolution/`
- `src/semantics/constraint-invariant-operational-contract/authorization/`
- `src/semantics/constraint-invariant-operational-contract/credentials/`
- `src/semantics/constraint-invariant-operational-contract/policy/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

## TREE DEEPENING III + SATURATION II

Cross-phase executable reconciliation infrastructure was added at `src/control/reconciliation/pipeline/`.
It implements the canonical control flow **observe → verify current state → synthesize plan → policy authorization → typed native operation execution → re-observe → verify convergence**, including dry-run and policy-denial paths. Linux/native mechanics remain behind injected executors/providers; the pipeline does not become a native source of truth.

Evidence:
- `src/control/reconciliation/pipeline/pipeline.hpp`
- `src/control/reconciliation/pipeline/pipeline.cpp`
- `tests/rebuntu/test_reconciliation_pipeline.cpp`
- strict build/test: `-std=c++20 -Wall -Wextra -Wpedantic -Werror` → `RECONCILIATION_PIPELINE_PASS`

This shared infrastructure is implementation evidence only for requirements that actually call for this orchestration. It does **not** establish completion of this phase. Remaining phase-specific prompts, models, constraints, recovery semantics and domain integration must still be implemented and evidenced before increasing depth.

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


## MASS IMPLEMENTATION II recovery + MASS IMPLEMENTATION III / SATURATION — 2026-09-23

### Verified implementation evidence
- `src/domains/common/capabilities/resolver.hpp`: deterministic capability/affordance resolution with contextual constraints and explicit blocker reasons.
- `src/domains/common/desired_state/differ.hpp`: typed desired-vs-observed attribute delta generation.
- `src/domains/common/topology/analyzer.hpp`: deterministic dependency ordering, dangling-edge reporting and dependency-cycle detection.
- `src/domains/common/health/evaluator.hpp`: evidence-backed healthy/degraded/failed/unknown aggregation.
- `src/domains/common/operations/planner.hpp`: diff-to-typed-native-operation synthesis gated by afforded verbs.
- `src/domains/common/reconciliation/domain_reconciler.hpp`: observe -> plan -> execute -> authoritative re-observe -> verify loop, including operation failure and compensating rollback callback.
- `src/domains/common/saturation.hpp`: domain-specific semantics/rules for services, processes, storage, networking, software, configuration, identity and accelerators. Native authorities are systemd, procfs/kernel, filesystems, Netlink, native package manager, native filesystem owner, NSS/PAM, and driver/sysfs respectively.
- `src/domains/{services,processes,storage,networking,software,configuration,identity,accelerators}/observation/translator.hpp`: native observation -> domain semantic model translation with provenance-aware health signals.
- `src/domains/{services,processes,storage,networking,software,configuration,identity,accelerators}/reconciliation/semantic_reconciler.hpp`: domain-specific reconciler construction over the shared semantic spine; no replacement Linux mechanics.

### Executed test evidence
- `tests/rebuntu/test_mass_implementation_ii_iii.cpp` compiled with `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src` and executed successfully. Observed markers: `CAPABILITY_RESOLVER_PASS`, `DESIRED_STATE_DIFF_PASS`, `TOPOLOGY_ANALYZER_PASS`, `HEALTH_EVALUATOR_PASS`, `OPERATION_PLANNER_PASS`, `DOMAIN_RECONCILER_PASS`, `DOMAIN_SATURATION_8_PASS`, `DEPENDENCY_CYCLE_PASS`, `ROLLBACK_PATH_PASS`.
- Header-integration TU covering all eight new domain reconcilers and translators compiled successfully with the same strict warning flags.
- Existing `tests/rebuntu/test_domain_synthesis.cpp` -> `DOMAIN_SYNTHESIS_PASS`.
- Existing `tests/rebuntu/test_domain_semantic_models.cpp` -> `DOMAIN_SEMANTIC_MODELS_PASS`.
- A standalone compile of `test_domain_pipeline_bindings.cpp` was not counted as PASS because it requires its implementation translation units at link time; the attempted one-file link produced unresolved symbols.

### Remaining implementation plan / depth constraint
This pass materially deepens shared domain semantics and all eight domain surfaces, but it does **not** make this phase complete. Full policy/security authorization, stale-evidence invalidation, provider-specific checkpoint construction, durable transaction journaling, richer per-domain rollback inverses, cross-domain orchestration/replanning, and complete prompt-by-prompt acceptance coverage remain. Existing maturity is therefore not promoted to 5/5 by this pass. Where the aggregate ledger was previously 0/5 due to skeleton-only evidence, this pass justifies at least **2/5 (partial concrete implementation)** for the requirements touched here; broader phase maturity must remain conservative until all prompt requirements are mapped and verified.

### Native Authority compliance
The new code performs Rebuntu-owned semantic evaluation, diffing, planning, health assessment, verification and reconciliation orchestration only. Actual machine mutation remains delegated through typed `core::NativeOperation` provider calls; no systemd/procfs/Netlink/filesystem/package/NSS/PAM/driver mechanism is reimplemented.

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `58.0-rebuntu-phase-58-0-constraint-ontology`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.0-rebuntu-phase-58-0-constraint-ontology.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_ontology_fc968a5a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/constraint_ontology_fc968a5a.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/constraint_ontology_fc968a5a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/observability/test_constraint_ontology_fc968a5a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.1-rebuntu-phase-58-1-invariant-ontology`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.1-rebuntu-phase-58-1-invariant-ontology.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/invariant_ontology_2d196fab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/invariant_ontology_2d196fab.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/invariant_ontology_2d196fab.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/observability/test_invariant_ontology_2d196fab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.10-rebuntu-phase-58-10-security-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.10-rebuntu-phase-58-10-security-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/security_invariants_af0b7098/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/security/security_invariants_af0b7098.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/security/security_invariants_af0b7098.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/security/test_security_invariants_af0b7098.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.11-rebuntu-phase-58-11-resource-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.11-rebuntu-phase-58-11-resource-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/resource_invariants_d3af914f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/resource_invariants_d3af914f.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/resource_invariants_d3af914f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_resource_invariants_d3af914f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.12-rebuntu-phase-58-12-topology-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.12-rebuntu-phase-58-12-topology-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/topology_invariants_c238417b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/topology_invariants_c238417b.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/topology_invariants_c238417b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/observability/test_topology_invariants_c238417b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.13-rebuntu-phase-58-13-service-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.13-rebuntu-phase-58-13-service-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/service_invariants_2c54b93d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/service_invariants_2c54b93d.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/service_invariants_2c54b93d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_service_invariants_2c54b93d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.14-rebuntu-phase-58-14-storage-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.14-rebuntu-phase-58-14-storage-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/storage_invariants_c759649c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/storage_invariants_c759649c.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/storage_invariants_c759649c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_storage_invariants_c759649c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.15-rebuntu-phase-58-15-network-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.15-rebuntu-phase-58-15-network-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/network_invariants_78997683/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/network_invariants_78997683.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/network_invariants_78997683.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_network_invariants_78997683.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.16-rebuntu-phase-58-16-gpu-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.16-rebuntu-phase-58-16-gpu-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/gpu_invariants_de2f1f1c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/gpu_invariants_de2f1f1c.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/gpu_invariants_de2f1f1c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_gpu_invariants_de2f1f1c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.17-rebuntu-phase-58-17-session-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.17-rebuntu-phase-58-17-session-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/session_invariants_4813550e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/session_invariants_4813550e.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/session_invariants_4813550e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_session_invariants_4813550e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.18-rebuntu-phase-58-18-temporal-constraints`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.18-rebuntu-phase-58-18-temporal-constraints.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/temporal_constraints_552de120/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/temporal_constraints_552de120.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/temporal_constraints_552de120.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_temporal_constraints_552de120.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.19-rebuntu-phase-58-19-maintenance-constraints`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.19-rebuntu-phase-58-19-maintenance-constraints.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/maintenance_constraints_7d87afda/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/maintenance_constraints_7d87afda.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/maintenance_constraints_7d87afda.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_maintenance_constraints_7d87afda.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.2-rebuntu-phase-58-2-operational-contract-model`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.2-rebuntu-phase-58-2-operational-contract-model.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/operational_contract_model_794ae3c0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/execution/operational_contract_model_794ae3c0.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/execution/operational_contract_model_794ae3c0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/execution/test_operational_contract_model_794ae3c0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.20-rebuntu-phase-58-20-cross-domain-constraints`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.20-rebuntu-phase-58-20-cross-domain-constraints.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/cross_domain_constraints_48f1300d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/cross_domain_constraints_48f1300d.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/cross_domain_constraints_48f1300d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_cross_domain_constraints_48f1300d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.21-rebuntu-phase-58-21-distributed-constraints`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.21-rebuntu-phase-58-21-distributed-constraints.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/distributed_constraints_cbcf700c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/distributed_constraints_cbcf700c.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/distributed_constraints_cbcf700c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_distributed_constraints_cbcf700c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.22-rebuntu-phase-58-22-constraint-composition`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.22-rebuntu-phase-58-22-constraint-composition.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_composition_b8ac44d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_composition_b8ac44d6.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_composition_b8ac44d6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_constraint_composition_b8ac44d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.23-rebuntu-phase-58-23-constraint-conflicts`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.23-rebuntu-phase-58-23-constraint-conflicts.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_conflicts_009cc503/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_conflicts_009cc503.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_conflicts_009cc503.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_constraint_conflicts_009cc503.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.24-rebuntu-phase-58-24-constraint-precedence`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.24-rebuntu-phase-58-24-constraint-precedence.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_precedence_81b16d73/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_precedence_81b16d73.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_precedence_81b16d73.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_constraint_precedence_81b16d73.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.25-rebuntu-phase-58-25-constraint-satisfiability`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.25-rebuntu-phase-58-25-constraint-satisfiability.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_satisfiability_5a87899e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_satisfiability_5a87899e.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_satisfiability_5a87899e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_constraint_satisfiability_5a87899e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.26-rebuntu-phase-58-26-invariant-evaluation`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.26-rebuntu-phase-58-26-invariant-evaluation.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/invariant_evaluation_d652e81a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/invariant_evaluation_d652e81a.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/invariant_evaluation_d652e81a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_invariant_evaluation_d652e81a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.27-rebuntu-phase-58-27-invariant-freshness`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.27-rebuntu-phase-58-27-invariant-freshness.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/invariant_freshness_3a6c84b9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/invariant_freshness_3a6c84b9.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/invariant_freshness_3a6c84b9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_invariant_freshness_3a6c84b9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.28-rebuntu-phase-58-28-invariant-unknown`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.28-rebuntu-phase-58-28-invariant-unknown.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/invariant_unknown_1a9c24eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/invariant_unknown_1a9c24eb.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/invariant_unknown_1a9c24eb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_invariant_unknown_1a9c24eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.29-rebuntu-phase-58-29-constraint-to-planner-integration`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.29-rebuntu-phase-58-29-constraint-to-planner-integration.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_to_planner_integration_2912f170/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/integration/constraint_to_planner_integration_2912f170.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/integration/constraint_to_planner_integration_2912f170.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/integration/test_constraint_to_planner_integration_2912f170.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.3-rebuntu-phase-58-3-constraint-identity`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.3-rebuntu-phase-58-3-constraint-identity.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_identity_7185a9ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/contracts/constraint_identity_7185a9ca.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/contracts/constraint_identity_7185a9ca.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/contracts/test_constraint_identity_7185a9ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.30-rebuntu-phase-58-30-constraint-to-affordance-integration`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.30-rebuntu-phase-58-30-constraint-to-affordance-integration.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_to_affordance_integration_ec957710/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/integration/constraint_to_affordance_integration_ec957710.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/integration/constraint_to_affordance_integration_ec957710.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/integration/test_constraint_to_affordance_integration_ec957710.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.31-rebuntu-phase-58-31-constraint-to-policy-boundary`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.31-rebuntu-phase-58-31-constraint-to-policy-boundary.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_to_policy_boundary_344796ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/security/constraint_to_policy_boundary_344796ce.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/security/constraint_to_policy_boundary_344796ce.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/security/test_constraint_to_policy_boundary_344796ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.32-rebuntu-phase-58-32-constraint-to-security-boundary`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.32-rebuntu-phase-58-32-constraint-to-security-boundary.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_to_security_boundary_976937f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/security/constraint_to_security_boundary_976937f0.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/security/constraint_to_security_boundary_976937f0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/security/test_constraint_to_security_boundary_976937f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.33-rebuntu-phase-58-33-pre-execution-invariant-gate`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.33-rebuntu-phase-58-33-pre-execution-invariant-gate.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/pre_execution_invariant_gate_db2a7f41/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/execution/pre_execution_invariant_gate_db2a7f41.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/execution/pre_execution_invariant_gate_db2a7f41.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/execution/test_pre_execution_invariant_gate_db2a7f41.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.34-rebuntu-phase-58-34-post-execution-invariant-verification`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.34-rebuntu-phase-58-34-post-execution-invariant-verification.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/post_execution_invariant_verification_27bfa1fd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/verification/post_execution_invariant_verification_27bfa1fd.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/verification/post_execution_invariant_verification_27bfa1fd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/verification/test_post_execution_invariant_verification_27bfa1fd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.35-rebuntu-phase-58-35-continuous-invariant-monitoring`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.35-rebuntu-phase-58-35-continuous-invariant-monitoring.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/continuous_invariant_monitoring_7b768316/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/continuous_invariant_monitoring_7b768316.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/continuous_invariant_monitoring_7b768316.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_continuous_invariant_monitoring_7b768316.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.36-rebuntu-phase-58-36-violation-event-model`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.36-rebuntu-phase-58-36-violation-event-model.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/violation_event_model_c3aa14af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/contracts/violation_event_model_c3aa14af.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/contracts/violation_event_model_c3aa14af.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/contracts/test_violation_event_model_c3aa14af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.37-rebuntu-phase-58-37-violation-escalation`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.37-rebuntu-phase-58-37-violation-escalation.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/violation_escalation_04c4586c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/violation_escalation_04c4586c.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/violation_escalation_04c4586c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_violation_escalation_04c4586c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.38-rebuntu-phase-58-38-violation-recovery-handoff`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.38-rebuntu-phase-58-38-violation-recovery-handoff.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/violation_recovery_handoff_d2594ade/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/recovery/violation_recovery_handoff_d2594ade.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/recovery/violation_recovery_handoff_d2594ade.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/recovery/test_violation_recovery_handoff_d2594ade.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.39-rebuntu-phase-58-39-operator-override-boundary`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.39-rebuntu-phase-58-39-operator-override-boundary.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/operator_override_boundary_59048bb0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/operator_override_boundary_59048bb0.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/operator_override_boundary_59048bb0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_operator_override_boundary_59048bb0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.4-rebuntu-phase-58-4-constraint-scope`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.4-rebuntu-phase-58-4-constraint-scope.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_scope_7c7e781b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_scope_7c7e781b.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_scope_7c7e781b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_constraint_scope_7c7e781b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.40-rebuntu-phase-58-40-override-expiry`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.40-rebuntu-phase-58-40-override-expiry.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/override_expiry_072bf017/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/override_expiry_072bf017.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/override_expiry_072bf017.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_override_expiry_072bf017.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.41-rebuntu-phase-58-41-constraint-explainability`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.41-rebuntu-phase-58-41-constraint-explainability.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_explainability_9dc04506/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/constraint_explainability_9dc04506.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/observability/constraint_explainability_9dc04506.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/observability/test_constraint_explainability_9dc04506.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.42-rebuntu-phase-58-42-why-blocked-integration`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.42-rebuntu-phase-58-42-why-blocked-integration.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/why_blocked_integration_32a88f25/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/integration/why_blocked_integration_32a88f25.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/integration/why_blocked_integration_32a88f25.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/integration/test_why_blocked_integration_32a88f25.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.43-rebuntu-phase-58-43-cli`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.43-rebuntu-phase-58-43-cli.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/cli_0620224f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/cli_0620224f.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/cli_0620224f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_cli_0620224f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.44-rebuntu-phase-58-44-gui`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.44-rebuntu-phase-58-44-gui.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/gui_bc9764d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/gui_bc9764d4.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/gui_bc9764d4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_gui_bc9764d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.45-rebuntu-phase-58-45-persistence-versioning`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.45-rebuntu-phase-58-45-persistence-versioning.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/persistence_versioning_4326abd0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/persistence/persistence_versioning_4326abd0.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/persistence/persistence_versioning_4326abd0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/persistence/test_persistence_versioning_4326abd0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.46-rebuntu-phase-58-46-adversarial-bypass-audit`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.46-rebuntu-phase-58-46-adversarial-bypass-audit.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/adversarial_bypass_audit_17e42b83/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/verification/adversarial_bypass_audit_17e42b83.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/verification/adversarial_bypass_audit_17e42b83.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/verification/test_adversarial_bypass_audit_17e42b83.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.47-rebuntu-phase-58-47-build-runtime-audit`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.47-rebuntu-phase-58-47-build-runtime-audit.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/build_runtime_audit_3e10ad1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/verification/build_runtime_audit_3e10ad1f.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/verification/build_runtime_audit_3e10ad1f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/verification/test_build_runtime_audit_3e10ad1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.48-rebuntu-phase-58-48-independent-rediscovery`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.48-rebuntu-phase-58-48-independent-rediscovery.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/independent_rediscovery_932c4d02/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/resolution/independent_rediscovery_932c4d02.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/resolution/independent_rediscovery_932c4d02.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/resolution/test_independent_rediscovery_932c4d02.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.49-rebuntu-phase-58-49-phase-closure`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.49-rebuntu-phase-58-49-phase-closure.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/phase_closure_502fa2cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/phase_closure_502fa2cf.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/phase_closure_502fa2cf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_phase_closure_502fa2cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.5-rebuntu-phase-58-5-constraint-provenance`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.5-rebuntu-phase-58-5-constraint-provenance.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/constraint_provenance_c8d4950c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_provenance_c8d4950c.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/constraint_provenance_c8d4950c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_constraint_provenance_c8d4950c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.6-rebuntu-phase-58-6-hard-constraints`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.6-rebuntu-phase-58-6-hard-constraints.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/hard_constraints_a2aa6f89/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/hard_constraints_a2aa6f89.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/hard_constraints_a2aa6f89.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_hard_constraints_a2aa6f89.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.7-rebuntu-phase-58-7-soft-constraints`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.7-rebuntu-phase-58-7-soft-constraints.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/soft_constraints_ca800fc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/soft_constraints_ca800fc3.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/soft_constraints_ca800fc3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_soft_constraints_ca800fc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.8-rebuntu-phase-58-8-safety-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.8-rebuntu-phase-58-8-safety-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/safety_invariants_e982716e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/safety_invariants_e982716e.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/safety_invariants_e982716e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_safety_invariants_e982716e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `58.9-rebuntu-phase-58-9-availability-invariants`
- **Source:** `.phases/phases/phase-58-constraint-invariant-operational-contract/prompts/58.9-rebuntu-phase-58-9-availability-invariants.md`
- **Structural package:** `src/semantics/constraint-invariant-operational-contract/subtask_packages/verification/availability_invariants_e39cc9fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/availability_invariants_e39cc9fe.hpp`, `src/semantics/constraint-invariant-operational-contract/subtask_targets/requirements/availability_invariants_e39cc9fe.cpp`
- **Structural test target:** `tests/structural-closure/semantics/constraint-invariant-operational-contract/requirements/test_availability_invariants_e39cc9fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

