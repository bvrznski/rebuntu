# Phase 18 — Capability Registry — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-18-capability-registry/`
- Primary prompt location: `.phases/phases/phase-18-capability-registry/prompts/`
- Prompt/specification Markdown files currently present: **27**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 27 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_18` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 18: Capability Registry
- Layout
- Prompt Index
- Agent Handoff — Phase 18
- Rebuntu --- Phase 18.9 --- Research Pipeline
- Agent Task
- Phase Mission
- Global Agent Contract
- Canonical Capability Model
- Inventory and Discovery
- Capability Search
- Composition Search

## Structural skeleton / canonical destination
- Canonical skeleton: `src/semantics/capability-registry/`
- Structural files: `src/semantics/capability-registry/component.hpp`, `src/semantics/capability-registry/component.cpp`, `src/semantics/capability-registry/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/observation/environment/capability_state.hpp`
- `src/security/authorization/capability_state.cpp`

### Existing test evidence
- `tests/native/test_capability_state.cpp`

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

- Structural skeleton materialized at `src/semantics/capability-registry/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/semantics/capability-registry/model/`
- `src/semantics/capability-registry/contracts/`
- `src/semantics/capability-registry/integration/`
- `src/semantics/capability-registry/verification/`
- `src/semantics/capability-registry/lifecycle/`
- `src/semantics/capability-registry/state/`
- `src/semantics/capability-registry/execution/`
- `src/semantics/capability-registry/transactions/`
- `src/semantics/capability-registry/events/`
- `src/semantics/capability-registry/scheduling/`
- `src/semantics/capability-registry/recovery/`
- `src/semantics/capability-registry/principals/`
- `src/semantics/capability-registry/groups/`
- `src/semantics/capability-registry/roles/`
- `src/semantics/capability-registry/resolution/`
- `src/semantics/capability-registry/authorization/`
- `src/semantics/capability-registry/credentials/`
- `src/semantics/capability-registry/policy/`



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

### `18.0`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.0.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_db12c918/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_db12c918.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_db12c918.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_db12c918.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.1`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.1.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_6ce6ec9f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_6ce6ec9f.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_6ce6ec9f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_6ce6ec9f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.10`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.10.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_cf1f9121/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_cf1f9121.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_cf1f9121.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_cf1f9121.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.11`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.11.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_c6a9ff24/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_c6a9ff24.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_c6a9ff24.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_c6a9ff24.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.12`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.12.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_06726207/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_06726207.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_06726207.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_06726207.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.13`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.13.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_eb9b0e83/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_eb9b0e83.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_eb9b0e83.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_eb9b0e83.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.14`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.14.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_c0c24d05/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_c0c24d05.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_c0c24d05.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_c0c24d05.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.15`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.15.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_686bf08b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_686bf08b.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_686bf08b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_686bf08b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.16`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.16.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_177052a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_177052a4.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_177052a4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_177052a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.17`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.17.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_18ed7e5f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_18ed7e5f.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_18ed7e5f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_18ed7e5f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.18`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.18.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_f5727fa0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_f5727fa0.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_f5727fa0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_f5727fa0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.19`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.19.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_e56c0443/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_e56c0443.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_e56c0443.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_e56c0443.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.2`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.2.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_abb81b93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_abb81b93.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_abb81b93.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_abb81b93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.20`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.20.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_c77e9680/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_c77e9680.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_c77e9680.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_c77e9680.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.3`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.3.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_1feecbfc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_1feecbfc.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_1feecbfc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_1feecbfc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.4`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.4.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_62b28359/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_62b28359.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_62b28359.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_62b28359.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.5`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.5.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_331b48f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_331b48f0.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_331b48f0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_331b48f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.6`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.6.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_006327ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_006327ea.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_006327ea.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_006327ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.7`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.7.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_705dbdbd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_705dbdbd.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_705dbdbd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_705dbdbd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.8`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.8.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_d1ada9cc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_d1ada9cc.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_d1ada9cc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_d1ada9cc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `18.9`
- **Source:** `.phases/phases/phase-18-capability-registry/prompts/18.9.md`
- **Structural package:** `src/semantics/capability-registry/subtask_packages/verification/requirement_6225b095/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/capability-registry/subtask_targets/requirements/requirement_6225b095.hpp`, `src/semantics/capability-registry/subtask_targets/requirements/requirement_6225b095.cpp`
- **Structural test target:** `tests/structural-closure/semantics/capability-registry/requirements/test_requirement_6225b095.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

