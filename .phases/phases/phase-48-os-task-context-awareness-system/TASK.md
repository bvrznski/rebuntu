# Phase 48 — Os Task Context Awareness System — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-48-os-task-context-awareness-system/`
- Primary prompt location: `.phases/phases/phase-48-os-task-context-awareness-system/prompts/`
- Prompt/specification Markdown files currently present: **425**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 425 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_48` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 48 — OS Task Context Awareness System
- Phase 48 Index
- Normative architecture
- Full executable prompts
- Phase 48 Agent Handoff
- Phase 48.323 — GPU task context scenario
- Objective
- Repository-first execution
- Core context contract
- Relevance and bounded awareness
- Current-state and temporal correctness
- Operator/task awareness

## Structural skeleton / canonical destination
- Canonical skeleton: `src/semantics/os-task-context-awareness-system/`
- Structural files: `src/semantics/os-task-context-awareness-system/component.hpp`, `src/semantics/os-task-context-awareness-system/component.cpp`, `src/semantics/os-task-context-awareness-system/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/operator/context/README.md`
- `src/operator/context/contract.hpp`
- `src/semantics/context/README.md`
- `src/semantics/context/contract.hpp`

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

- Structural skeleton materialized at `src/semantics/os-task-context-awareness-system/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/semantics/os-task-context-awareness-system/model/`
- `src/semantics/os-task-context-awareness-system/contracts/`
- `src/semantics/os-task-context-awareness-system/integration/`
- `src/semantics/os-task-context-awareness-system/verification/`
- `src/semantics/os-task-context-awareness-system/lifecycle/`
- `src/semantics/os-task-context-awareness-system/state/`
- `src/semantics/os-task-context-awareness-system/execution/`
- `src/semantics/os-task-context-awareness-system/transactions/`
- `src/semantics/os-task-context-awareness-system/events/`
- `src/semantics/os-task-context-awareness-system/scheduling/`
- `src/semantics/os-task-context-awareness-system/recovery/`
- `src/semantics/os-task-context-awareness-system/principals/`
- `src/semantics/os-task-context-awareness-system/groups/`
- `src/semantics/os-task-context-awareness-system/roles/`
- `src/semantics/os-task-context-awareness-system/resolution/`
- `src/semantics/os-task-context-awareness-system/authorization/`
- `src/semantics/os-task-context-awareness-system/credentials/`
- `src/semantics/os-task-context-awareness-system/policy/`



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

### `48.000-foundation-and-repository-archaeology`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.000-foundation-and-repository-archaeology.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/foundation_and_repository_archaeology_5d285489/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/foundation_and_repository_archaeology_5d285489.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/foundation_and_repository_archaeology_5d285489.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_foundation_and_repository_archaeology_5d285489.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.001-existing-context-inventory`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.001-existing-context-inventory.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/existing_context_inventory_bcc128d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/existing_context_inventory_bcc128d4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/existing_context_inventory_bcc128d4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_existing_context_inventory_bcc128d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.002-canonical-architecture`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.002-canonical-architecture.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/canonical_architecture_4dfa4ae2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/canonical_architecture_4dfa4ae2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/canonical_architecture_4dfa4ae2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_canonical_architecture_4dfa4ae2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.003-c-first-context-runtime`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.003-c-first-context-runtime.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/c_first_context_runtime_5d7549c0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/c_first_context_runtime_5d7549c0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/c_first_context_runtime_5d7549c0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_c_first_context_runtime_5d7549c0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.004-context-strong-types`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.004-context-strong-types.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_strong_types_d9226ba6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_strong_types_d9226ba6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_strong_types_d9226ba6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_context_strong_types_d9226ba6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.005-context-identity`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.005-context-identity.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_identity_a859ec8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_identity_a859ec8d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_identity_a859ec8d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_context_identity_a859ec8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.006-context-snapshot`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.006-context-snapshot.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_snapshot_1581a6fa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/context_snapshot_1581a6fa.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/context_snapshot_1581a6fa.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_context_snapshot_1581a6fa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.007-context-fact`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.007-context-fact.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_fact_cc480ad5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_fact_cc480ad5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_fact_cc480ad5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_fact_cc480ad5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.008-context-reference`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.008-context-reference.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_reference_1aef23dd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_reference_1aef23dd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_reference_1aef23dd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_reference_1aef23dd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.009-context-scope`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.009-context-scope.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_scope_66331c62/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_scope_66331c62.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_scope_66331c62.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_scope_66331c62.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.010-context-window`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.010-context-window.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_window_b3930231/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_window_b3930231.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_window_b3930231.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_window_b3930231.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.011-context-provenance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.011-context-provenance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_provenance_250c2bf8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_provenance_250c2bf8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_provenance_250c2bf8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_provenance_250c2bf8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.012-context-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.012-context-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_freshness_fe86b35d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_freshness_fe86b35d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_freshness_fe86b35d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_freshness_fe86b35d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.013-context-uncertainty`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.013-context-uncertainty.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_uncertainty_07c0a186/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_uncertainty_07c0a186.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_uncertainty_07c0a186.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_uncertainty_07c0a186.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.014-context-epistemic-class`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.014-context-epistemic-class.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_epistemic_class_cd2199cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_epistemic_class_cd2199cb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_epistemic_class_cd2199cb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_epistemic_class_cd2199cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.015-context-gaps`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.015-context-gaps.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_gaps_d116826d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_gaps_d116826d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_gaps_d116826d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_gaps_d116826d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.016-context-conflicts`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.016-context-conflicts.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_conflicts_5abcfd9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_conflicts_5abcfd9d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_conflicts_5abcfd9d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_conflicts_5abcfd9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.017-context-hypotheses`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.017-context-hypotheses.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_hypotheses_fe1636d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_hypotheses_fe1636d7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_hypotheses_fe1636d7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_hypotheses_fe1636d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.018-context-projections`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.018-context-projections.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_projections_2c7c651b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_projections_2c7c651b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_projections_2c7c651b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_projections_2c7c651b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.019-context-budgets`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.019-context-budgets.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_budgets_1907315c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_budgets_1907315c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_budgets_1907315c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_budgets_1907315c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.020-context-lifecycle`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.020-context-lifecycle.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_lifecycle_5a8b32ac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/context_lifecycle_5a8b32ac.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/context_lifecycle_5a8b32ac.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/lifecycle/test_context_lifecycle_5a8b32ac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.021-context-invalidation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.021-context-invalidation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_invalidation_64c6f1ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_invalidation_64c6f1ee.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_invalidation_64c6f1ee.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_invalidation_64c6f1ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.022-context-cache`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.022-context-cache.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_cache_de6087eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/context_cache_de6087eb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/context_cache_de6087eb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_context_cache_de6087eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.023-cache-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.023-cache-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cache_freshness_1bf34dcd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/cache_freshness_1bf34dcd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/cache_freshness_1bf34dcd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_cache_freshness_1bf34dcd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.024-cache-isolation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.024-cache-isolation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cache_isolation_2a353137/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/cache_isolation_2a353137.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/cache_isolation_2a353137.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_cache_isolation_2a353137.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.025-cache-invalidation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.025-cache-invalidation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cache_invalidation_45b6db7d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/cache_invalidation_45b6db7d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/cache_invalidation_45b6db7d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_cache_invalidation_45b6db7d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.026-context-persistence-boundary`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.026-context-persistence-boundary.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_persistence_boundary_a7e0dd86/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/context_persistence_boundary_a7e0dd86.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/context_persistence_boundary_a7e0dd86.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_context_persistence_boundary_a7e0dd86.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.027-context-serialization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.027-context-serialization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_serialization_6a35cc32/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_serialization_6a35cc32.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_serialization_6a35cc32.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_serialization_6a35cc32.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.028-authoritative-observation-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.028-authoritative-observation-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/authoritative_observation_integration_59c9a3c7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/authoritative_observation_integration_59c9a3c7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/authoritative_observation_integration_59c9a3c7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_authoritative_observation_integration_59c9a3c7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.029-phase-39-temporal-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.029-phase-39-temporal-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/temporal_integration_86d93479/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/temporal_integration_86d93479.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/temporal_integration_86d93479.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_temporal_integration_86d93479.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.030-phase-42-structural-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.030-phase-42-structural-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/structural_integration_ff13b06b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/structural_integration_ff13b06b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/structural_integration_ff13b06b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_structural_integration_ff13b06b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.031-phase-43-intelligence-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.031-phase-43-intelligence-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/intelligence_integration_6ec2ff05/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/intelligence_integration_6ec2ff05.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/intelligence_integration_6ec2ff05.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_intelligence_integration_6ec2ff05.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.032-phase-44-adaptation-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.032-phase-44-adaptation-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adaptation_integration_7e84e026/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/adaptation_integration_7e84e026.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/adaptation_integration_7e84e026.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_adaptation_integration_7e84e026.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.033-phase-45-control-plane-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.033-phase-45-control-plane-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/control_plane_integration_da927899/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/control_plane_integration_da927899.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/control_plane_integration_da927899.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_control_plane_integration_da927899.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.034-phase-46-ask-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.034-phase-46-ask-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ask_integration_32e6f70b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/ask_integration_32e6f70b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/ask_integration_32e6f70b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_ask_integration_32e6f70b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.035-phase-47-policy-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.035-phase-47-policy-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/policy_integration_76e88666/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/policy_integration_76e88666.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/policy_integration_76e88666.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_policy_integration_76e88666.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.036-phase-41-workflow-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.036-phase-41-workflow-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/workflow_integration_6000f594/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/workflow_integration_6000f594.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/workflow_integration_6000f594.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_workflow_integration_6000f594.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.037-phase-29-workload-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.037-phase-29-workload-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/workload_integration_35c44886/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/workload_integration_35c44886.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/workload_integration_35c44886.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_workload_integration_35c44886.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.038-phase-30-resource-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.038-phase-30-resource-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/resource_integration_9d058734/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/resource_integration_9d058734.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/resource_integration_9d058734.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_resource_integration_9d058734.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.039-identity-and-session-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.039-identity-and-session-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/identity_and_session_context_122aa296/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/identity_and_session_context_122aa296.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/identity_and_session_context_122aa296.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_identity_and_session_context_122aa296.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.040-cwd-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.040-cwd-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cwd_context_f005c2a5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cwd_context_f005c2a5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cwd_context_f005c2a5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cwd_context_f005c2a5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.041-project-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.041-project-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/project_context_963c4373/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/project_context_963c4373.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/project_context_963c4373.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_project_context_963c4373.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.042-repository-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.042-repository-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/repository_context_c4f3f2b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/repository_context_c4f3f2b0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/repository_context_c4f3f2b0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_repository_context_c4f3f2b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.043-development-workspace-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.043-development-workspace-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/development_workspace_context_9519f1fd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/development_workspace_context_9519f1fd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/development_workspace_context_9519f1fd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_development_workspace_context_9519f1fd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.044-active-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.044-active-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/active_task_context_74425707/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/active_task_context_74425707.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/active_task_context_74425707.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_active_task_context_74425707.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.045-taskwarrior-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.045-taskwarrior-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/taskwarrior_context_1c686e0b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taskwarrior_context_1c686e0b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taskwarrior_context_1c686e0b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_taskwarrior_context_1c686e0b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.046-active-workflow-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.046-active-workflow-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/active_workflow_context_ea133bc9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/active_workflow_context_ea133bc9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/active_workflow_context_ea133bc9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_active_workflow_context_ea133bc9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.047-automation-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.047-automation-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/automation_context_c8cb937f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/automation_context_c8cb937f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/automation_context_c8cb937f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_automation_context_c8cb937f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.048-recent-operator-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.048-recent-operator-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/recent_operator_context_987ba7a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recent_operator_context_987ba7a7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recent_operator_context_987ba7a7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_recent_operator_context_987ba7a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.049-explicit-referent-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.049-explicit-referent-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/explicit_referent_context_6dbb9b83/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/explicit_referent_context_6dbb9b83.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/explicit_referent_context_6dbb9b83.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_explicit_referent_context_6dbb9b83.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.050-pronoun-referent-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.050-pronoun-referent-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/pronoun_referent_context_677422be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/pronoun_referent_context_677422be.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/pronoun_referent_context_677422be.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_pronoun_referent_context_677422be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.051-ordinal-referent-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.051-ordinal-referent-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ordinal_referent_context_04c80e33/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ordinal_referent_context_04c80e33.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ordinal_referent_context_04c80e33.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_ordinal_referent_context_04c80e33.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.052-selected-target-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.052-selected-target-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/selected_target_context_83bf8499/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/selected_target_context_83bf8499.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/selected_target_context_83bf8499.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/resolution/test_selected_target_context_83bf8499.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.053-recent-object-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.053-recent-object-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/recent_object_context_5889c966/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recent_object_context_5889c966.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recent_object_context_5889c966.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_recent_object_context_5889c966.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.054-shell-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.054-shell-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/shell_context_1345f697/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/shell_context_1345f697.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/shell_context_1345f697.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_shell_context_1345f697.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.055-terminal-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.055-terminal-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/terminal_context_d658b7ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/terminal_context_d658b7ee.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/terminal_context_d658b7ee.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_terminal_context_d658b7ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.056-process-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.056-process-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/process_context_a3c05ceb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/process_context_a3c05ceb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/process_context_a3c05ceb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_process_context_a3c05ceb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.057-service-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.057-service-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/service_context_25478b06/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/service_context_25478b06.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/service_context_25478b06.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_service_context_25478b06.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.058-network-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.058-network-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/network_context_eeb3b927/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/network_context_eeb3b927.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/network_context_eeb3b927.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_network_context_eeb3b927.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.059-storage-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.059-storage-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/storage_context_de883c09/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/storage_context_de883c09.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/storage_context_de883c09.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_storage_context_de883c09.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.060-filesystem-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.060-filesystem-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/filesystem_context_b34d68a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/filesystem_context_b34d68a1.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/filesystem_context_b34d68a1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_filesystem_context_b34d68a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.061-mount-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.061-mount-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/mount_context_a21ed5e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/mount_context_a21ed5e8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/mount_context_a21ed5e8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_mount_context_a21ed5e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.062-package-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.062-package-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/package_context_acea3525/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/package_context_acea3525.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/package_context_acea3525.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_package_context_acea3525.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.063-configuration-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.063-configuration-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/configuration_context_c40b5003/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/configuration_context_c40b5003.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/configuration_context_c40b5003.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_configuration_context_c40b5003.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.064-gpu-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.064-gpu-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/gpu_context_ff93bbba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/gpu_context_ff93bbba.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/gpu_context_ff93bbba.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_gpu_context_ff93bbba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.065-accelerator-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.065-accelerator-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/accelerator_context_e93dbfc9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/accelerator_context_e93dbfc9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/accelerator_context_e93dbfc9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_accelerator_context_e93dbfc9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.066-cpu-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.066-cpu-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cpu_context_d9839fc4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cpu_context_d9839fc4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cpu_context_d9839fc4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cpu_context_d9839fc4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.067-memory-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.067-memory-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/memory_context_638d7aa8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/memory_context_638d7aa8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/memory_context_638d7aa8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_memory_context_638d7aa8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.068-resource-pressure-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.068-resource-pressure-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/resource_pressure_context_99e3101f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/resource_pressure_context_99e3101f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/resource_pressure_context_99e3101f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_resource_pressure_context_99e3101f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.069-user-identity-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.069-user-identity-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/user_identity_context_f69f644f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/user_identity_context_f69f644f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/user_identity_context_f69f644f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_user_identity_context_f69f644f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.070-security-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.070-security-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/security_context_fe5ed84b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/security_context_fe5ed84b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/security_context_fe5ed84b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_security_context_fe5ed84b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.071-credential-reference-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.071-credential-reference-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/credential_reference_context_200b0309/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/credential_reference_context_200b0309.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/credential_reference_context_200b0309.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_credential_reference_context_200b0309.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.072-system-health-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.072-system-health-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/system_health_context_84c51a8f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/system_health_context_84c51a8f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/system_health_context_84c51a8f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_system_health_context_84c51a8f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.073-boot-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.073-boot-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/boot_context_3bc9b259/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/boot_context_3bc9b259.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/boot_context_3bc9b259.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_boot_context_3bc9b259.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.074-session-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.074-session-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/session_context_8fae69c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/session_context_8fae69c4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/session_context_8fae69c4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_session_context_8fae69c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.075-maintenance-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.075-maintenance-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/maintenance_context_d23d3173/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/maintenance_context_d23d3173.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/maintenance_context_d23d3173.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_maintenance_context_d23d3173.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.076-power-state-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.076-power-state-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/power_state_context_9b1e0c27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/power_state_context_9b1e0c27.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/power_state_context_9b1e0c27.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/lifecycle/test_power_state_context_9b1e0c27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.077-kernel-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.077-kernel-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/kernel_context_bbe1ef2d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/kernel_context_bbe1ef2d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/kernel_context_bbe1ef2d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_kernel_context_bbe1ef2d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.078-driver-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.078-driver-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/driver_context_2d33f40f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/driver_context_2d33f40f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/driver_context_2d33f40f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_driver_context_2d33f40f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.079-container-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.079-container-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/container_context_9e0ca9f6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/container_context_9e0ca9f6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/container_context_9e0ca9f6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_container_context_9e0ca9f6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.080-model-service-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.080-model-service-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/model_service_context_ac9fd1e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_service_context_ac9fd1e3.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_service_context_ac9fd1e3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_model_service_context_ac9fd1e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.081-ai-workload-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.081-ai-workload-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ai_workload_context_4769acf8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ai_workload_context_4769acf8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ai_workload_context_4769acf8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_ai_workload_context_4769acf8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.082-dependency-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.082-dependency-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/dependency_context_c6513246/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/dependency_context_c6513246.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/dependency_context_c6513246.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_dependency_context_c6513246.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.083-ownership-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.083-ownership-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ownership_context_e9bcbdaa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ownership_context_e9bcbdaa.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ownership_context_e9bcbdaa.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_ownership_context_e9bcbdaa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.084-containment-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.084-containment-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/containment_context_930783fd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/containment_context_930783fd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/containment_context_930783fd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_containment_context_930783fd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.085-attachment-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.085-attachment-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/attachment_context_d9078a07/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/attachment_context_d9078a07.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/attachment_context_d9078a07.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_attachment_context_d9078a07.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.086-data-flow-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.086-data-flow-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/data_flow_context_7de8cbc1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/data_flow_context_7de8cbc1.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/data_flow_context_7de8cbc1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_data_flow_context_7de8cbc1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.087-endpoint-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.087-endpoint-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/endpoint_context_8a92246a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/endpoint_context_8a92246a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/endpoint_context_8a92246a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_endpoint_context_8a92246a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.088-listener-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.088-listener-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/listener_context_4fdc85a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/listener_context_4fdc85a3.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/listener_context_4fdc85a3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_listener_context_4fdc85a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.089-external-destination-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.089-external-destination-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/external_destination_context_3b316a10/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/external_destination_context_3b316a10.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/external_destination_context_3b316a10.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_external_destination_context_3b316a10.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.090-persistence-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.090-persistence-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/persistence_context_3c83c65f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/persistence_context_3c83c65f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/persistence_context_3c83c65f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_persistence_context_3c83c65f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.091-privilege-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.091-privilege-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/privilege_context_d9b52698/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/privilege_context_d9b52698.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/privilege_context_d9b52698.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_privilege_context_d9b52698.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.092-protected-resource-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.092-protected-resource-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/protected_resource_context_16ca5b1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/protected_resource_context_16ca5b1f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/protected_resource_context_16ca5b1f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_protected_resource_context_16ca5b1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.093-relevance-engine`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.093-relevance-engine.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/relevance_engine_3ffb42bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_engine_3ffb42bf.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_engine_3ffb42bf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_relevance_engine_3ffb42bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.094-relevance-seeds`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.094-relevance-seeds.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/relevance_seeds_c67a9631/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_seeds_c67a9631.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_seeds_c67a9631.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_relevance_seeds_c67a9631.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.095-entity-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.095-entity-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/entity_relevance_f1e0e2e9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/entity_relevance_f1e0e2e9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/entity_relevance_f1e0e2e9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_entity_relevance_f1e0e2e9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.096-domain-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.096-domain-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/domain_relevance_14e86ae7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/domain_relevance_14e86ae7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/domain_relevance_14e86ae7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_domain_relevance_14e86ae7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.097-dependency-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.097-dependency-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/dependency_relevance_f3f36019/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/dependency_relevance_f3f36019.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/dependency_relevance_f3f36019.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_dependency_relevance_f3f36019.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.098-temporal-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.098-temporal-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/temporal_relevance_1be67f46/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/temporal_relevance_1be67f46.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/temporal_relevance_1be67f46.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_temporal_relevance_1be67f46.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.099-structural-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.099-structural-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/structural_relevance_c2df2bbf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/structural_relevance_c2df2bbf.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/structural_relevance_c2df2bbf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_structural_relevance_c2df2bbf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.100-workflow-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.100-workflow-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/workflow_relevance_afa433c6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/workflow_relevance_afa433c6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/workflow_relevance_afa433c6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_workflow_relevance_afa433c6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.101-operator-focus-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.101-operator-focus-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/operator_focus_relevance_24e91fa8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/operator_focus_relevance_24e91fa8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/operator_focus_relevance_24e91fa8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_operator_focus_relevance_24e91fa8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.102-task-goal-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.102-task-goal-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_goal_relevance_2288b85f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_goal_relevance_2288b85f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_goal_relevance_2288b85f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_goal_relevance_2288b85f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.103-risk-driven-relevance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.103-risk-driven-relevance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/risk_driven_relevance_80f234be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/risk_driven_relevance_80f234be.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/risk_driven_relevance_80f234be.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_risk_driven_relevance_80f234be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.104-relevance-expansion`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.104-relevance-expansion.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/relevance_expansion_9ca37e1c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_expansion_9ca37e1c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_expansion_9ca37e1c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_relevance_expansion_9ca37e1c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.105-relevance-stopping-criteria`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.105-relevance-stopping-criteria.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/relevance_stopping_criteria_433bda9b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/relevance_stopping_criteria_433bda9b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/relevance_stopping_criteria_433bda9b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/lifecycle/test_relevance_stopping_criteria_433bda9b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.106-relevance-budgets`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.106-relevance-budgets.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/relevance_budgets_ee156bc8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_budgets_ee156bc8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/relevance_budgets_ee156bc8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_relevance_budgets_ee156bc8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.107-relevance-explanation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.107-relevance-explanation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/relevance_explanation_92c717b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/planning/relevance_explanation_92c717b2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/planning/relevance_explanation_92c717b2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/planning/test_relevance_explanation_92c717b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.108-irrelevant-context-exclusion`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.108-irrelevant-context-exclusion.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/irrelevant_context_exclusion_56fca61b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/irrelevant_context_exclusion_56fca61b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/irrelevant_context_exclusion_56fca61b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_irrelevant_context_exclusion_56fca61b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.109-context-minimization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.109-context-minimization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_minimization_1a305e5b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_minimization_1a305e5b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_minimization_1a305e5b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_minimization_1a305e5b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.110-context-prioritization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.110-context-prioritization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_prioritization_fb22fb03/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_prioritization_fb22fb03.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_prioritization_fb22fb03.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_prioritization_fb22fb03.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.111-context-ranking`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.111-context-ranking.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_ranking_4d02e51e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_ranking_4d02e51e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_ranking_4d02e51e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_ranking_4d02e51e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.112-context-deduplication`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.112-context-deduplication.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_deduplication_4af15625/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_deduplication_4af15625.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_deduplication_4af15625.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_deduplication_4af15625.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.113-context-normalization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.113-context-normalization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_normalization_85bc1a9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_normalization_85bc1a9d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_normalization_85bc1a9d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_normalization_85bc1a9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.114-context-merge`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.114-context-merge.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_merge_d1c6c58a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_merge_d1c6c58a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_merge_d1c6c58a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_merge_d1c6c58a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.115-context-contradiction-preservation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.115-context-contradiction-preservation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_contradiction_preservation_f305864d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_contradiction_preservation_f305864d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_contradiction_preservation_f305864d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_contradiction_preservation_f305864d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.116-context-conflict-resolution-boundary`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.116-context-conflict-resolution-boundary.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_conflict_resolution_boundary_56b1501d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_conflict_resolution_boundary_56b1501d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_conflict_resolution_boundary_56b1501d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_conflict_resolution_boundary_56b1501d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.117-context-missing-data-handling`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.117-context-missing-data-handling.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_missing_data_handling_b13458aa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_missing_data_handling_b13458aa.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_missing_data_handling_b13458aa.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_missing_data_handling_b13458aa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.118-fresh-observation-requests`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.118-fresh-observation-requests.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/fresh_observation_requests_d39c75d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/fresh_observation_requests_d39c75d1.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/fresh_observation_requests_d39c75d1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_fresh_observation_requests_d39c75d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.119-stale-observation-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.119-stale-observation-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/stale_observation_detection_a4c7f8e6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/stale_observation_detection_a4c7f8e6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/stale_observation_detection_a4c7f8e6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_stale_observation_detection_a4c7f8e6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.120-staleness-thresholds`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.120-staleness-thresholds.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/staleness_thresholds_96998f49/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/staleness_thresholds_96998f49.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/staleness_thresholds_96998f49.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_staleness_thresholds_96998f49.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.121-domain-specific-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.121-domain-specific-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/domain_specific_freshness_26be4f75/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/domain_specific_freshness_26be4f75.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/domain_specific_freshness_26be4f75.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_domain_specific_freshness_26be4f75.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.122-freshness-propagation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.122-freshness-propagation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/freshness_propagation_e4a54521/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/freshness_propagation_e4a54521.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/freshness_propagation_e4a54521.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_freshness_propagation_e4a54521.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.123-freshness-explanation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.123-freshness-explanation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/freshness_explanation_4581a93b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/planning/freshness_explanation_4581a93b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/planning/freshness_explanation_4581a93b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/planning/test_freshness_explanation_4581a93b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.124-boot-bound-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.124-boot-bound-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/boot_bound_freshness_26967a06/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/boot_bound_freshness_26967a06.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/boot_bound_freshness_26967a06.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_boot_bound_freshness_26967a06.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.125-session-bound-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.125-session-bound-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/session_bound_freshness_488a75a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/session_bound_freshness_488a75a9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/session_bound_freshness_488a75a9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_session_bound_freshness_488a75a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.126-task-bound-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.126-task-bound-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_bound_freshness_fe5d72c7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_bound_freshness_fe5d72c7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_bound_freshness_fe5d72c7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_bound_freshness_fe5d72c7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.127-plan-bound-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.127-plan-bound-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/plan_bound_freshness_9bac0c3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/planning/plan_bound_freshness_9bac0c3a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/planning/plan_bound_freshness_9bac0c3a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/planning/test_plan_bound_freshness_9bac0c3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.128-event-time-awareness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.128-event-time-awareness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/event_time_awareness_5b03fbb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/event_time_awareness_5b03fbb9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/event_time_awareness_5b03fbb9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_event_time_awareness_5b03fbb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.129-observation-time-awareness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.129-observation-time-awareness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/observation_time_awareness_ad437e27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/observation_time_awareness_ad437e27.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/observation_time_awareness_ad437e27.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_observation_time_awareness_ad437e27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.130-clock-jump-handling`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.130-clock-jump-handling.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/clock_jump_handling_d9da968a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/clock_jump_handling_d9da968a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/clock_jump_handling_d9da968a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_clock_jump_handling_d9da968a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.131-clock-skew-handling`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.131-clock-skew-handling.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/clock_skew_handling_d474ca65/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/clock_skew_handling_d474ca65.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/clock_skew_handling_d474ca65.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_clock_skew_handling_d474ca65.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.132-out-of-order-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.132-out-of-order-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/out_of_order_context_57bc69aa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/out_of_order_context_57bc69aa.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/out_of_order_context_57bc69aa.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_out_of_order_context_57bc69aa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.133-replayed-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.133-replayed-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/replayed_context_0e25dc8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/replayed_context_0e25dc8d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/replayed_context_0e25dc8d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_replayed_context_0e25dc8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.134-temporal-gaps`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.134-temporal-gaps.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/temporal_gaps_a8a91152/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/temporal_gaps_a8a91152.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/temporal_gaps_a8a91152.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_temporal_gaps_a8a91152.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.135-temporal-neighborhood`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.135-temporal-neighborhood.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/temporal_neighborhood_8d42f266/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/temporal_neighborhood_8d42f266.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/temporal_neighborhood_8d42f266.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_temporal_neighborhood_8d42f266.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.136-recent-change-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.136-recent-change-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/recent_change_context_084cabcf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recent_change_context_084cabcf.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recent_change_context_084cabcf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_recent_change_context_084cabcf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.137-before-after-relations`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.137-before-after-relations.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/before_after_relations_f026809b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/before_after_relations_f026809b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/before_after_relations_f026809b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_before_after_relations_f026809b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.138-causality-non-inference`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.138-causality-non-inference.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/causality_non_inference_1ade55d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/causality_non_inference_1ade55d2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/causality_non_inference_1ade55d2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_causality_non_inference_1ade55d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.139-causal-evidence-references`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.139-causal-evidence-references.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/causal_evidence_references_b47500c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/causal_evidence_references_b47500c3.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/causal_evidence_references_b47500c3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_causal_evidence_references_b47500c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.140-structural-neighborhood`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.140-structural-neighborhood.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/structural_neighborhood_af77766f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/structural_neighborhood_af77766f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/structural_neighborhood_af77766f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_structural_neighborhood_af77766f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.141-graph-traversal-bounds`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.141-graph-traversal-bounds.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/graph_traversal_bounds_8dfec515/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/graph_traversal_bounds_8dfec515.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/graph_traversal_bounds_8dfec515.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_graph_traversal_bounds_8dfec515.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.142-identity-resolution-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.142-identity-resolution-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/identity_resolution_context_f4c7bcd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/identity_resolution_context_f4c7bcd4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/identity_resolution_context_f4c7bcd4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_identity_resolution_context_f4c7bcd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.143-ambiguous-identity-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.143-ambiguous-identity-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ambiguous_identity_context_3212c718/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/ambiguous_identity_context_3212c718.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/ambiguous_identity_context_3212c718.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_ambiguous_identity_context_3212c718.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.144-persistent-device-identity`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.144-persistent-device-identity.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/persistent_device_identity_c2f4aeeb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/persistent_device_identity_c2f4aeeb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/persistent_device_identity_c2f4aeeb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_persistent_device_identity_c2f4aeeb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.145-gpu-identity-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.145-gpu-identity-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/gpu_identity_context_a1195986/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/gpu_identity_context_a1195986.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/gpu_identity_context_a1195986.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_gpu_identity_context_a1195986.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.146-network-interface-identity`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.146-network-interface-identity.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/network_interface_identity_e4869088/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/network_interface_identity_e4869088.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/network_interface_identity_e4869088.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_network_interface_identity_e4869088.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.147-storage-identity`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.147-storage-identity.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/storage_identity_fcc42472/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/storage_identity_fcc42472.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/storage_identity_fcc42472.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_storage_identity_fcc42472.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.148-process-identity-lifecycle`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.148-process-identity-lifecycle.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/process_identity_lifecycle_f7d0d177/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/process_identity_lifecycle_f7d0d177.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/process_identity_lifecycle_f7d0d177.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/lifecycle/test_process_identity_lifecycle_f7d0d177.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.149-service-identity`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.149-service-identity.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/service_identity_0d4482a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/service_identity_0d4482a4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/service_identity_0d4482a4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_service_identity_0d4482a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.150-user-identity-mapping`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.150-user-identity-mapping.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/user_identity_mapping_55429689/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/user_identity_mapping_55429689.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/user_identity_mapping_55429689.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_user_identity_mapping_55429689.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.151-task-identity-mapping`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.151-task-identity-mapping.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_identity_mapping_efc67d27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/task_identity_mapping_efc67d27.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/task_identity_mapping_efc67d27.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_task_identity_mapping_efc67d27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.152-workflow-identity-mapping`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.152-workflow-identity-mapping.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/workflow_identity_mapping_6a8e904f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/workflow_identity_mapping_6a8e904f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/workflow_identity_mapping_6a8e904f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_workflow_identity_mapping_6a8e904f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.153-contextual-coherence-engine`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.153-contextual-coherence-engine.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/contextual_coherence_engine_e90e0b5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/contextual_coherence_engine_e90e0b5d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/contextual_coherence_engine_e90e0b5d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_contextual_coherence_engine_e90e0b5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.154-task-state-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.154-task-state-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_state_coherence_8b760da6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/task_state_coherence_8b760da6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/task_state_coherence_8b760da6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/lifecycle/test_task_state_coherence_8b760da6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.155-task-project-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.155-task-project-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_project_coherence_45d2a97a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_project_coherence_45d2a97a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_project_coherence_45d2a97a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_project_coherence_45d2a97a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.156-task-workflow-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.156-task-workflow-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_workflow_coherence_135f545d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_workflow_coherence_135f545d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_workflow_coherence_135f545d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_workflow_coherence_135f545d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.157-task-service-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.157-task-service-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_service_coherence_649b1580/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_service_coherence_649b1580.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_service_coherence_649b1580.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_service_coherence_649b1580.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.158-task-endpoint-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.158-task-endpoint-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_endpoint_coherence_e1f19efb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_endpoint_coherence_e1f19efb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_endpoint_coherence_e1f19efb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_endpoint_coherence_e1f19efb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.159-task-dataflow-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.159-task-dataflow-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_dataflow_coherence_67b3b3c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_dataflow_coherence_67b3b3c9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_dataflow_coherence_67b3b3c9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_dataflow_coherence_67b3b3c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.160-task-resource-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.160-task-resource-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_resource_coherence_95fcbccd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_resource_coherence_95fcbccd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_resource_coherence_95fcbccd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_resource_coherence_95fcbccd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.161-task-security-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.161-task-security-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_security_coherence_22d34e62/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/task_security_coherence_22d34e62.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/task_security_coherence_22d34e62.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_task_security_coherence_22d34e62.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.162-task-maintenance-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.162-task-maintenance-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_maintenance_coherence_7fd6dda1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_maintenance_coherence_7fd6dda1.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_maintenance_coherence_7fd6dda1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_maintenance_coherence_7fd6dda1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.163-task-history-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.163-task-history-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_history_coherence_4824e2fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_history_coherence_4824e2fc.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_history_coherence_4824e2fc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_history_coherence_4824e2fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.164-prerequisite-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.164-prerequisite-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/prerequisite_coherence_3ffd86cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/prerequisite_coherence_3ffd86cb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/prerequisite_coherence_3ffd86cb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_prerequisite_coherence_3ffd86cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.165-expected-state-coherence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.165-expected-state-coherence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/expected_state_coherence_3baeeffe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/expected_state_coherence_3baeeffe.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/lifecycle/expected_state_coherence_3baeeffe.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/lifecycle/test_expected_state_coherence_3baeeffe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.166-unexpected-novelty-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.166-unexpected-novelty-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/unexpected_novelty_detection_d3ff4d64/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/unexpected_novelty_detection_d3ff4d64.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/unexpected_novelty_detection_d3ff4d64.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_unexpected_novelty_detection_d3ff4d64.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.167-novel-endpoint-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.167-novel-endpoint-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_endpoint_detection_d0b88bcf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_endpoint_detection_d0b88bcf.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_endpoint_detection_d0b88bcf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_novel_endpoint_detection_d0b88bcf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.168-novel-listener-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.168-novel-listener-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_listener_detection_e67349ac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_listener_detection_e67349ac.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_listener_detection_e67349ac.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_novel_listener_detection_e67349ac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.169-novel-persistence-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.169-novel-persistence-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_persistence_detection_d86074a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/novel_persistence_detection_d86074a9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/persistence/novel_persistence_detection_d86074a9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/persistence/test_novel_persistence_detection_d86074a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.170-novel-privilege-use-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.170-novel-privilege-use-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_privilege_use_detection_a24be6f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/novel_privilege_use_detection_a24be6f7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/novel_privilege_use_detection_a24be6f7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_novel_privilege_use_detection_a24be6f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.171-novel-data-access-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.171-novel-data-access-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_data_access_detection_fb512a6c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_data_access_detection_fb512a6c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_data_access_detection_fb512a6c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_novel_data_access_detection_fb512a6c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.172-novel-secret-access-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.172-novel-secret-access-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_secret_access_detection_e6910aee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/novel_secret_access_detection_e6910aee.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/novel_secret_access_detection_e6910aee.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_novel_secret_access_detection_e6910aee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.173-novel-bulk-export-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.173-novel-bulk-export-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_bulk_export_detection_1b8aeb94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_bulk_export_detection_1b8aeb94.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/novel_bulk_export_detection_1b8aeb94.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_novel_bulk_export_detection_1b8aeb94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.174-novel-destructive-mutation-detection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.174-novel-destructive-mutation-detection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/novel_destructive_mutation_detection_3b08fbd3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/execution/novel_destructive_mutation_detection_3b08fbd3.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/execution/novel_destructive_mutation_detection_3b08fbd3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/execution/test_novel_destructive_mutation_detection_3b08fbd3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.175-cross-domain-novelty`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.175-cross-domain-novelty.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_domain_novelty_c8f8c609/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_domain_novelty_c8f8c609.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_domain_novelty_c8f8c609.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cross_domain_novelty_c8f8c609.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.176-coherence-explanation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.176-coherence-explanation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/coherence_explanation_3db4144c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/planning/coherence_explanation_3db4144c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/planning/coherence_explanation_3db4144c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/planning/test_coherence_explanation_3db4144c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.177-contextual-anomaly-evidence`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.177-contextual-anomaly-evidence.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/contextual_anomaly_evidence_3fbf02cc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/contextual_anomaly_evidence_3fbf02cc.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/contextual_anomaly_evidence_3fbf02cc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_contextual_anomaly_evidence_3fbf02cc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.178-anomaly-severity-semantics`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.178-anomaly-severity-semantics.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/anomaly_severity_semantics_725f2ede/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_severity_semantics_725f2ede.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_severity_semantics_725f2ede.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_anomaly_severity_semantics_725f2ede.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.179-anomaly-uncertainty`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.179-anomaly-uncertainty.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/anomaly_uncertainty_bfba6fc6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_uncertainty_bfba6fc6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_uncertainty_bfba6fc6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_anomaly_uncertainty_bfba6fc6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.180-anomaly-provenance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.180-anomaly-provenance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/anomaly_provenance_a7a14826/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_provenance_a7a14826.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_provenance_a7a14826.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_anomaly_provenance_a7a14826.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.181-anomaly-not-maliciousness-invariant`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.181-anomaly-not-maliciousness-invariant.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/anomaly_not_maliciousness_invariant_74fc3c73/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_not_maliciousness_invariant_74fc3c73.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/anomaly_not_maliciousness_invariant_74fc3c73.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_anomaly_not_maliciousness_invariant_74fc3c73.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.182-baseline-free-anomaly-handling`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.182-baseline-free-anomaly-handling.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/baseline_free_anomaly_handling_2b3b787e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/baseline_free_anomaly_handling_2b3b787e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/baseline_free_anomaly_handling_2b3b787e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_baseline_free_anomaly_handling_2b3b787e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.183-expected-use-baseline-boundary`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.183-expected-use-baseline-boundary.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/expected_use_baseline_boundary_abed6529/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/expected_use_baseline_boundary_abed6529.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/expected_use_baseline_boundary_abed6529.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_expected_use_baseline_boundary_abed6529.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.184-operator-explanation-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.184-operator-explanation-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/operator_explanation_integration_8935378a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/operator_explanation_integration_8935378a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/operator_explanation_integration_8935378a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_operator_explanation_integration_8935378a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.185-justification-context-integration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.185-justification-context-integration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/justification_context_integration_d41719ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/justification_context_integration_d41719ce.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/justification_context_integration_d41719ce.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_justification_context_integration_d41719ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.186-justification-consistency-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.186-justification-consistency-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/justification_consistency_context_a76e6583/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/justification_consistency_context_a76e6583.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/justification_consistency_context_a76e6583.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_justification_consistency_context_a76e6583.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.187-phase-47-policy-context-projection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.187-phase-47-policy-context-projection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/policy_context_projection_0dec43b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/policy_context_projection_0dec43b7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/policy_context_projection_0dec43b7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_policy_context_projection_0dec43b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.188-policy-relevant-context-extraction`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.188-policy-relevant-context-extraction.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/policy_relevant_context_extraction_ab186cc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/policy_relevant_context_extraction_ab186cc3.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/policy_relevant_context_extraction_ab186cc3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_policy_relevant_context_extraction_ab186cc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.189-authorization-relevant-context-boundary`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.189-authorization-relevant-context-boundary.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/authorization_relevant_context_boundary_889f7d83/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/authorization_relevant_context_boundary_889f7d83.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/authorization_relevant_context_boundary_889f7d83.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_authorization_relevant_context_boundary_889f7d83.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.190-capability-relevant-context-extraction`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.190-capability-relevant-context-extraction.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/capability_relevant_context_extraction_83e65645/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/capability_relevant_context_extraction_83e65645.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/capability_relevant_context_extraction_83e65645.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_capability_relevant_context_extraction_83e65645.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.191-data-flow-policy-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.191-data-flow-policy-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/data_flow_policy_context_81fcd205/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/data_flow_policy_context_81fcd205.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/data_flow_policy_context_81fcd205.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_data_flow_policy_context_81fcd205.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.192-resource-policy-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.192-resource-policy-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/resource_policy_context_7f451dd6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/resource_policy_context_7f451dd6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/resource_policy_context_7f451dd6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_resource_policy_context_7f451dd6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.193-delegation-policy-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.193-delegation-policy-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/delegation_policy_context_336a62ad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/delegation_policy_context_336a62ad.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/delegation_policy_context_336a62ad.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_delegation_policy_context_336a62ad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.194-scheduled-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.194-scheduled-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/scheduled_task_context_583bbd0c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/planning/scheduled_task_context_583bbd0c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/planning/scheduled_task_context_583bbd0c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/planning/test_scheduled_task_context_583bbd0c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.195-unattended-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.195-unattended-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/unattended_task_context_5812653e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/unattended_task_context_5812653e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/unattended_task_context_5812653e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_unattended_task_context_5812653e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.196-interactive-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.196-interactive-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/interactive_task_context_20fb90b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/interactive_task_context_20fb90b5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/interactive_task_context_20fb90b5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_interactive_task_context_20fb90b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.197-agent-originated-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.197-agent-originated-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/agent_originated_task_context_07b6d4a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/agent_originated_task_context_07b6d4a2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/agent_originated_task_context_07b6d4a2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_agent_originated_task_context_07b6d4a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.198-semantic-originated-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.198-semantic-originated-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_originated_task_context_67dffcc1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_originated_task_context_67dffcc1.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_originated_task_context_67dffcc1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_semantic_originated_task_context_67dffcc1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.199-workflow-child-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.199-workflow-child-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/workflow_child_task_context_58e61bd8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/workflow_child_task_context_58e61bd8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/workflow_child_task_context_58e61bd8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_workflow_child_task_context_58e61bd8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.200-cross-task-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.200-cross-task-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_task_context_e996e88d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_task_context_e996e88d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_task_context_e996e88d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cross_task_context_e996e88d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.201-cross-step-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.201-cross-step-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_step_context_44e7fcc4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_step_context_44e7fcc4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_step_context_44e7fcc4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cross_step_context_44e7fcc4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.202-task-splitting-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.202-task-splitting-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/task_splitting_context_f53adffb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_splitting_context_f53adffb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/task_splitting_context_f53adffb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_task_splitting_context_f53adffb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.203-multi-stage-data-flow-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.203-multi-stage-data-flow-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/multi_stage_data_flow_context_36192323/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/multi_stage_data_flow_context_36192323.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/multi_stage_data_flow_context_36192323.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_multi_stage_data_flow_context_36192323.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.204-delegation-chain-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.204-delegation-chain-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/delegation_chain_context_f2884bc6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/delegation_chain_context_f2884bc6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/delegation_chain_context_f2884bc6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_delegation_chain_context_f2884bc6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.205-origin-chain-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.205-origin-chain-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/origin_chain_context_9539e823/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/origin_chain_context_9539e823.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/origin_chain_context_9539e823.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_origin_chain_context_9539e823.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.206-trust-domain-model`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.206-trust-domain-model.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/trust_domain_model_cc5c341a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/trust_domain_model_cc5c341a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/trust_domain_model_cc5c341a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_trust_domain_model_cc5c341a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.207-operator-input-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.207-operator-input-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/operator_input_trust_91f3accd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/operator_input_trust_91f3accd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/operator_input_trust_91f3accd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_operator_input_trust_91f3accd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.208-local-authoritative-state-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.208-local-authoritative-state-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/local_authoritative_state_trust_f4a7c7a0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/local_authoritative_state_trust_f4a7c7a0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/local_authoritative_state_trust_f4a7c7a0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_local_authoritative_state_trust_f4a7c7a0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.209-remote-data-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.209-remote-data-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/remote_data_trust_445468d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/remote_data_trust_445468d9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/remote_data_trust_445468d9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_remote_data_trust_445468d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.210-log-content-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.210-log-content-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/log_content_trust_b56516d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/log_content_trust_b56516d8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/log_content_trust_b56516d8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_log_content_trust_b56516d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.211-file-content-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.211-file-content-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/file_content_trust_d135ac9a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/file_content_trust_d135ac9a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/file_content_trust_d135ac9a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_file_content_trust_d135ac9a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.212-readme-content-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.212-readme-content-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/readme_content_trust_d2a0d061/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/readme_content_trust_d2a0d061.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/readme_content_trust_d2a0d061.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_readme_content_trust_d2a0d061.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.213-process-output-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.213-process-output-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/process_output_trust_6cba830b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/process_output_trust_6cba830b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/process_output_trust_6cba830b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_process_output_trust_6cba830b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.214-web-content-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.214-web-content-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/web_content_trust_a8e42679/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/web_content_trust_a8e42679.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/web_content_trust_a8e42679.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_web_content_trust_a8e42679.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.215-model-output-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.215-model-output-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/model_output_trust_4f71627b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/model_output_trust_4f71627b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/model_output_trust_4f71627b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_model_output_trust_4f71627b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.216-quoted-text-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.216-quoted-text-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/quoted_text_trust_c7909937/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/quoted_text_trust_c7909937.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/quoted_text_trust_c7909937.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_quoted_text_trust_c7909937.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.217-copied-command-trust`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.217-copied-command-trust.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/copied_command_trust_655b22ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/copied_command_trust_655b22ca.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/copied_command_trust_655b22ca.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_copied_command_trust_655b22ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.218-taint-propagation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.218-taint-propagation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/taint_propagation_eeb81a75/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taint_propagation_eeb81a75.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taint_propagation_eeb81a75.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_taint_propagation_eeb81a75.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.219-taint-merge`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.219-taint-merge.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/taint_merge_3fc903b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taint_merge_3fc903b2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taint_merge_3fc903b2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_taint_merge_3fc903b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.220-taint-projection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.220-taint-projection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/taint_projection_fadc3861/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taint_projection_fadc3861.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taint_projection_fadc3861.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_taint_projection_fadc3861.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.221-instruction-data-separation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.221-instruction-data-separation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/instruction_data_separation_0d87ebd8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/instruction_data_separation_0d87ebd8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/instruction_data_separation_0d87ebd8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_instruction_data_separation_0d87ebd8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.222-prompt-injection-resistance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.222-prompt-injection-resistance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/prompt_injection_resistance_5af00ddd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/prompt_injection_resistance_5af00ddd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/prompt_injection_resistance_5af00ddd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_prompt_injection_resistance_5af00ddd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.223-context-poisoning-resistance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.223-context-poisoning-resistance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_poisoning_resistance_06e8263f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_poisoning_resistance_06e8263f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_poisoning_resistance_06e8263f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_poisoning_resistance_06e8263f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.224-context-laundering-resistance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.224-context-laundering-resistance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_laundering_resistance_f070102a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_laundering_resistance_f070102a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_laundering_resistance_f070102a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_laundering_resistance_f070102a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.225-authority-laundering-resistance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.225-authority-laundering-resistance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/authority_laundering_resistance_fa41ff67/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/authority_laundering_resistance_fa41ff67.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/authority_laundering_resistance_fa41ff67.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_authority_laundering_resistance_fa41ff67.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.226-cross-session-poisoning-resistance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.226-cross-session-poisoning-resistance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_session_poisoning_resistance_8499cba8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_session_poisoning_resistance_8499cba8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_session_poisoning_resistance_8499cba8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cross_session_poisoning_resistance_8499cba8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.227-cross-user-context-isolation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.227-cross-user-context-isolation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_user_context_isolation_2960a582/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_user_context_isolation_2960a582.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_user_context_isolation_2960a582.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cross_user_context_isolation_2960a582.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.228-cross-project-context-isolation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.228-cross-project-context-isolation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_project_context_isolation_67ebe7af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_project_context_isolation_67ebe7af.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/cross_project_context_isolation_67ebe7af.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_cross_project_context_isolation_67ebe7af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.229-stale-context-poisoning-resistance`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.229-stale-context-poisoning-resistance.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/stale_context_poisoning_resistance_96add176/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/stale_context_poisoning_resistance_96add176.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/stale_context_poisoning_resistance_96add176.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_stale_context_poisoning_resistance_96add176.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.230-semantic-context-projection-schema`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.230-semantic-context-projection-schema.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_context_projection_schema_d89db57c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/semantic_context_projection_schema_d89db57c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/semantic_context_projection_schema_d89db57c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_semantic_context_projection_schema_d89db57c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.231-bitnet-context-projection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.231-bitnet-context-projection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/bitnet_context_projection_627402cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/bitnet_context_projection_627402cb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/bitnet_context_projection_627402cb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_bitnet_context_projection_627402cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.232-gordon-evidencebundle-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.232-gordon-evidencebundle-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/gordon_evidencebundle_context_69057dfd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/gordon_evidencebundle_context_69057dfd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/gordon_evidencebundle_context_69057dfd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_gordon_evidencebundle_context_69057dfd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.233-semantic-redaction`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.233-semantic-redaction.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_redaction_896a8564/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_redaction_896a8564.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_redaction_896a8564.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_semantic_redaction_896a8564.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.234-semantic-minimization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.234-semantic-minimization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_minimization_fa8ed2b8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_minimization_fa8ed2b8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_minimization_fa8ed2b8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_semantic_minimization_fa8ed2b8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.235-semantic-token-budget`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.235-semantic-token-budget.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_token_budget_0a350ee0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_token_budget_0a350ee0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_token_budget_0a350ee0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_semantic_token_budget_0a350ee0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.236-semantic-provenance-labels`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.236-semantic-provenance-labels.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_provenance_labels_b1f00514/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_provenance_labels_b1f00514.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_provenance_labels_b1f00514.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_semantic_provenance_labels_b1f00514.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.237-semantic-untrusted-content-labels`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.237-semantic-untrusted-content-labels.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_untrusted_content_labels_c9493a2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/semantic_untrusted_content_labels_c9493a2e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/semantic_untrusted_content_labels_c9493a2e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_semantic_untrusted_content_labels_c9493a2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.238-semantic-projection-freshness`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.238-semantic-projection-freshness.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_projection_freshness_e9820c0f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_projection_freshness_e9820c0f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_projection_freshness_e9820c0f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_semantic_projection_freshness_e9820c0f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.239-semantic-projection-invalidation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.239-semantic-projection-invalidation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_projection_invalidation_19e1fa94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_projection_invalidation_19e1fa94.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/semantic_projection_invalidation_19e1fa94.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_semantic_projection_invalidation_19e1fa94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.240-model-returned-context-candidates`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.240-model-returned-context-candidates.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/model_returned_context_candidates_32e0b5c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_returned_context_candidates_32e0b5c4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_returned_context_candidates_32e0b5c4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_model_returned_context_candidates_32e0b5c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.241-candidate-validation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.241-candidate-validation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/candidate_validation_10956542/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/candidate_validation_10956542.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/candidate_validation_10956542.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_candidate_validation_10956542.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.242-model-hallucination-containment`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.242-model-hallucination-containment.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/model_hallucination_containment_501adef0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_hallucination_containment_501adef0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_hallucination_containment_501adef0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_model_hallucination_containment_501adef0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.243-model-outage-fallback`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.243-model-outage-fallback.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/model_outage_fallback_94bf9a92/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_outage_fallback_94bf9a92.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_outage_fallback_94bf9a92.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_model_outage_fallback_94bf9a92.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.244-model-compromise-containment`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.244-model-compromise-containment.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/model_compromise_containment_e096b00c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_compromise_containment_e096b00c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/model_compromise_containment_e096b00c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_model_compromise_containment_e096b00c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.245-no-model-authority`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.245-no-model-authority.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/no_model_authority_6e94990d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/no_model_authority_6e94990d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/no_model_authority_6e94990d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_no_model_authority_6e94990d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.246-secret-safe-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.246-secret-safe-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/secret_safe_context_9520f198/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/secret_safe_context_9520f198.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/secret_safe_context_9520f198.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_secret_safe_context_9520f198.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.247-secretref-context`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.247-secretref-context.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/secretref_context_e2ef74fb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/secretref_context_e2ef74fb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/secretref_context_e2ef74fb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_secretref_context_e2ef74fb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.248-secret-value-exclusion`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.248-secret-value-exclusion.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/secret_value_exclusion_70d564df/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/secret_value_exclusion_70d564df.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/secret_value_exclusion_70d564df.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_secret_value_exclusion_70d564df.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.249-credential-value-exclusion`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.249-credential-value-exclusion.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/credential_value_exclusion_579d8671/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/credential_value_exclusion_579d8671.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/credential_value_exclusion_579d8671.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_credential_value_exclusion_579d8671.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.250-environment-redaction`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.250-environment-redaction.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/environment_redaction_840ad6f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/environment_redaction_840ad6f7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/environment_redaction_840ad6f7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_environment_redaction_840ad6f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.251-history-redaction`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.251-history-redaction.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/history_redaction_73143a97/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/history_redaction_73143a97.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/history_redaction_73143a97.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_history_redaction_73143a97.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.252-log-redaction`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.252-log-redaction.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/log_redaction_b91a195c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/log_redaction_b91a195c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/log_redaction_b91a195c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_log_redaction_b91a195c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.253-path-sensitivity-policy`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.253-path-sensitivity-policy.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/path_sensitivity_policy_ce6a70f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/path_sensitivity_policy_ce6a70f2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/path_sensitivity_policy_ce6a70f2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_path_sensitivity_policy_ce6a70f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.254-pii-minimization-boundary`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.254-pii-minimization-boundary.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/pii_minimization_boundary_c8a1dbfb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/pii_minimization_boundary_c8a1dbfb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/pii_minimization_boundary_c8a1dbfb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_pii_minimization_boundary_c8a1dbfb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.255-context-privacy-controls`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.255-context-privacy-controls.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_privacy_controls_ef6fe950/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_privacy_controls_ef6fe950.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_privacy_controls_ef6fe950.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_privacy_controls_ef6fe950.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.256-context-access-control`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.256-context-access-control.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_access_control_f0af7a4f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_access_control_f0af7a4f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_access_control_f0af7a4f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_access_control_f0af7a4f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.257-context-query-authorization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.257-context-query-authorization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_query_authorization_2f50e309/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/context_query_authorization_2f50e309.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/context_query_authorization_2f50e309.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_context_query_authorization_2f50e309.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.258-context-projection-authorization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.258-context-projection-authorization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_projection_authorization_0b26fec7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/context_projection_authorization_0b26fec7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/context_projection_authorization_0b26fec7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_context_projection_authorization_0b26fec7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.259-context-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.259-context-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_audit_85b56968/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_audit_85b56968.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_audit_85b56968.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_context_audit_85b56968.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.260-context-observability`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.260-context-observability.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_observability_363c75dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_observability_363c75dc.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_observability_363c75dc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_context_observability_363c75dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.261-context-metrics`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.261-context-metrics.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_metrics_2c3d47d2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_metrics_2c3d47d2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_metrics_2c3d47d2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_context_metrics_2c3d47d2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.262-context-tracing`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.262-context-tracing.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_tracing_543fb3ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_tracing_543fb3ec.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_tracing_543fb3ec.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_tracing_543fb3ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.263-context-decision-trace`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.263-context-decision-trace.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_decision_trace_6528cf3c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_decision_trace_6528cf3c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_decision_trace_6528cf3c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_context_decision_trace_6528cf3c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.264-why-this-context-explanation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.264-why-this-context-explanation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/why_this_context_explanation_0bf4f2e4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/planning/why_this_context_explanation_0bf4f2e4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/planning/why_this_context_explanation_0bf4f2e4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/planning/test_why_this_context_explanation_0bf4f2e4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.265-why-not-this-context-explanation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.265-why-not-this-context-explanation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/why_not_this_context_explanation_49fbcf6d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/planning/why_not_this_context_explanation_49fbcf6d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/planning/why_not_this_context_explanation_49fbcf6d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/planning/test_why_not_this_context_explanation_49fbcf6d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.266-show-context-cli`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.266-show-context-cli.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/show_context_cli_f44251cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_cli_f44251cb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_cli_f44251cb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_show_context_cli_f44251cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.267-show-context-sources-cli`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.267-show-context-sources-cli.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/show_context_sources_cli_4618f53f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_sources_cli_4618f53f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_sources_cli_4618f53f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_show_context_sources_cli_4618f53f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.268-show-context-freshness-cli`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.268-show-context-freshness-cli.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/show_context_freshness_cli_97a6dc51/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_freshness_cli_97a6dc51.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_freshness_cli_97a6dc51.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_show_context_freshness_cli_97a6dc51.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.269-show-context-conflicts-cli`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.269-show-context-conflicts-cli.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/show_context_conflicts_cli_14f46c5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_conflicts_cli_14f46c5d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_conflicts_cli_14f46c5d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_show_context_conflicts_cli_14f46c5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.270-show-context-gaps-cli`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.270-show-context-gaps-cli.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/show_context_gaps_cli_0d4a7864/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_gaps_cli_0d4a7864.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_gaps_cli_0d4a7864.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_show_context_gaps_cli_0d4a7864.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.271-show-context-relevance-cli`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.271-show-context-relevance-cli.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/show_context_relevance_cli_3b7f70f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_relevance_cli_3b7f70f2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/show_context_relevance_cli_3b7f70f2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_show_context_relevance_cli_3b7f70f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.272-context-dry-run`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.272-context-dry-run.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_dry_run_91ccb6d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_dry_run_91ccb6d4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_dry_run_91ccb6d4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_dry_run_91ccb6d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.273-context-explain`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.273-context-explain.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_explain_af3425fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_explain_af3425fe.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/context_explain_af3425fe.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_context_explain_af3425fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.274-panel-context-overview`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.274-panel-context-overview.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/panel_context_overview_67fcc61d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_context_overview_67fcc61d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_context_overview_67fcc61d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_panel_context_overview_67fcc61d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.275-panel-task-context-view`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.275-panel-task-context-view.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/panel_task_context_view_0742a78e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_task_context_view_0742a78e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_task_context_view_0742a78e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_panel_task_context_view_0742a78e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.276-panel-freshness-view`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.276-panel-freshness-view.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/panel_freshness_view_f7c53f36/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_freshness_view_f7c53f36.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_freshness_view_f7c53f36.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_panel_freshness_view_f7c53f36.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.277-panel-anomaly-view`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.277-panel-anomaly-view.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/panel_anomaly_view_912f71fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_anomaly_view_912f71fc.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_anomaly_view_912f71fc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_panel_anomaly_view_912f71fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.278-panel-provenance-view`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.278-panel-provenance-view.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/panel_provenance_view_5855b2a7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_provenance_view_5855b2a7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/panel_provenance_view_5855b2a7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_panel_provenance_view_5855b2a7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.279-context-api`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.279-context-api.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_api_84bf0063/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_api_84bf0063.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_api_84bf0063.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_context_api_84bf0063.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.280-context-ipc`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.280-context-ipc.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_ipc_ec4403c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_ipc_ec4403c5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_ipc_ec4403c5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_ipc_ec4403c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.281-context-provider-api`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.281-context-provider-api.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_provider_api_dd75dd4b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/context_provider_api_dd75dd4b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/context_provider_api_dd75dd4b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_context_provider_api_dd75dd4b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.282-context-source-registration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.282-context-source-registration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_registration_a40553a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_registration_a40553a1.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_registration_a40553a1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_source_registration_a40553a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.283-context-source-capability-discovery`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.283-context-source-capability-discovery.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_capability_discovery_e3fa47c6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/context_source_capability_discovery_e3fa47c6.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/context_source_capability_discovery_e3fa47c6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/resolution/test_context_source_capability_discovery_e3fa47c6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.284-context-source-health`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.284-context-source-health.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_health_1fb75a0b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_health_1fb75a0b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_health_1fb75a0b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_source_health_1fb75a0b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.285-context-source-timeout`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.285-context-source-timeout.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_timeout_09e78087/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_timeout_09e78087.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_timeout_09e78087.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_source_timeout_09e78087.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.286-context-source-cancellation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.286-context-source-cancellation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_cancellation_9ccc7b6b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_cancellation_9ccc7b6b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_cancellation_9ccc7b6b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_source_cancellation_9ccc7b6b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.287-context-source-backpressure`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.287-context-source-backpressure.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_backpressure_9d96d785/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_backpressure_9d96d785.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_backpressure_9d96d785.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_source_backpressure_9d96d785.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.288-context-source-partial-failure`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.288-context-source-partial-failure.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_partial_failure_246499da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_partial_failure_246499da.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_partial_failure_246499da.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_source_partial_failure_246499da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.289-context-source-unknown`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.289-context-source-unknown.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_unknown_266be782/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_unknown_266be782.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_source_unknown_266be782.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_source_unknown_266be782.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.290-parallel-context-collection`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.290-parallel-context-collection.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/parallel_context_collection_e875d692/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/parallel_context_collection_e875d692.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/parallel_context_collection_e875d692.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_parallel_context_collection_e875d692.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.291-bounded-concurrency`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.291-bounded-concurrency.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/bounded_concurrency_7f65937c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/bounded_concurrency_7f65937c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/bounded_concurrency_7f65937c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_bounded_concurrency_7f65937c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.292-context-latency-budget`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.292-context-latency-budget.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_latency_budget_9f52cc23/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_latency_budget_9f52cc23.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_latency_budget_9f52cc23.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_latency_budget_9f52cc23.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.293-context-memory-budget`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.293-context-memory-budget.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_memory_budget_dbb7e050/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_memory_budget_dbb7e050.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_memory_budget_dbb7e050.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_memory_budget_dbb7e050.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.294-context-size-budget`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.294-context-size-budget.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_size_budget_9409cc63/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_size_budget_9409cc63.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_size_budget_9409cc63.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_size_budget_9409cc63.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.295-context-collection-timeout`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.295-context-collection-timeout.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_collection_timeout_73891aff/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_collection_timeout_73891aff.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_collection_timeout_73891aff.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_collection_timeout_73891aff.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.296-context-cancellation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.296-context-cancellation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_cancellation_73f48139/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_cancellation_73f48139.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_cancellation_73f48139.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_cancellation_73f48139.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.297-context-crash-recovery`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.297-context-crash-recovery.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_crash_recovery_0793d5de/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/recovery/context_crash_recovery_0793d5de.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/recovery/context_crash_recovery_0793d5de.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/recovery/test_context_crash_recovery_0793d5de.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.298-context-restart-behavior`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.298-context-restart-behavior.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_restart_behavior_625ef056/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/recovery/context_restart_behavior_625ef056.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/recovery/context_restart_behavior_625ef056.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/recovery/test_context_restart_behavior_625ef056.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.299-context-reboot-behavior`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.299-context-reboot-behavior.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_reboot_behavior_8781b79e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_reboot_behavior_8781b79e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_reboot_behavior_8781b79e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_reboot_behavior_8781b79e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.300-context-schema-versioning`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.300-context-schema-versioning.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_schema_versioning_0a9fea5a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_schema_versioning_0a9fea5a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/context_schema_versioning_0a9fea5a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_context_schema_versioning_0a9fea5a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.301-context-migration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.301-context-migration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_migration_e505d3a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/context_migration_e505d3a4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/context_migration_e505d3a4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_context_migration_e505d3a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.302-context-compatibility`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.302-context-compatibility.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_compatibility_2a90a72f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_compatibility_2a90a72f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/context_compatibility_2a90a72f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_context_compatibility_2a90a72f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.303-context-testing-framework`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.303-context-testing-framework.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_testing_framework_871ab345/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_testing_framework_871ab345.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_testing_framework_871ab345.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_context_testing_framework_871ab345.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.304-synthetic-context-fixtures`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.304-synthetic-context-fixtures.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/synthetic_context_fixtures_1574451d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/synthetic_context_fixtures_1574451d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/synthetic_context_fixtures_1574451d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_synthetic_context_fixtures_1574451d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.305-recorded-context-fixtures`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.305-recorded-context-fixtures.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/recorded_context_fixtures_23e3683d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recorded_context_fixtures_23e3683d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/recorded_context_fixtures_23e3683d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_recorded_context_fixtures_23e3683d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.306-holdout-context-corpus`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.306-holdout-context-corpus.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/holdout_context_corpus_6ea7fc04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/holdout_context_corpus_6ea7fc04.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/holdout_context_corpus_6ea7fc04.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_holdout_context_corpus_6ea7fc04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.307-benign-context-corpus`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.307-benign-context-corpus.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/benign_context_corpus_023bd30a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/benign_context_corpus_023bd30a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/benign_context_corpus_023bd30a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_benign_context_corpus_023bd30a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.308-ambiguous-context-corpus`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.308-ambiguous-context-corpus.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ambiguous_context_corpus_9f5b7f38/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ambiguous_context_corpus_9f5b7f38.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ambiguous_context_corpus_9f5b7f38.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_ambiguous_context_corpus_9f5b7f38.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.309-stale-context-corpus`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.309-stale-context-corpus.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/stale_context_corpus_05c63f41/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/stale_context_corpus_05c63f41.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/stale_context_corpus_05c63f41.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_stale_context_corpus_05c63f41.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.310-poisoned-context-corpus`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.310-poisoned-context-corpus.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/poisoned_context_corpus_bd721ba4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/poisoned_context_corpus_bd721ba4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/poisoned_context_corpus_bd721ba4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_poisoned_context_corpus_bd721ba4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.311-adversarial-context-corpus`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.311-adversarial-context-corpus.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_context_corpus_0e0debea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/adversarial_context_corpus_0e0debea.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/adversarial_context_corpus_0e0debea.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_adversarial_context_corpus_0e0debea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.312-read-only-task-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.312-read-only-task-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/read_only_task_scenario_ee55b225/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/read_only_task_scenario_ee55b225.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/read_only_task_scenario_ee55b225.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_read_only_task_scenario_ee55b225.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.313-mutating-task-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.313-mutating-task-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/mutating_task_scenario_095a5c13/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/mutating_task_scenario_095a5c13.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/mutating_task_scenario_095a5c13.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_mutating_task_scenario_095a5c13.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.314-ask-referent-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.314-ask-referent-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ask_referent_scenario_675d42b2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ask_referent_scenario_675d42b2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/ask_referent_scenario_675d42b2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_ask_referent_scenario_675d42b2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.315-taskwarrior-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.315-taskwarrior-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/taskwarrior_scenario_a765a5e9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taskwarrior_scenario_a765a5e9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/taskwarrior_scenario_a765a5e9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_taskwarrior_scenario_a765a5e9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.316-workflow-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.316-workflow-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/workflow_scenario_ff87daa5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/workflow_scenario_ff87daa5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/workflow_scenario_ff87daa5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_workflow_scenario_ff87daa5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.317-automation-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.317-automation-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/automation_scenario_3121f112/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/automation_scenario_3121f112.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/automation_scenario_3121f112.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_automation_scenario_3121f112.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.318-agent-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.318-agent-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/agent_scenario_ba259d36/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/agent_scenario_ba259d36.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/agent_scenario_ba259d36.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_agent_scenario_ba259d36.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.319-maintenance-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.319-maintenance-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/maintenance_scenario_833d7793/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/maintenance_scenario_833d7793.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/maintenance_scenario_833d7793.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_maintenance_scenario_833d7793.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.320-unexpected-network-task-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.320-unexpected-network-task-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/unexpected_network_task_scenario_2861d03b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/unexpected_network_task_scenario_2861d03b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/unexpected_network_task_scenario_2861d03b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_unexpected_network_task_scenario_2861d03b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.321-log-export-context-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.321-log-export-context-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/log_export_context_scenario_60569280/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/log_export_context_scenario_60569280.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/log_export_context_scenario_60569280.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_log_export_context_scenario_60569280.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.322-fork-bomb-intent-context-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.322-fork-bomb-intent-context-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/fork_bomb_intent_context_scenario_e87d5c12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/fork_bomb_intent_context_scenario_e87d5c12.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/fork_bomb_intent_context_scenario_e87d5c12.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_fork_bomb_intent_context_scenario_e87d5c12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.323-gpu-task-context-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.323-gpu-task-context-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/gpu_task_context_scenario_0359d1d3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/gpu_task_context_scenario_0359d1d3.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/gpu_task_context_scenario_0359d1d3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_gpu_task_context_scenario_0359d1d3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.324-storage-task-context-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.324-storage-task-context-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/storage_task_context_scenario_78a1ee3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/storage_task_context_scenario_78a1ee3f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/storage_task_context_scenario_78a1ee3f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_storage_task_context_scenario_78a1ee3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.325-service-task-context-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.325-service-task-context-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/service_task_context_scenario_d08879f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/service_task_context_scenario_d08879f0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/service_task_context_scenario_d08879f0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_service_task_context_scenario_d08879f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.326-package-task-context-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.326-package-task-context-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/package_task_context_scenario_b3449707/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/package_task_context_scenario_b3449707.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/package_task_context_scenario_b3449707.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_package_task_context_scenario_b3449707.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.327-configuration-task-context-scenario`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.327-configuration-task-context-scenario.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/configuration_task_context_scenario_faf34f7f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/configuration_task_context_scenario_faf34f7f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/configuration_task_context_scenario_faf34f7f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_configuration_task_context_scenario_faf34f7f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.328-stale-context-adversarial-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.328-stale-context-adversarial-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/stale_context_adversarial_test_d004a228/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/stale_context_adversarial_test_d004a228.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/stale_context_adversarial_test_d004a228.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_stale_context_adversarial_test_d004a228.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.329-cross-session-leakage-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.329-cross-session-leakage-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_session_leakage_test_987b4906/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cross_session_leakage_test_987b4906.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cross_session_leakage_test_987b4906.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_cross_session_leakage_test_987b4906.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.330-cross-user-leakage-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.330-cross-user-leakage-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cross_user_leakage_test_e299daa0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cross_user_leakage_test_e299daa0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cross_user_leakage_test_e299daa0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_cross_user_leakage_test_e299daa0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.331-ambiguous-referent-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.331-ambiguous-referent-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ambiguous_referent_test_580b024b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/ambiguous_referent_test_580b024b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/ambiguous_referent_test_580b024b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_ambiguous_referent_test_580b024b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.332-ordinal-referent-confusion-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.332-ordinal-referent-confusion-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/ordinal_referent_confusion_test_7eb20635/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/ordinal_referent_confusion_test_7eb20635.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/ordinal_referent_confusion_test_7eb20635.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_ordinal_referent_confusion_test_7eb20635.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.333-device-renumbering-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.333-device-renumbering-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/device_renumbering_test_4a9892c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/device_renumbering_test_4a9892c3.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/device_renumbering_test_4a9892c3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_device_renumbering_test_4a9892c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.334-gpu-index-identity-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.334-gpu-index-identity-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/gpu_index_identity_test_1cde247e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/gpu_index_identity_test_1cde247e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/gpu_index_identity_test_1cde247e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_gpu_index_identity_test_1cde247e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.335-pid-reuse-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.335-pid-reuse-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/pid_reuse_context_test_b80bac26/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/pid_reuse_context_test_b80bac26.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/pid_reuse_context_test_b80bac26.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_pid_reuse_context_test_b80bac26.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.336-network-interface-rename-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.336-network-interface-rename-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/network_interface_rename_test_a51efaeb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/network_interface_rename_test_a51efaeb.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/network_interface_rename_test_a51efaeb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_network_interface_rename_test_a51efaeb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.337-mount-identity-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.337-mount-identity-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/mount_identity_test_ffe3e825/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/mount_identity_test_ffe3e825.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/mount_identity_test_ffe3e825.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_mount_identity_test_ffe3e825.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.338-clock-jump-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.338-clock-jump-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/clock_jump_test_af49949f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/clock_jump_test_af49949f.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/clock_jump_test_af49949f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_clock_jump_test_af49949f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.339-reboot-freshness-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.339-reboot-freshness-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/reboot_freshness_test_39eb0b94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/reboot_freshness_test_39eb0b94.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/reboot_freshness_test_39eb0b94.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_reboot_freshness_test_39eb0b94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.340-out-of-order-event-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.340-out-of-order-event-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/out_of_order_event_test_183a814b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/out_of_order_event_test_183a814b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/out_of_order_event_test_183a814b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_out_of_order_event_test_183a814b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.341-missing-event-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.341-missing-event-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/missing_event_test_4f7ec7e5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/missing_event_test_4f7ec7e5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/missing_event_test_4f7ec7e5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_missing_event_test_4f7ec7e5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.342-graph-contradiction-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.342-graph-contradiction-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/graph_contradiction_test_7d0a0ec8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/graph_contradiction_test_7d0a0ec8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/graph_contradiction_test_7d0a0ec8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_graph_contradiction_test_7d0a0ec8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.343-graph-path-causality-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.343-graph-path-causality-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/graph_path_causality_test_465ab2f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/graph_path_causality_test_465ab2f2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/graph_path_causality_test_465ab2f2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_graph_path_causality_test_465ab2f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.344-prompt-injection-from-log-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.344-prompt-injection-from-log-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/prompt_injection_from_log_test_e6936d7a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_log_test_e6936d7a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_log_test_e6936d7a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_prompt_injection_from_log_test_e6936d7a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.345-prompt-injection-from-readme-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.345-prompt-injection-from-readme-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/prompt_injection_from_readme_test_33562487/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_readme_test_33562487.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_readme_test_33562487.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_prompt_injection_from_readme_test_33562487.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.346-prompt-injection-from-process-output-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.346-prompt-injection-from-process-output-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/prompt_injection_from_process_output_test_37f12458/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_process_output_test_37f12458.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_process_output_test_37f12458.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_prompt_injection_from_process_output_test_37f12458.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.347-prompt-injection-from-remote-content-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.347-prompt-injection-from-remote-content-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/prompt_injection_from_remote_content_test_2f1ff6cd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_remote_content_test_2f1ff6cd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/prompt_injection_from_remote_content_test_2f1ff6cd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_prompt_injection_from_remote_content_test_2f1ff6cd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.348-context-poisoning-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.348-context-poisoning-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_poisoning_test_b232f91a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_poisoning_test_b232f91a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_poisoning_test_b232f91a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_context_poisoning_test_b232f91a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.349-context-laundering-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.349-context-laundering-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_laundering_test_5841a9e9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_laundering_test_5841a9e9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_laundering_test_5841a9e9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_context_laundering_test_5841a9e9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.350-authority-laundering-via-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.350-authority-laundering-via-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/authority_laundering_via_context_test_954d132a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/authority_laundering_via_context_test_954d132a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/authority_laundering_via_context_test_954d132a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_authority_laundering_via_context_test_954d132a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.351-fake-operator-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.351-fake-operator-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/fake_operator_context_test_149e6887/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/fake_operator_context_test_149e6887.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/fake_operator_context_test_149e6887.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_fake_operator_context_test_149e6887.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.352-semantic-hallucinated-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.352-semantic-hallucinated-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/semantic_hallucinated_context_test_d9742928/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/semantic_hallucinated_context_test_d9742928.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/semantic_hallucinated_context_test_d9742928.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_semantic_hallucinated_context_test_d9742928.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.353-gordon-hallucinated-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.353-gordon-hallucinated-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/gordon_hallucinated_context_test_3852b04c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/gordon_hallucinated_context_test_3852b04c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/gordon_hallucinated_context_test_3852b04c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_gordon_hallucinated_context_test_3852b04c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.354-secret-leakage-projection-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.354-secret-leakage-projection-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/secret_leakage_projection_test_66451289/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/secret_leakage_projection_test_66451289.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/secret_leakage_projection_test_66451289.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_secret_leakage_projection_test_66451289.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.355-oversized-context-dos-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.355-oversized-context-dos-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/oversized_context_dos_test_270a775b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/oversized_context_dos_test_270a775b.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/oversized_context_dos_test_270a775b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_oversized_context_dos_test_270a775b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.356-context-source-timeout-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.356-context-source-timeout-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_timeout_test_3f161691/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_source_timeout_test_3f161691.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_source_timeout_test_3f161691.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_context_source_timeout_test_3f161691.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.357-context-source-compromise-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.357-context-source-compromise-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/context_source_compromise_test_a20df33e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_source_compromise_test_a20df33e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/context_source_compromise_test_a20df33e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_context_source_compromise_test_a20df33e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.358-cache-poisoning-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.358-cache-poisoning-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cache_poisoning_test_1dda3604/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cache_poisoning_test_1dda3604.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cache_poisoning_test_1dda3604.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_cache_poisoning_test_1dda3604.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.359-cache-staleness-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.359-cache-staleness-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/cache_staleness_test_83d938c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cache_staleness_test_83d938c2.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/cache_staleness_test_83d938c2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_cache_staleness_test_83d938c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.360-toctou-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.360-toctou-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/toctou_context_test_58762eb4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/toctou_context_test_58762eb4.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/toctou_context_test_58762eb4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_toctou_context_test_58762eb4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.361-state-drift-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.361-state-drift-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/state_drift_test_cbfe1acf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/state_drift_test_cbfe1acf.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/state_drift_test_cbfe1acf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_state_drift_test_cbfe1acf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.362-changed-target-after-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.362-changed-target-after-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/changed_target_after_context_test_8ef68295/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/changed_target_after_context_test_8ef68295.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/changed_target_after_context_test_8ef68295.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_changed_target_after_context_test_8ef68295.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.363-changed-destination-after-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.363-changed-destination-after-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/changed_destination_after_context_test_c376285c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/changed_destination_after_context_test_c376285c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/changed_destination_after_context_test_c376285c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_changed_destination_after_context_test_c376285c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.364-changed-requester-after-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.364-changed-requester-after-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/changed_requester_after_context_test_2e69dc7d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/changed_requester_after_context_test_2e69dc7d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/changed_requester_after_context_test_2e69dc7d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_changed_requester_after_context_test_2e69dc7d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.365-concurrent-task-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.365-concurrent-task-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/concurrent_task_context_test_bca68d35/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/concurrent_task_context_test_bca68d35.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/concurrent_task_context_test_bca68d35.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_concurrent_task_context_test_bca68d35.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.366-concurrent-session-context-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.366-concurrent-session-context-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/concurrent_session_context_test_b711a6bd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/concurrent_session_context_test_b711a6bd.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/concurrent_session_context_test_b711a6bd.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_concurrent_session_context_test_b711a6bd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.367-performance-regression-test`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.367-performance-regression-test.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/performance_regression_test_ef384661/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/performance_regression_test_ef384661.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/performance_regression_test_ef384661.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_performance_regression_test_ef384661.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.368-repository-source-tree-normalization`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.368-repository-source-tree-normalization.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/repository_source_tree_normalization_54e69474/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/repository_source_tree_normalization_54e69474.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/repository_source_tree_normalization_54e69474.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_repository_source_tree_normalization_54e69474.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.369-existing-context-code-migration`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.369-existing-context-code-migration.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/existing_context_code_migration_cf3a656d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/integration/existing_context_code_migration_cf3a656d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/integration/existing_context_code_migration_cf3a656d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/integration/test_existing_context_code_migration_cf3a656d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.370-duplicate-context-store-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.370-duplicate-context-store-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/duplicate_context_store_audit_d2748941/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_context_store_audit_d2748941.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_context_store_audit_d2748941.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_duplicate_context_store_audit_d2748941.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.371-duplicate-context-cache-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.371-duplicate-context-cache-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/duplicate_context_cache_audit_49cbe915/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_context_cache_audit_49cbe915.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_context_cache_audit_49cbe915.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_duplicate_context_cache_audit_49cbe915.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.372-duplicate-referent-resolver-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.372-duplicate-referent-resolver-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/duplicate_referent_resolver_audit_2584b662/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_referent_resolver_audit_2584b662.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_referent_resolver_audit_2584b662.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_duplicate_referent_resolver_audit_2584b662.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.373-duplicate-relevance-engine-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.373-duplicate-relevance-engine-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/duplicate_relevance_engine_audit_d2c42c0a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_relevance_engine_audit_d2c42c0a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/duplicate_relevance_engine_audit_d2c42c0a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_duplicate_relevance_engine_audit_d2c42c0a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.374-implicit-global-context-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.374-implicit-global-context-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/implicit_global_context_audit_68912cc9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/implicit_global_context_audit_68912cc9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/implicit_global_context_audit_68912cc9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_implicit_global_context_audit_68912cc9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.375-direct-semantic-raw-state-dump-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.375-direct-semantic-raw-state-dump-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/direct_semantic_raw_state_dump_audit_2c43f1f5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/direct_semantic_raw_state_dump_audit_2c43f1f5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/direct_semantic_raw_state_dump_audit_2c43f1f5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_direct_semantic_raw_state_dump_audit_2c43f1f5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.376-direct-model-context-authority-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.376-direct-model-context-authority-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/direct_model_context_authority_audit_5b4ee01a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/direct_model_context_authority_audit_5b4ee01a.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/direct_model_context_authority_audit_5b4ee01a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_direct_model_context_authority_audit_5b4ee01a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.377-stale-python-context-ownership-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.377-stale-python-context-ownership-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/stale_python_context_ownership_audit_34697a73/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/stale_python_context_ownership_audit_34697a73.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/stale_python_context_ownership_audit_34697a73.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_stale_python_context_ownership_audit_34697a73.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.378-remaining-python-boundary-inventory`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.378-remaining-python-boundary-inventory.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/remaining_python_boundary_inventory_86db06f1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/remaining_python_boundary_inventory_86db06f1.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/remaining_python_boundary_inventory_86db06f1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_remaining_python_boundary_inventory_86db06f1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.379-c-first-context-contract-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.379-c-first-context-contract-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/c_first_context_contract_audit_d7723b48/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/c_first_context_contract_audit_d7723b48.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/c_first_context_contract_audit_d7723b48.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_c_first_context_contract_audit_d7723b48.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.380-agents-context-architecture-contract`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.380-agents-context-architecture-contract.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/agents_context_architecture_contract_52628abc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_context_architecture_contract_52628abc.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_context_architecture_contract_52628abc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_agents_context_architecture_contract_52628abc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.381-agents-provenance-contract`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.381-agents-provenance-contract.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/agents_provenance_contract_ce4d5b2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_provenance_contract_ce4d5b2e.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_provenance_contract_ce4d5b2e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_agents_provenance_contract_ce4d5b2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.382-agents-freshness-contract`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.382-agents-freshness-contract.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/agents_freshness_contract_d874de43/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_freshness_contract_d874de43.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_freshness_contract_d874de43.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_agents_freshness_contract_d874de43.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.383-agents-context-no-authority-contract`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.383-agents-context-no-authority-contract.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/agents_context_no_authority_contract_d6ef0d8d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_context_no_authority_contract_d6ef0d8d.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_context_no_authority_contract_d6ef0d8d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_agents_context_no_authority_contract_d6ef0d8d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.384-agents-semantic-projection-contract`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.384-agents-semantic-projection-contract.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/agents_semantic_projection_contract_882acc36/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_semantic_projection_contract_882acc36.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/contracts/agents_semantic_projection_contract_882acc36.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/contracts/test_agents_semantic_projection_contract_882acc36.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.385-recursive-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.385-recursive-rediscovery-pass-one.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/recursive_rediscovery_pass_one_9ced3436/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/recursive_rediscovery_pass_one_9ced3436.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/recursive_rediscovery_pass_one_9ced3436.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/resolution/test_recursive_rediscovery_pass_one_9ced3436.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.386-resolve-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.386-resolve-rediscovery-pass-one.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/resolve_rediscovery_pass_one_0817e699/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/resolve_rediscovery_pass_one_0817e699.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/resolve_rediscovery_pass_one_0817e699.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/resolution/test_resolve_rediscovery_pass_one_0817e699.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.387-recursive-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.387-recursive-rediscovery-pass-two.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/recursive_rediscovery_pass_two_ffa97928/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/recursive_rediscovery_pass_two_ffa97928.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/recursive_rediscovery_pass_two_ffa97928.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/resolution/test_recursive_rediscovery_pass_two_ffa97928.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.388-resolve-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.388-resolve-rediscovery-pass-two.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/resolve_rediscovery_pass_two_8fb60ae5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/resolve_rediscovery_pass_two_8fb60ae5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/resolve_rediscovery_pass_two_8fb60ae5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/resolution/test_resolve_rediscovery_pass_two_8fb60ae5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.389-adversarial-context-bypass-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.389-adversarial-context-bypass-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_context_bypass_audit_ffa022e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_context_bypass_audit_ffa022e8.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_context_bypass_audit_ffa022e8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_adversarial_context_bypass_audit_ffa022e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.390-adversarial-poisoning-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.390-adversarial-poisoning-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_poisoning_audit_640a3482/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_poisoning_audit_640a3482.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_poisoning_audit_640a3482.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_adversarial_poisoning_audit_640a3482.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.391-adversarial-freshness-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.391-adversarial-freshness-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_freshness_audit_aa818c44/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_freshness_audit_aa818c44.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_freshness_audit_aa818c44.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_adversarial_freshness_audit_aa818c44.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.392-adversarial-isolation-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.392-adversarial-isolation-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_isolation_audit_3f591c0c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_isolation_audit_3f591c0c.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_isolation_audit_3f591c0c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_adversarial_isolation_audit_3f591c0c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.393-adversarial-referent-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.393-adversarial-referent-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_referent_audit_235fae82/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_referent_audit_235fae82.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_referent_audit_235fae82.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_adversarial_referent_audit_235fae82.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.394-adversarial-secret-safety-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.394-adversarial-secret-safety-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_secret_safety_audit_311aeac0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_secret_safety_audit_311aeac0.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_secret_safety_audit_311aeac0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_adversarial_secret_safety_audit_311aeac0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.395-adversarial-semantic-provider-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.395-adversarial-semantic-provider-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/adversarial_semantic_provider_audit_b9a471a5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_semantic_provider_audit_b9a471a5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/adversarial_semantic_provider_audit_b9a471a5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_adversarial_semantic_provider_audit_b9a471a5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.396-final-native-build`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.396-final-native-build.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_native_build_5f1b50b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_native_build_5f1b50b7.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_native_build_5f1b50b7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_final_native_build_5f1b50b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.397-final-unit-tests`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.397-final-unit-tests.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_unit_tests_8cb401e9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_unit_tests_8cb401e9.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_unit_tests_8cb401e9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_final_unit_tests_8cb401e9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.398-final-integration-tests`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.398-final-integration-tests.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_integration_tests_8aa709fc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_integration_tests_8aa709fc.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_integration_tests_8aa709fc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_final_integration_tests_8aa709fc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.399-final-end-to-end-tests`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.399-final-end-to-end-tests.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_end_to_end_tests_d19e6405/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_end_to_end_tests_d19e6405.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_end_to_end_tests_d19e6405.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_final_end_to_end_tests_d19e6405.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.400-final-adversarial-suite`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.400-final-adversarial-suite.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_adversarial_suite_8b7734ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_adversarial_suite_8b7734ee.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_adversarial_suite_8b7734ee.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_final_adversarial_suite_8b7734ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.401-final-performance-validation`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.401-final-performance-validation.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_performance_validation_c7a132ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_performance_validation_c7a132ea.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_performance_validation_c7a132ea.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_final_performance_validation_c7a132ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.402-final-context-source-inventory`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.402-final-context-source-inventory.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_context_source_inventory_b8f969ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_context_source_inventory_b8f969ae.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_context_source_inventory_b8f969ae.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_final_context_source_inventory_b8f969ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.403-final-source-tree-audit`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.403-final-source-tree-audit.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_source_tree_audit_e73abb99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_source_tree_audit_e73abb99.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/verification/final_source_tree_audit_e73abb99.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/verification/test_final_source_tree_audit_e73abb99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.404-final-production-call-graph-trace`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.404-final-production-call-graph-trace.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_production_call_graph_trace_cb5a6595/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/observability/final_production_call_graph_trace_cb5a6595.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/observability/final_production_call_graph_trace_cb5a6595.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/observability/test_final_production_call_graph_trace_cb5a6595.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.405-final-context-flow-graph`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.405-final-context-flow-graph.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_context_flow_graph_bb240d93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_context_flow_graph_bb240d93.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_context_flow_graph_bb240d93.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_final_context_flow_graph_bb240d93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.406-final-trust-graph`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.406-final-trust-graph.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_trust_graph_219eff30/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/security/final_trust_graph_219eff30.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/security/final_trust_graph_219eff30.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/security/test_final_trust_graph_219eff30.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.407-final-remaining-python-inventory`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.407-final-remaining-python-inventory.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_remaining_python_inventory_6e0f3aa5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_remaining_python_inventory_6e0f3aa5.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/final_remaining_python_inventory_6e0f3aa5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_final_remaining_python_inventory_6e0f3aa5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.408-final-fixed-point-rediscovery`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.408-final-fixed-point-rediscovery.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/final_fixed_point_rediscovery_8ba484ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/final_fixed_point_rediscovery_8ba484ed.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/resolution/final_fixed_point_rediscovery_8ba484ed.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/resolution/test_final_fixed_point_rediscovery_8ba484ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `48.409-phase-48-closure-and-future-handoff`
- **Source:** `.phases/phases/phase-48-os-task-context-awareness-system/prompts/48.409-phase-48-closure-and-future-handoff.md`
- **Structural package:** `src/semantics/os-task-context-awareness-system/subtask_packages/verification/closure_and_future_handoff_c8912119/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/closure_and_future_handoff_c8912119.hpp`, `src/semantics/os-task-context-awareness-system/subtask_targets/requirements/closure_and_future_handoff_c8912119.cpp`
- **Structural test target:** `tests/structural-closure/semantics/os-task-context-awareness-system/requirements/test_closure_and_future_handoff_c8912119.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

