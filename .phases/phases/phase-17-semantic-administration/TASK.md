# Phase 17 — Semantic Administration — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-17-semantic-administration/`
- Primary prompt location: `.phases/phases/phase-17-semantic-administration/prompts/`
- Prompt/specification Markdown files currently present: **25**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 25 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_17` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 17: Semantic Administration
- Layout
- Prompt Index
- Agent Handoff — Phase 17
- Rebuntu --- Phase 17.1 --- Semantic Intent Parsing
- Agent Task
- Phase Mission
- Global Agent Contract
- Typed Semantic IR
- Semantic Object Resolution and Ambiguity
- Facts, Evidence and Semantic Claims
- Logs, Events and Alerts as Untrusted Content

## Structural skeleton / canonical destination
- Canonical skeleton: `src/semantics/semantic-administration/`
- Structural files: `src/semantics/semantic-administration/component.hpp`, `src/semantics/semantic-administration/component.cpp`, `src/semantics/semantic-administration/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/system/shell/sources/administration/_init.sh`

### Existing test evidence
- `tests/native/test_semantic_provider.cpp`

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

- Structural skeleton materialized at `src/semantics/semantic-administration/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/semantics/semantic-administration/model/`
- `src/semantics/semantic-administration/contracts/`
- `src/semantics/semantic-administration/integration/`
- `src/semantics/semantic-administration/verification/`
- `src/semantics/semantic-administration/lifecycle/`
- `src/semantics/semantic-administration/state/`
- `src/semantics/semantic-administration/execution/`
- `src/semantics/semantic-administration/transactions/`
- `src/semantics/semantic-administration/events/`
- `src/semantics/semantic-administration/scheduling/`
- `src/semantics/semantic-administration/recovery/`
- `src/semantics/semantic-administration/principals/`
- `src/semantics/semantic-administration/groups/`
- `src/semantics/semantic-administration/roles/`
- `src/semantics/semantic-administration/resolution/`
- `src/semantics/semantic-administration/authorization/`
- `src/semantics/semantic-administration/credentials/`
- `src/semantics/semantic-administration/policy/`



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

### `17.0`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.0.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_bbec9461/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_bbec9461.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_bbec9461.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_bbec9461.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.1`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.1.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_428f8291/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_428f8291.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_428f8291.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_428f8291.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.10`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.10.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_9cca9fc2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_9cca9fc2.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_9cca9fc2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_9cca9fc2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.11`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.11.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_95a2155c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_95a2155c.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_95a2155c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_95a2155c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.12`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.12.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_c8203557/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_c8203557.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_c8203557.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_c8203557.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.13`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.13.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_fbfdabe6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_fbfdabe6.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_fbfdabe6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_fbfdabe6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.14`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.14.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_8106e9c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_8106e9c8.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_8106e9c8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_8106e9c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.15`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.15.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_6290b426/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_6290b426.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_6290b426.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_6290b426.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.16`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.16.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_1bcdc7c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_1bcdc7c4.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_1bcdc7c4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_1bcdc7c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.17`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.17.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_63c5e680/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_63c5e680.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_63c5e680.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_63c5e680.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.18`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.18.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_0979cc89/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_0979cc89.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_0979cc89.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_0979cc89.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.2`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.2.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_633339f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_633339f0.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_633339f0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_633339f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.3`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.3.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_cb638d56/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_cb638d56.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_cb638d56.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_cb638d56.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.4`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.4.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_d3838f44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_d3838f44.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_d3838f44.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_d3838f44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.5`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.5.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_5b911d56/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_5b911d56.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_5b911d56.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_5b911d56.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.6`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.6.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_2770049e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_2770049e.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_2770049e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_2770049e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.7`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.7.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_343a1a88/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_343a1a88.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_343a1a88.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_343a1a88.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.8`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.8.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_8da4a07d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_8da4a07d.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_8da4a07d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_8da4a07d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `17.9`
- **Source:** `.phases/phases/phase-17-semantic-administration/prompts/17.9.md`
- **Structural package:** `src/semantics/semantic-administration/subtask_packages/verification/requirement_80f8c6dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/semantic-administration/subtask_targets/requirements/requirement_80f8c6dc.hpp`, `src/semantics/semantic-administration/subtask_targets/requirements/requirement_80f8c6dc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/semantic-administration/requirements/test_requirement_80f8c6dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

