# Phase 12 — Stability And Recovery — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-12-stability-and-recovery/`
- Primary prompt location: `.phases/phases/phase-12-stability-and-recovery/prompts/`
- Prompt/specification Markdown files currently present: **27**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 27 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_12` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 12: Stability And Recovery
- Layout
- Prompt Index
- Agent Handoff — Phase 12
- Rebuntu --- Phase 12.20 --- Resilience / Fault-Injection Audit
- Agent Task
- Phase Mission
- Global Agent Contract
- Binding earlier phases
- Recovery is not reconciliation
- Recovery is not diagnosis
- Recovery is not "restart everything"

## Structural skeleton / canonical destination
- Canonical skeleton: `src/control/stability-and-recovery/`
- Structural files: `src/control/stability-and-recovery/component.hpp`, `src/control/stability-and-recovery/component.cpp`, `src/control/stability-and-recovery/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/control/recovery/README.md`
- `src/control/recovery/contract.hpp`
- `src/control/recovery/recovery.hpp`
- `src/domains/networking/recovery/README.md`
- `src/domains/networking/recovery/contract.hpp`
- `src/domains/processes/recovery/README.md`
- `src/domains/processes/recovery/contract.hpp`
- `src/domains/services/recovery/README.md`
- `src/domains/services/recovery/contract.hpp`
- `src/domains/software/recovery/README.md`
- `src/domains/software/recovery/contract.hpp`
- `src/domains/storage/recovery/README.md`

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

- Structural skeleton materialized at `src/control/stability-and-recovery/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/control/stability-and-recovery/model/`
- `src/control/stability-and-recovery/contracts/`
- `src/control/stability-and-recovery/integration/`
- `src/control/stability-and-recovery/verification/`
- `src/control/stability-and-recovery/lifecycle/`
- `src/control/stability-and-recovery/state/`
- `src/control/stability-and-recovery/execution/`
- `src/control/stability-and-recovery/transactions/`
- `src/control/stability-and-recovery/events/`
- `src/control/stability-and-recovery/scheduling/`
- `src/control/stability-and-recovery/recovery/`
- `src/control/stability-and-recovery/identity/`
- `src/control/stability-and-recovery/resources/`
- `src/control/stability-and-recovery/relationships/`
- `src/control/stability-and-recovery/topology/`
- `src/control/stability-and-recovery/capabilities/`
- `src/control/stability-and-recovery/requirements/`
- `src/control/stability-and-recovery/capacity/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

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

### `12.0`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.0.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_50cf372f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_50cf372f.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_50cf372f.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_50cf372f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.1`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.1.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_af33c7b3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_af33c7b3.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_af33c7b3.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_af33c7b3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.10`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.10.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_c3101e67/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_c3101e67.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_c3101e67.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_c3101e67.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.11`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.11.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_2fe7ec69/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_2fe7ec69.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_2fe7ec69.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_2fe7ec69.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.12`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.12.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_312528d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_312528d5.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_312528d5.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_312528d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.13`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.13.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_c4b5f50c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_c4b5f50c.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_c4b5f50c.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_c4b5f50c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.14`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.14.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_13164634/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_13164634.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_13164634.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_13164634.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.15`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.15.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_4cadca8f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_4cadca8f.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_4cadca8f.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_4cadca8f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.16`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.16.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_bbba1d26/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_bbba1d26.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_bbba1d26.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_bbba1d26.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.17`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.17.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_bbc79bec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_bbc79bec.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_bbc79bec.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_bbc79bec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.18`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.18.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_eda43b31/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_eda43b31.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_eda43b31.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_eda43b31.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.19`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.19.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_3be66248/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_3be66248.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_3be66248.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_3be66248.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.2`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.2.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_61608f3e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_61608f3e.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_61608f3e.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_61608f3e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.20`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.20.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_5b0f5f4a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_5b0f5f4a.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_5b0f5f4a.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_5b0f5f4a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.3`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.3.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_e7136d72/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_e7136d72.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_e7136d72.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_e7136d72.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.4`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.4.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_d1aef997/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_d1aef997.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_d1aef997.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_d1aef997.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.5`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.5.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_f94097af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_f94097af.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_f94097af.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_f94097af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.6`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.6.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_ec3ff441/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_ec3ff441.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_ec3ff441.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_ec3ff441.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.7`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.7.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_a8249a76/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_a8249a76.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_a8249a76.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_a8249a76.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.8`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.8.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_2d548512/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_2d548512.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_2d548512.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_2d548512.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `12.9`
- **Source:** `.phases/phases/phase-12-stability-and-recovery/prompts/12.9.md`
- **Structural package:** `src/control/stability-and-recovery/subtask_packages/verification/requirement_ed0bef59/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/control/stability-and-recovery/subtask_targets/requirements/requirement_ed0bef59.hpp`, `src/control/stability-and-recovery/subtask_targets/requirements/requirement_ed0bef59.cpp`
- **Structural test target:** `tests/structural-closure/control/stability-and-recovery/requirements/test_requirement_ed0bef59.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

