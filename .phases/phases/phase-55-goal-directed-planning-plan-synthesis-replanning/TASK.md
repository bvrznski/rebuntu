# Phase 55 — Goal Directed Planning Plan Synthesis Replanning — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/`
- Primary prompt location: `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/`
- Prompt/specification Markdown files currently present: **200**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 200 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_55` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 55 — Goal-Directed Planning, Plan Synthesis & Replanning — FULL 2000+ LINE PROMPTS
- Rebuntu — Phase 55.85: Plan resource validation
- Mission
- Non-negotiable invariants
- Exhaustive repository discovery
- Execution stage 1: Discovery
- Discovery task matrix
- Execution stage 2: Problem formulation
- Problem formulation task matrix
- Execution stage 3: Transition modeling
- Transition modeling task matrix
- Execution stage 4: Search and synthesis

## Structural skeleton / canonical destination
- Canonical skeleton: `src/planning/goal-directed-planning-plan-synthesis-replanning/`
- Structural files: `src/planning/goal-directed-planning-plan-synthesis-replanning/component.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/component.cpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/planning/replanning/README.md`
- `src/planning/replanning/contract.hpp`
- `src/planning/synthesis/README.md`
- `src/planning/synthesis/contract.hpp`
- `src/planning/change_planner.hpp`

### Existing test evidence
- `tests/native/test_install_planning.cpp`

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

- Structural skeleton materialized at `src/planning/goal-directed-planning-plan-synthesis-replanning/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/planning/goal-directed-planning-plan-synthesis-replanning/model/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/contracts/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/integration/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/verification/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/lifecycle/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/state/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/execution/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/transactions/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/events/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/scheduling/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/recovery/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/preflight/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/planning/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/staging/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/ownership/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/repair/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/upgrade/`
- `src/planning/goal-directed-planning-plan-synthesis-replanning/uninstall/`



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

### `55.0-rebuntu-phase-55-0-phase-bootstrap-and-planning-topology-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.0-rebuntu-phase-55-0-phase-bootstrap-and-planning-topology-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_bootstrap_and_planning_topology_audit_742e7fcb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/phase_bootstrap_and_planning_topology_audit_742e7fcb.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/phase_bootstrap_and_planning_topology_audit_742e7fcb.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_phase_bootstrap_and_planning_topology_audit_742e7fcb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.1-rebuntu-phase-55-1-goal-representation-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.1-rebuntu-phase-55-1-goal-representation-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/goal_representation_contract_3cd238b8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/goal_representation_contract_3cd238b8.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/goal_representation_contract_3cd238b8.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/contracts/test_goal_representation_contract_3cd238b8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.10-rebuntu-phase-55-10-plan-step-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.10-rebuntu-phase-55-10-plan-step-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_step_contract_e6f3b49f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_step_contract_e6f3b49f.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_step_contract_e6f3b49f.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_step_contract_e6f3b49f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.100-rebuntu-phase-55-100-predicted-versus-observed-distinction`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.100-rebuntu-phase-55-100-predicted-versus-observed-distinction.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/predicted_versus_observed_distinction_52125106/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/predicted_versus_observed_distinction_52125106.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/predicted_versus_observed_distinction_52125106.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_predicted_versus_observed_distinction_52125106.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.101-rebuntu-phase-55-101-plan-preview-rendering`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.101-rebuntu-phase-55-101-plan-preview-rendering.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_preview_rendering_1ceec0d3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_preview_rendering_1ceec0d3.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_preview_rendering_1ceec0d3.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_preview_rendering_1ceec0d3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.102-rebuntu-phase-55-102-plan-explainability`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.102-rebuntu-phase-55-102-plan-explainability.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_explainability_94629af5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/plan_explainability_94629af5.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/plan_explainability_94629af5.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_plan_explainability_94629af5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.103-rebuntu-phase-55-103-why-this-plan-explanation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.103-rebuntu-phase-55-103-why-this-plan-explanation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/why_this_plan_explanation_c97a136d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/why_this_plan_explanation_c97a136d.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/why_this_plan_explanation_c97a136d.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_why_this_plan_explanation_c97a136d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.104-rebuntu-phase-55-104-why-this-step-explanation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.104-rebuntu-phase-55-104-why-this-step-explanation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/why_this_step_explanation_7933b383/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/why_this_step_explanation_7933b383.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/why_this_step_explanation_7933b383.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_why_this_step_explanation_7933b383.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.105-rebuntu-phase-55-105-why-not-alternative-explanation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.105-rebuntu-phase-55-105-why-not-alternative-explanation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/why_not_alternative_explanation_3daae335/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/why_not_alternative_explanation_3daae335.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/why_not_alternative_explanation_3daae335.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_why_not_alternative_explanation_3daae335.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.106-rebuntu-phase-55-106-blocker-explanation-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.106-rebuntu-phase-55-106-blocker-explanation-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/blocker_explanation_integration_4a34cce8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/blocker_explanation_integration_4a34cce8.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/blocker_explanation_integration_4a34cce8.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_blocker_explanation_integration_4a34cce8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.107-rebuntu-phase-55-107-cli-plan-command`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.107-rebuntu-phase-55-107-cli-plan-command.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/cli_plan_command_5fb3ac0e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/cli_plan_command_5fb3ac0e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/cli_plan_command_5fb3ac0e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/execution/test_cli_plan_command_5fb3ac0e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.108-rebuntu-phase-55-108-cli-plan-inspect`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.108-rebuntu-phase-55-108-cli-plan-inspect.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/cli_plan_inspect_c031721a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/cli_plan_inspect_c031721a.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/cli_plan_inspect_c031721a.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_cli_plan_inspect_c031721a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.109-rebuntu-phase-55-109-cli-plan-explain`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.109-rebuntu-phase-55-109-cli-plan-explain.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/cli_plan_explain_cd2f4759/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/cli_plan_explain_cd2f4759.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/cli_plan_explain_cd2f4759.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_cli_plan_explain_cd2f4759.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.11-rebuntu-phase-55-11-typed-state-transition-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.11-rebuntu-phase-55-11-typed-state-transition-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/typed_state_transition_model_e6221118/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/typed_state_transition_model_e6221118.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/typed_state_transition_model_e6221118.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/lifecycle/test_typed_state_transition_model_e6221118.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.110-rebuntu-phase-55-110-cli-plan-alternatives`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.110-rebuntu-phase-55-110-cli-plan-alternatives.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/cli_plan_alternatives_955a97b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/cli_plan_alternatives_955a97b1.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/cli_plan_alternatives_955a97b1.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_cli_plan_alternatives_955a97b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.111-rebuntu-phase-55-111-gui-plan-explorer`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.111-rebuntu-phase-55-111-gui-plan-explorer.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/gui_plan_explorer_760caac4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/gui_plan_explorer_760caac4.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/gui_plan_explorer_760caac4.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_gui_plan_explorer_760caac4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.112-rebuntu-phase-55-112-gui-dependency-visualization`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.112-rebuntu-phase-55-112-gui-dependency-visualization.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/gui_dependency_visualization_3fa39e9c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/gui_dependency_visualization_3fa39e9c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/gui_dependency_visualization_3fa39e9c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_gui_dependency_visualization_3fa39e9c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.113-rebuntu-phase-55-113-gui-plan-comparison`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.113-rebuntu-phase-55-113-gui-plan-comparison.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/gui_plan_comparison_67a8dd8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/gui_plan_comparison_67a8dd8d.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/gui_plan_comparison_67a8dd8d.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_gui_plan_comparison_67a8dd8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.114-rebuntu-phase-55-114-phase-46-natural-language-goal-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.114-rebuntu-phase-55-114-phase-46-natural-language-goal-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_46_natural_language_goal_integration_549f5637/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_46_natural_language_goal_integration_549f5637.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_46_natural_language_goal_integration_549f5637.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_46_natural_language_goal_integration_549f5637.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.115-rebuntu-phase-55-115-natural-language-plan-questions`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.115-rebuntu-phase-55-115-natural-language-plan-questions.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/natural_language_plan_questions_13e7338e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/natural_language_plan_questions_13e7338e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/natural_language_plan_questions_13e7338e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_natural_language_plan_questions_13e7338e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.116-rebuntu-phase-55-116-phase-40-command-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.116-rebuntu-phase-55-116-phase-40-command-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_40_command_integration_02c05132/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_40_command_integration_02c05132.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_40_command_integration_02c05132.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_40_command_integration_02c05132.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.117-rebuntu-phase-55-117-phase-41-workflow-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.117-rebuntu-phase-55-117-phase-41-workflow-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_41_workflow_boundary_b1f2b2ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/phase_41_workflow_boundary_b1f2b2ba.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/phase_41_workflow_boundary_b1f2b2ba.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_phase_41_workflow_boundary_b1f2b2ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.118-rebuntu-phase-55-118-workflow-from-plan-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.118-rebuntu-phase-55-118-workflow-from-plan-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/workflow_from_plan_boundary_88f7d5c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/workflow_from_plan_boundary_88f7d5c2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/workflow_from_plan_boundary_88f7d5c2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_workflow_from_plan_boundary_88f7d5c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.119-rebuntu-phase-55-119-plan-to-workflow-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.119-rebuntu-phase-55-119-plan-to-workflow-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_to_workflow_boundary_8b02f1f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_to_workflow_boundary_8b02f1f0.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_to_workflow_boundary_8b02f1f0.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_to_workflow_boundary_8b02f1f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.12-rebuntu-phase-55-12-operation-effect-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.12-rebuntu-phase-55-12-operation-effect-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/operation_effect_model_60ef9b1c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/operation_effect_model_60ef9b1c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/operation_effect_model_60ef9b1c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/execution/test_operation_effect_model_60ef9b1c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.120-rebuntu-phase-55-120-automation-planning-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.120-rebuntu-phase-55-120-automation-planning-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/automation_planning_boundary_782a6993/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/automation_planning_boundary_782a6993.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/automation_planning_boundary_782a6993.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_automation_planning_boundary_782a6993.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.121-rebuntu-phase-55-121-phase-48-context-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.121-rebuntu-phase-55-121-phase-48-context-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_48_context_integration_4c3f1543/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_48_context_integration_4c3f1543.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_48_context_integration_4c3f1543.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_48_context_integration_4c3f1543.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.122-rebuntu-phase-55-122-phase-42-knowledge-graph-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.122-rebuntu-phase-55-122-phase-42-knowledge-graph-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_42_knowledge_graph_integration_7c640e2c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_42_knowledge_graph_integration_7c640e2c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_42_knowledge_graph_integration_7c640e2c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_42_knowledge_graph_integration_7c640e2c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.123-rebuntu-phase-55-123-phase-39-timeline-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.123-rebuntu-phase-55-123-phase-39-timeline-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_39_timeline_integration_959c525e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_39_timeline_integration_959c525e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_39_timeline_integration_959c525e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_39_timeline_integration_959c525e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.124-rebuntu-phase-55-124-phase-50-platform-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.124-rebuntu-phase-55-124-phase-50-platform-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_50_platform_integration_f40bc614/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_50_platform_integration_f40bc614.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_50_platform_integration_f40bc614.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_50_platform_integration_f40bc614.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.125-rebuntu-phase-55-125-phase-51-distributed-planning-foundation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.125-rebuntu-phase-55-125-phase-51-distributed-planning-foundation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_51_distributed_planning_foundation_36c70d10/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/phase_51_distributed_planning_foundation_36c70d10.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/phase_51_distributed_planning_foundation_36c70d10.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_phase_51_distributed_planning_foundation_36c70d10.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.126-rebuntu-phase-55-126-phase-52-associated-system-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.126-rebuntu-phase-55-126-phase-52-associated-system-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_52_associated_system_planning_8007b389/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/phase_52_associated_system_planning_8007b389.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/phase_52_associated_system_planning_8007b389.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_phase_52_associated_system_planning_8007b389.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.127-rebuntu-phase-55-127-remote-operation-planning-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.127-rebuntu-phase-55-127-remote-operation-planning-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/remote_operation_planning_boundary_f33d7d2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/remote_operation_planning_boundary_f33d7d2e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/remote_operation_planning_boundary_f33d7d2e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/execution/test_remote_operation_planning_boundary_f33d7d2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.128-rebuntu-phase-55-128-remote-capability-freshness`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.128-rebuntu-phase-55-128-remote-capability-freshness.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/remote_capability_freshness_c3d21918/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/remote_capability_freshness_c3d21918.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/remote_capability_freshness_c3d21918.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_remote_capability_freshness_c3d21918.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.129-rebuntu-phase-55-129-cross-node-dependency-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.129-rebuntu-phase-55-129-cross-node-dependency-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/cross_node_dependency_planning_1f77726c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/cross_node_dependency_planning_1f77726c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/cross_node_dependency_planning_1f77726c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_cross_node_dependency_planning_1f77726c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.13-rebuntu-phase-55-13-expected-effect-epistemic-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.13-rebuntu-phase-55-13-expected-effect-epistemic-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/expected_effect_epistemic_boundary_c0222ec8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/expected_effect_epistemic_boundary_c0222ec8.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/expected_effect_epistemic_boundary_c0222ec8.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_expected_effect_epistemic_boundary_c0222ec8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.130-rebuntu-phase-55-130-cross-node-resource-constraints`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.130-rebuntu-phase-55-130-cross-node-resource-constraints.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/cross_node_resource_constraints_0360bd73/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/cross_node_resource_constraints_0360bd73.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/cross_node_resource_constraints_0360bd73.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_cross_node_resource_constraints_0360bd73.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.131-rebuntu-phase-55-131-distributed-failure-assumptions`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.131-rebuntu-phase-55-131-distributed-failure-assumptions.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/distributed_failure_assumptions_c351f917/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/distributed_failure_assumptions_c351f917.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/distributed_failure_assumptions_c351f917.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_distributed_failure_assumptions_c351f917.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.132-rebuntu-phase-55-132-distributed-plan-authority-separation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.132-rebuntu-phase-55-132-distributed-plan-authority-separation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/distributed_plan_authority_separation_ab696947/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/distributed_plan_authority_separation_ab696947.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/distributed_plan_authority_separation_ab696947.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_distributed_plan_authority_separation_ab696947.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.133-rebuntu-phase-55-133-plan-persistence-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.133-rebuntu-phase-55-133-plan-persistence-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_persistence_boundary_d8058f2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_persistence_boundary_d8058f2e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_persistence_boundary_d8058f2e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_persistence_boundary_d8058f2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.134-rebuntu-phase-55-134-plan-cache-semantics`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.134-rebuntu-phase-55-134-plan-cache-semantics.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_cache_semantics_6538c2b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_cache_semantics_6538c2b5.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_cache_semantics_6538c2b5.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_cache_semantics_6538c2b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.135-rebuntu-phase-55-135-plan-freshness-and-expiry`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.135-rebuntu-phase-55-135-plan-freshness-and-expiry.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_freshness_and_expiry_c3123ca2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_freshness_and_expiry_c3123ca2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_freshness_and_expiry_c3123ca2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_freshness_and_expiry_c3123ca2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.136-rebuntu-phase-55-136-plan-invalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.136-rebuntu-phase-55-136-plan-invalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_invalidation_2f97a0ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_invalidation_2f97a0ae.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_invalidation_2f97a0ae.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_invalidation_2f97a0ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.137-rebuntu-phase-55-137-observation-triggered-plan-invalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.137-rebuntu-phase-55-137-observation-triggered-plan-invalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/observation_triggered_plan_invalidation_8ae139fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/observation_triggered_plan_invalidation_8ae139fc.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/observation_triggered_plan_invalidation_8ae139fc.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_observation_triggered_plan_invalidation_8ae139fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.138-rebuntu-phase-55-138-policy-triggered-plan-invalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.138-rebuntu-phase-55-138-policy-triggered-plan-invalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/policy_triggered_plan_invalidation_728e938a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/policy_triggered_plan_invalidation_728e938a.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/policy_triggered_plan_invalidation_728e938a.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_policy_triggered_plan_invalidation_728e938a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.139-rebuntu-phase-55-139-security-triggered-plan-invalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.139-rebuntu-phase-55-139-security-triggered-plan-invalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/security_triggered_plan_invalidation_89d427dd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/security_triggered_plan_invalidation_89d427dd.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/security_triggered_plan_invalidation_89d427dd.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_security_triggered_plan_invalidation_89d427dd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.14-rebuntu-phase-55-14-step-precondition-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.14-rebuntu-phase-55-14-step-precondition-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/step_precondition_model_fb952d04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/step_precondition_model_fb952d04.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/step_precondition_model_fb952d04.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/contracts/test_step_precondition_model_fb952d04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.140-rebuntu-phase-55-140-resource-triggered-plan-invalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.140-rebuntu-phase-55-140-resource-triggered-plan-invalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/resource_triggered_plan_invalidation_8b4f8ee2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/resource_triggered_plan_invalidation_8b4f8ee2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/resource_triggered_plan_invalidation_8b4f8ee2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_resource_triggered_plan_invalidation_8b4f8ee2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.141-rebuntu-phase-55-141-topology-triggered-plan-invalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.141-rebuntu-phase-55-141-topology-triggered-plan-invalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/topology_triggered_plan_invalidation_9ba4b3cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/topology_triggered_plan_invalidation_9ba4b3cb.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/topology_triggered_plan_invalidation_9ba4b3cb.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_topology_triggered_plan_invalidation_9ba4b3cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.142-rebuntu-phase-55-142-provider-triggered-plan-invalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.142-rebuntu-phase-55-142-provider-triggered-plan-invalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/provider_triggered_plan_invalidation_10d5d6ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/provider_triggered_plan_invalidation_10d5d6ee.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/provider_triggered_plan_invalidation_10d5d6ee.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_provider_triggered_plan_invalidation_10d5d6ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.143-rebuntu-phase-55-143-pre-execution-plan-revalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.143-rebuntu-phase-55-143-pre-execution-plan-revalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/pre_execution_plan_revalidation_e27b59d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/pre_execution_plan_revalidation_e27b59d2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/pre_execution_plan_revalidation_e27b59d2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/execution/test_pre_execution_plan_revalidation_e27b59d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.144-rebuntu-phase-55-144-step-by-step-revalidation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.144-rebuntu-phase-55-144-step-by-step-revalidation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/step_by_step_revalidation_70a0aa0f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/step_by_step_revalidation_70a0aa0f.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/step_by_step_revalidation_70a0aa0f.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_step_by_step_revalidation_70a0aa0f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.145-rebuntu-phase-55-145-execution-feedback-ingestion`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.145-rebuntu-phase-55-145-execution-feedback-ingestion.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/execution_feedback_ingestion_6cf44e12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/execution_feedback_ingestion_6cf44e12.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/execution_feedback_ingestion_6cf44e12.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/execution/test_execution_feedback_ingestion_6cf44e12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.146-rebuntu-phase-55-146-expected-versus-observed-comparison`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.146-rebuntu-phase-55-146-expected-versus-observed-comparison.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/expected_versus_observed_comparison_7db672fb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/expected_versus_observed_comparison_7db672fb.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/expected_versus_observed_comparison_7db672fb.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_expected_versus_observed_comparison_7db672fb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.147-rebuntu-phase-55-147-plan-deviation-detection`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.147-rebuntu-phase-55-147-plan-deviation-detection.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_deviation_detection_f1400f25/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_deviation_detection_f1400f25.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_deviation_detection_f1400f25.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_deviation_detection_f1400f25.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.148-rebuntu-phase-55-148-replanning-trigger-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.148-rebuntu-phase-55-148-replanning-trigger-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/replanning_trigger_contract_a4993416/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/replanning_trigger_contract_a4993416.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/replanning_trigger_contract_a4993416.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_replanning_trigger_contract_a4993416.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.149-rebuntu-phase-55-149-replanning-problem-construction`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.149-rebuntu-phase-55-149-replanning-problem-construction.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/replanning_problem_construction_8feb55b8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/replanning_problem_construction_8feb55b8.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/replanning_problem_construction_8feb55b8.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_replanning_problem_construction_8feb55b8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.15-rebuntu-phase-55-15-step-postcondition-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.15-rebuntu-phase-55-15-step-postcondition-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/step_postcondition_model_26912493/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/step_postcondition_model_26912493.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/step_postcondition_model_26912493.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_step_postcondition_model_26912493.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.150-rebuntu-phase-55-150-remaining-goal-computation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.150-rebuntu-phase-55-150-remaining-goal-computation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/remaining_goal_computation_04c54f4d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/remaining_goal_computation_04c54f4d.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/remaining_goal_computation_04c54f4d.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_remaining_goal_computation_04c54f4d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.151-rebuntu-phase-55-151-plan-repair`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.151-rebuntu-phase-55-151-plan-repair.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_repair_26375915/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/plan_repair_26375915.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/plan_repair_26375915.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/recovery/test_plan_repair_26375915.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.152-rebuntu-phase-55-152-partial-plan-reuse`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.152-rebuntu-phase-55-152-partial-plan-reuse.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/partial_plan_reuse_6c758a9c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/partial_plan_reuse_6c758a9c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/partial_plan_reuse_6c758a9c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_partial_plan_reuse_6c758a9c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.153-rebuntu-phase-55-153-safe-continuation-criteria`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.153-rebuntu-phase-55-153-safe-continuation-criteria.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/safe_continuation_criteria_5fadfa9f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/safe_continuation_criteria_5fadfa9f.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/safe_continuation_criteria_5fadfa9f.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_safe_continuation_criteria_5fadfa9f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.154-rebuntu-phase-55-154-stop-and-replan-semantics`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.154-rebuntu-phase-55-154-stop-and-replan-semantics.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/stop_and_replan_semantics_44c8e9fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/stop_and_replan_semantics_44c8e9fc.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/stop_and_replan_semantics_44c8e9fc.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_stop_and_replan_semantics_44c8e9fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.155-rebuntu-phase-55-155-stop-and-escalate-semantics`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.155-rebuntu-phase-55-155-stop-and-escalate-semantics.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/stop_and_escalate_semantics_835217df/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/stop_and_escalate_semantics_835217df.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/stop_and_escalate_semantics_835217df.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/lifecycle/test_stop_and_escalate_semantics_835217df.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.156-rebuntu-phase-55-156-irreversible-step-replanning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.156-rebuntu-phase-55-156-irreversible-step-replanning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/irreversible_step_replanning_a2e12f0a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/irreversible_step_replanning_a2e12f0a.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/irreversible_step_replanning_a2e12f0a.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_irreversible_step_replanning_a2e12f0a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.157-rebuntu-phase-55-157-compensation-aware-replanning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.157-rebuntu-phase-55-157-compensation-aware-replanning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/compensation_aware_replanning_200437b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/compensation_aware_replanning_200437b7.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/compensation_aware_replanning_200437b7.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/recovery/test_compensation_aware_replanning_200437b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.158-rebuntu-phase-55-158-failed-compensation-handling`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.158-rebuntu-phase-55-158-failed-compensation-handling.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/failed_compensation_handling_d21becc9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/failed_compensation_handling_d21becc9.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/failed_compensation_handling_d21becc9.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/recovery/test_failed_compensation_handling_d21becc9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.159-rebuntu-phase-55-159-ambiguous-effect-replanning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.159-rebuntu-phase-55-159-ambiguous-effect-replanning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/ambiguous_effect_replanning_2089339a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/ambiguous_effect_replanning_2089339a.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/ambiguous_effect_replanning_2089339a.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_ambiguous_effect_replanning_2089339a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.16-rebuntu-phase-55-16-step-verification-specification`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.16-rebuntu-phase-55-16-step-verification-specification.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/step_verification_specification_cdb44d45/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/step_verification_specification_cdb44d45.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/step_verification_specification_cdb44d45.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_step_verification_specification_cdb44d45.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.160-rebuntu-phase-55-160-crash-restart-plan-reconciliation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.160-rebuntu-phase-55-160-crash-restart-plan-reconciliation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/crash_restart_plan_reconciliation_13714334/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/crash_restart_plan_reconciliation_13714334.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/crash_restart_plan_reconciliation_13714334.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/recovery/test_crash_restart_plan_reconciliation_13714334.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.161-rebuntu-phase-55-161-interrupted-plan-semantics`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.161-rebuntu-phase-55-161-interrupted-plan-semantics.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/interrupted_plan_semantics_594820e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/interrupted_plan_semantics_594820e0.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/interrupted_plan_semantics_594820e0.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_interrupted_plan_semantics_594820e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.162-rebuntu-phase-55-162-stale-plan-restart-handling`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.162-rebuntu-phase-55-162-stale-plan-restart-handling.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/stale_plan_restart_handling_88e1ac9e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/stale_plan_restart_handling_88e1ac9e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/stale_plan_restart_handling_88e1ac9e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/recovery/test_stale_plan_restart_handling_88e1ac9e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.163-rebuntu-phase-55-163-reboot-spanning-plan-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.163-rebuntu-phase-55-163-reboot-spanning-plan-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/reboot_spanning_plan_boundary_80da3fea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/reboot_spanning_plan_boundary_80da3fea.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/reboot_spanning_plan_boundary_80da3fea.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_reboot_spanning_plan_boundary_80da3fea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.164-rebuntu-phase-55-164-idempotency-aware-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.164-rebuntu-phase-55-164-idempotency-aware-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/idempotency_aware_planning_250a36d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/idempotency_aware_planning_250a36d1.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/idempotency_aware_planning_250a36d1.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_idempotency_aware_planning_250a36d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.165-rebuntu-phase-55-165-retry-aware-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.165-rebuntu-phase-55-165-retry-aware-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/retry_aware_planning_9db68006/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/retry_aware_planning_9db68006.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/retry_aware_planning_9db68006.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_retry_aware_planning_9db68006.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.166-rebuntu-phase-55-166-exactly-once-fiction-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.166-rebuntu-phase-55-166-exactly-once-fiction-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/exactly_once_fiction_audit_405e9049/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/exactly_once_fiction_audit_405e9049.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/exactly_once_fiction_audit_405e9049.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_exactly_once_fiction_audit_405e9049.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.167-rebuntu-phase-55-167-toctou-planning-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.167-rebuntu-phase-55-167-toctou-planning-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/toctou_planning_audit_d6d13981/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/toctou_planning_audit_d6d13981.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/toctou_planning_audit_d6d13981.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_toctou_planning_audit_d6d13981.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.168-rebuntu-phase-55-168-target-replacement-adversarial-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.168-rebuntu-phase-55-168-target-replacement-adversarial-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/target_replacement_adversarial_audit_14d4bf98/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/target_replacement_adversarial_audit_14d4bf98.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/target_replacement_adversarial_audit_14d4bf98.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_target_replacement_adversarial_audit_14d4bf98.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.169-rebuntu-phase-55-169-stale-affordance-adversarial-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.169-rebuntu-phase-55-169-stale-affordance-adversarial-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/stale_affordance_adversarial_audit_cbb239e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/stale_affordance_adversarial_audit_cbb239e3.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/stale_affordance_adversarial_audit_cbb239e3.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_stale_affordance_adversarial_audit_cbb239e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.17-rebuntu-phase-55-17-step-resource-requirements`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.17-rebuntu-phase-55-17-step-resource-requirements.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/step_resource_requirements_f37d08de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/step_resource_requirements_f37d08de.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/step_resource_requirements_f37d08de.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_step_resource_requirements_f37d08de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.170-rebuntu-phase-55-170-resource-race-adversarial-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.170-rebuntu-phase-55-170-resource-race-adversarial-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/resource_race_adversarial_audit_e256107c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/resource_race_adversarial_audit_e256107c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/resource_race_adversarial_audit_e256107c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_resource_race_adversarial_audit_e256107c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.171-rebuntu-phase-55-171-policy-change-adversarial-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.171-rebuntu-phase-55-171-policy-change-adversarial-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/policy_change_adversarial_audit_7c8da3a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/policy_change_adversarial_audit_7c8da3a4.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/policy_change_adversarial_audit_7c8da3a4.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_policy_change_adversarial_audit_7c8da3a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.172-rebuntu-phase-55-172-security-change-adversarial-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.172-rebuntu-phase-55-172-security-change-adversarial-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/security_change_adversarial_audit_59215b28/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/security_change_adversarial_audit_59215b28.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/security_change_adversarial_audit_59215b28.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_security_change_adversarial_audit_59215b28.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.173-rebuntu-phase-55-173-provider-failure-adversarial-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.173-rebuntu-phase-55-173-provider-failure-adversarial-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/provider_failure_adversarial_audit_cac7ebab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/provider_failure_adversarial_audit_cac7ebab.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/provider_failure_adversarial_audit_cac7ebab.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_provider_failure_adversarial_audit_cac7ebab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.174-rebuntu-phase-55-174-graph-explosion-adversarial-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.174-rebuntu-phase-55-174-graph-explosion-adversarial-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/graph_explosion_adversarial_audit_e16b9846/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/graph_explosion_adversarial_audit_e16b9846.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/graph_explosion_adversarial_audit_e16b9846.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_graph_explosion_adversarial_audit_e16b9846.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.175-rebuntu-phase-55-175-planner-nontermination-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.175-rebuntu-phase-55-175-planner-nontermination-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planner_nontermination_audit_13aa3cb1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/planner_nontermination_audit_13aa3cb1.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/planner_nontermination_audit_13aa3cb1.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_planner_nontermination_audit_13aa3cb1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.176-rebuntu-phase-55-176-malicious-semantic-proposal-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.176-rebuntu-phase-55-176-malicious-semantic-proposal-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/malicious_semantic_proposal_audit_289c24aa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/malicious_semantic_proposal_audit_289c24aa.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/malicious_semantic_proposal_audit_289c24aa.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_malicious_semantic_proposal_audit_289c24aa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.177-rebuntu-phase-55-177-shell-control-regression-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.177-rebuntu-phase-55-177-shell-control-regression-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/shell_control_regression_audit_9ba9a802/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/shell_control_regression_audit_9ba9a802.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/shell_control_regression_audit_9ba9a802.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_shell_control_regression_audit_9ba9a802.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.178-rebuntu-phase-55-178-python-authority-regression-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.178-rebuntu-phase-55-178-python-authority-regression-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/python_authority_regression_audit_13236685/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/python_authority_regression_audit_13236685.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/python_authority_regression_audit_13236685.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_python_authority_regression_audit_13236685.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.179-rebuntu-phase-55-179-duplicate-planner-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.179-rebuntu-phase-55-179-duplicate-planner-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/duplicate_planner_audit_407f89c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/duplicate_planner_audit_407f89c1.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/duplicate_planner_audit_407f89c1.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_duplicate_planner_audit_407f89c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.18-rebuntu-phase-55-18-step-evidence-requirements`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.18-rebuntu-phase-55-18-step-evidence-requirements.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/step_evidence_requirements_b696b93d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/step_evidence_requirements_b696b93d.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/step_evidence_requirements_b696b93d.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_step_evidence_requirements_b696b93d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.180-rebuntu-phase-55-180-planning-memory-growth-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.180-rebuntu-phase-55-180-planning-memory-growth-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_memory_growth_audit_65025ada/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/planning_memory_growth_audit_65025ada.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/planning_memory_growth_audit_65025ada.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_planning_memory_growth_audit_65025ada.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.181-rebuntu-phase-55-181-planning-performance-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.181-rebuntu-phase-55-181-planning-performance-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_performance_audit_519ad18e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/planning_performance_audit_519ad18e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/planning_performance_audit_519ad18e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_planning_performance_audit_519ad18e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.182-rebuntu-phase-55-182-concurrency-and-sanitizer-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.182-rebuntu-phase-55-182-concurrency-and-sanitizer-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/concurrency_and_sanitizer_audit_8a54769e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/concurrency_and_sanitizer_audit_8a54769e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/concurrency_and_sanitizer_audit_8a54769e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_concurrency_and_sanitizer_audit_8a54769e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.183-rebuntu-phase-55-183-build-and-runtime-reachability-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.183-rebuntu-phase-55-183-build-and-runtime-reachability-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/build_and_runtime_reachability_audit_beec75c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/build_and_runtime_reachability_audit_beec75c9.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/build_and_runtime_reachability_audit_beec75c9.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_build_and_runtime_reachability_audit_beec75c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.184-rebuntu-phase-55-184-integration-test-matrix`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.184-rebuntu-phase-55-184-integration-test-matrix.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/integration_test_matrix_250656da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/integration_test_matrix_250656da.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/integration_test_matrix_250656da.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_integration_test_matrix_250656da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.185-rebuntu-phase-55-185-documentation-and-agents-synchronization`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.185-rebuntu-phase-55-185-documentation-and-agents-synchronization.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/documentation_and_agents_synchronization_8430afe9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/documentation_and_agents_synchronization_8430afe9.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/documentation_and_agents_synchronization_8430afe9.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_documentation_and_agents_synchronization_8430afe9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.186-rebuntu-phase-55-186-independent-planning-rediscovery`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.186-rebuntu-phase-55-186-independent-planning-rediscovery.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/independent_planning_rediscovery_6178f1d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/independent_planning_rediscovery_6178f1d5.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/independent_planning_rediscovery_6178f1d5.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_independent_planning_rediscovery_6178f1d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.187-rebuntu-phase-55-187-independent-authority-boundary-rediscovery`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.187-rebuntu-phase-55-187-independent-authority-boundary-rediscovery.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/independent_authority_boundary_rediscovery_2133ff7e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/resolution/independent_authority_boundary_rediscovery_2133ff7e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/resolution/independent_authority_boundary_rediscovery_2133ff7e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/resolution/test_independent_authority_boundary_rediscovery_2133ff7e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.188-rebuntu-phase-55-188-fixed-point-architecture-audit`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.188-rebuntu-phase-55-188-fixed-point-architecture-audit.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/fixed_point_architecture_audit_3be70199/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/fixed_point_architecture_audit_3be70199.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/fixed_point_architecture_audit_3be70199.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_fixed_point_architecture_audit_3be70199.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.189-rebuntu-phase-55-189-phase-55-final-closure`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.189-rebuntu-phase-55-189-phase-55-final-closure.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_55_final_closure_97d92057/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/phase_55_final_closure_97d92057.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/phase_55_final_closure_97d92057.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_phase_55_final_closure_97d92057.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.19-rebuntu-phase-55-19-step-compensation-references`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.19-rebuntu-phase-55-19-step-compensation-references.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/step_compensation_references_9dd649bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/step_compensation_references_9dd649bb.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/step_compensation_references_9dd649bb.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/recovery/test_step_compensation_references_9dd649bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.2-rebuntu-phase-55-2-goal-identity-and-scope`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.2-rebuntu-phase-55-2-goal-identity-and-scope.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/goal_identity_and_scope_56953c7f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/goal_identity_and_scope_56953c7f.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/goal_identity_and_scope_56953c7f.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/contracts/test_goal_identity_and_scope_56953c7f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.20-rebuntu-phase-55-20-phase-54-capability-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.20-rebuntu-phase-55-20-phase-54-capability-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_54_capability_integration_7c54959f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_54_capability_integration_7c54959f.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_54_capability_integration_7c54959f.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_54_capability_integration_7c54959f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.21-rebuntu-phase-55-21-phase-54-affordance-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.21-rebuntu-phase-55-21-phase-54-affordance-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_54_affordance_integration_eee6c7ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_54_affordance_integration_eee6c7ab.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/phase_54_affordance_integration_eee6c7ab.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_phase_54_affordance_integration_eee6c7ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.22-rebuntu-phase-55-22-prerequisite-graph-expansion`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.22-rebuntu-phase-55-22-prerequisite-graph-expansion.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/prerequisite_graph_expansion_54d0c185/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/prerequisite_graph_expansion_54d0c185.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/prerequisite_graph_expansion_54d0c185.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_prerequisite_graph_expansion_54d0c185.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.23-rebuntu-phase-55-23-prerequisite-to-plan-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.23-rebuntu-phase-55-23-prerequisite-to-plan-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/prerequisite_to_plan_boundary_462ac62c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/prerequisite_to_plan_boundary_462ac62c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/prerequisite_to_plan_boundary_462ac62c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_prerequisite_to_plan_boundary_462ac62c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.24-rebuntu-phase-55-24-operation-catalog-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.24-rebuntu-phase-55-24-operation-catalog-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/operation_catalog_integration_74bd96d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/operation_catalog_integration_74bd96d6.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/operation_catalog_integration_74bd96d6.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_operation_catalog_integration_74bd96d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.25-rebuntu-phase-55-25-state-transition-catalog-integration`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.25-rebuntu-phase-55-25-state-transition-catalog-integration.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/state_transition_catalog_integration_530f3bb4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/state_transition_catalog_integration_530f3bb4.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/state_transition_catalog_integration_530f3bb4.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_state_transition_catalog_integration_530f3bb4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.26-rebuntu-phase-55-26-plan-dependency-graph`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.26-rebuntu-phase-55-26-plan-dependency-graph.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_dependency_graph_87291002/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_dependency_graph_87291002.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_dependency_graph_87291002.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_dependency_graph_87291002.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.27-rebuntu-phase-55-27-plan-dag-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.27-rebuntu-phase-55-27-plan-dag-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_dag_validation_6d512600/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_dag_validation_6d512600.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_dag_validation_6d512600.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_dag_validation_6d512600.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.28-rebuntu-phase-55-28-plan-cycle-detection`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.28-rebuntu-phase-55-28-plan-cycle-detection.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_cycle_detection_369f2d51/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_cycle_detection_369f2d51.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_cycle_detection_369f2d51.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_cycle_detection_369f2d51.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.29-rebuntu-phase-55-29-plan-ordering-constraints`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.29-rebuntu-phase-55-29-plan-ordering-constraints.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_ordering_constraints_44471b12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_ordering_constraints_44471b12.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_ordering_constraints_44471b12.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_ordering_constraints_44471b12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.3-rebuntu-phase-55-3-goal-predicate-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.3-rebuntu-phase-55-3-goal-predicate-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/goal_predicate_model_98bcd138/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/goal_predicate_model_98bcd138.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/contracts/goal_predicate_model_98bcd138.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/contracts/test_goal_predicate_model_98bcd138.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.30-rebuntu-phase-55-30-partial-order-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.30-rebuntu-phase-55-30-partial-order-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/partial_order_planning_46bd0331/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/partial_order_planning_46bd0331.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/partial_order_planning_46bd0331.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_partial_order_planning_46bd0331.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.31-rebuntu-phase-55-31-sequential-plan-synthesis`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.31-rebuntu-phase-55-31-sequential-plan-synthesis.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/sequential_plan_synthesis_ba202011/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/sequential_plan_synthesis_ba202011.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/sequential_plan_synthesis_ba202011.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_sequential_plan_synthesis_ba202011.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.32-rebuntu-phase-55-32-parallelizable-step-detection`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.32-rebuntu-phase-55-32-parallelizable-step-detection.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/parallelizable_step_detection_ae4d716c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/parallelizable_step_detection_ae4d716c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/parallelizable_step_detection_ae4d716c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_parallelizable_step_detection_ae4d716c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.33-rebuntu-phase-55-33-concurrency-conflict-detection`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.33-rebuntu-phase-55-33-concurrency-conflict-detection.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/concurrency_conflict_detection_f1d12aaa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/concurrency_conflict_detection_f1d12aaa.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/concurrency_conflict_detection_f1d12aaa.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_concurrency_conflict_detection_f1d12aaa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.34-rebuntu-phase-55-34-resource-aware-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.34-rebuntu-phase-55-34-resource-aware-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/resource_aware_planning_cb391276/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/resource_aware_planning_cb391276.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/resource_aware_planning_cb391276.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_resource_aware_planning_cb391276.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.35-rebuntu-phase-55-35-resource-contention-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.35-rebuntu-phase-55-35-resource-contention-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/resource_contention_planning_b1ca8bbb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/resource_contention_planning_b1ca8bbb.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/resource_contention_planning_b1ca8bbb.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_resource_contention_planning_b1ca8bbb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.36-rebuntu-phase-55-36-temporal-planning-foundation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.36-rebuntu-phase-55-36-temporal-planning-foundation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/temporal_planning_foundation_6bf2d156/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/temporal_planning_foundation_6bf2d156.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/temporal_planning_foundation_6bf2d156.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_temporal_planning_foundation_6bf2d156.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.37-rebuntu-phase-55-37-deadline-aware-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.37-rebuntu-phase-55-37-deadline-aware-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/deadline_aware_planning_caf41c12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/deadline_aware_planning_caf41c12.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/deadline_aware_planning_caf41c12.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_deadline_aware_planning_caf41c12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.38-rebuntu-phase-55-38-schedule-aware-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.38-rebuntu-phase-55-38-schedule-aware-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/schedule_aware_planning_ced71226/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/schedule_aware_planning_ced71226.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/schedule_aware_planning_ced71226.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_schedule_aware_planning_ced71226.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.39-rebuntu-phase-55-39-service-state-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.39-rebuntu-phase-55-39-service-state-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/service_state_planning_0ec06e5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/service_state_planning_0ec06e5d.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/service_state_planning_0ec06e5d.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_service_state_planning_0ec06e5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.4-rebuntu-phase-55-4-desired-state-representation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.4-rebuntu-phase-55-4-desired-state-representation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/desired_state_representation_84e2fecf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/desired_state_representation_84e2fecf.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/desired_state_representation_84e2fecf.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/lifecycle/test_desired_state_representation_84e2fecf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.40-rebuntu-phase-55-40-storage-state-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.40-rebuntu-phase-55-40-storage-state-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/storage_state_planning_04633a62/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/storage_state_planning_04633a62.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/storage_state_planning_04633a62.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_storage_state_planning_04633a62.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.41-rebuntu-phase-55-41-network-state-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.41-rebuntu-phase-55-41-network-state-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/network_state_planning_d7b22ec0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/network_state_planning_d7b22ec0.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/network_state_planning_d7b22ec0.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_network_state_planning_d7b22ec0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.42-rebuntu-phase-55-42-gpu-and-accelerator-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.42-rebuntu-phase-55-42-gpu-and-accelerator-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/gpu_and_accelerator_planning_e080cdbb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/gpu_and_accelerator_planning_e080cdbb.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/gpu_and_accelerator_planning_e080cdbb.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_gpu_and_accelerator_planning_e080cdbb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.43-rebuntu-phase-55-43-process-and-workload-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.43-rebuntu-phase-55-43-process-and-workload-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/process_and_workload_planning_0c5ef37b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/process_and_workload_planning_0c5ef37b.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/process_and_workload_planning_0c5ef37b.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_process_and_workload_planning_0c5ef37b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.44-rebuntu-phase-55-44-user-and-session-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.44-rebuntu-phase-55-44-user-and-session-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/user_and_session_planning_203d3669/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/user_and_session_planning_203d3669.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/user_and_session_planning_203d3669.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_user_and_session_planning_203d3669.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.45-rebuntu-phase-55-45-configuration-state-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.45-rebuntu-phase-55-45-configuration-state-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/configuration_state_planning_77dbfd9e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/configuration_state_planning_77dbfd9e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/configuration_state_planning_77dbfd9e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_configuration_state_planning_77dbfd9e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.46-rebuntu-phase-55-46-privilege-requirement-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.46-rebuntu-phase-55-46-privilege-requirement-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/privilege_requirement_planning_dcb0080d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/privilege_requirement_planning_dcb0080d.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/privilege_requirement_planning_dcb0080d.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_privilege_requirement_planning_dcb0080d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.47-rebuntu-phase-55-47-secret-reference-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.47-rebuntu-phase-55-47-secret-reference-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/secret_reference_planning_3596bcb7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/secret_reference_planning_3596bcb7.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/secret_reference_planning_3596bcb7.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_secret_reference_planning_3596bcb7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.48-rebuntu-phase-55-48-alternative-plan-generation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.48-rebuntu-phase-55-48-alternative-plan-generation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/alternative_plan_generation_fdbecac0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/alternative_plan_generation_fdbecac0.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/alternative_plan_generation_fdbecac0.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_alternative_plan_generation_fdbecac0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.49-rebuntu-phase-55-49-provider-alternative-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.49-rebuntu-phase-55-49-provider-alternative-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/provider_alternative_planning_d611a54c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/provider_alternative_planning_d611a54c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/integration/provider_alternative_planning_d611a54c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/integration/test_provider_alternative_planning_d611a54c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.5-rebuntu-phase-55-5-current-versus-desired-state-delta`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.5-rebuntu-phase-55-5-current-versus-desired-state-delta.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/current_versus_desired_state_delta_3bababa2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/current_versus_desired_state_delta_3bababa2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/current_versus_desired_state_delta_3bababa2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/lifecycle/test_current_versus_desired_state_delta_3bababa2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.50-rebuntu-phase-55-50-capability-alternative-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.50-rebuntu-phase-55-50-capability-alternative-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/capability_alternative_planning_0f5d6efa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/capability_alternative_planning_0f5d6efa.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/capability_alternative_planning_0f5d6efa.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_capability_alternative_planning_0f5d6efa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.51-rebuntu-phase-55-51-prerequisite-alternative-planning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.51-rebuntu-phase-55-51-prerequisite-alternative-planning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/prerequisite_alternative_planning_e927b646/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/prerequisite_alternative_planning_e927b646.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/prerequisite_alternative_planning_e927b646.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_prerequisite_alternative_planning_e927b646.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.52-rebuntu-phase-55-52-plan-branching-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.52-rebuntu-phase-55-52-plan-branching-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_branching_model_e2304bc2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_branching_model_e2304bc2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_branching_model_e2304bc2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_branching_model_e2304bc2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.53-rebuntu-phase-55-53-conditional-plan-steps`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.53-rebuntu-phase-55-53-conditional-plan-steps.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/conditional_plan_steps_ce9396fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/conditional_plan_steps_ce9396fe.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/conditional_plan_steps_ce9396fe.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_conditional_plan_steps_ce9396fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.54-rebuntu-phase-55-54-bounded-loop-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.54-rebuntu-phase-55-54-bounded-loop-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/bounded_loop_boundary_011e7fc8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/bounded_loop_boundary_011e7fc8.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/bounded_loop_boundary_011e7fc8.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_bounded_loop_boundary_011e7fc8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.55-rebuntu-phase-55-55-subplan-composition`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.55-rebuntu-phase-55-55-subplan-composition.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/subplan_composition_87b835c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/subplan_composition_87b835c1.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/subplan_composition_87b835c1.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_subplan_composition_87b835c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.56-rebuntu-phase-55-56-plan-decomposition`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.56-rebuntu-phase-55-56-plan-decomposition.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_decomposition_bb8f2f51/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_decomposition_bb8f2f51.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_decomposition_bb8f2f51.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_decomposition_bb8f2f51.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.57-rebuntu-phase-55-57-hierarchical-planning-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.57-rebuntu-phase-55-57-hierarchical-planning-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/hierarchical_planning_boundary_9ac4e32e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/hierarchical_planning_boundary_9ac4e32e.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/hierarchical_planning_boundary_9ac4e32e.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_hierarchical_planning_boundary_9ac4e32e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.58-rebuntu-phase-55-58-planning-search-space-bounds`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.58-rebuntu-phase-55-58-planning-search-space-bounds.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_search_space_bounds_a32120b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_search_space_bounds_a32120b0.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_search_space_bounds_a32120b0.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_planning_search_space_bounds_a32120b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.59-rebuntu-phase-55-59-planning-depth-bounds`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.59-rebuntu-phase-55-59-planning-depth-bounds.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_depth_bounds_2eeaae9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_depth_bounds_2eeaae9b.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_depth_bounds_2eeaae9b.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_planning_depth_bounds_2eeaae9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.6-rebuntu-phase-55-6-planning-problem-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.6-rebuntu-phase-55-6-planning-problem-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_problem_contract_1ed06103/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_problem_contract_1ed06103.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_problem_contract_1ed06103.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_planning_problem_contract_1ed06103.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.60-rebuntu-phase-55-60-planning-breadth-bounds`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.60-rebuntu-phase-55-60-planning-breadth-bounds.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_breadth_bounds_4c61aabc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_breadth_bounds_4c61aabc.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_breadth_bounds_4c61aabc.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_planning_breadth_bounds_4c61aabc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.61-rebuntu-phase-55-61-planning-deadline-and-cancellation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.61-rebuntu-phase-55-61-planning-deadline-and-cancellation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_deadline_and_cancellation_dffdee67/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_deadline_and_cancellation_dffdee67.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_deadline_and_cancellation_dffdee67.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_planning_deadline_and_cancellation_dffdee67.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.62-rebuntu-phase-55-62-planning-resource-budget`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.62-rebuntu-phase-55-62-planning-resource-budget.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_resource_budget_e8c9e5a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_resource_budget_e8c9e5a7.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_resource_budget_e8c9e5a7.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_planning_resource_budget_e8c9e5a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.63-rebuntu-phase-55-63-plan-cost-vector-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.63-rebuntu-phase-55-63-plan-cost-vector-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_cost_vector_model_5ec60c07/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_cost_vector_model_5ec60c07.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_cost_vector_model_5ec60c07.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_cost_vector_model_5ec60c07.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.64-rebuntu-phase-55-64-mutation-count-metric`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.64-rebuntu-phase-55-64-mutation-count-metric.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/mutation_count_metric_fa714d94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/mutation_count_metric_fa714d94.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/mutation_count_metric_fa714d94.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_mutation_count_metric_fa714d94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.65-rebuntu-phase-55-65-restart-and-reboot-cost-metric`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.65-rebuntu-phase-55-65-restart-and-reboot-cost-metric.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/restart_and_reboot_cost_metric_b6489e25/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/restart_and_reboot_cost_metric_b6489e25.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/recovery/restart_and_reboot_cost_metric_b6489e25.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/recovery/test_restart_and_reboot_cost_metric_b6489e25.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.66-rebuntu-phase-55-66-resource-cost-metric`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.66-rebuntu-phase-55-66-resource-cost-metric.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/resource_cost_metric_c2e9af59/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/resource_cost_metric_c2e9af59.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/resource_cost_metric_c2e9af59.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_resource_cost_metric_c2e9af59.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.67-rebuntu-phase-55-67-temporal-cost-metric`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.67-rebuntu-phase-55-67-temporal-cost-metric.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/temporal_cost_metric_a24db7d3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/temporal_cost_metric_a24db7d3.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/temporal_cost_metric_a24db7d3.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_temporal_cost_metric_a24db7d3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.68-rebuntu-phase-55-68-uncertainty-cost-metric`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.68-rebuntu-phase-55-68-uncertainty-cost-metric.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/uncertainty_cost_metric_b1f8f3ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/uncertainty_cost_metric_b1f8f3ab.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/uncertainty_cost_metric_b1f8f3ab.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_uncertainty_cost_metric_b1f8f3ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.69-rebuntu-phase-55-69-reversibility-metric`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.69-rebuntu-phase-55-69-reversibility-metric.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/reversibility_metric_9a63dbe7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/reversibility_metric_9a63dbe7.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/observability/reversibility_metric_9a63dbe7.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/observability/test_reversibility_metric_9a63dbe7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.7-rebuntu-phase-55-7-planning-context-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.7-rebuntu-phase-55-7-planning-context-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/planning_context_contract_8871c4f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_context_contract_8871c4f2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/planning_context_contract_8871c4f2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_planning_context_contract_8871c4f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.70-rebuntu-phase-55-70-irreversibility-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.70-rebuntu-phase-55-70-irreversibility-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/irreversibility_boundary_c94de2f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/irreversibility_boundary_c94de2f0.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/irreversibility_boundary_c94de2f0.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_irreversibility_boundary_c94de2f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.71-rebuntu-phase-55-71-risk-metadata-without-authorization`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.71-rebuntu-phase-55-71-risk-metadata-without-authorization.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/risk_metadata_without_authorization_c6220185/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/risk_metadata_without_authorization_c6220185.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/risk_metadata_without_authorization_c6220185.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_risk_metadata_without_authorization_c6220185.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.72-rebuntu-phase-55-72-plan-comparison-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.72-rebuntu-phase-55-72-plan-comparison-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_comparison_contract_f2635d84/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_comparison_contract_f2635d84.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_comparison_contract_f2635d84.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_comparison_contract_f2635d84.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.73-rebuntu-phase-55-73-plan-dominance-and-pareto-frontier`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.73-rebuntu-phase-55-73-plan-dominance-and-pareto-frontier.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_dominance_and_pareto_frontier_a16ad03b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_dominance_and_pareto_frontier_a16ad03b.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_dominance_and_pareto_frontier_a16ad03b.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_dominance_and_pareto_frontier_a16ad03b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.74-rebuntu-phase-55-74-plan-ranking-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.74-rebuntu-phase-55-74-plan-ranking-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_ranking_boundary_f86ad517/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_ranking_boundary_f86ad517.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_ranking_boundary_f86ad517.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_ranking_boundary_f86ad517.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.75-rebuntu-phase-55-75-heuristic-planning-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.75-rebuntu-phase-55-75-heuristic-planning-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/heuristic_planning_boundary_3581c9ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/heuristic_planning_boundary_3581c9ae.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/heuristic_planning_boundary_3581c9ae.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_heuristic_planning_boundary_3581c9ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.76-rebuntu-phase-55-76-semantic-proposer-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.76-rebuntu-phase-55-76-semantic-proposer-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/semantic_proposer_boundary_067b792a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/semantic_proposer_boundary_067b792a.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/semantic_proposer_boundary_067b792a.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_semantic_proposer_boundary_067b792a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.77-rebuntu-phase-55-77-model-proposed-plan-ingestion`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.77-rebuntu-phase-55-77-model-proposed-plan-ingestion.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/model_proposed_plan_ingestion_6b6a96c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/model_proposed_plan_ingestion_6b6a96c5.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/model_proposed_plan_ingestion_6b6a96c5.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_model_proposed_plan_ingestion_6b6a96c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.78-rebuntu-phase-55-78-deterministic-plan-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.78-rebuntu-phase-55-78-deterministic-plan-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/deterministic_plan_validation_0122ea23/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/deterministic_plan_validation_0122ea23.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/deterministic_plan_validation_0122ea23.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_deterministic_plan_validation_0122ea23.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.79-rebuntu-phase-55-79-plan-schema-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.79-rebuntu-phase-55-79-plan-schema-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_schema_validation_a6bd9a85/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_schema_validation_a6bd9a85.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_schema_validation_a6bd9a85.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_schema_validation_a6bd9a85.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.8-rebuntu-phase-55-8-candidate-plan-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.8-rebuntu-phase-55-8-candidate-plan-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/candidate_plan_contract_d7f4cb5c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/candidate_plan_contract_d7f4cb5c.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/candidate_plan_contract_d7f4cb5c.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_candidate_plan_contract_d7f4cb5c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.80-rebuntu-phase-55-80-plan-target-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.80-rebuntu-phase-55-80-plan-target-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_target_validation_1b499db5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_target_validation_1b499db5.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_target_validation_1b499db5.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_target_validation_1b499db5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.81-rebuntu-phase-55-81-plan-identity-freshness-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.81-rebuntu-phase-55-81-plan-identity-freshness-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_identity_freshness_validation_7d21f9b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_identity_freshness_validation_7d21f9b7.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_identity_freshness_validation_7d21f9b7.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_identity_freshness_validation_7d21f9b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.82-rebuntu-phase-55-82-plan-precondition-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.82-rebuntu-phase-55-82-plan-precondition-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_precondition_validation_2e037260/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_precondition_validation_2e037260.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_precondition_validation_2e037260.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_precondition_validation_2e037260.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.83-rebuntu-phase-55-83-plan-capability-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.83-rebuntu-phase-55-83-plan-capability-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_capability_validation_75729a3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_capability_validation_75729a3f.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_capability_validation_75729a3f.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_capability_validation_75729a3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.84-rebuntu-phase-55-84-plan-affordance-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.84-rebuntu-phase-55-84-plan-affordance-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_affordance_validation_9b510962/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_affordance_validation_9b510962.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_affordance_validation_9b510962.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_affordance_validation_9b510962.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.85-rebuntu-phase-55-85-plan-resource-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.85-rebuntu-phase-55-85-plan-resource-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_resource_validation_c8cccc04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_resource_validation_c8cccc04.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_resource_validation_c8cccc04.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_resource_validation_c8cccc04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.86-rebuntu-phase-55-86-plan-temporal-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.86-rebuntu-phase-55-86-plan-temporal-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_temporal_validation_03b89c98/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_temporal_validation_03b89c98.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_temporal_validation_03b89c98.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_temporal_validation_03b89c98.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.87-rebuntu-phase-55-87-plan-privilege-validation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.87-rebuntu-phase-55-87-plan-privilege-validation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_privilege_validation_2975ed61/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/plan_privilege_validation_2975ed61.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/plan_privilege_validation_2975ed61.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_plan_privilege_validation_2975ed61.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.88-rebuntu-phase-55-88-phase-47-task-policy-validation-seam`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.88-rebuntu-phase-55-88-phase-47-task-policy-validation-seam.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_47_task_policy_validation_seam_43c22aa2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/phase_47_task_policy_validation_seam_43c22aa2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/phase_47_task_policy_validation_seam_43c22aa2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_phase_47_task_policy_validation_seam_43c22aa2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.89-rebuntu-phase-55-89-phase-53-mandatory-security-validation-seam`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.89-rebuntu-phase-55-89-phase-53-mandatory-security-validation-seam.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_53_mandatory_security_validation_seam_2ba791ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/phase_53_mandatory_security_validation_seam_2ba791ce.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/phase_53_mandatory_security_validation_seam_2ba791ce.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_phase_53_mandatory_security_validation_seam_2ba791ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.9-rebuntu-phase-55-9-plan-identity-and-versioning`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.9-rebuntu-phase-55-9-plan-identity-and-versioning.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_identity_and_versioning_bc3f72f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_identity_and_versioning_bc3f72f2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_identity_and_versioning_bc3f72f2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_identity_and_versioning_bc3f72f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.90-rebuntu-phase-55-90-phase-45-control-plane-handoff`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.90-rebuntu-phase-55-90-phase-45-control-plane-handoff.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/phase_45_control_plane_handoff_473fdae2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/phase_45_control_plane_handoff_473fdae2.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/phase_45_control_plane_handoff_473fdae2.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_phase_45_control_plane_handoff_473fdae2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.91-rebuntu-phase-55-91-plan-is-not-authorization-enforcement`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.91-rebuntu-phase-55-91-plan-is-not-authorization-enforcement.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_is_not_authorization_enforcement_f8740a91/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/plan_is_not_authorization_enforcement_f8740a91.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/security/plan_is_not_authorization_enforcement_f8740a91.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/security/test_plan_is_not_authorization_enforcement_f8740a91.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.92-rebuntu-phase-55-92-goal-is-not-command-enforcement`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.92-rebuntu-phase-55-92-goal-is-not-command-enforcement.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/goal_is_not_command_enforcement_cd7b1e92/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/goal_is_not_command_enforcement_cd7b1e92.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/execution/goal_is_not_command_enforcement_cd7b1e92.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/execution/test_goal_is_not_command_enforcement_cd7b1e92.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.93-rebuntu-phase-55-93-prerequisite-graph-is-not-plan-enforcement`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.93-rebuntu-phase-55-93-prerequisite-graph-is-not-plan-enforcement.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/prerequisite_graph_is_not_plan_enforcement_e694d6c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/prerequisite_graph_is_not_plan_enforcement_e694d6c4.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/prerequisite_graph_is_not_plan_enforcement_e694d6c4.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_prerequisite_graph_is_not_plan_enforcement_e694d6c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.94-rebuntu-phase-55-94-model-plan-is-not-authority-enforcement`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.94-rebuntu-phase-55-94-model-plan-is-not-authority-enforcement.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/model_plan_is_not_authority_enforcement_e3e4fcad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/model_plan_is_not_authority_enforcement_e3e4fcad.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/model_plan_is_not_authority_enforcement_e3e4fcad.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_model_plan_is_not_authority_enforcement_e3e4fcad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.95-rebuntu-phase-55-95-dry-planning-contract`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.95-rebuntu-phase-55-95-dry-planning-contract.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/dry_planning_contract_fbf91acd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/dry_planning_contract_fbf91acd.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/dry_planning_contract_fbf91acd.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_dry_planning_contract_fbf91acd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.96-rebuntu-phase-55-96-plan-simulation-model`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.96-rebuntu-phase-55-96-plan-simulation-model.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/plan_simulation_model_3a77c662/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_simulation_model_3a77c662.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/planning/plan_simulation_model_3a77c662.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/planning/test_plan_simulation_model_3a77c662.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.97-rebuntu-phase-55-97-simulation-evidence-boundary`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.97-rebuntu-phase-55-97-simulation-evidence-boundary.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/simulation_evidence_boundary_b9260090/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/simulation_evidence_boundary_b9260090.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/verification/simulation_evidence_boundary_b9260090.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/verification/test_simulation_evidence_boundary_b9260090.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.98-rebuntu-phase-55-98-simulation-uncertainty-propagation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.98-rebuntu-phase-55-98-simulation-uncertainty-propagation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/simulation_uncertainty_propagation_18dc1b67/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/simulation_uncertainty_propagation_18dc1b67.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/requirements/simulation_uncertainty_propagation_18dc1b67.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/requirements/test_simulation_uncertainty_propagation_18dc1b67.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `55.99-rebuntu-phase-55-99-predicted-state-representation`
- **Source:** `.phases/phases/phase-55-goal-directed-planning-plan-synthesis-replanning/prompts/55.99-rebuntu-phase-55-99-predicted-state-representation.md`
- **Structural package:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_packages/verification/predicted_state_representation_39787de9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/predicted_state_representation_39787de9.hpp`, `src/planning/goal-directed-planning-plan-synthesis-replanning/subtask_targets/lifecycle/predicted_state_representation_39787de9.cpp`
- **Structural test target:** `tests/structural-closure/planning/goal-directed-planning-plan-synthesis-replanning/lifecycle/test_predicted_state_representation_39787de9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

