# Phase 04 — Stability And Shell — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-04-stability-and-shell/`
- Primary prompt location: `.phases/phases/phase-04-stability-and-shell/prompts/`
- Prompt/specification Markdown files currently present: **27**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 27 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_04` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 4: Stability And Shell
- Layout
- Prompt Index
- Agent Handoff — Phase 4
- Rebuntu — Phase 4.8 — Resolver
- Agent Task
- Global Agent Contract
- Mandatory engineering laws
- Required Context Before Coding
- Canonical Runtime Flow
- Runtime State Axes
- Concurrency & Resource Discipline

## Structural skeleton / canonical destination
- Canonical skeleton: `src/runtime/stability-and-shell/`
- Structural files: `src/runtime/stability-and-shell/component.hpp`, `src/runtime/stability-and-shell/component.cpp`, `src/runtime/stability-and-shell/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/shell/README.md`
- `src/domains/shell/commands/README.md`
- `src/domains/shell/commands/contract.hpp`
- `src/domains/shell/completion/README.md`
- `src/domains/shell/completion/contract.hpp`
- `src/domains/shell/desired_state/README.md`
- `src/domains/shell/desired_state/contract.hpp`
- `src/domains/shell/environments/README.md`
- `src/domains/shell/environments/contract.hpp`
- `src/domains/shell/history/README.md`
- `src/domains/shell/history/contract.hpp`
- `src/domains/shell/language.hpp`

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

- Structural skeleton materialized at `src/runtime/stability-and-shell/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/runtime/stability-and-shell/model/`
- `src/runtime/stability-and-shell/contracts/`
- `src/runtime/stability-and-shell/integration/`
- `src/runtime/stability-and-shell/verification/`
- `src/runtime/stability-and-shell/lifecycle/`
- `src/runtime/stability-and-shell/state/`
- `src/runtime/stability-and-shell/execution/`
- `src/runtime/stability-and-shell/transactions/`
- `src/runtime/stability-and-shell/events/`
- `src/runtime/stability-and-shell/scheduling/`
- `src/runtime/stability-and-shell/recovery/`
- `src/runtime/stability-and-shell/principals/`
- `src/runtime/stability-and-shell/groups/`
- `src/runtime/stability-and-shell/roles/`
- `src/runtime/stability-and-shell/resolution/`
- `src/runtime/stability-and-shell/authorization/`
- `src/runtime/stability-and-shell/credentials/`
- `src/runtime/stability-and-shell/policy/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `4.0`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.0.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_f14112cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_f14112cf.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_f14112cf.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_f14112cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.1`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.1.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_6c654d9e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_6c654d9e.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_6c654d9e.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_6c654d9e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.10`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.10.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_e78b837f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_e78b837f.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_e78b837f.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_e78b837f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.11`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.11.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_ec1968e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_ec1968e4.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_ec1968e4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_ec1968e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.12`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.12.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_296deb19/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_296deb19.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_296deb19.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_296deb19.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.13`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.13.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_2858d729/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_2858d729.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_2858d729.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_2858d729.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.14`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.14.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_6e1e8a03/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_6e1e8a03.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_6e1e8a03.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_6e1e8a03.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.15`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.15.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_6b2e6dab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_6b2e6dab.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_6b2e6dab.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_6b2e6dab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.16`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.16.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_77d867c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_77d867c4.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_77d867c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_77d867c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.17`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.17.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_d27daaf1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_d27daaf1.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_d27daaf1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_d27daaf1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.18`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.18.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_e75c8d37/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_e75c8d37.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_e75c8d37.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_e75c8d37.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.19`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.19.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_2b11e1c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_2b11e1c1.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_2b11e1c1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_2b11e1c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.2`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.2.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_773adafb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_773adafb.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_773adafb.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_773adafb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.20`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.20.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_a6b2a28d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_a6b2a28d.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_a6b2a28d.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_a6b2a28d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.3`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.3.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_363718fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_363718fe.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_363718fe.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_363718fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.4`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.4.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_21579349/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_21579349.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_21579349.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_21579349.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.5`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.5.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_5b691fd0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_5b691fd0.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_5b691fd0.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_5b691fd0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.6`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.6.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_9c473bcd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_9c473bcd.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_9c473bcd.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_9c473bcd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.7`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.7.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_c11502c6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_c11502c6.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_c11502c6.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_c11502c6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.8`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.8.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_d7967901/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_d7967901.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_d7967901.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_d7967901.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `4.9`
- **Source:** `.phases/phases/phase-04-stability-and-shell/prompts/4.9.md`
- **Structural package:** `src/runtime/stability-and-shell/subtask_packages/verification/requirement_cbabb260/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_cbabb260.hpp`, `src/runtime/stability-and-shell/subtask_targets/requirements/requirement_cbabb260.cpp`
- **Structural test target:** `tests/structural-closure/runtime/stability-and-shell/requirements/test_requirement_cbabb260.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

