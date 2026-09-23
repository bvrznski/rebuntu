# Phase 90 — Root Cause Diagnostic Reasoning — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-90-root-cause-diagnostic-reasoning/`
- Primary prompt location: `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_90` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 90 — Root-Cause Analysis & Diagnostic Reasoning System
- Rebuntu — Phase 90.10: Resources and topology
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
- Canonical skeleton: `src/knowledge/root-cause-diagnostic-reasoning/`
- Structural files: `src/knowledge/root-cause-diagnostic-reasoning/component.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/component.cpp`, `src/knowledge/root-cause-diagnostic-reasoning/IMPLEMENTATION.json`
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

- Structural skeleton materialized at `src/knowledge/root-cause-diagnostic-reasoning/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/knowledge/root-cause-diagnostic-reasoning/model/`
- `src/knowledge/root-cause-diagnostic-reasoning/contracts/`
- `src/knowledge/root-cause-diagnostic-reasoning/integration/`
- `src/knowledge/root-cause-diagnostic-reasoning/verification/`
- `src/knowledge/root-cause-diagnostic-reasoning/lifecycle/`
- `src/knowledge/root-cause-diagnostic-reasoning/state/`
- `src/knowledge/root-cause-diagnostic-reasoning/execution/`
- `src/knowledge/root-cause-diagnostic-reasoning/transactions/`
- `src/knowledge/root-cause-diagnostic-reasoning/events/`
- `src/knowledge/root-cause-diagnostic-reasoning/scheduling/`
- `src/knowledge/root-cause-diagnostic-reasoning/recovery/`
- `src/knowledge/root-cause-diagnostic-reasoning/principals/`
- `src/knowledge/root-cause-diagnostic-reasoning/groups/`
- `src/knowledge/root-cause-diagnostic-reasoning/roles/`
- `src/knowledge/root-cause-diagnostic-reasoning/resolution/`
- `src/knowledge/root-cause-diagnostic-reasoning/authorization/`
- `src/knowledge/root-cause-diagnostic-reasoning/credentials/`
- `src/knowledge/root-cause-diagnostic-reasoning/policy/`



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

### `90.0`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.0.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_36fda5d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_36fda5d6.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_36fda5d6.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_36fda5d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.1`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.1.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_530b8866/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_530b8866.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_530b8866.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_530b8866.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.10`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.10.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_a7848447/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_a7848447.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_a7848447.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_a7848447.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.11`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.11.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_1014206f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_1014206f.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_1014206f.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_1014206f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.12`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.12.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_50ee186c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_50ee186c.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_50ee186c.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_50ee186c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.13`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.13.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_1463a834/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_1463a834.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_1463a834.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_1463a834.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.14`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.14.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_6e69e067/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_6e69e067.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_6e69e067.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_6e69e067.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.15`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.15.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_8fd6ae33/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_8fd6ae33.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_8fd6ae33.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_8fd6ae33.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.16`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.16.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_badf9b9c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_badf9b9c.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_badf9b9c.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_badf9b9c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.17`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.17.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_d1da9b97/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d1da9b97.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d1da9b97.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_d1da9b97.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.18`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.18.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_69985681/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_69985681.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_69985681.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_69985681.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.19`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.19.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_ef47720c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_ef47720c.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_ef47720c.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_ef47720c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.2`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.2.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_abad3f9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_abad3f9b.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_abad3f9b.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_abad3f9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.20`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.20.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_d358b193/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d358b193.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d358b193.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_d358b193.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.21`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.21.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_4246c99e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_4246c99e.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_4246c99e.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_4246c99e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.22`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.22.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_356fb679/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_356fb679.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_356fb679.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_356fb679.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.23`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.23.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_63ea5f04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_63ea5f04.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_63ea5f04.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_63ea5f04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.3`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.3.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_d1ca3d0c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d1ca3d0c.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d1ca3d0c.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_d1ca3d0c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.4`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.4.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_ca24596b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_ca24596b.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_ca24596b.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_ca24596b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.5`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.5.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_69783d6a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_69783d6a.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_69783d6a.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_69783d6a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.6`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.6.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_88ae07c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_88ae07c3.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_88ae07c3.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_88ae07c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.7`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.7.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_02c6c5a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_02c6c5a1.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_02c6c5a1.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_02c6c5a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.8`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.8.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_d4c6315c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d4c6315c.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_d4c6315c.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_d4c6315c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `90.9`
- **Source:** `.phases/phases/phase-90-root-cause-diagnostic-reasoning/prompts/90.9.md`
- **Structural package:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_packages/verification/requirement_804b9484/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_804b9484.hpp`, `src/knowledge/root-cause-diagnostic-reasoning/subtask_targets/requirements/requirement_804b9484.cpp`
- **Structural test target:** `tests/structural-closure/knowledge/root-cause-diagnostic-reasoning/requirements/test_requirement_804b9484.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

