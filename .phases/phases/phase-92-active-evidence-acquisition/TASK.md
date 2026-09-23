# Phase 92 — Active Evidence Acquisition — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-92-active-evidence-acquisition/`
- Primary prompt location: `.phases/phases/phase-92-active-evidence-acquisition/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_92` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 92 — Active Evidence Acquisition System
- Rebuntu — Phase 92.1: Canonical ontology and identity
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
- Canonical skeleton: `src/observation/active-evidence-acquisition/`
- Structural files: `src/observation/active-evidence-acquisition/component.hpp`, `src/observation/active-evidence-acquisition/component.cpp`, `src/observation/active-evidence-acquisition/IMPLEMENTATION.json`
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

- Structural skeleton materialized at `src/observation/active-evidence-acquisition/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/observation/active-evidence-acquisition/model/`
- `src/observation/active-evidence-acquisition/contracts/`
- `src/observation/active-evidence-acquisition/integration/`
- `src/observation/active-evidence-acquisition/verification/`
- `src/observation/active-evidence-acquisition/lifecycle/`
- `src/observation/active-evidence-acquisition/state/`
- `src/observation/active-evidence-acquisition/execution/`
- `src/observation/active-evidence-acquisition/transactions/`
- `src/observation/active-evidence-acquisition/events/`
- `src/observation/active-evidence-acquisition/scheduling/`
- `src/observation/active-evidence-acquisition/recovery/`
- `src/observation/active-evidence-acquisition/principals/`
- `src/observation/active-evidence-acquisition/groups/`
- `src/observation/active-evidence-acquisition/roles/`
- `src/observation/active-evidence-acquisition/resolution/`
- `src/observation/active-evidence-acquisition/authorization/`
- `src/observation/active-evidence-acquisition/credentials/`
- `src/observation/active-evidence-acquisition/policy/`



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

### `92.0`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.0.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_a3cd3c07/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_a3cd3c07.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_a3cd3c07.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_a3cd3c07.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.1`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.1.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_c847acce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_c847acce.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_c847acce.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_c847acce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.10`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.10.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_95162ae6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_95162ae6.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_95162ae6.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_95162ae6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.11`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.11.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_0eda7573/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_0eda7573.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_0eda7573.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_0eda7573.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.12`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.12.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_24a97c08/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_24a97c08.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_24a97c08.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_24a97c08.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.13`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.13.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_f4b7673d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_f4b7673d.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_f4b7673d.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_f4b7673d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.14`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.14.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_e0255dcc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_e0255dcc.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_e0255dcc.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_e0255dcc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.15`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.15.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_8702fe1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_8702fe1f.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_8702fe1f.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_8702fe1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.16`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.16.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_13fa5831/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_13fa5831.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_13fa5831.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_13fa5831.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.17`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.17.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_5b7820dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_5b7820dc.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_5b7820dc.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_5b7820dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.18`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.18.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_3ed3abdc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_3ed3abdc.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_3ed3abdc.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_3ed3abdc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.19`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.19.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_8515258d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_8515258d.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_8515258d.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_8515258d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.2`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.2.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_21a16d9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_21a16d9b.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_21a16d9b.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_21a16d9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.20`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.20.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_78516cdc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_78516cdc.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_78516cdc.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_78516cdc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.21`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.21.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_174ff5e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_174ff5e4.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_174ff5e4.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_174ff5e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.22`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.22.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_c22bb3b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_c22bb3b7.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_c22bb3b7.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_c22bb3b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.23`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.23.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_ed834a6c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_ed834a6c.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_ed834a6c.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_ed834a6c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.3`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.3.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_c59b17a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_c59b17a9.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_c59b17a9.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_c59b17a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.4`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.4.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_a0a1fdfe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_a0a1fdfe.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_a0a1fdfe.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_a0a1fdfe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.5`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.5.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_07a1912e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_07a1912e.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_07a1912e.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_07a1912e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.6`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.6.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_27dcff1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_27dcff1f.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_27dcff1f.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_27dcff1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.7`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.7.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_7c5d9b24/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_7c5d9b24.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_7c5d9b24.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_7c5d9b24.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.8`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.8.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_a997c3cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_a997c3cf.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_a997c3cf.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_a997c3cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `92.9`
- **Source:** `.phases/phases/phase-92-active-evidence-acquisition/prompts/92.9.md`
- **Structural package:** `src/observation/active-evidence-acquisition/subtask_packages/verification/requirement_5f845158/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_5f845158.hpp`, `src/observation/active-evidence-acquisition/subtask_targets/requirements/requirement_5f845158.cpp`
- **Structural test target:** `tests/structural-closure/observation/active-evidence-acquisition/requirements/test_requirement_5f845158.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

