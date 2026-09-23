# Phase 91 — Uncertainty Evidence Reasoning — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-91-uncertainty-evidence-reasoning/`
- Primary prompt location: `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_91` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 91 — Uncertainty & Evidence Reasoning System
- Rebuntu — Phase 91.18: CLI GUI natural-language integration
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
- Canonical skeleton: `src/knowledge/uncertainty-evidence-reasoning/`
- Structural files: `src/knowledge/uncertainty-evidence-reasoning/component.hpp`, `src/knowledge/uncertainty-evidence-reasoning/component.cpp`, `src/knowledge/uncertainty-evidence-reasoning/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/semantics/evidence/README.md`
- `src/semantics/evidence/contract.hpp`

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

- Structural skeleton materialized at `src/knowledge/uncertainty-evidence-reasoning/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/knowledge/uncertainty-evidence-reasoning/model/`
- `src/knowledge/uncertainty-evidence-reasoning/contracts/`
- `src/knowledge/uncertainty-evidence-reasoning/integration/`
- `src/knowledge/uncertainty-evidence-reasoning/verification/`
- `src/knowledge/uncertainty-evidence-reasoning/lifecycle/`
- `src/knowledge/uncertainty-evidence-reasoning/state/`
- `src/knowledge/uncertainty-evidence-reasoning/execution/`
- `src/knowledge/uncertainty-evidence-reasoning/transactions/`
- `src/knowledge/uncertainty-evidence-reasoning/events/`
- `src/knowledge/uncertainty-evidence-reasoning/scheduling/`
- `src/knowledge/uncertainty-evidence-reasoning/recovery/`
- `src/knowledge/uncertainty-evidence-reasoning/principals/`
- `src/knowledge/uncertainty-evidence-reasoning/groups/`
- `src/knowledge/uncertainty-evidence-reasoning/roles/`
- `src/knowledge/uncertainty-evidence-reasoning/resolution/`
- `src/knowledge/uncertainty-evidence-reasoning/authorization/`
- `src/knowledge/uncertainty-evidence-reasoning/credentials/`
- `src/knowledge/uncertainty-evidence-reasoning/policy/`



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

### `91.0`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.0.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_25cf2dae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_25cf2dae.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_25cf2dae.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_25cf2dae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.1`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.1.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_f876e81b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_f876e81b.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_f876e81b.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_f876e81b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.10`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.10.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_d2a30d3d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_d2a30d3d.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_d2a30d3d.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_d2a30d3d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.11`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.11.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_71a2a4f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_71a2a4f2.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_71a2a4f2.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_71a2a4f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.12`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.12.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_58a69ccd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_58a69ccd.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_58a69ccd.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_58a69ccd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.13`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.13.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_b1d35de5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_b1d35de5.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_b1d35de5.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_b1d35de5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.14`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.14.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_04be4341/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_04be4341.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_04be4341.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_04be4341.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.15`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.15.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_7b33fd56/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_7b33fd56.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_7b33fd56.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_7b33fd56.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.16`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.16.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_8321fdf8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_8321fdf8.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_8321fdf8.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_8321fdf8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.17`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.17.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_69d2e5e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_69d2e5e0.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_69d2e5e0.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_69d2e5e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.18`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.18.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_453b10d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_453b10d1.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_453b10d1.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_453b10d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.19`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.19.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_79042d6c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_79042d6c.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_79042d6c.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_79042d6c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.2`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.2.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_14093078/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_14093078.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_14093078.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_14093078.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.20`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.20.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_579f510a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_579f510a.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_579f510a.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_579f510a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.21`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.21.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_21469e3e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_21469e3e.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_21469e3e.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_21469e3e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.22`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.22.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_f51b8306/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_f51b8306.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_f51b8306.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_f51b8306.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.23`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.23.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_805f9809/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_805f9809.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_805f9809.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_805f9809.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.3`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.3.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_0bfa2fc8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_0bfa2fc8.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_0bfa2fc8.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_0bfa2fc8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.4`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.4.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_5cf60228/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_5cf60228.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_5cf60228.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_5cf60228.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.5`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.5.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_38c732b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_38c732b2.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_38c732b2.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_38c732b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.6`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.6.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_bdd4b226/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_bdd4b226.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_bdd4b226.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_bdd4b226.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.7`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.7.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_a0591d83/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_a0591d83.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_a0591d83.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_a0591d83.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.8`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.8.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_3c7dc8ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_3c7dc8ea.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_3c7dc8ea.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_3c7dc8ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `91.9`
- **Source:** `.phases/phases/phase-91-uncertainty-evidence-reasoning/prompts/91.9.md`
- **Structural package:** `src/knowledge/uncertainty-evidence-reasoning/subtask_packages/verification/requirement_b7e89045/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_b7e89045.hpp`, `src/knowledge/uncertainty-evidence-reasoning/subtask_targets/requirements/requirement_b7e89045.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/uncertainty-evidence-reasoning/requirements/test_requirement_b7e89045.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

