# Phase 19 — Reconciliation — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-19-reconciliation/`
- Primary prompt location: `.phases/phases/phase-19-reconciliation/prompts/`
- Prompt/specification Markdown files currently present: **25**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 25 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_19` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 19: Reconciliation
- Layout
- Prompt Index
- Agent Handoff — Phase 19
- Rebuntu --- Phase 19.11 --- Resource Constraints
- Agent Task
- Phase Mission
- Global Agent Contract
- Desired State
- Observed State
- Semantic State Comparison
- Drift

## Structural skeleton / canonical destination
- Canonical skeleton: `src/control/reconciliation/`
- Structural files: `src/control/reconciliation/component.hpp`, `src/control/reconciliation/component.cpp`, `src/control/reconciliation/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/control/reconciliation/README.md`
- `src/control/reconciliation/contract.hpp`
- `src/control/reconciliation/native_reconciler.hpp`
- `src/control/reconciliation/reconciler.cpp`
- `src/control/reconciliation/reconciler.hpp`
- `src/domains/processes/reconciliation/process_controller.cpp`
- `src/domains/processes/reconciliation/process_controller.hpp`
- `src/domains/services/reconciliation/README.md`
- `src/domains/services/reconciliation/contract.hpp`
- `src/domains/services/reconciliation/service_controller.cpp`
- `src/domains/services/reconciliation/service_controller.hpp`
- `src/domains/storage/reconciliation/storage_controller.cpp`

### Existing test evidence
- `tests/rebuntu/test_storage_reconciliation.cpp`
- `tests/rebuntu/test_process_reconciliation.cpp`
- `tests/rebuntu/service_reconciliation_test.cpp`

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

- Structural skeleton materialized at `src/control/reconciliation/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/control/reconciliation/model/`
- `src/control/reconciliation/contracts/`
- `src/control/reconciliation/integration/`
- `src/control/reconciliation/verification/`
- `src/control/reconciliation/lifecycle/`
- `src/control/reconciliation/state/`
- `src/control/reconciliation/execution/`
- `src/control/reconciliation/transactions/`
- `src/control/reconciliation/events/`
- `src/control/reconciliation/scheduling/`
- `src/control/reconciliation/recovery/`
- `src/control/reconciliation/identity/`
- `src/control/reconciliation/resources/`
- `src/control/reconciliation/relationships/`
- `src/control/reconciliation/topology/`
- `src/control/reconciliation/capabilities/`
- `src/control/reconciliation/requirements/`
- `src/control/reconciliation/capacity/`



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

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `19.0`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.0.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_6ab6ed6a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_6ab6ed6a.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_6ab6ed6a.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_6ab6ed6a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.1`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.1.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_1b5964ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_1b5964ab.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_1b5964ab.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_1b5964ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.10`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.10.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_efbb1bce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_efbb1bce.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_efbb1bce.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_efbb1bce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.11`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.11.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_af4f7691/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_af4f7691.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_af4f7691.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_af4f7691.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.12`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.12.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_1ab664e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_1ab664e7.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_1ab664e7.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_1ab664e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.13`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.13.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_428b0dd1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_428b0dd1.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_428b0dd1.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_428b0dd1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.14`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.14.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_b9366ccf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_b9366ccf.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_b9366ccf.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_b9366ccf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.15`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.15.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_2cf968b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_2cf968b2.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_2cf968b2.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_2cf968b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.16`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.16.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_a0772e18/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_a0772e18.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_a0772e18.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_a0772e18.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.17`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.17.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_df641dfc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_df641dfc.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_df641dfc.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_df641dfc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.18`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.18.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_78144f1d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_78144f1d.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_78144f1d.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_78144f1d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.2`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.2.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_33f9206c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_33f9206c.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_33f9206c.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_33f9206c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.3`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.3.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_8ac2796f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_8ac2796f.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_8ac2796f.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_8ac2796f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.4`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.4.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_2fb584c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_2fb584c5.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_2fb584c5.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_2fb584c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.5`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.5.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_40e46cc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_40e46cc3.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_40e46cc3.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_40e46cc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.6`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.6.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_c83b5db1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_c83b5db1.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_c83b5db1.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_c83b5db1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.7`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.7.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_ad41d9dd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_ad41d9dd.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_ad41d9dd.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_ad41d9dd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.8`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.8.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_12346e75/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_12346e75.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_12346e75.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_12346e75.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `19.9`
- **Source:** `.phases/phases/phase-19-reconciliation/prompts/19.9.md`
- **Structural package:** `src/control/reconciliation/subtask_packages/verification/requirement_0d69554e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/reconciliation/subtask_targets/requirements/requirement_0d69554e.hpp`, `src/control/reconciliation/subtask_targets/requirements/requirement_0d69554e.cpp`
- **Structural test target:** `tests/structural-closure/control/reconciliation/requirements/test_requirement_0d69554e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

