# Phase 61 — Recovery Repair Self Healing — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-61-recovery-repair-self-healing/`
- Primary prompt location: `.phases/phases/phase-61-recovery-repair-self-healing/prompts/`
- Prompt/specification Markdown files currently present: **56**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 56 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_61` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 61 — Recovery, Repair & Self-Healing System — FULL 2000+ LINE PROMPTS
- Rebuntu — Phase 61.8: Repair planning
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
- Canonical skeleton: `src/control/recovery-repair-self-healing/`
- Structural files: `src/control/recovery-repair-self-healing/component.hpp`, `src/control/recovery-repair-self-healing/component.cpp`, `src/control/recovery-repair-self-healing/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** SKELETON
- **Implementation depth:** **1/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- No implementation evidence was matched automatically; inspect `src/` before concluding that the requirement is absent.

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
- Baseline ledger created automatically from the current repository. Depth **0/5** is deliberately conservative and not a completion claim.

- Structural skeleton materialized at `src/control/recovery-repair-self-healing/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/control/recovery-repair-self-healing/model/`
- `src/control/recovery-repair-self-healing/contracts/`
- `src/control/recovery-repair-self-healing/integration/`
- `src/control/recovery-repair-self-healing/verification/`
- `src/control/recovery-repair-self-healing/lifecycle/`
- `src/control/recovery-repair-self-healing/state/`
- `src/control/recovery-repair-self-healing/execution/`
- `src/control/recovery-repair-self-healing/transactions/`
- `src/control/recovery-repair-self-healing/events/`
- `src/control/recovery-repair-self-healing/scheduling/`
- `src/control/recovery-repair-self-healing/recovery/`
- `src/control/recovery-repair-self-healing/principals/`
- `src/control/recovery-repair-self-healing/groups/`
- `src/control/recovery-repair-self-healing/roles/`
- `src/control/recovery-repair-self-healing/resolution/`
- `src/control/recovery-repair-self-healing/authorization/`
- `src/control/recovery-repair-self-healing/credentials/`
- `src/control/recovery-repair-self-healing/policy/`



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


## MASS IMPLEMENTATION VI / SATURATION — 2026-09-23

Concrete implementation added in this pass (this is implementation evidence, not structural coverage):
- `src/security/policy/mutation_gate.hpp` adds a typed fail-closed mutation authorization boundary with deterministic operation fingerprints. Mutating reconciliation operations cannot execute without an authorization callback; an allow decision is valid only when bound to the exact operation fingerprint, preventing stale-plan/target authorization reuse. Authorization is re-evaluated on every replan attempt and compensation can use a distinct authorization callback.
- `src/domains/common/reconciliation/domain_reconciler.hpp` now enforces authorization immediately before each native mutating operation and before compensating mutations. Denial/UNKNOWN/unavailable authorization cannot fall through to provider execution. Existing authoritative observe -> plan -> execute -> re-observe -> verify behavior remains intact.
- `src/control/checkpoints/durable_store.hpp` adds a C++20/Linux durable append-only transaction checkpoint store. Records are persisted with `write(2)` + `fsync(2)` and parent-directory fsync, strict field/stage parsing, transaction identity, work identity and monotonic sequence evidence. This persists Rebuntu transaction semantics only; it does not replace any Linux state authority.
- `src/control/reconciliation/coordination/durable_cross_domain.hpp` integrates durable checkpoints with cross-domain reconciliation. Restart can recover already-applied work without blindly reapplying it, continue dependency-ordered work, durably commit convergence, and compensate work recovered from a pre-crash transaction if a later dependency fails.
- `tests/rebuntu/test_saturation_vi.cpp` exercises fail-closed mutation denial, successful fingerprint-bound authorization, stale authorization rejection, crash/resume without duplicate application, durable commit, and rollback of pre-crash applied work after resumed failure.

Actual strict verification executed for this pass:
- `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc tests/rebuntu/test_saturation_vi.cpp` -> executed successfully: `MUTATION_FAIL_CLOSED_PASS`, `AUTHORIZED_MUTATION_PASS`, `AUTHORIZATION_BINDING_PASS`, `CRASH_RESUME_CHECKPOINT_PASS`, `RESUMED_TRANSACTION_ROLLBACK_PASS`.
- Regression strict builds/execution: `test_saturation_v.cpp` -> `REPLAN_CONVERGENCE_PASS`, `TRANSACTION_ROLLBACK_PASS`, `CROSS_DOMAIN_ROLLBACK_PASS`, `CROSS_DOMAIN_CYCLE_PASS`; `test_domain_semantic_models.cpp` -> `DOMAIN_SEMANTIC_MODELS_PASS`; `test_domain_synthesis.cpp` -> `DOMAIN_SYNTHESIS_PASS`; `test_saturation_tree_ii.cpp` -> `TREE_DEEPENING_II_SATURATION_PASS`.

Native Authority compliance: the new persistence owns only Rebuntu transaction/checkpoint metadata. Real service/process/storage/network/package/configuration/identity/accelerator state remains owned and observed through native Linux authorities/providers. The policy gate authorizes Rebuntu mutations but does not replace polkit/sudo/PAM/NSS or provider/native authorization.

Remaining work: provider-specific compensation semantics still need broader integration; durable checkpoint compaction/retention and multi-process locking are not complete; full build-system reachability remains limited by the repository's current absence of a root CMake build; distributed transaction recovery is not claimed. **Do not infer 5/5 phase completion from this pass.** Existing depth remains conservative unless all phase prompt acceptance criteria are independently verified.


## MASS IMPLEMENTATION VII / SATURATION — 2026-09-23

Verified implementation evidence:
- `src/domains/common/reconciliation/domain_reconciler.hpp` now enforces an independent native-operation execution budget in addition to the existing replan budget. Exhaustion fails closed before another mutation and enters the existing rollback/failure path.
- Reconciliation now fingerprints authoritative observations deterministically and detects repeated non-progress states with a configurable stagnant-replan allowance. This prevents an accepted-but-ineffective native mutation from causing unbounded reconcile churn while preserving bounded retry for transient drift.
- Existing authorization-before-mutation, authoritative re-observation, verification, rollback and journal transitions remain in the same canonical control path; no Linux mechanism is reimplemented.
- `tests/rebuntu/test_mass_implementation_ii_iii.cpp` was corrected to exercise the current fail-closed authorization contract explicitly rather than relying on the pre-security legacy call shape.

Executed strict test evidence (`g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src`):
- `test_saturation_vii.cpp`: `ANTI_THRASH_NO_PROGRESS_PASS`, `OPERATION_BUDGET_PASS`, `DURABLE_CORRUPTION_FAIL_CLOSED_PASS`.
- Regression `test_saturation_vi.cpp`: `MUTATION_FAIL_CLOSED_PASS`, `AUTHORIZED_MUTATION_PASS`, `AUTHORIZATION_BINDING_PASS`, `CRASH_RESUME_CHECKPOINT_PASS`, `RESUMED_TRANSACTION_ROLLBACK_PASS`.
- Regression `test_saturation_v.cpp`: `REPLAN_CONVERGENCE_PASS`, `TRANSACTION_ROLLBACK_PASS`, `CROSS_DOMAIN_ROLLBACK_PASS`, `CROSS_DOMAIN_CYCLE_PASS`.
- Regression `test_mass_implementation_ii_iii.cpp`: all nine existing MASS II/III markers passed.
- Regression semantic/tree tests: `DOMAIN_SEMANTIC_MODELS_PASS`, `DOMAIN_SYNTHESIS_PASS`, `TREE_DEEPENING_II_SATURATION_PASS`.

Native Authority / architecture compliance: anti-thrashing is Rebuntu control semantics only. State fingerprints are derived from authoritative provider observations; they are not shadow machine state. Execution remains through typed native operations and success still requires authoritative re-observation. Durable-store corruption is rejected rather than interpreted as successful recovery.

Remaining implementation plan / depth constraint: provider-specific postcondition probes and compensation remain incomplete across all eight domains; durable checkpoint multi-process locking/compaction/retention is still incomplete; distributed recovery and complete build-system reachability are not claimed. Existing implementation depth is therefore retained unless the complete phase prompt is independently satisfied.

## MASS IMPLEMENTATION VIII / SATURATION — 2026-09-23

**Implementation evidence.** Saturated the existing domain/control spine rather than adding a parallel subsystem. `src/domains/common/operations/planner.hpp` now binds explicit compensation verb/provider metadata into each planned native mutation when a semantically valid inverse exists. `src/domains/common/reconciliation/domain_reconciler.hpp` consumes that bound metadata during reverse-order rollback, so compensation is no longer guessed by replaying the forward verb with a previous value. `src/domains/common/saturation.hpp` defines native-authority-specific inverse operations for reversible service/systemd, storage/filesystem, networking/Netlink, software/package-manager, and configuration/native-owner mutations. Irreversible or identity-sensitive operations (notably process termination, package upgrade, accelerator placement where no proven inverse is available) remain deliberately without fabricated rollback semantics. Identity remains observation-only. This preserves Native Authority: Rebuntu synthesizes typed intent/compensation; Linux providers remain the executors and source of observed truth.

**Test evidence.** `tests/rebuntu/test_saturation_viii.cpp` was compiled and executed with `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc`. Observed: `DOMAIN_SPECIFIC_COMPENSATION_PASS`, `EIGHT_DOMAIN_AUTHORITY_BOUNDARY_PASS`, `PLANNED_COMPENSATION_BINDING_PASS`. Regression tests `test_saturation_vii.cpp`, `test_saturation_vi.cpp`, `test_domain_synthesis.cpp`, and `test_domain_semantic_models.cpp` were also compiled/executed under the same strict flags and passed. A standalone compile/link of `test_saturation_iv.cpp` was attempted but not counted as PASS because that test requires additional existing translation units and produced unresolved-symbol linker errors when invoked as a single TU.

**Remaining work / depth discipline.** This pass strengthens rollback correctness but does not prove provider-specific compensation against live systemd/Netlink/package-manager/filesystem authorities, nor crash recovery at every instruction boundary. Process termination and other non-reversible operations require checkpoint/recreate semantics rather than a fake inverse. No phase is promoted solely because of this pass; existing depth remains constrained by the unresolved integration/E2E requirements already listed above.

### 2026-09-23 — MASS IMPLEMENTATION IX / SATURATION
- Added pre-execution authoritative re-observation/TOCTOU guard to `src/domains/common/reconciliation/domain_reconciler.hpp`; state drift between planning and mutation now consumes the bounded replan budget before any native mutation is issued.
- Added per-operation authoritative postcondition verification. A provider returning success is insufficient: Rebuntu re-observes native authority and verifies the operation-bound `attribute=desired` postcondition before continuing the plan.
- Failed per-operation verification enters the existing compensation/rollback path; false provider success therefore fails closed instead of allowing later plan operations to compound drift.
- Added explicit counters/evidence (`operation_verifications`, `drift_replans`) and preserved operation/replan budgets, authorization, checkpointing, anti-thrashing, and final convergence verification.
- Transaction journal now permits `prepared -> replanning`, required when the TOCTOU guard detects drift before the first mutation; terminal-state invariants remain unchanged.
- Strict evidence: `tests/rebuntu/test_saturation_ix.cpp` compiled with `-std=c++20 -Wall -Wextra -Wpedantic -Werror` and emitted `PER_OPERATION_NATIVE_POSTCONDITION_PASS`, `FALSE_PROVIDER_SUCCESS_REJECTED_PASS`, `PRE_EXECUTION_TOCTOU_REPLAN_PASS`, `IDENTITY_OBSERVATION_ONLY_PASS`.
- Regression evidence under the same strict flags: saturation VIII (`DOMAIN_SPECIFIC_COMPENSATION_PASS`, `EIGHT_DOMAIN_AUTHORITY_BOUNDARY_PASS`, `PLANNED_COMPENSATION_BINDING_PASS`), saturation VII (`ANTI_THRASH_NO_PROGRESS_PASS`, `OPERATION_BUDGET_PASS`, `DURABLE_CORRUPTION_FAIL_CLOSED_PASS`), saturation VI (all five security/durability passes), and MASS II/III (all nine algorithm/domain passes).
- Native Authority compliance: verification is based on re-observation through the supplied typed observation boundary; no systemd/procfs/filesystem/Netlink/package/NSS/PAM/driver mechanism is reimplemented.
- Remaining: provider adapters should expose richer provider-specific postconditions/evidence (including disappearance semantics such as terminated processes), concurrency/version tokens should replace whole-entity fingerprints where native authorities provide them, and full build-system/E2E reachability remains required before phase-complete maturity.
- Maturity: unchanged unless the phase already has stronger independent evidence; this pass strengthens verification/reconciliation behavior but does not by itself justify 5/5.

### 2026-09-23 — MASS IMPLEMENTATION X / DEEP SATURATION
- Deepened the existing canonical `src/domains/common/reconciliation/domain_reconciler.hpp` rather than creating a parallel verification subsystem. Per-operation verification now emits operation-bound evidence containing the exact authorization/operation fingerprint, native authority, evaluated predicate, observed value, and pass/fail result.
- Added provider-supplied native generation/version-token concurrency guards through `ReconcileOptions::native_generation_attribute`. When an authority exposes a token (for example procfs `start_ticks`), the TOCTOU guard compares that token rather than unrelated whole-entity attributes. If a configured token is missing on either side, the guard fails closed. When no token is configured, the previous deterministic whole-observation fingerprint remains the conservative fallback.
- Added explicit disappearance postconditions. Process termination semantics now accept authoritative disappearance as the strongest success condition (`absent_or_equals` retains compatibility with providers that expose a terminal/stopped observation). Final convergence can therefore commit after verified authoritative disappearance instead of incorrectly treating absence as observation failure.
- Native Authority compliance: Rebuntu does not manufacture generation numbers or process state. Tokens and disappearance are consumed only from typed provider observations; procfs/kernel/systemd/etc. remain authoritative.
- Strict test evidence: `tests/rebuntu/test_saturation_x.cpp` compiled/executed with `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc` and emitted `PROCESS_DISAPPEARANCE_POSTCONDITION_PASS`, `NATIVE_GENERATION_TOKEN_TOCTOU_PASS`, `MISSING_GENERATION_TOKEN_FAIL_CLOSED_PASS`, `OPERATION_BOUND_VERIFICATION_EVIDENCE_PASS`.
- Strict regression evidence under the same flags: saturation IX (4 PASS markers), saturation VIII (3), saturation VII (3), saturation VI (5), MASS II/III (9), plus `DOMAIN_SEMANTIC_MODELS_PASS` and `DOMAIN_SYNTHESIS_PASS`.
- Remaining/depth discipline: provider adapters still need to populate native generation/version attributes consistently per authority; richer predicates (multi-attribute, ranges, relationship/topology postconditions) and live-provider E2E tests remain incomplete. No phase is promoted to 5/5 from this pass alone.

### 2026-09-23 — MASS IMPLEMENTATION XI / DEEPER SATURATION
- Deepened the canonical domain reconciliation path; no parallel Linux mechanism or phase-shaped runtime subsystem was introduced.
- Added rich operation-bound authoritative postconditions through typed operation arguments: multiple equality predicates and numeric minimum/maximum predicates can now be required simultaneously. Every predicate emits separate evidence bound to the exact operation fingerprint, native authority and operation index. Malformed/missing native numeric observations fail closed.
- Added per-operation CAS-like stale-plan rejection. Before every planned operation Rebuntu re-observes native authority and compares the provider generation/version token when configured (otherwise deterministic observation fingerprint). The verified observation after one operation becomes the concurrency baseline for the next, closing the previous gap where drift between operations of one plan could escape the plan-level TOCTOU guard.
- Failure after partial execution enters the existing reverse compensation path rather than continuing a stale plan. Native authorities remain systemd/kernel/procfs/filesystems/Netlink/package manager/NSS-PAM/drivers; Rebuntu only consumes their typed observations.
- Strict evidence: `tests/rebuntu/test_saturation_xi.cpp` compiled/executed with `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc` and emitted `RICH_MULTI_PREDICATE_VERIFICATION_PASS`, `PER_OPERATION_CAS_STALE_PLAN_REJECTION_PASS`, and `MALFORMED_NATIVE_METRIC_FAIL_CLOSED_PASS`.
- Strict regression evidence under the same flags: saturation X (4 PASS markers), IX (4), VIII (3), VII (3), and VI (5) all recompiled and executed successfully.
- Remaining/depth discipline: relationship/topology predicates still require richer authoritative observation types than the current flat `core::Entity`; concrete Linux provider adapters need systematic native generation-token population; live-provider E2E/build-system reachability and durable evidence persistence remain closure gaps. Maturity is not promoted to 5/5 by this pass alone.


### MASS IMPLEMENTATION XII / DEEP SATURATION — 2026-09-23
- Added relationship/topology-aware authoritative postconditions to the canonical `domains/common/reconciliation/DomainReconciler`; relationship evidence is observed through an explicit callback boundary and fails closed when relationship observation is unavailable. No Linux topology mechanism is reimplemented.
- Operation verification evidence now carries an explicit transaction binding, preserving operation fingerprint + authority + predicate + observation + operation index while allowing evidence to be associated with the transaction/checkpoint context.
- Added `control/verification/evidence/durable_chain.hpp`: append-only, fsync-backed, sequence-checked logical hash-chain persistence for verification evidence. Load rejects malformed, reordered, truncated/mismatched-chain records instead of silently accepting corrupted evidence. This is an integrity chain, not a replacement for OS/native authority or a claim of cryptographic authentication.
- Strict test evidence: `tests/rebuntu/test_saturation_xii.cpp` compiled with `-std=c++20 -Wall -Wextra -Wpedantic -Werror` and executed with `RELATIONSHIP_POSTCONDITION_PASS`, `RELATIONSHIP_OBSERVATION_FAIL_CLOSED_PASS`, `DURABLE_EVIDENCE_CHAIN_PASS`.
- Regression evidence: saturation XI/X/IX/VIII/VII/VI strict tests were rebuilt and executed successfully after this change (21 prior PASS markers).
- Native Authority compliance: relationship state remains provider-observed machine state; Rebuntu only evaluates semantic predicates and persists verification provenance.
- Remaining work: wire relationship observations from concrete Netlink/systemd/storage/provider adapters; bind durable evidence records directly to durable transaction/checkpoint sequence IDs in the production coordinator; add crash/torn-write recovery semantics and authenticated digests if evidence must cross trust boundaries.
- Maturity was not raised solely because of this pass; existing phase-wide unresolved requirements remain authoritative.

### MASS IMPLEMENTATION XIII / DEEP SATURATION — 2026-09-23
- Bound durable verification evidence to an existing durable checkpoint sequence through `control/verification/evidence/transaction_binding.hpp`; orphan evidence referencing a nonexistent checkpoint is rejected fail-closed.
- Extended durable evidence records with checkpoint sequence identity and strengthened persistence with parent-directory fsync after append/recovery.
- Added explicit torn-tail recovery: only an incomplete final record may be truncated after the preceding chain validates; malformed/corrupt complete records remain hard failures. This avoids treating arbitrary corruption as crash recovery.
- Strict evidence: `tests/rebuntu/test_saturation_xiii.cpp` compiled/executed with `-std=c++20 -Wall -Wextra -Wpedantic -Werror` and emitted `CHECKPOINT_EVIDENCE_BINDING_PASS`, `TORN_EVIDENCE_TAIL_RECOVERY_PASS`, `MID_LOG_CORRUPTION_FAIL_CLOSED_PASS`.
- Strict regression: saturation XII, XI, X, IX, VIII, VII and VI rebuilt/executed successfully (24 prior PASS markers).
- Native Authority compliance: this pass persists Rebuntu transaction/verification provenance only; it does not replace any Linux authority or provider.
- Remaining: production coordinator must emit operation evidence directly through the durable binding, checkpoint journal itself needs equivalent explicit torn-tail repair/compaction policy, and authenticated integrity is still required for evidence crossing a trust boundary. Maturity is not promoted to 5/5 from this pass alone.

### MASS IMPLEMENTATION XIV / DEEP SATURATION — 2026-09-23
- Integrated the durable verification-evidence sink directly into `control/reconciliation/coordination/durable_cross_domain.hpp`; successful work now persists `applied`, operation-bound verification evidence, then `verified` before it is eligible for evidence-aware crash-resume skipping.
- Evidence-aware resume is anchored to the last durable `verified` work item rather than merely trusting an `applied` checkpoint. Legacy coordinator behavior without an evidence sink remains backward-compatible.
- Hardened `control/checkpoints/durable_store.hpp` with checksummed records, backward-compatible loading of legacy records, explicit torn-tail detection/recovery, file `fsync`, parent-directory `fsync`, and fail-closed rejection of complete corrupted records.
- Added `tests/rebuntu/test_saturation_xiv.cpp`. Strict C++20 evidence: `PRODUCTION_DURABLE_EVIDENCE_SINK_PASS`, `RESUME_FROM_LAST_VERIFIED_POSTCONDITION_PASS`, `TORN_CHECKPOINT_TAIL_RECOVERY_PASS`, `CHECKPOINT_CORRUPTION_FAIL_CLOSED_PASS` under `-std=c++20 -Wall -Wextra -Wpedantic -Werror`.
- Regression evidence: saturation VI–XIII strict tests were rebuilt and executed successfully after this pass.
- Native Authority compliance: no Linux mechanism is reimplemented; this pass only hardens Rebuntu-owned transaction/checkpoint/provenance state around typed native-provider execution and authoritative postcondition observations.
- Remaining work: stronger cross-file atomicity between checkpoint and evidence journals, authenticated/cryptographic integrity where required by the trust model, compaction/retention, concurrent-writer locking, and broader end-to-end provider-backed crash injection.
- Maturity was not raised solely because of this pass; existing phase depth remains evidence-conservative until the remaining acceptance criteria are closed.

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `61.0-rebuntu-phase-61-0-recovery-topology`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.0-rebuntu-phase-61-0-recovery-topology.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_topology_b294ed63/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_topology_b294ed63.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_topology_b294ed63.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_topology_b294ed63.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.1-rebuntu-phase-61-1-failure-observation`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.1-rebuntu-phase-61-1-failure-observation.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/failure_observation_4fead6ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/observability/failure_observation_4fead6ca.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/observability/failure_observation_4fead6ca.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/observability/test_failure_observation_4fead6ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.10-rebuntu-phase-61-10-recovery-security-boundary`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.10-rebuntu-phase-61-10-recovery-security-boundary.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_security_boundary_2dc9e0d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_security_boundary_2dc9e0d7.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_security_boundary_2dc9e0d7.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_security_boundary_2dc9e0d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.11-rebuntu-phase-61-11-recovery-authorization-boundary`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.11-rebuntu-phase-61-11-recovery-authorization-boundary.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_authorization_boundary_13b24942/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_authorization_boundary_13b24942.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_authorization_boundary_13b24942.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_authorization_boundary_13b24942.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.12-rebuntu-phase-61-12-self-healing-delegation-boundary`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.12-rebuntu-phase-61-12-self-healing-delegation-boundary.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/self_healing_delegation_boundary_e94db24f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/self_healing_delegation_boundary_e94db24f.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/self_healing_delegation_boundary_e94db24f.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_self_healing_delegation_boundary_e94db24f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.13-rebuntu-phase-61-13-evidence-acquisition`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.13-rebuntu-phase-61-13-evidence-acquisition.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/evidence_acquisition_41343ae1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/verification/evidence_acquisition_41343ae1.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/verification/evidence_acquisition_41343ae1.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/verification/test_evidence_acquisition_41343ae1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.14-rebuntu-phase-61-14-root-cause-handoff`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.14-rebuntu-phase-61-14-root-cause-handoff.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/root_cause_handoff_79f10d9e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/root_cause_handoff_79f10d9e.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/root_cause_handoff_79f10d9e.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_root_cause_handoff_79f10d9e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.15-rebuntu-phase-61-15-minimal-repair-principle`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.15-rebuntu-phase-61-15-minimal-repair-principle.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/minimal_repair_principle_5831f328/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/minimal_repair_principle_5831f328.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/minimal_repair_principle_5831f328.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_minimal_repair_principle_5831f328.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.16-rebuntu-phase-61-16-repair-alternatives`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.16-rebuntu-phase-61-16-repair-alternatives.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/repair_alternatives_1a8eeeb7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_alternatives_1a8eeeb7.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_alternatives_1a8eeeb7.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_repair_alternatives_1a8eeeb7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.17-rebuntu-phase-61-17-repair-impact-analysis`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.17-rebuntu-phase-61-17-repair-impact-analysis.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/repair_impact_analysis_f72e0562/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_impact_analysis_f72e0562.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_impact_analysis_f72e0562.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_repair_impact_analysis_f72e0562.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.18-rebuntu-phase-61-18-invariant-preserving-repair`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.18-rebuntu-phase-61-18-invariant-preserving-repair.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/invariant_preserving_repair_095a5ef9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/invariant_preserving_repair_095a5ef9.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/invariant_preserving_repair_095a5ef9.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_invariant_preserving_repair_095a5ef9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.19-rebuntu-phase-61-19-resource-aware-repair`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.19-rebuntu-phase-61-19-resource-aware-repair.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/resource_aware_repair_a7197d9e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/resource_aware_repair_a7197d9e.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/resource_aware_repair_a7197d9e.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_resource_aware_repair_a7197d9e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.2-rebuntu-phase-61-2-failure-classification`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.2-rebuntu-phase-61-2-failure-classification.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/failure_classification_2b07149a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/failure_classification_2b07149a.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/failure_classification_2b07149a.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_failure_classification_2b07149a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.20-rebuntu-phase-61-20-service-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.20-rebuntu-phase-61-20-service-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/service_recovery_d6d2fe51/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/service_recovery_d6d2fe51.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/service_recovery_d6d2fe51.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_service_recovery_d6d2fe51.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.21-rebuntu-phase-61-21-process-workload-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.21-rebuntu-phase-61-21-process-workload-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/process_workload_recovery_fabae772/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/process_workload_recovery_fabae772.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/process_workload_recovery_fabae772.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_process_workload_recovery_fabae772.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.22-rebuntu-phase-61-22-storage-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.22-rebuntu-phase-61-22-storage-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/storage_recovery_38477a4f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/storage_recovery_38477a4f.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/storage_recovery_38477a4f.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_storage_recovery_38477a4f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.23-rebuntu-phase-61-23-network-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.23-rebuntu-phase-61-23-network-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/network_recovery_008d5ab1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/network_recovery_008d5ab1.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/network_recovery_008d5ab1.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_network_recovery_008d5ab1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.24-rebuntu-phase-61-24-gpu-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.24-rebuntu-phase-61-24-gpu-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/gpu_recovery_5eeac751/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/gpu_recovery_5eeac751.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/gpu_recovery_5eeac751.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_gpu_recovery_5eeac751.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.25-rebuntu-phase-61-25-configuration-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.25-rebuntu-phase-61-25-configuration-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/configuration_recovery_4afbfbb8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/configuration_recovery_4afbfbb8.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/configuration_recovery_4afbfbb8.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_configuration_recovery_4afbfbb8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.26-rebuntu-phase-61-26-package-software-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.26-rebuntu-phase-61-26-package-software-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/package_software_recovery_9d8c38f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/package_software_recovery_9d8c38f4.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/package_software_recovery_9d8c38f4.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_package_software_recovery_9d8c38f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.27-rebuntu-phase-61-27-distributed-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.27-rebuntu-phase-61-27-distributed-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/distributed_recovery_f2494d6c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/distributed_recovery_f2494d6c.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/distributed_recovery_f2494d6c.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_distributed_recovery_f2494d6c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.28-rebuntu-phase-61-28-partition-aware-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.28-rebuntu-phase-61-28-partition-aware-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/partition_aware_recovery_983b9a2b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/partition_aware_recovery_983b9a2b.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/partition_aware_recovery_983b9a2b.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_partition_aware_recovery_983b9a2b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.29-rebuntu-phase-61-29-crash-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.29-rebuntu-phase-61-29-crash-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/crash_recovery_fe10588d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/crash_recovery_fe10588d.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/crash_recovery_fe10588d.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_crash_recovery_fe10588d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.3-rebuntu-phase-61-3-repairability-model`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.3-rebuntu-phase-61-3-repairability-model.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/repairability_model_f74f7081/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/repairability_model_f74f7081.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/repairability_model_f74f7081.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_repairability_model_f74f7081.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.30-rebuntu-phase-61-30-boot-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.30-rebuntu-phase-61-30-boot-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/boot_recovery_701ebf05/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/boot_recovery_701ebf05.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/boot_recovery_701ebf05.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_boot_recovery_701ebf05.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.31-rebuntu-phase-61-31-degraded-mode-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.31-rebuntu-phase-61-31-degraded-mode-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/degraded_mode_recovery_26b7c7d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/degraded_mode_recovery_26b7c7d8.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/degraded_mode_recovery_26b7c7d8.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_degraded_mode_recovery_26b7c7d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.32-rebuntu-phase-61-32-compensation-recovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.32-rebuntu-phase-61-32-compensation-recovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/compensation_recovery_5c314568/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/compensation_recovery_5c314568.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/compensation_recovery_5c314568.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_compensation_recovery_5c314568.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.33-rebuntu-phase-61-33-failed-repair-handling`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.33-rebuntu-phase-61-33-failed-repair-handling.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/failed_repair_handling_213eebee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/failed_repair_handling_213eebee.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/failed_repair_handling_213eebee.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_failed_repair_handling_213eebee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.34-rebuntu-phase-61-34-repair-verification`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.34-rebuntu-phase-61-34-repair-verification.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/repair_verification_a887d91c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/verification/repair_verification_a887d91c.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/verification/repair_verification_a887d91c.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/verification/test_repair_verification_a887d91c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.35-rebuntu-phase-61-35-post-repair-observation`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.35-rebuntu-phase-61-35-post-repair-observation.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/post_repair_observation_3b1055f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/post_repair_observation_3b1055f2.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/post_repair_observation_3b1055f2.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_post_repair_observation_3b1055f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.36-rebuntu-phase-61-36-recurrence-detection`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.36-rebuntu-phase-61-36-recurrence-detection.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recurrence_detection_945fdd50/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/recurrence_detection_945fdd50.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/recurrence_detection_945fdd50.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_recurrence_detection_945fdd50.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.37-rebuntu-phase-61-37-escalation`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.37-rebuntu-phase-61-37-escalation.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/escalation_67653b4b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/escalation_67653b4b.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/escalation_67653b4b.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_escalation_67653b4b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.38-rebuntu-phase-61-38-operator-handoff`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.38-rebuntu-phase-61-38-operator-handoff.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/operator_handoff_51168bbd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/operator_handoff_51168bbd.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/operator_handoff_51168bbd.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_operator_handoff_51168bbd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.39-rebuntu-phase-61-39-repair-cooldown`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.39-rebuntu-phase-61-39-repair-cooldown.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/repair_cooldown_134fadf3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_cooldown_134fadf3.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_cooldown_134fadf3.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_repair_cooldown_134fadf3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.4-rebuntu-phase-61-4-recovery-goal-construction`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.4-rebuntu-phase-61-4-recovery-goal-construction.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_goal_construction_7f888b99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_goal_construction_7f888b99.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_goal_construction_7f888b99.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_goal_construction_7f888b99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.40-rebuntu-phase-61-40-loop-prevention`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.40-rebuntu-phase-61-40-loop-prevention.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/loop_prevention_0d9e485b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/loop_prevention_0d9e485b.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/loop_prevention_0d9e485b.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_loop_prevention_0d9e485b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.41-rebuntu-phase-61-41-repair-budgets`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.41-rebuntu-phase-61-41-repair-budgets.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/repair_budgets_c5fcf139/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_budgets_c5fcf139.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_budgets_c5fcf139.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_repair_budgets_c5fcf139.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.42-rebuntu-phase-61-42-recovery-history`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.42-rebuntu-phase-61-42-recovery-history.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_history_36d5803c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_history_36d5803c.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_history_36d5803c.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_history_36d5803c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.43-rebuntu-phase-61-43-explainability`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.43-rebuntu-phase-61-43-explainability.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/explainability_a6af5fcd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/observability/explainability_a6af5fcd.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/observability/explainability_a6af5fcd.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/observability/test_explainability_a6af5fcd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.44-rebuntu-phase-61-44-cli`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.44-rebuntu-phase-61-44-cli.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/cli_198413a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/cli_198413a9.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/cli_198413a9.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_cli_198413a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.45-rebuntu-phase-61-45-gui`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.45-rebuntu-phase-61-45-gui.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/gui_ab320dad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/gui_ab320dad.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/gui_ab320dad.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_gui_ab320dad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.46-rebuntu-phase-61-46-adversarial-false-positive-audit`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.46-rebuntu-phase-61-46-adversarial-false-positive-audit.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/adversarial_false_positive_audit_7a695253/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/verification/adversarial_false_positive_audit_7a695253.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/verification/adversarial_false_positive_audit_7a695253.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/verification/test_adversarial_false_positive_audit_7a695253.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.47-rebuntu-phase-61-47-destructive-repair-prevention`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.47-rebuntu-phase-61-47-destructive-repair-prevention.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/destructive_repair_prevention_3a66b398/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/destructive_repair_prevention_3a66b398.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/destructive_repair_prevention_3a66b398.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_destructive_repair_prevention_3a66b398.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.48-rebuntu-phase-61-48-build-runtime-audit`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.48-rebuntu-phase-61-48-build-runtime-audit.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/build_runtime_audit_b310d38f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/verification/build_runtime_audit_b310d38f.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/verification/build_runtime_audit_b310d38f.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/verification/test_build_runtime_audit_b310d38f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.49-rebuntu-phase-61-49-integration-matrix`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.49-rebuntu-phase-61-49-integration-matrix.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/integration_matrix_86033426/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/integration/integration_matrix_86033426.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/integration/integration_matrix_86033426.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/integration/test_integration_matrix_86033426.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.5-rebuntu-phase-61-5-recovery-capability-discovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.5-rebuntu-phase-61-5-recovery-capability-discovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_capability_discovery_26431b95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_capability_discovery_26431b95.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_capability_discovery_26431b95.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_capability_discovery_26431b95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.50-rebuntu-phase-61-50-independent-rediscovery`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.50-rebuntu-phase-61-50-independent-rediscovery.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/independent_rediscovery_b845ed35/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/resolution/independent_rediscovery_b845ed35.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/resolution/independent_rediscovery_b845ed35.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/resolution/test_independent_rediscovery_b845ed35.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.51-rebuntu-phase-61-51-phase-closure`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.51-rebuntu-phase-61-51-phase-closure.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/phase_closure_be58aa3b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/requirements/phase_closure_be58aa3b.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/requirements/phase_closure_be58aa3b.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/requirements/test_phase_closure_be58aa3b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.6-rebuntu-phase-61-6-recovery-affordance-evaluation`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.6-rebuntu-phase-61-6-recovery-affordance-evaluation.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_affordance_evaluation_39517496/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_affordance_evaluation_39517496.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_affordance_evaluation_39517496.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_affordance_evaluation_39517496.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.7-rebuntu-phase-61-7-recovery-planning`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.7-rebuntu-phase-61-7-recovery-planning.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_planning_250414a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_planning_250414a2.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_planning_250414a2.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_planning_250414a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.8-rebuntu-phase-61-8-repair-planning`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.8-rebuntu-phase-61-8-repair-planning.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/repair_planning_2b961474/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_planning_2b961474.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/repair_planning_2b961474.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_repair_planning_2b961474.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `61.9-rebuntu-phase-61-9-recovery-policy-boundary`
- **Source:** `.phases/phases/phase-61-recovery-repair-self-healing/prompts/61.9-rebuntu-phase-61-9-recovery-policy-boundary.md`
- **Structural package:** `src/control/recovery-repair-self-healing/subtask_packages/verification/recovery_policy_boundary_9869e280/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_policy_boundary_9869e280.hpp`, `src/control/recovery-repair-self-healing/subtask_targets/recovery/recovery_policy_boundary_9869e280.cpp`
- **Structural test target:** `tests/structural-closure/control/recovery-repair-self-healing/recovery/test_recovery_policy_boundary_9869e280.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

