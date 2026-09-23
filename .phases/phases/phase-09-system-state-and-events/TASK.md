# Phase 09 — System State And Events — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-09-system-state-and-events/`
- Primary prompt location: `.phases/phases/phase-09-system-state-and-events/prompts/`
- Prompt/specification Markdown files currently present: **25**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 25 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_09` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 9: System State And Events
- Layout
- Prompt Index
- Agent Handoff — Phase 9
- Rebuntu --- Phase 9.16 --- Historical Automaton Migration
- Agent Task
- Phase Mission
- Core architectural contract
- Native Linux first
- Automaton ontology
- Activation semantics
- Overlap, concurrency and idempotency

## Structural skeleton / canonical destination
- Canonical skeleton: `src/runtime/system-state-and-events/`
- Structural files: `src/runtime/system-state-and-events/component.hpp`, `src/runtime/system-state-and-events/component.cpp`, `src/runtime/system-state-and-events/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/logs/events/README.md`
- `src/domains/logs/events/contract.hpp`
- `src/observation/events/README.md`
- `src/observation/events/contract.hpp`
- `src/providers/linux/udev/events/README.md`
- `src/providers/linux/udev/events/contract.hpp`
- `src/runtime/events/README.md`
- `src/runtime/events/contract.hpp`
- `src/runtime/events/engine.hpp`
- `src/runtime/state/README.md`
- `src/runtime/state/contract.hpp`
- `src/runtime/state/persistence/journal.hpp`

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
- Baseline ledger created automatically from the current repository. Depth **3/5** is deliberately conservative and not a completion claim.

- Structural skeleton materialized at `src/runtime/system-state-and-events/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/runtime/system-state-and-events/model/`
- `src/runtime/system-state-and-events/contracts/`
- `src/runtime/system-state-and-events/integration/`
- `src/runtime/system-state-and-events/verification/`
- `src/runtime/system-state-and-events/lifecycle/`
- `src/runtime/system-state-and-events/state/`
- `src/runtime/system-state-and-events/execution/`
- `src/runtime/system-state-and-events/transactions/`
- `src/runtime/system-state-and-events/events/`
- `src/runtime/system-state-and-events/scheduling/`
- `src/runtime/system-state-and-events/recovery/`
- `src/runtime/system-state-and-events/principals/`
- `src/runtime/system-state-and-events/groups/`
- `src/runtime/system-state-and-events/roles/`
- `src/runtime/system-state-and-events/resolution/`
- `src/runtime/system-state-and-events/authorization/`
- `src/runtime/system-state-and-events/credentials/`
- `src/runtime/system-state-and-events/policy/`



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

### `9.0`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.0.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_45091c36/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_45091c36.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_45091c36.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_45091c36.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.1`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.1.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_b49d7b0a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_b49d7b0a.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_b49d7b0a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_b49d7b0a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.10`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.10.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_fa0927bc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_fa0927bc.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_fa0927bc.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_fa0927bc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.11`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.11.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_9131fcff/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_9131fcff.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_9131fcff.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_9131fcff.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.12`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.12.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_36e89bf1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_36e89bf1.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_36e89bf1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_36e89bf1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.13`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.13.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_1df7d1a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_1df7d1a3.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_1df7d1a3.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_1df7d1a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.14`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.14.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_d7e0f0df/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_d7e0f0df.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_d7e0f0df.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_d7e0f0df.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.15`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.15.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_45d993c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_45d993c4.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_45d993c4.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_45d993c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.16`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.16.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_f10e61f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_f10e61f9.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_f10e61f9.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_f10e61f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.17`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.17.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_8e15e9ef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_8e15e9ef.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_8e15e9ef.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_8e15e9ef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.18`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.18.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_95dfa2ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_95dfa2ba.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_95dfa2ba.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_95dfa2ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.2`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.2.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_927db332/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_927db332.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_927db332.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_927db332.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.3`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.3.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_5aa71856/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_5aa71856.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_5aa71856.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_5aa71856.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.4`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.4.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_2c136df1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_2c136df1.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_2c136df1.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_2c136df1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.5`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.5.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_f998c264/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_f998c264.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_f998c264.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_f998c264.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.6`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.6.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_b9dd0103/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_b9dd0103.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_b9dd0103.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_b9dd0103.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.7`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.7.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_d5d15710/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_d5d15710.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_d5d15710.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_d5d15710.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.8`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.8.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_046c41ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_046c41ec.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_046c41ec.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_046c41ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `9.9`
- **Source:** `.phases/phases/phase-09-system-state-and-events/prompts/9.9.md`
- **Structural package:** `src/runtime/system-state-and-events/subtask_packages/verification/requirement_42056556/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_42056556.hpp`, `src/runtime/system-state-and-events/subtask_targets/requirements/requirement_42056556.cpp`
- **Structural test target:** `tests/structural-closure/runtime/system-state-and-events/requirements/test_requirement_42056556.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

