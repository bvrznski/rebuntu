# Phase 88 — Counterfactual Analysis — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-88-counterfactual-analysis/`
- Primary prompt location: `.phases/phases/phase-88-counterfactual-analysis/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_88` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 88 — Counterfactual Analysis System
- Rebuntu — Phase 88.21: Python model shell authority audit
- Mission
- Non-negotiable invariants
- Repository discovery
- DISCOVER
- RECONSTRUCT
- DESIGN
- IMPLEMENT
- INTEGRATE
- SECURE
- VERIFY

## Structural skeleton / canonical destination
- Canonical skeleton: `src/planning/counterfactual-analysis/`
- Structural files: `src/planning/counterfactual-analysis/component.hpp`, `src/planning/counterfactual-analysis/component.cpp`, `src/planning/counterfactual-analysis/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/domains/logs/analysis/README.md`
- `src/domains/logs/analysis/contract.hpp`

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

- Structural skeleton materialized at `src/planning/counterfactual-analysis/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/planning/counterfactual-analysis/model/`
- `src/planning/counterfactual-analysis/contracts/`
- `src/planning/counterfactual-analysis/integration/`
- `src/planning/counterfactual-analysis/verification/`
- `src/planning/counterfactual-analysis/lifecycle/`
- `src/planning/counterfactual-analysis/state/`
- `src/planning/counterfactual-analysis/execution/`
- `src/planning/counterfactual-analysis/transactions/`
- `src/planning/counterfactual-analysis/events/`
- `src/planning/counterfactual-analysis/scheduling/`
- `src/planning/counterfactual-analysis/recovery/`
- `src/planning/counterfactual-analysis/principals/`
- `src/planning/counterfactual-analysis/groups/`
- `src/planning/counterfactual-analysis/roles/`
- `src/planning/counterfactual-analysis/resolution/`
- `src/planning/counterfactual-analysis/authorization/`
- `src/planning/counterfactual-analysis/credentials/`
- `src/planning/counterfactual-analysis/policy/`



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

### `88.0`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.0.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_89ef5401/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_89ef5401.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_89ef5401.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_89ef5401.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.1`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.1.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_2e590260/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_2e590260.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_2e590260.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_2e590260.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.10`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.10.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_91b19c72/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_91b19c72.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_91b19c72.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_91b19c72.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.11`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.11.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_6d0e2080/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_6d0e2080.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_6d0e2080.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_6d0e2080.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.12`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.12.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_d8c02f47/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_d8c02f47.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_d8c02f47.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_d8c02f47.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.13`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.13.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_dd45adee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_dd45adee.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_dd45adee.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_dd45adee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.14`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.14.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_15815f9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_15815f9b.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_15815f9b.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_15815f9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.15`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.15.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_157e18af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_157e18af.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_157e18af.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_157e18af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.16`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.16.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_2d36e975/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_2d36e975.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_2d36e975.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_2d36e975.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.17`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.17.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_2c5da04a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_2c5da04a.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_2c5da04a.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_2c5da04a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.18`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.18.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_96218709/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_96218709.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_96218709.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_96218709.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.19`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.19.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_7579b1df/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_7579b1df.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_7579b1df.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_7579b1df.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.2`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.2.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_ca982c8f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_ca982c8f.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_ca982c8f.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_ca982c8f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.20`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.20.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_4bebb99e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_4bebb99e.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_4bebb99e.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_4bebb99e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.21`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.21.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_68c31e8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_68c31e8d.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_68c31e8d.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_68c31e8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.22`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.22.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_79a4edb1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_79a4edb1.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_79a4edb1.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_79a4edb1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.23`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.23.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_9959b5a5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_9959b5a5.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_9959b5a5.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_9959b5a5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.3`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.3.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_108d3a20/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_108d3a20.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_108d3a20.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_108d3a20.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.4`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.4.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_91b8fa14/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_91b8fa14.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_91b8fa14.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_91b8fa14.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.5`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.5.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_c7abf60c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_c7abf60c.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_c7abf60c.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_c7abf60c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.6`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.6.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_cb570abc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_cb570abc.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_cb570abc.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_cb570abc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.7`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.7.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_dbd7a98a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_dbd7a98a.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_dbd7a98a.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_dbd7a98a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.8`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.8.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_0227c396/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_0227c396.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_0227c396.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_0227c396.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `88.9`
- **Source:** `.phases/phases/phase-88-counterfactual-analysis/prompts/88.9.md`
- **Structural package:** `src/planning/counterfactual-analysis/subtask_packages/verification/requirement_bffa8d11/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_bffa8d11.hpp`, `src/planning/counterfactual-analysis/subtask_targets/requirements/requirement_bffa8d11.cpp`
- **Structural test target:** `tests/structural-closure/planning/counterfactual-analysis/requirements/test_requirement_bffa8d11.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

