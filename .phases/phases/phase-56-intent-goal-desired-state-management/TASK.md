# Phase 56 — Intent Goal Desired State Management — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-56-intent-goal-desired-state-management/`
- Primary prompt location: `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/`
- Prompt/specification Markdown files currently present: **50**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 50 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_56` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 56 — Intent, Goal & Desired-State Management System — FULL 2000+ LINE PROMPTS
- Rebuntu — Phase 56.32: Goal persistence and restart
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
- Canonical skeleton: `src/semantics/intent-goal-desired-state-management/`
- Structural files: `src/semantics/intent-goal-desired-state-management/component.hpp`, `src/semantics/intent-goal-desired-state-management/component.cpp`, `src/semantics/intent-goal-desired-state-management/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** SKELETON
- **Implementation depth:** **1/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- No implementation evidence was matched automatically; inspect `src/` before concluding that the requirement is absent.

### Existing test evidence
- `tests/native/test_capability_state.cpp`
- `tests/native/test_state_provider.cpp`

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

- Structural skeleton materialized at `src/semantics/intent-goal-desired-state-management/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/semantics/intent-goal-desired-state-management/model/`
- `src/semantics/intent-goal-desired-state-management/contracts/`
- `src/semantics/intent-goal-desired-state-management/integration/`
- `src/semantics/intent-goal-desired-state-management/verification/`
- `src/semantics/intent-goal-desired-state-management/lifecycle/`
- `src/semantics/intent-goal-desired-state-management/state/`
- `src/semantics/intent-goal-desired-state-management/execution/`
- `src/semantics/intent-goal-desired-state-management/transactions/`
- `src/semantics/intent-goal-desired-state-management/events/`
- `src/semantics/intent-goal-desired-state-management/scheduling/`
- `src/semantics/intent-goal-desired-state-management/recovery/`
- `src/semantics/intent-goal-desired-state-management/principals/`
- `src/semantics/intent-goal-desired-state-management/groups/`
- `src/semantics/intent-goal-desired-state-management/roles/`
- `src/semantics/intent-goal-desired-state-management/resolution/`
- `src/semantics/intent-goal-desired-state-management/authorization/`
- `src/semantics/intent-goal-desired-state-management/credentials/`
- `src/semantics/intent-goal-desired-state-management/policy/`



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

### `56.0-rebuntu-phase-56-0-intent-lifecycle`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.0-rebuntu-phase-56-0-intent-lifecycle.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/intent_lifecycle_8431468b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/lifecycle/intent_lifecycle_8431468b.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/lifecycle/intent_lifecycle_8431468b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/lifecycle/test_intent_lifecycle_8431468b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.1-rebuntu-phase-56-1-goal-lifecycle`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.1-rebuntu-phase-56-1-goal-lifecycle.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_lifecycle_d34224cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/lifecycle/goal_lifecycle_d34224cf.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/lifecycle/goal_lifecycle_d34224cf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/lifecycle/test_goal_lifecycle_d34224cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.10-rebuntu-phase-56-10-goal-suspension-and-resumption`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.10-rebuntu-phase-56-10-goal-suspension-and-resumption.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_suspension_and_resumption_8fa642e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_suspension_and_resumption_8fa642e4.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_suspension_and_resumption_8fa642e4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_suspension_and_resumption_8fa642e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.11-rebuntu-phase-56-11-goal-cancellation`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.11-rebuntu-phase-56-11-goal-cancellation.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_cancellation_62af39be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_cancellation_62af39be.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_cancellation_62af39be.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_cancellation_62af39be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.12-rebuntu-phase-56-12-goal-satisfaction`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.12-rebuntu-phase-56-12-goal-satisfaction.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_satisfaction_53c16fdd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_satisfaction_53c16fdd.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_satisfaction_53c16fdd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_satisfaction_53c16fdd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.13-rebuntu-phase-56-13-goal-failure`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.13-rebuntu-phase-56-13-goal-failure.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_failure_a3961d71/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_failure_a3961d71.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_failure_a3961d71.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_failure_a3961d71.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.14-rebuntu-phase-56-14-goal-expiry`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.14-rebuntu-phase-56-14-goal-expiry.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_expiry_a6eeb9ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_expiry_a6eeb9ca.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_expiry_a6eeb9ca.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_expiry_a6eeb9ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.15-rebuntu-phase-56-15-persistent-goals`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.15-rebuntu-phase-56-15-persistent-goals.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/persistent_goals_2831cb7b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/persistence/persistent_goals_2831cb7b.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/persistence/persistent_goals_2831cb7b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/persistence/test_persistent_goals_2831cb7b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.16-rebuntu-phase-56-16-ephemeral-goals`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.16-rebuntu-phase-56-16-ephemeral-goals.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/ephemeral_goals_401051c0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/ephemeral_goals_401051c0.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/ephemeral_goals_401051c0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_ephemeral_goals_401051c0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.17-rebuntu-phase-56-17-operator-owned-goals`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.17-rebuntu-phase-56-17-operator-owned-goals.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/operator_owned_goals_33ca3442/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/operator_owned_goals_33ca3442.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/operator_owned_goals_33ca3442.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_operator_owned_goals_33ca3442.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.18-rebuntu-phase-56-18-system-maintenance-goals`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.18-rebuntu-phase-56-18-system-maintenance-goals.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/system_maintenance_goals_36dbdff1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/system_maintenance_goals_36dbdff1.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/system_maintenance_goals_36dbdff1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_system_maintenance_goals_36dbdff1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.19-rebuntu-phase-56-19-distributed-goals`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.19-rebuntu-phase-56-19-distributed-goals.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/distributed_goals_da42bdad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/distributed_goals_da42bdad.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/distributed_goals_da42bdad.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_distributed_goals_da42bdad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.2-rebuntu-phase-56-2-goal-identity`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.2-rebuntu-phase-56-2-goal-identity.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_identity_3cef8c4b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/contracts/goal_identity_3cef8c4b.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/contracts/goal_identity_3cef8c4b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/contracts/test_goal_identity_3cef8c4b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.20-rebuntu-phase-56-20-goal-provenance`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.20-rebuntu-phase-56-20-goal-provenance.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_provenance_e45c581c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_provenance_e45c581c.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_provenance_e45c581c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_provenance_e45c581c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.21-rebuntu-phase-56-21-goal-freshness`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.21-rebuntu-phase-56-21-goal-freshness.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_freshness_7b1fcb1d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_freshness_7b1fcb1d.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_freshness_7b1fcb1d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_freshness_7b1fcb1d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.22-rebuntu-phase-56-22-goal-uncertainty`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.22-rebuntu-phase-56-22-goal-uncertainty.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_uncertainty_b540a563/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_uncertainty_b540a563.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_uncertainty_b540a563.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_uncertainty_b540a563.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.23-rebuntu-phase-56-23-goal-policy-boundary`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.23-rebuntu-phase-56-23-goal-policy-boundary.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_policy_boundary_9a914f19/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/security/goal_policy_boundary_9a914f19.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/security/goal_policy_boundary_9a914f19.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/security/test_goal_policy_boundary_9a914f19.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.24-rebuntu-phase-56-24-goal-security-boundary`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.24-rebuntu-phase-56-24-goal-security-boundary.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_security_boundary_cba2932c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/security/goal_security_boundary_cba2932c.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/security/goal_security_boundary_cba2932c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/security/test_goal_security_boundary_cba2932c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.25-rebuntu-phase-56-25-goal-to-planning-handoff`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.25-rebuntu-phase-56-25-goal-to-planning-handoff.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_to_planning_handoff_661c6367/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/planning/goal_to_planning_handoff_661c6367.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/planning/goal_to_planning_handoff_661c6367.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/planning/test_goal_to_planning_handoff_661c6367.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.26-rebuntu-phase-56-26-goal-to-reconciliation-handoff`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.26-rebuntu-phase-56-26-goal-to-reconciliation-handoff.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_to_reconciliation_handoff_7b1f6677/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_to_reconciliation_handoff_7b1f6677.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_to_reconciliation_handoff_7b1f6677.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_to_reconciliation_handoff_7b1f6677.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.27-rebuntu-phase-56-27-goal-explainability`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.27-rebuntu-phase-56-27-goal-explainability.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_explainability_93c9c36d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/observability/goal_explainability_93c9c36d.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/observability/goal_explainability_93c9c36d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/observability/test_goal_explainability_93c9c36d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.28-rebuntu-phase-56-28-goal-cli`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.28-rebuntu-phase-56-28-goal-cli.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_cli_1f3beb4d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_cli_1f3beb4d.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_cli_1f3beb4d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_cli_1f3beb4d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.29-rebuntu-phase-56-29-goal-gui`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.29-rebuntu-phase-56-29-goal-gui.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_gui_40fd1590/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_gui_40fd1590.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_gui_40fd1590.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_gui_40fd1590.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.3-rebuntu-phase-56-3-desired-state-model`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.3-rebuntu-phase-56-3-desired-state-model.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/desired_state_model_8685ca5a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/lifecycle/desired_state_model_8685ca5a.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/lifecycle/desired_state_model_8685ca5a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/lifecycle/test_desired_state_model_8685ca5a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.30-rebuntu-phase-56-30-natural-language-goal-ingestion`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.30-rebuntu-phase-56-30-natural-language-goal-ingestion.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/natural_language_goal_ingestion_ecd21c99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/natural_language_goal_ingestion_ecd21c99.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/natural_language_goal_ingestion_ecd21c99.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_natural_language_goal_ingestion_ecd21c99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.31-rebuntu-phase-56-31-semantic-goal-proposal-boundary`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.31-rebuntu-phase-56-31-semantic-goal-proposal-boundary.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/semantic_goal_proposal_boundary_053df4ef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/semantic_goal_proposal_boundary_053df4ef.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/semantic_goal_proposal_boundary_053df4ef.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_semantic_goal_proposal_boundary_053df4ef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.32-rebuntu-phase-56-32-goal-persistence-and-restart`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.32-rebuntu-phase-56-32-goal-persistence-and-restart.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_persistence_and_restart_d7753a9a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/recovery/goal_persistence_and_restart_d7753a9a.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/recovery/goal_persistence_and_restart_d7753a9a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/recovery/test_goal_persistence_and_restart_d7753a9a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.33-rebuntu-phase-56-33-goal-deduplication`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.33-rebuntu-phase-56-33-goal-deduplication.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_deduplication_1b13c53f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_deduplication_1b13c53f.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_deduplication_1b13c53f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_deduplication_1b13c53f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.34-rebuntu-phase-56-34-goal-supersession`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.34-rebuntu-phase-56-34-goal-supersession.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_supersession_cb1301e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_supersession_cb1301e3.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_supersession_cb1301e3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_supersession_cb1301e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.35-rebuntu-phase-56-35-goal-versioning`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.35-rebuntu-phase-56-35-goal-versioning.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_versioning_d41e0de7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_versioning_d41e0de7.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_versioning_d41e0de7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_versioning_d41e0de7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.36-rebuntu-phase-56-36-goal-audit-trail`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.36-rebuntu-phase-56-36-goal-audit-trail.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_audit_trail_9a97a09d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/goal_audit_trail_9a97a09d.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/goal_audit_trail_9a97a09d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/verification/test_goal_audit_trail_9a97a09d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.37-rebuntu-phase-56-37-goal-privacy`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.37-rebuntu-phase-56-37-goal-privacy.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_privacy_1a2202dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_privacy_1a2202dc.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_privacy_1a2202dc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_privacy_1a2202dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.38-rebuntu-phase-56-38-goal-boundedness`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.38-rebuntu-phase-56-38-goal-boundedness.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_boundedness_d8c867b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_boundedness_d8c867b4.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_boundedness_d8c867b4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_boundedness_d8c867b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.39-rebuntu-phase-56-39-goal-adversarial-audit`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.39-rebuntu-phase-56-39-goal-adversarial-audit.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_adversarial_audit_04ff5e1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/goal_adversarial_audit_04ff5e1a.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/goal_adversarial_audit_04ff5e1a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/verification/test_goal_adversarial_audit_04ff5e1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.4-rebuntu-phase-56-4-goal-predicates`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.4-rebuntu-phase-56-4-goal-predicates.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_predicates_bdb3a0c7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_predicates_bdb3a0c7.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_predicates_bdb3a0c7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_predicates_bdb3a0c7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.40-rebuntu-phase-56-40-python-authority-audit`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.40-rebuntu-phase-56-40-python-authority-audit.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/python_authority_audit_dbb62e7e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/python_authority_audit_dbb62e7e.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/python_authority_audit_dbb62e7e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/verification/test_python_authority_audit_dbb62e7e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.41-rebuntu-phase-56-41-shell-authority-audit`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.41-rebuntu-phase-56-41-shell-authority-audit.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/shell_authority_audit_1dcb00f1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/shell_authority_audit_1dcb00f1.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/shell_authority_audit_1dcb00f1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/verification/test_shell_authority_audit_1dcb00f1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.42-rebuntu-phase-56-42-build-runtime-audit`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.42-rebuntu-phase-56-42-build-runtime-audit.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/build_runtime_audit_70c9d3b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/build_runtime_audit_70c9d3b7.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/verification/build_runtime_audit_70c9d3b7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/verification/test_build_runtime_audit_70c9d3b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.43-rebuntu-phase-56-43-integration-matrix`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.43-rebuntu-phase-56-43-integration-matrix.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/integration_matrix_4a262a3b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/integration/integration_matrix_4a262a3b.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/integration/integration_matrix_4a262a3b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/integration/test_integration_matrix_4a262a3b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.44-rebuntu-phase-56-44-independent-rediscovery`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.44-rebuntu-phase-56-44-independent-rediscovery.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/independent_rediscovery_1c285719/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/resolution/independent_rediscovery_1c285719.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/resolution/independent_rediscovery_1c285719.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/resolution/test_independent_rediscovery_1c285719.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.45-rebuntu-phase-56-45-phase-closure`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.45-rebuntu-phase-56-45-phase-closure.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/phase_closure_a508f29f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/phase_closure_a508f29f.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/phase_closure_a508f29f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_phase_closure_a508f29f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.5-rebuntu-phase-56-5-goal-hierarchy`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.5-rebuntu-phase-56-5-goal-hierarchy.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_hierarchy_08663c89/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_hierarchy_08663c89.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_hierarchy_08663c89.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_hierarchy_08663c89.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.6-rebuntu-phase-56-6-goal-decomposition`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.6-rebuntu-phase-56-6-goal-decomposition.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_decomposition_eaa6cb28/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_decomposition_eaa6cb28.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_decomposition_eaa6cb28.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_decomposition_eaa6cb28.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.7-rebuntu-phase-56-7-goal-dependencies`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.7-rebuntu-phase-56-7-goal-dependencies.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_dependencies_17413332/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_dependencies_17413332.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_dependencies_17413332.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_dependencies_17413332.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.8-rebuntu-phase-56-8-goal-conflicts`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.8-rebuntu-phase-56-8-goal-conflicts.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_conflicts_aaab16a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_conflicts_aaab16a3.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_conflicts_aaab16a3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_conflicts_aaab16a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `56.9-rebuntu-phase-56-9-goal-priorities`
- **Source:** `.phases/phases/phase-56-intent-goal-desired-state-management/prompts/56.9-rebuntu-phase-56-9-goal-priorities.md`
- **Structural package:** `src/semantics/intent-goal-desired-state-management/subtask_packages/verification/goal_priorities_d5219a70/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_priorities_d5219a70.hpp`, `src/semantics/intent-goal-desired-state-management/subtask_targets/requirements/goal_priorities_d5219a70.cpp`
- **Structural test target:** `tests/structural-closure/semantics/intent-goal-desired-state-management/requirements/test_goal_priorities_d5219a70.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

