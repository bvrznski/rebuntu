# Phase 80 — Machine Reproducibility Reconstruction — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-80-machine-reproducibility-reconstruction/`
- Primary prompt location: `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/`
- Prompt/specification Markdown files currently present: **26**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 26 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_80` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 80 — Machine Reproducibility & Reconstruction System
- Rebuntu — Phase 80.17: Boundedness and budgets
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
- Canonical skeleton: `src/domains/machine-reproducibility-reconstruction/`
- Structural files: `src/domains/machine-reproducibility-reconstruction/component.hpp`, `src/domains/machine-reproducibility-reconstruction/component.cpp`, `src/domains/machine-reproducibility-reconstruction/IMPLEMENTATION.json`
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

- Structural skeleton materialized at `src/domains/machine-reproducibility-reconstruction/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/domains/machine-reproducibility-reconstruction/model/`
- `src/domains/machine-reproducibility-reconstruction/contracts/`
- `src/domains/machine-reproducibility-reconstruction/integration/`
- `src/domains/machine-reproducibility-reconstruction/verification/`
- `src/domains/machine-reproducibility-reconstruction/lifecycle/`
- `src/domains/machine-reproducibility-reconstruction/state/`
- `src/domains/machine-reproducibility-reconstruction/execution/`
- `src/domains/machine-reproducibility-reconstruction/transactions/`
- `src/domains/machine-reproducibility-reconstruction/events/`
- `src/domains/machine-reproducibility-reconstruction/scheduling/`
- `src/domains/machine-reproducibility-reconstruction/recovery/`
- `src/domains/machine-reproducibility-reconstruction/principals/`
- `src/domains/machine-reproducibility-reconstruction/groups/`
- `src/domains/machine-reproducibility-reconstruction/roles/`
- `src/domains/machine-reproducibility-reconstruction/resolution/`
- `src/domains/machine-reproducibility-reconstruction/authorization/`
- `src/domains/machine-reproducibility-reconstruction/credentials/`
- `src/domains/machine-reproducibility-reconstruction/policy/`



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

### `80.0`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.0.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_f2973afd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_f2973afd.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_f2973afd.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_f2973afd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.1`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.1.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_dab0b50b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_dab0b50b.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_dab0b50b.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_dab0b50b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.10`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.10.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_1885fecf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_1885fecf.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_1885fecf.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_1885fecf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.11`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.11.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_cdf0d7dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_cdf0d7dc.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_cdf0d7dc.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_cdf0d7dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.12`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.12.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_406170af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_406170af.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_406170af.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_406170af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.13`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.13.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_2a3dd283/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_2a3dd283.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_2a3dd283.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_2a3dd283.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.14`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.14.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_cb3d2b77/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_cb3d2b77.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_cb3d2b77.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_cb3d2b77.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.15`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.15.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_b8c0f91b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_b8c0f91b.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_b8c0f91b.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_b8c0f91b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.16`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.16.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_f8089077/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_f8089077.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_f8089077.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_f8089077.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.17`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.17.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_29ea443d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_29ea443d.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_29ea443d.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_29ea443d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.18`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.18.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_42af7e15/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_42af7e15.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_42af7e15.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_42af7e15.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.19`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.19.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_64383ea9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_64383ea9.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_64383ea9.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_64383ea9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.2`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.2.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_e41533e6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_e41533e6.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_e41533e6.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_e41533e6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.20`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.20.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_f3a9f5ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_f3a9f5ea.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_f3a9f5ea.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_f3a9f5ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.21`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.21.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_bec03560/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_bec03560.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_bec03560.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_bec03560.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.22`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.22.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_1e98974b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_1e98974b.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_1e98974b.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_1e98974b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.23`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.23.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_a6a1d4e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_a6a1d4e5.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_a6a1d4e5.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_a6a1d4e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.3`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.3.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_da911b6b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_da911b6b.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_da911b6b.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_da911b6b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.4`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.4.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_7a0aa631/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_7a0aa631.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_7a0aa631.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_7a0aa631.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.5`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.5.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_7eddd6f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_7eddd6f7.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_7eddd6f7.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_7eddd6f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.6`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.6.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_d964469a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_d964469a.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_d964469a.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_d964469a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.7`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.7.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_d28e771c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_d28e771c.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_d28e771c.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_d28e771c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.8`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.8.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_38396a18/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_38396a18.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_38396a18.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_38396a18.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `80.9`
- **Source:** `.phases/phases/phase-80-machine-reproducibility-reconstruction/prompts/80.9.md`
- **Structural package:** `src/domains/machine-reproducibility-reconstruction/subtask_packages/verification/requirement_b0110c05/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_b0110c05.hpp`, `src/domains/machine-reproducibility-reconstruction/subtask_targets/requirements/requirement_b0110c05.cpp`
- **Structural test target:** `tests/structural-closure/domains/machine-reproducibility-reconstruction/requirements/test_requirement_b0110c05.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

