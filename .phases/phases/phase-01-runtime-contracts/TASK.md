# Phase 01 — Runtime Contracts — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-01-runtime-contracts/`
- Primary prompt location: `.phases/phases/phase-01-runtime-contracts/prompts/`
- Prompt/specification Markdown files currently present: **19**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 19 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_01` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Phase 1: Runtime Contracts
- Layout
- Prompt Index
- Agent Handoff — Phase 1
- Rebuntu — Phase 1.2 — Installation Planning & Environment Preparation
- Agent Task
- Global Agent Contract
- Non-negotiable engineering principles
- Required repository-first procedure
- Phase 0 contracts are binding inputs
- Safe host-modification policy
- Native Linux policy

## Structural skeleton / canonical destination
- Canonical skeleton: `src/runtime/runtime-contracts/`
- Structural files: `src/runtime/runtime-contracts/component.hpp`, `src/runtime/runtime-contracts/component.cpp`, `src/runtime/runtime-contracts/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** FUNCTIONAL-PARTIAL
- **Implementation depth:** **3/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/runtime/contracts.hpp`
- `src/runtime/core/contracts.hpp`
- `src/runtime/lifecycle/contracts.hpp`
- `src/automation/runtime/automation.cpp`
- `src/automation/runtime/automation_runtime.cpp`
- `src/control/runtime/backend.cpp`
- `src/control/runtime/change_executor.cpp`
- `src/control/runtime/change_planner.cpp`
- `src/control/runtime/control_runtime.cpp`
- `src/control/runtime/domain_controller.cpp`
- `src/control/runtime/graph.cpp`
- `src/control/runtime/health_monitor.cpp`

### Existing test evidence
- `tests/native/test_runtime_contracts.cpp`
- `tests/native/test_production_runtime.cpp`
- `tests/native/test_deep_runtime.cpp`
- `tests/native/test_contracts.cpp`
- `tests/native/test_container_runtime.cpp`

## What is already implemented

### IMPLEMENTATION SATURATION II — verified additions
- **Phase 1.1 host discovery/preconditions (partial behavioral implementation):** `src/runtime/preflight/host_preflight.hpp/.cpp` now discovers distribution/version from `/etc/os-release`, kernel/architecture through `uname(2)`, effective UID, HOME/SHELL evidence, systemd presence, package-manager availability, and filesystem free space. Important facts carry source/provenance and unknown distribution is treated as unknown rather than automatically unsupported.
- **Precondition separation:** `HostPreflight::evaluate()` derives warnings/blockers from facts through an explicit `Policy`; discovery itself does not mutate the host.
- **Machine/human report:** `Report` retains structured facts/findings and provides a human-readable summary.
- **Phase 1.2 installation planning (partial behavioral implementation):** `src/runtime/installation/installation_plan.hpp/.cpp` converts validated intent + preflight into explicit ordered steps with targets, prerequisites, privilege/mutation markers, verification text and checkpoints.
- **Truthful dry-run semantics:** planning records the race/uncertainty warning and does not execute the plan.
- **Dependency classification:** bootstrap/runtime/optional/development/provider-specific classes are represented; optional non-required development dependencies are not blindly planned.
- **Safety:** relative installation roots are rejected; a blocked preflight yields a reviewable but non-executable plan.
- **Verification evidence:** `tests/rebuntu/test_preflight_planning.cpp` exercises supported/blocked hosts, dry-run planning, dependency selection, and invalid target roots. It compiled with `-std=c++20 -Wall -Wextra -Wpedantic -Werror` and produced `PREFLIGHT_PLANNING_PASS`.

- The paths above are candidate evidence of concrete implementation related to this phase.
- Treat an item as implemented only after confirming its behavior satisfies the corresponding prompt requirement.
- Shared infrastructure may satisfy parts of several phases; record that relationship rather than duplicating code.

## What remains to implement
- [ ] Phase 1.1: deepen privilege/elevation discovery without privileged mutation; writable-target checks; richer virtualization/container facts where behavior differs; optional capability reporting.
- [ ] Phase 1.2: connect planning to canonical Operation/Workflow contracts instead of keeping the current small plan grammar isolated; add secure staging implementation, artifact integrity/provenance verification, version constraints, rollback/repair metadata and dependency graph ordering.
- [ ] Read/audit prompts 1.0 and 1.3–1.12 and convert them into requirement-specific ledger entries; SATURATION II deliberately implemented 1.1/1.2 rather than pretending the complete Phase 1 prompt set was audited.
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

- Structural skeleton materialized at `src/runtime/runtime-contracts/`; this raises structural coverage only and does not claim prompt behavior.

## Update log — IMPLEMENTATION SATURATION II
- Implemented concrete Phase 1.1 host preflight discovery/evaluation and Phase 1.2 installation planning/dry-run behavior.
- Added strict C++20 test `tests/rebuntu/test_preflight_planning.cpp`; observed result: `PREFLIGHT_PLANNING_PASS`.
- Overall phase remains **3/5 FUNCTIONAL-PARTIAL** because prompts 1.0 and 1.3–1.12 remain to be audited/implemented and the new planner still needs integration with canonical runtime operation/workflow execution.

## Update log — IMPLEMENTATION SATURATION III
- Audited Phase 1.3–1.6 source prompts against existing code instead of creating duplicate phase-local subsystems.
- **1.3 Structured setup input:** deepened `src/portability/install/forms.hpp`. `FormParser` now rejects unknown fields, validates enum/choice admissibility, performs strict integer/boolean parsing, supports non-mutating path constraints, and returns structured validation errors. Existing separation of schema, channel, parsed result and metadata is retained.
- **1.6 Options:** deliberately kept options as `allowed_values` schema metadata rather than introducing a first-class runtime Option subsystem. Invalid selections now fail validation. Dynamic host choices remain observation/provider responsibility and are not hardcoded as options.
- **1.5 Settings:** audited existing `src/runtime/settings.hpp` and `tests/native/test_settings.cpp`; typed definitions, scope, defaults, allowed values, registry/manager and validation already exist. This pass did not claim serialization/policy/precedence closure; those remain explicit gaps.
- **1.4 User context:** audited existing NSS-backed `src/observation/environment/user_identity.hpp` and native implementation. Linux/NSS remains authority. Full sudo-target validation/multi-user authorization remains incomplete, so no completion claim is made.
- Added `tests/rebuntu/test_structured_setup.cpp`; strict C++20 compile/run observed `STRUCTURED_SETUP_PASS`.
- Re-ran `tests/native/test_forms.cpp` with `-Wall -Wextra -Wpedantic -Werror`; observed `All tests passed`.
- Phase remains **3/5 FUNCTIONAL-PARTIAL**: meaningful behavior exists across 1.1–1.6, but prompts 1.0 and 1.7–1.12 plus integration/negative-path requirements remain open.

### SATURATION III remaining gaps
- [ ] 1.3: add cross-field dependency/mutual-exclusion and policy-constraint validators; secret-safe rendering/reporting; explicit host-derived suggestion provenance; complete non-interactive required-field semantics.
- [ ] 1.4: validate sudo invoking identity against NSS/UID evidence; model target-user authorization and shared-vs-user ownership without duplicating NSS.
- [ ] 1.5: verify Phase 0.18/0.20 vocabulary decision; deterministic multi-source precedence, durable round-trip only where required, policy constraints and provenance rendering.
- [ ] 1.6: connect dynamic choice metadata to observation where a real consumer requires it; do not create an Option service merely for coverage.

## IMPLEMENTATION SATURATION IV — saturation + tree deepening

This pass deepens Phase 1.7–1.12 as semantic vertical slices rather than adding a parallel installer framework.

### Added implementation evidence
- `src/runtime/preferences/resolver.hpp/.cpp` — layered preference precedence, availability/policy constraint evaluation, explicit fallback and explanation without rewriting the stored preference.
- `src/portability/setup/configuration/model.hpp/.cpp` — configuration ownership classification and deterministic semantic diff; user-owned configuration is not treated as managed removal state.
- `src/observation/discovery/installation/facts.hpp/.cpp` — fresh, timestamped installation-scoped facts from `uname`, procfs and systemd filesystem evidence with graceful partial discovery.
- `src/portability/setup/profile/bootstrap.hpp/.cpp` — deterministic bounded bootstrap profile derivation with per-key provenance and precedence `discovery < preference < explicit < policy`.
- `src/runtime/installation/lifecycle/operations.hpp/.cpp` — lifecycle vocabulary and ownership-gated uninstall/purge removal planning; uninstall preserves user-authored artifacts.
- `src/runtime/installation/verification/invariants.hpp/.cpp` — explicit installation invariant evaluation and failed-invariant reporting.
- `tests/rebuntu/test_saturation_iv.cpp` — integration test across the six new slices.

### Verification
`test_saturation_iv.cpp` compiled with C++20 and `-Wall -Wextra -Wpedantic -Werror` and returned `SATURATION_IV_PASS`.

### Current depth assessment
Phase 1 remains **3/5 — FUNCTIONAL-PARTIAL**. The phase now has concrete behavior across 1.1–1.12, but 4/5 requires integration of these slices into one isolated-root setup/install transaction, provider-backed mutations, ownership manifest verification, repair/upgrade fixtures, and end-to-end repeated-install/reconfigure/uninstall verification. 5/5 additionally requires closing every prompt acceptance item with evidence.

### Next implementation targets
1. Introduce an isolated installation root and ownership manifest shared by install/repair/uninstall.
2. Connect configuration diff/profile derivation to typed operations and atomic file provider behavior.
3. Expand installation discovery into CPU/memory/storage/network/GPU/package-manager domain probes only where setup has consumers.
4. Add repair and upgrade planning with checkpoint/migration contracts.
5. Build Phase 1.12 end-to-end fixture: preflight → plan → setup → verify → reconfigure → repair → uninstall, proving convergence and user-data preservation.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/runtime/runtime-contracts/model/`
- `src/runtime/runtime-contracts/contracts/`
- `src/runtime/runtime-contracts/integration/`
- `src/runtime/runtime-contracts/verification/`
- `src/runtime/runtime-contracts/lifecycle/`
- `src/runtime/runtime-contracts/state/`
- `src/runtime/runtime-contracts/execution/`
- `src/runtime/runtime-contracts/transactions/`
- `src/runtime/runtime-contracts/events/`
- `src/runtime/runtime-contracts/scheduling/`
- `src/runtime/runtime-contracts/recovery/`
- `src/runtime/runtime-contracts/preflight/`
- `src/runtime/runtime-contracts/planning/`
- `src/runtime/runtime-contracts/staging/`
- `src/runtime/runtime-contracts/ownership/`
- `src/runtime/runtime-contracts/repair/`
- `src/runtime/runtime-contracts/upgrade/`
- `src/runtime/runtime-contracts/uninstall/`



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

### `1.0`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.0.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_f5348357/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_f5348357.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_f5348357.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_f5348357.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.1`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.1.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_011be87b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_011be87b.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_011be87b.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_011be87b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.10`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.10.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_d6657060/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_d6657060.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_d6657060.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_d6657060.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.11`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.11.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_c0511ace/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_c0511ace.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_c0511ace.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_c0511ace.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.12`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.12.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_f6ae25d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_f6ae25d8.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_f6ae25d8.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_f6ae25d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.2`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.2.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_75d05476/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_75d05476.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_75d05476.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_75d05476.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.3`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.3.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_9103d563/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_9103d563.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_9103d563.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_9103d563.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.4`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.4.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_5b32be4a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_5b32be4a.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_5b32be4a.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_5b32be4a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.5`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.5.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_e78066ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_e78066ee.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_e78066ee.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_e78066ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.6`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.6.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_3539003c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_3539003c.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_3539003c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_3539003c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.7`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.7.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_c9f52a7c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_c9f52a7c.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_c9f52a7c.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_c9f52a7c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.8`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.8.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_143501c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_143501c5.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_143501c5.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_143501c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `1.9`
- **Source:** `.phases/phases/phase-01-runtime-contracts/prompts/1.9.md`
- **Structural package:** `src/runtime/runtime-contracts/subtask_packages/verification/requirement_61913901/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_61913901.hpp`, `src/runtime/runtime-contracts/subtask_targets/requirements/requirement_61913901.cpp`
- **Structural test target:** `tests/structural-closure/runtime/runtime-contracts/requirements/test_requirement_61913901.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`


## MASS IMPLEMENTATION XXII — Structural Skeleton Oversaturation
- Expanded canonical structural address space in `src/adapters`, `src/core`, `src/governance`, `src/interfaces`, `src/portability`, and `src/system`.
- Added explicit contracts/model/verification facets with local `AGENTS.md` boundaries and compilable skeleton tags.
- Evidence: `docs/reports/structural_saturation_xxii.md`, `docs/reports/structural_saturation_xxii.json`, `tools/materialize_structural_saturation.py`.
- Verification observed: `STRUCTURAL_HEADERS_STRICT_COMPILE_PASS`; phase-contract and subtask-ledger validators pass.
- **Maturity rule:** this is structural scaffolding only. It does not implement prompt behavior and does not raise this phase's depth. Future behavioral passes must replace/saturate these placement points with real integrated code and per-subtask evidence.
- Native Authority: compliant; no native Linux mechanism was reimplemented.

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

