# Phase 46 — Natural Language Operator Interface — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-46-natural-language-operator-interface/`
- Primary prompt location: `.phases/phases/phase-46-natural-language-operator-interface/prompts/`
- Prompt/specification Markdown files currently present: **487**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 487 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_46` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 46 — Natural Language Operator Interface (`ask`)
- Phase 46 Index
- Normative architecture
- Full executable prompts
- Phase 46 Agent Handoff
- Phase 46.458 — final native build
- Objective
- Repository-first execution
- `ask` interaction contract
- Fundamental security invariants
- Effect-based suspicious-use analysis
- Semantic and Gordon boundaries

## Structural skeleton / canonical destination
- Canonical skeleton: `src/operator/natural-language-operator-interface/`
- Structural files: `src/operator/natural-language-operator-interface/component.hpp`, `src/operator/natural-language-operator-interface/component.cpp`, `src/operator/natural-language-operator-interface/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** PARTIAL
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- `src/operator/interface/README.md`
- `src/operator/interface/contract.hpp`
- `src/operator/natural_language/README.md`
- `src/operator/natural_language/contract.hpp`

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

- Structural skeleton materialized at `src/operator/natural-language-operator-interface/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/operator/natural-language-operator-interface/model/`
- `src/operator/natural-language-operator-interface/contracts/`
- `src/operator/natural-language-operator-interface/integration/`
- `src/operator/natural-language-operator-interface/verification/`
- `src/operator/natural-language-operator-interface/lifecycle/`
- `src/operator/natural-language-operator-interface/state/`
- `src/operator/natural-language-operator-interface/execution/`
- `src/operator/natural-language-operator-interface/transactions/`
- `src/operator/natural-language-operator-interface/events/`
- `src/operator/natural-language-operator-interface/scheduling/`
- `src/operator/natural-language-operator-interface/recovery/`
- `src/operator/natural-language-operator-interface/principals/`
- `src/operator/natural-language-operator-interface/groups/`
- `src/operator/natural-language-operator-interface/roles/`
- `src/operator/natural-language-operator-interface/resolution/`
- `src/operator/natural-language-operator-interface/authorization/`
- `src/operator/natural-language-operator-interface/credentials/`
- `src/operator/natural-language-operator-interface/policy/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

### 2026-09-23 — Working LLM integration (BitNet Falcon3-10B)
- Rebuntu now carries the supplied local Falcon3-10B BitNet deployment at `deploy/bitnet-falcon10b/`, configured as the working semantic LLM on loopback `127.0.0.1:8082`.
- `src/semantics/working_llm/endpoint.hpp` supplies the typed non-authoritative boundary used by operator/NL integration; `config/llm/working-llm.conf` declares the active model identity and endpoint.
- `scripts/rebuntu-working-llm verify` checks the live OpenAI-compatible endpoint and fails if the response does not identify `Falcon3-10B-Instruct-1.58bit`.
- Test evidence: strict C++20 compile/run of `tests/rebuntu/test_working_llm_bitnet.cpp` produced `WORKING_LLM_BITNET_FALCON10B_PASS`.
- Security/authority invariant: LLM output remains advisory and must pass Rebuntu typed semantics, validation, policy/security, planning and control before any native mutation.
- Depth remains 2/5: this is concrete LLM plumbing, not evidence that all 487 Phase 46 specifications are implemented.

### 2026-09-23 — MASS IMPLEMENTATION XVI / working-LLM saturation
- Deepened the existing BitNet working-LLM boundary rather than adding another model subsystem.
- `src/semantics/working_llm/advisory.hpp` adds explicit non-authoritative advisory semantics, provenance requirements, bounded request/response budgets and a bounded circuit breaker.
- `src/semantics/working_llm/session.hpp` adds deterministic request identity, guarded system instructions, prompt/response budget enforcement, model provenance and fail-closed behavior while the circuit is open.
- `src/operator/natural_language/working_llm_bridge.hpp` carries validated model output into the existing operator natural-language contract with stable request identity and evidence/provenance; it does not convert model text into native execution.
- Native Authority compliance: the LLM still cannot observe authoritative Linux state by assertion, cannot report mutations as verified, and cannot bypass typed semantics/policy/planning/control/native providers.
- Strict C++20 test evidence (`-std=c++20 -Wall -Wextra -Wpedantic -Werror`): `WORKING_LLM_GUARDED_SESSION_PASS`, `WORKING_LLM_BUDGET_FAIL_CLOSED_PASS`, `WORKING_LLM_CIRCUIT_BREAKER_PASS`, `WORKING_LLM_NATIVE_EXECUTION_REJECTED_PASS`, `WORKING_LLM_OPERATOR_PROVENANCE_BRIDGE_PASS`; the previous `WORKING_LLM_BITNET_FALCON10B_PASS` regression also passed.
- Remaining work: live transport integration is intentionally still external to these semantic contracts; production HTTP lifecycle, streaming/cancellation and full Phase requirements require further integration/evidence. No maturity increase is claimed from contracts/tests alone.

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `46.000-foundation-and-repository-archaeology`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.000-foundation-and-repository-archaeology.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/foundation_and_repository_archaeology_afcb11be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/foundation_and_repository_archaeology_afcb11be.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/foundation_and_repository_archaeology_afcb11be.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_foundation_and_repository_archaeology_afcb11be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.001-existing-natural-language-interface-inventory`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.001-existing-natural-language-interface-inventory.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/existing_natural_language_interface_inventory_005eb822/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/existing_natural_language_interface_inventory_005eb822.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/existing_natural_language_interface_inventory_005eb822.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_existing_natural_language_interface_inventory_005eb822.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.002-existing-semantic-command-path-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.002-existing-semantic-command-path-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/existing_semantic_command_path_audit_3a50c845/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/existing_semantic_command_path_audit_3a50c845.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/existing_semantic_command_path_audit_3a50c845.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_existing_semantic_command_path_audit_3a50c845.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.003-existing-shell-wrapper-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.003-existing-shell-wrapper-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/existing_shell_wrapper_audit_0ddafdea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/existing_shell_wrapper_audit_0ddafdea.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/existing_shell_wrapper_audit_0ddafdea.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_existing_shell_wrapper_audit_0ddafdea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.004-canonical-ask-architecture`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.004-canonical-ask-architecture.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/canonical_ask_architecture_7e1b6b03/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/canonical_ask_architecture_7e1b6b03.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/canonical_ask_architecture_7e1b6b03.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_canonical_ask_architecture_7e1b6b03.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.005-c-first-ask-runtime`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.005-c-first-ask-runtime.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/c_first_ask_runtime_49848e12/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/c_first_ask_runtime_49848e12.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/c_first_ask_runtime_49848e12.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_c_first_ask_runtime_49848e12.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.006-ask-executable-entrypoint`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.006-ask-executable-entrypoint.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_executable_entrypoint_5ecfae91/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/ask_executable_entrypoint_5ecfae91.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/ask_executable_entrypoint_5ecfae91.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_ask_executable_entrypoint_5ecfae91.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.007-ask-argv-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.007-ask-argv-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_argv_mode_f978bc09/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_argv_mode_f978bc09.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_argv_mode_f978bc09.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_argv_mode_f978bc09.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.008-bare-ask-one-shot-prompt-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.008-bare-ask-one-shot-prompt-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bare_ask_one_shot_prompt_mode_6e21282f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bare_ask_one_shot_prompt_mode_6e21282f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bare_ask_one_shot_prompt_mode_6e21282f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bare_ask_one_shot_prompt_mode_6e21282f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.009-ask-prompt-ux`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.009-ask-prompt-ux.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_prompt_ux_883d1098/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_prompt_ux_883d1098.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_prompt_ux_883d1098.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_prompt_ux_883d1098.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.010-shell-return-semantics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.010-shell-return-semantics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/shell_return_semantics_32c5e106/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/shell_return_semantics_32c5e106.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/shell_return_semantics_32c5e106.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_shell_return_semantics_32c5e106.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.011-fish-integration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.011-fish-integration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/fish_integration_ec68077d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/fish_integration_ec68077d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/fish_integration_ec68077d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_fish_integration_ec68077d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.012-bash-compatibility`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.012-bash-compatibility.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bash_compatibility_390092f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bash_compatibility_390092f2.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bash_compatibility_390092f2.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bash_compatibility_390092f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.013-tty-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.013-tty-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/tty_detection_66976390/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/tty_detection_66976390.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/tty_detection_66976390.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_tty_detection_66976390.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.014-noninteractive-invocation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.014-noninteractive-invocation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/noninteractive_invocation_c22e9505/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/noninteractive_invocation_c22e9505.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/noninteractive_invocation_c22e9505.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_noninteractive_invocation_c22e9505.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.015-stdin-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.015-stdin-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/stdin_handling_d84d7c95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/stdin_handling_d84d7c95.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/stdin_handling_d84d7c95.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_stdin_handling_d84d7c95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.016-stdout-stderr-contract`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.016-stdout-stderr-contract.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/stdout_stderr_contract_cf975a97/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/stdout_stderr_contract_cf975a97.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/stdout_stderr_contract_cf975a97.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_stdout_stderr_contract_cf975a97.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.017-exit-status-contract`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.017-exit-status-contract.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/exit_status_contract_5e86956a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/exit_status_contract_5e86956a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/exit_status_contract_5e86956a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_exit_status_contract_5e86956a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.018-structured-output-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.018-structured-output-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/structured_output_mode_4176f84f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/structured_output_mode_4176f84f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/structured_output_mode_4176f84f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_structured_output_mode_4176f84f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.019-machine-readable-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.019-machine-readable-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/machine_readable_mode_833c5914/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/machine_readable_mode_833c5914.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/machine_readable_mode_833c5914.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_machine_readable_mode_833c5914.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.020-operator-identity-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.020-operator-identity-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/operator_identity_context_cf063f3b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/operator_identity_context_cf063f3b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/operator_identity_context_cf063f3b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_operator_identity_context_cf063f3b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.021-session-identity-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.021-session-identity-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/session_identity_context_abeb485a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/session_identity_context_abeb485a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/session_identity_context_abeb485a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_session_identity_context_abeb485a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.022-cwd-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.022-cwd-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/cwd_context_9c82fd81/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/cwd_context_9c82fd81.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/cwd_context_9c82fd81.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_cwd_context_9c82fd81.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.023-project-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.023-project-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/project_context_eec1dadd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/project_context_eec1dadd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/project_context_eec1dadd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_project_context_eec1dadd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.024-repository-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.024-repository-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/repository_context_3a484daa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/repository_context_3a484daa.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/repository_context_3a484daa.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_repository_context_3a484daa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.025-active-workflow-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.025-active-workflow-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/active_workflow_context_f8dc8986/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/active_workflow_context_f8dc8986.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/active_workflow_context_f8dc8986.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_active_workflow_context_f8dc8986.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.026-recent-operator-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.026-recent-operator-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recent_operator_context_74636881/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/recent_operator_context_74636881.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/recent_operator_context_74636881.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_recent_operator_context_74636881.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.027-explicit-referent-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.027-explicit-referent-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/explicit_referent_context_507ab0b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/explicit_referent_context_507ab0b5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/explicit_referent_context_507ab0b5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_explicit_referent_context_507ab0b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.028-temporal-context-from-phase-39`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.028-temporal-context-from-phase-39.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/temporal_context_from_phase_39_ef9e7dd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/temporal_context_from_phase_39_ef9e7dd4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/temporal_context_from_phase_39_ef9e7dd4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_temporal_context_from_phase_39_ef9e7dd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.029-structural-context-from-phase-42`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.029-structural-context-from-phase-42.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/structural_context_from_phase_42_8fce551e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/structural_context_from_phase_42_8fce551e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/structural_context_from_phase_42_8fce551e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_structural_context_from_phase_42_8fce551e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.030-intelligence-context-from-phase-43`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.030-intelligence-context-from-phase-43.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intelligence_context_from_phase_43_d21d9db6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/intelligence_context_from_phase_43_d21d9db6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/intelligence_context_from_phase_43_d21d9db6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_intelligence_context_from_phase_43_d21d9db6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.031-adaptive-context-from-phase-44`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.031-adaptive-context-from-phase-44.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adaptive_context_from_phase_44_359335d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/adaptive_context_from_phase_44_359335d1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/adaptive_context_from_phase_44_359335d1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_adaptive_context_from_phase_44_359335d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.032-capability-context-from-phase-45`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.032-capability-context-from-phase-45.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/capability_context_from_phase_45_8e32ffa5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/capability_context_from_phase_45_8e32ffa5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/capability_context_from_phase_45_8e32ffa5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_capability_context_from_phase_45_8e32ffa5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.033-authoritative-state-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.033-authoritative-state-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/authoritative_state_context_d933d869/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/authoritative_state_context_d933d869.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/authoritative_state_context_d933d869.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/lifecycle/test_authoritative_state_context_d933d869.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.034-context-schema`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.034-context-schema.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_schema_db822b93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/context_schema_db822b93.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/context_schema_db822b93.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_context_schema_db822b93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.035-context-provenance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.035-context-provenance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_provenance_a31c456e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_provenance_a31c456e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_provenance_a31c456e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_provenance_a31c456e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.036-context-freshness`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.036-context-freshness.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_freshness_9510e14c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_freshness_9510e14c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_freshness_9510e14c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_freshness_9510e14c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.037-context-minimization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.037-context-minimization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_minimization_8fea5970/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_minimization_8fea5970.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_minimization_8fea5970.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_minimization_8fea5970.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.038-context-redaction`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.038-context-redaction.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_redaction_220c8b1b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_redaction_220c8b1b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_redaction_220c8b1b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_redaction_220c8b1b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.039-context-size-bounds`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.039-context-size-bounds.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_size_bounds_b78bd48e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_size_bounds_b78bd48e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_size_bounds_b78bd48e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_size_bounds_b78bd48e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.040-context-priority`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.040-context-priority.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_priority_accd3629/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_priority_accd3629.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_priority_accd3629.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_priority_accd3629.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.041-context-conflict-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.041-context-conflict-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_conflict_handling_e7d1a59a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_conflict_handling_e7d1a59a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_conflict_handling_e7d1a59a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_conflict_handling_e7d1a59a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.042-context-invalidation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.042-context-invalidation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_invalidation_d0cbf499/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_invalidation_d0cbf499.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_invalidation_d0cbf499.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_invalidation_d0cbf499.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.043-context-expiry`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.043-context-expiry.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_expiry_d938a3f7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_expiry_d938a3f7.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_expiry_d938a3f7.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_expiry_d938a3f7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.044-context-cache`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.044-context-cache.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_cache_30693e57/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/persistence/context_cache_30693e57.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/persistence/context_cache_30693e57.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/persistence/test_context_cache_30693e57.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.045-context-isolation-between-sessions`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.045-context-isolation-between-sessions.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_isolation_between_sessions_b6e95fce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_isolation_between_sessions_b6e95fce.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_isolation_between_sessions_b6e95fce.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_isolation_between_sessions_b6e95fce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.046-context-inheritance-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.046-context-inheritance-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_inheritance_boundary_31956d8c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_inheritance_boundary_31956d8c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_inheritance_boundary_31956d8c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_inheritance_boundary_31956d8c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.047-context-poisoning-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.047-context-poisoning-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_poisoning_resistance_8f888e8b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_poisoning_resistance_8f888e8b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_poisoning_resistance_8f888e8b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_poisoning_resistance_8f888e8b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.048-intent-candidate-schema`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.048-intent-candidate-schema.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intent_candidate_schema_c1d57297/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/intent_candidate_schema_c1d57297.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/intent_candidate_schema_c1d57297.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_intent_candidate_schema_c1d57297.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.049-intent-classes`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.049-intent-classes.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intent_classes_2ad49004/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_classes_2ad49004.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_classes_2ad49004.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_intent_classes_2ad49004.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.050-query-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.050-query-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/query_intent_ab04ea81/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/query_intent_ab04ea81.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/query_intent_ab04ea81.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_query_intent_ab04ea81.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.051-task-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.051-task-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/task_intent_3913ced1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/task_intent_3913ced1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/task_intent_3913ced1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_task_intent_3913ced1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.052-recommendation-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.052-recommendation-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recommendation_intent_9a14de8c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/recommendation_intent_9a14de8c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/recommendation_intent_9a14de8c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_recommendation_intent_9a14de8c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.053-plan-request-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.053-plan-request-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/plan_request_intent_444f7660/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/plan_request_intent_444f7660.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/plan_request_intent_444f7660.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_plan_request_intent_444f7660.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.054-action-request-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.054-action-request-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/action_request_intent_e8317d1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/action_request_intent_e8317d1f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/action_request_intent_e8317d1f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_action_request_intent_e8317d1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.055-clarification-response-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.055-clarification-response-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/clarification_response_intent_87a6f7cf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/clarification_response_intent_87a6f7cf.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/clarification_response_intent_87a6f7cf.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_clarification_response_intent_87a6f7cf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.056-meta-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.056-meta-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/meta_intent_f0f0b196/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/meta_intent_f0f0b196.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/meta_intent_f0f0b196.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_meta_intent_f0f0b196.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.057-unsupported-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.057-unsupported-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unsupported_intent_6abbcaed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/unsupported_intent_6abbcaed.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/unsupported_intent_6abbcaed.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_unsupported_intent_6abbcaed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.058-intent-provenance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.058-intent-provenance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intent_provenance_ab12627e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_provenance_ab12627e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_provenance_ab12627e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_intent_provenance_ab12627e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.059-intent-confidence-semantics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.059-intent-confidence-semantics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intent_confidence_semantics_6a813011/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_confidence_semantics_6a813011.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_confidence_semantics_6a813011.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_intent_confidence_semantics_6a813011.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.060-intent-ambiguity`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.060-intent-ambiguity.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intent_ambiguity_f1b18327/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_ambiguity_f1b18327.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_ambiguity_f1b18327.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_intent_ambiguity_f1b18327.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.061-intent-alternatives`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.061-intent-alternatives.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intent_alternatives_c582623f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_alternatives_c582623f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_alternatives_c582623f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_intent_alternatives_c582623f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.062-intent-decomposition`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.062-intent-decomposition.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/intent_decomposition_4542af1c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_decomposition_4542af1c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/intent_decomposition_4542af1c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_intent_decomposition_4542af1c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.063-multi-action-request-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.063-multi-action-request-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/multi_action_request_handling_7c93d6e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/multi_action_request_handling_7c93d6e0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/multi_action_request_handling_7c93d6e0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_multi_action_request_handling_7c93d6e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.064-compound-intent-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.064-compound-intent-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/compound_intent_handling_524a85c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/compound_intent_handling_524a85c9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/compound_intent_handling_524a85c9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_compound_intent_handling_524a85c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.065-referent-resolution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.065-referent-resolution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/referent_resolution_bac77536/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/referent_resolution_bac77536.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/referent_resolution_bac77536.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_referent_resolution_bac77536.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.066-pronoun-resolution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.066-pronoun-resolution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/pronoun_resolution_c3cf2bb5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/pronoun_resolution_c3cf2bb5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/pronoun_resolution_c3cf2bb5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_pronoun_resolution_c3cf2bb5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.067-ellipsis-resolution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.067-ellipsis-resolution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ellipsis_resolution_5de22f8c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ellipsis_resolution_5de22f8c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ellipsis_resolution_5de22f8c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ellipsis_resolution_5de22f8c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.068-deictic-reference-resolution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.068-deictic-reference-resolution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/deictic_reference_resolution_5c82e5c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/deictic_reference_resolution_5c82e5c4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/deictic_reference_resolution_5c82e5c4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_deictic_reference_resolution_5c82e5c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.069-ordinal-reference-resolution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.069-ordinal-reference-resolution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ordinal_reference_resolution_cf0ca2a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ordinal_reference_resolution_cf0ca2a4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ordinal_reference_resolution_cf0ca2a4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ordinal_reference_resolution_cf0ca2a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.070-recent-object-resolution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.070-recent-object-resolution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recent_object_resolution_7a95958c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/recent_object_resolution_7a95958c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/recent_object_resolution_7a95958c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_recent_object_resolution_7a95958c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.071-ambiguous-referent-rejection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.071-ambiguous-referent-rejection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ambiguous_referent_rejection_a9323e02/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ambiguous_referent_rejection_a9323e02.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ambiguous_referent_rejection_a9323e02.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ambiguous_referent_rejection_a9323e02.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.072-consequential-ambiguity-threshold`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.072-consequential-ambiguity-threshold.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/consequential_ambiguity_threshold_abbd2379/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/consequential_ambiguity_threshold_abbd2379.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/consequential_ambiguity_threshold_abbd2379.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_consequential_ambiguity_threshold_abbd2379.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.073-bitnet-provider-adapter`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.073-bitnet-provider-adapter.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_provider_adapter_ebcc7344/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/bitnet_provider_adapter_ebcc7344.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/bitnet_provider_adapter_ebcc7344.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_bitnet_provider_adapter_ebcc7344.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.074-bitnet-capability-negotiation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.074-bitnet-capability-negotiation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_capability_negotiation_33e25e85/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_capability_negotiation_33e25e85.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_capability_negotiation_33e25e85.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_capability_negotiation_33e25e85.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.075-bitnet-prompt-construction`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.075-bitnet-prompt-construction.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_prompt_construction_d1072e3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_prompt_construction_d1072e3a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_prompt_construction_d1072e3a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_prompt_construction_d1072e3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.076-bitnet-context-projection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.076-bitnet-context-projection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_context_projection_6526e73a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_context_projection_6526e73a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_context_projection_6526e73a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_context_projection_6526e73a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.077-bitnet-structured-output-schema`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.077-bitnet-structured-output-schema.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_structured_output_schema_1c10b3f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/bitnet_structured_output_schema_1c10b3f4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/bitnet_structured_output_schema_1c10b3f4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_bitnet_structured_output_schema_1c10b3f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.078-bitnet-parser`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.078-bitnet-parser.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_parser_60ea15ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_parser_60ea15ab.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_parser_60ea15ab.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_parser_60ea15ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.079-bitnet-schema-validation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.079-bitnet-schema-validation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_schema_validation_39fe82a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/bitnet_schema_validation_39fe82a9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/bitnet_schema_validation_39fe82a9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_bitnet_schema_validation_39fe82a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.080-bitnet-malformed-output-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.080-bitnet-malformed-output-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_malformed_output_handling_b0d33d1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_malformed_output_handling_b0d33d1f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_malformed_output_handling_b0d33d1f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_malformed_output_handling_b0d33d1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.081-bitnet-hallucination-containment`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.081-bitnet-hallucination-containment.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_hallucination_containment_023a9a26/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_hallucination_containment_023a9a26.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_hallucination_containment_023a9a26.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_hallucination_containment_023a9a26.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.082-bitnet-unavailable-fallback`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.082-bitnet-unavailable-fallback.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_unavailable_fallback_8be82f94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_unavailable_fallback_8be82f94.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_unavailable_fallback_8be82f94.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_unavailable_fallback_8be82f94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.083-bitnet-timeout-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.083-bitnet-timeout-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_timeout_handling_300422bc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_timeout_handling_300422bc.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_timeout_handling_300422bc.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_timeout_handling_300422bc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.084-bitnet-resource-budget`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.084-bitnet-resource-budget.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_resource_budget_03268e0c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_resource_budget_03268e0c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_resource_budget_03268e0c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_resource_budget_03268e0c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.085-bitnet-local-only-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.085-bitnet-local-only-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_local_only_boundary_89d3834e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_local_only_boundary_89d3834e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_local_only_boundary_89d3834e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_local_only_boundary_89d3834e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.086-semantic-provider-abstraction`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.086-semantic-provider-abstraction.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_provider_abstraction_00113681/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_abstraction_00113681.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_abstraction_00113681.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_semantic_provider_abstraction_00113681.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.087-alternate-semantic-provider-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.087-alternate-semantic-provider-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/alternate_semantic_provider_boundary_8c6b980c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/alternate_semantic_provider_boundary_8c6b980c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/alternate_semantic_provider_boundary_8c6b980c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_alternate_semantic_provider_boundary_8c6b980c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.088-semantic-provider-hot-swap`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.088-semantic-provider-hot-swap.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_provider_hot_swap_0885629c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_hot_swap_0885629c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_hot_swap_0885629c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_semantic_provider_hot_swap_0885629c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.089-semantic-provider-no-authority-invariant`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.089-semantic-provider-no-authority-invariant.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_provider_no_authority_invariant_b6e1c109/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_no_authority_invariant_b6e1c109.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_no_authority_invariant_b6e1c109.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_semantic_provider_no_authority_invariant_b6e1c109.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.090-natural-language-may-broaden-understanding-not-authority`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.090-natural-language-may-broaden-understanding-not-authority.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/natural_language_may_broaden_understanding_not_authority_69766f25/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/natural_language_may_broaden_understanding_not_authority_69766f25.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/natural_language_may_broaden_understanding_not_authority_69766f25.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_natural_language_may_broaden_understanding_not_authority_69766f25.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.091-capability-resolver`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.091-capability-resolver.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/capability_resolver_ee6b8343/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/capability_resolver_ee6b8343.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/capability_resolver_ee6b8343.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_capability_resolver_ee6b8343.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.092-typed-capability-mapping`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.092-typed-capability-mapping.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/typed_capability_mapping_3f88068c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/typed_capability_mapping_3f88068c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/typed_capability_mapping_3f88068c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_typed_capability_mapping_3f88068c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.093-unknown-capability-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.093-unknown-capability-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unknown_capability_handling_93c9e229/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/unknown_capability_handling_93c9e229.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/unknown_capability_handling_93c9e229.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_unknown_capability_handling_93c9e229.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.094-capability-applicability`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.094-capability-applicability.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/capability_applicability_040f04aa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/capability_applicability_040f04aa.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/capability_applicability_040f04aa.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_capability_applicability_040f04aa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.095-authority-resolver`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.095-authority-resolver.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/authority_resolver_675f9694/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/authority_resolver_675f9694.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/authority_resolver_675f9694.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_authority_resolver_675f9694.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.096-authorization-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.096-authorization-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/authorization_context_f35f451e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/authorization_context_f35f451e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/authorization_context_f35f451e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_authorization_context_f35f451e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.097-policy-resolver`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.097-policy-resolver.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_resolver_36a092d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_resolver_36a092d4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_resolver_36a092d4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_resolver_36a092d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.098-policy-precedence`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.098-policy-precedence.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_precedence_7c896660/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_precedence_7c896660.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_precedence_7c896660.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_precedence_7c896660.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.099-policy-conflict-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.099-policy-conflict-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_conflict_handling_fb6d7aed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_conflict_handling_fb6d7aed.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_conflict_handling_fb6d7aed.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_conflict_handling_fb6d7aed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.100-policy-deny-semantics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.100-policy-deny-semantics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_deny_semantics_79e570cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_deny_semantics_79e570cb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_deny_semantics_79e570cb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_deny_semantics_79e570cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.101-policy-allow-semantics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.101-policy-allow-semantics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_allow_semantics_29d67b9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_allow_semantics_29d67b9d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_allow_semantics_29d67b9d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_allow_semantics_29d67b9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.102-policy-require-confirmation-semantics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.102-policy-require-confirmation-semantics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_require_confirmation_semantics_adb7c577/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_require_confirmation_semantics_adb7c577.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_require_confirmation_semantics_adb7c577.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_require_confirmation_semantics_adb7c577.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.103-policy-require-justification-semantics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.103-policy-require-justification-semantics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_require_justification_semantics_96905ab2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_require_justification_semantics_96905ab2.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_require_justification_semantics_96905ab2.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_require_justification_semantics_96905ab2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.104-policy-require-advisory-review-semantics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.104-policy-require-advisory-review-semantics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_require_advisory_review_semantics_ee753c0e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_require_advisory_review_semantics_ee753c0e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_require_advisory_review_semantics_ee753c0e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_require_advisory_review_semantics_ee753c0e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.105-contextual-legitimacy-model`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.105-contextual-legitimacy-model.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/contextual_legitimacy_model_b86f842a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/contextual_legitimacy_model_b86f842a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/contextual_legitimacy_model_b86f842a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_contextual_legitimacy_model_b86f842a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.106-contextual-legitimacy-evidence`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.106-contextual-legitimacy-evidence.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/contextual_legitimacy_evidence_04fd1486/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/contextual_legitimacy_evidence_04fd1486.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/contextual_legitimacy_evidence_04fd1486.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_contextual_legitimacy_evidence_04fd1486.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.107-expected-use-baseline`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.107-expected-use-baseline.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/expected_use_baseline_249443d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/expected_use_baseline_249443d5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/expected_use_baseline_249443d5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_expected_use_baseline_249443d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.108-unexpected-use-detector`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.108-unexpected-use-detector.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_use_detector_011f5adf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/unexpected_use_detector_011f5adf.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/unexpected_use_detector_011f5adf.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_unexpected_use_detector_011f5adf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.109-context-anomaly-scoring-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.109-context-anomaly-scoring-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_anomaly_scoring_boundary_478f6124/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_anomaly_scoring_boundary_478f6124.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_anomaly_scoring_boundary_478f6124.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_anomaly_scoring_boundary_478f6124.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.110-context-anomaly-explanation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.110-context-anomaly-explanation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_anomaly_explanation_dc23d282/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/context_anomaly_explanation_dc23d282.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/context_anomaly_explanation_dc23d282.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_context_anomaly_explanation_dc23d282.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.111-current-state-consistency-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.111-current-state-consistency-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/current_state_consistency_check_1b16a997/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/current_state_consistency_check_1b16a997.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/current_state_consistency_check_1b16a997.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/lifecycle/test_current_state_consistency_check_1b16a997.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.112-active-task-consistency-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.112-active-task-consistency-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/active_task_consistency_check_b2df8b1f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/active_task_consistency_check_b2df8b1f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/active_task_consistency_check_b2df8b1f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_active_task_consistency_check_b2df8b1f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.113-recent-action-consistency-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.113-recent-action-consistency-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recent_action_consistency_check_9b3bd06a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/recent_action_consistency_check_9b3bd06a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/recent_action_consistency_check_9b3bd06a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_recent_action_consistency_check_9b3bd06a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.114-known-service-consistency-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.114-known-service-consistency-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/known_service_consistency_check_b598dd98/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/known_service_consistency_check_b598dd98.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/known_service_consistency_check_b598dd98.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_known_service_consistency_check_b598dd98.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.115-known-data-flow-consistency-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.115-known-data-flow-consistency-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/known_data_flow_consistency_check_b8e2a73e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/known_data_flow_consistency_check_b8e2a73e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/known_data_flow_consistency_check_b8e2a73e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_known_data_flow_consistency_check_b8e2a73e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.116-known-endpoint-consistency-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.116-known-endpoint-consistency-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/known_endpoint_consistency_check_52e8c53b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/known_endpoint_consistency_check_52e8c53b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/known_endpoint_consistency_check_52e8c53b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_known_endpoint_consistency_check_52e8c53b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.117-new-external-endpoint-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.117-new-external-endpoint-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/new_external_endpoint_detection_575a96d6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/new_external_endpoint_detection_575a96d6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/new_external_endpoint_detection_575a96d6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_new_external_endpoint_detection_575a96d6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.118-new-listener-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.118-new-listener-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/new_listener_detection_cc69ed25/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/new_listener_detection_cc69ed25.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/new_listener_detection_cc69ed25.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_new_listener_detection_cc69ed25.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.119-new-outbound-flow-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.119-new-outbound-flow-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/new_outbound_flow_detection_53d2f69c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/new_outbound_flow_detection_53d2f69c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/new_outbound_flow_detection_53d2f69c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_new_outbound_flow_detection_53d2f69c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.120-new-persistence-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.120-new-persistence-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/new_persistence_detection_75c8742f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/persistence/new_persistence_detection_75c8742f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/persistence/new_persistence_detection_75c8742f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/persistence/test_new_persistence_detection_75c8742f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.121-unexpected-privilege-use-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.121-unexpected-privilege-use-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_privilege_use_detection_f0944b33/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/unexpected_privilege_use_detection_f0944b33.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/unexpected_privilege_use_detection_f0944b33.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_unexpected_privilege_use_detection_f0944b33.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.122-unexpected-secret-access-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.122-unexpected-secret-access-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_secret_access_detection_e951fd61/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/unexpected_secret_access_detection_e951fd61.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/unexpected_secret_access_detection_e951fd61.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_unexpected_secret_access_detection_e951fd61.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.123-unexpected-bulk-data-access-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.123-unexpected-bulk-data-access-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_bulk_data_access_detection_4c238166/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/unexpected_bulk_data_access_detection_4c238166.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/unexpected_bulk_data_access_detection_4c238166.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_unexpected_bulk_data_access_detection_4c238166.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.124-unexpected-configuration-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.124-unexpected-configuration-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_configuration_mutation_detection_50280cf4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_configuration_mutation_detection_50280cf4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_configuration_mutation_detection_50280cf4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_configuration_mutation_detection_50280cf4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.125-unexpected-security-control-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.125-unexpected-security-control-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_security_control_mutation_detection_87b5c477/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/unexpected_security_control_mutation_detection_87b5c477.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/unexpected_security_control_mutation_detection_87b5c477.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_unexpected_security_control_mutation_detection_87b5c477.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.126-unexpected-identity-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.126-unexpected-identity-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_identity_mutation_detection_d67f6ef6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_identity_mutation_detection_d67f6ef6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_identity_mutation_detection_d67f6ef6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_identity_mutation_detection_d67f6ef6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.127-unexpected-storage-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.127-unexpected-storage-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_storage_mutation_detection_fef382bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_storage_mutation_detection_fef382bb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_storage_mutation_detection_fef382bb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_storage_mutation_detection_fef382bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.128-unexpected-network-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.128-unexpected-network-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_network_mutation_detection_94b93a3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_network_mutation_detection_94b93a3f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_network_mutation_detection_94b93a3f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_network_mutation_detection_94b93a3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.129-unexpected-service-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.129-unexpected-service-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_service_mutation_detection_739c1f02/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_service_mutation_detection_739c1f02.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_service_mutation_detection_739c1f02.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_service_mutation_detection_739c1f02.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.130-unexpected-package-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.130-unexpected-package-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_package_mutation_detection_81ed9f04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_package_mutation_detection_81ed9f04.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_package_mutation_detection_81ed9f04.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_package_mutation_detection_81ed9f04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.131-unexpected-gpu-resource-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.131-unexpected-gpu-resource-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_gpu_resource_mutation_detection_4bb6191f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_gpu_resource_mutation_detection_4bb6191f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_gpu_resource_mutation_detection_4bb6191f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_gpu_resource_mutation_detection_4bb6191f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.132-unexpected-process-mutation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.132-unexpected-process-mutation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_process_mutation_detection_d34f06ef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_process_mutation_detection_d34f06ef.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/unexpected_process_mutation_detection_d34f06ef.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_unexpected_process_mutation_detection_d34f06ef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.133-unexpected-workflow-creation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.133-unexpected-workflow-creation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_workflow_creation_detection_48b346fe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/unexpected_workflow_creation_detection_48b346fe.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/unexpected_workflow_creation_detection_48b346fe.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_unexpected_workflow_creation_detection_48b346fe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.134-unexpected-scheduled-persistence-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.134-unexpected-scheduled-persistence-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_scheduled_persistence_detection_ebdb74b8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/unexpected_scheduled_persistence_detection_ebdb74b8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/unexpected_scheduled_persistence_detection_ebdb74b8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_unexpected_scheduled_persistence_detection_ebdb74b8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.135-cross-capability-risk-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.135-cross-capability-risk-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/cross_capability_risk_detection_f397c375/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/cross_capability_risk_detection_f397c375.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/cross_capability_risk_detection_f397c375.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_cross_capability_risk_detection_f397c375.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.136-effect-based-suspicious-use-analysis`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.136-effect-based-suspicious-use-analysis.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/effect_based_suspicious_use_analysis_480babee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/effect_based_suspicious_use_analysis_480babee.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/effect_based_suspicious_use_analysis_480babee.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_effect_based_suspicious_use_analysis_480babee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.137-suspicious-intent-taxonomy`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.137-suspicious-intent-taxonomy.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/suspicious_intent_taxonomy_f1f2b50e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/suspicious_intent_taxonomy_f1f2b50e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/suspicious_intent_taxonomy_f1f2b50e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_suspicious_intent_taxonomy_f1f2b50e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.138-resource-exhaustion-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.138-resource-exhaustion-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/resource_exhaustion_intent_899cd03b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/resource_exhaustion_intent_899cd03b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/resource_exhaustion_intent_899cd03b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_resource_exhaustion_intent_899cd03b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.139-unbounded-process-creation-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.139-unbounded-process-creation-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unbounded_process_creation_detection_c844f7fd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/unbounded_process_creation_detection_c844f7fd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/unbounded_process_creation_detection_c844f7fd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_unbounded_process_creation_detection_c844f7fd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.140-fork-bomb-semantic-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.140-fork-bomb-semantic-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/fork_bomb_semantic_detection_307077b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/fork_bomb_semantic_detection_307077b7.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/fork_bomb_semantic_detection_307077b7.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_fork_bomb_semantic_detection_307077b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.141-obfuscated-resource-exhaustion-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.141-obfuscated-resource-exhaustion-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/obfuscated_resource_exhaustion_detection_d795ea4b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/obfuscated_resource_exhaustion_detection_d795ea4b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/obfuscated_resource_exhaustion_detection_d795ea4b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_obfuscated_resource_exhaustion_detection_d795ea4b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.142-destructive-storage-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.142-destructive-storage-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/destructive_storage_effect_detection_52458698/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/destructive_storage_effect_detection_52458698.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/destructive_storage_effect_detection_52458698.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_destructive_storage_effect_detection_52458698.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.143-filesystem-destruction-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.143-filesystem-destruction-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/filesystem_destruction_effect_detection_7c10e908/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/filesystem_destruction_effect_detection_7c10e908.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/filesystem_destruction_effect_detection_7c10e908.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_filesystem_destruction_effect_detection_7c10e908.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.144-boot-impairment-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.144-boot-impairment-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/boot_impairment_effect_detection_3653922e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/boot_impairment_effect_detection_3653922e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/boot_impairment_effect_detection_3653922e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_boot_impairment_effect_detection_3653922e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.145-network-isolation-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.145-network-isolation-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/network_isolation_effect_detection_3ca62630/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/network_isolation_effect_detection_3ca62630.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/network_isolation_effect_detection_3ca62630.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_network_isolation_effect_detection_3ca62630.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.146-security-safeguard-disablement-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.146-security-safeguard-disablement-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/security_safeguard_disablement_detection_1aa1c749/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/security_safeguard_disablement_detection_1aa1c749.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/security_safeguard_disablement_detection_1aa1c749.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_security_safeguard_disablement_detection_1aa1c749.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.147-firewall-weakening-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.147-firewall-weakening-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/firewall_weakening_effect_detection_6a9e7d68/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/firewall_weakening_effect_detection_6a9e7d68.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/firewall_weakening_effect_detection_6a9e7d68.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_firewall_weakening_effect_detection_6a9e7d68.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.148-credential-collection-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.148-credential-collection-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/credential_collection_effect_detection_f07c8fdb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/credential_collection_effect_detection_f07c8fdb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/credential_collection_effect_detection_f07c8fdb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_credential_collection_effect_detection_f07c8fdb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.149-secret-movement-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.149-secret-movement-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/secret_movement_effect_detection_ee62192d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/secret_movement_effect_detection_ee62192d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/secret_movement_effect_detection_ee62192d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_secret_movement_effect_detection_ee62192d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.150-sensitive-log-export-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.150-sensitive-log-export-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/sensitive_log_export_effect_detection_807ec2bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/sensitive_log_export_effect_detection_807ec2bf.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/sensitive_log_export_effect_detection_807ec2bf.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_sensitive_log_export_effect_detection_807ec2bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.151-history-export-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.151-history-export-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/history_export_effect_detection_ab3db19a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/history_export_effect_detection_ab3db19a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/history_export_effect_detection_ab3db19a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_history_export_effect_detection_ab3db19a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.152-environment-variable-export-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.152-environment-variable-export-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/environment_variable_export_effect_detection_63c03b73/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/environment_variable_export_effect_detection_63c03b73.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/environment_variable_export_effect_detection_63c03b73.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_environment_variable_export_effect_detection_63c03b73.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.153-home-directory-exposure-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.153-home-directory-exposure-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/home_directory_exposure_effect_detection_a061ac76/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/home_directory_exposure_effect_detection_a061ac76.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/home_directory_exposure_effect_detection_a061ac76.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_home_directory_exposure_effect_detection_a061ac76.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.154-service-exposure-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.154-service-exposure-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/service_exposure_effect_detection_69b4c953/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/service_exposure_effect_detection_69b4c953.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/service_exposure_effect_detection_69b4c953.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_service_exposure_effect_detection_69b4c953.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.155-remote-listener-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.155-remote-listener-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/remote_listener_effect_detection_8a7a8453/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/remote_listener_effect_detection_8a7a8453.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/remote_listener_effect_detection_8a7a8453.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_remote_listener_effect_detection_8a7a8453.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.156-reverse-connection-effect-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.156-reverse-connection-effect-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/reverse_connection_effect_detection_20bc6a46/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/reverse_connection_effect_detection_20bc6a46.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/reverse_connection_effect_detection_20bc6a46.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_reverse_connection_effect_detection_20bc6a46.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.157-external-data-destination-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.157-external-data-destination-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/external_data_destination_detection_c4914af0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/external_data_destination_detection_c4914af0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/external_data_destination_detection_c4914af0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_external_data_destination_detection_c4914af0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.158-unknown-destination-trust-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.158-unknown-destination-trust-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unknown_destination_trust_handling_43cfc844/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/unknown_destination_trust_handling_43cfc844.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/unknown_destination_trust_handling_43cfc844.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_unknown_destination_trust_handling_43cfc844.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.159-data-classification`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.159-data-classification.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/data_classification_72b79775/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/data_classification_72b79775.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/data_classification_72b79775.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_data_classification_72b79775.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.160-destination-trust-classification`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.160-destination-trust-classification.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/destination_trust_classification_4de676ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/destination_trust_classification_4de676ca.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/destination_trust_classification_4de676ca.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_destination_trust_classification_4de676ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.161-data-flow-policy-engine`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.161-data-flow-policy-engine.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/data_flow_policy_engine_743d8873/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/data_flow_policy_engine_743d8873.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/data_flow_policy_engine_743d8873.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_data_flow_policy_engine_743d8873.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.162-source-destination-policy`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.162-source-destination-policy.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/source_destination_policy_ce5d39e0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/source_destination_policy_ce5d39e0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/source_destination_policy_ce5d39e0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_source_destination_policy_ce5d39e0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.163-exfiltration-shaped-combination-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.163-exfiltration-shaped-combination-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/exfiltration_shaped_combination_detection_9c9983f1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/exfiltration_shaped_combination_detection_9c9983f1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/exfiltration_shaped_combination_detection_9c9983f1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_exfiltration_shaped_combination_detection_9c9983f1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.164-persistence-plus-outbound-flow-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.164-persistence-plus-outbound-flow-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/persistence_plus_outbound_flow_detection_d5842284/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/persistence/persistence_plus_outbound_flow_detection_d5842284.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/persistence/persistence_plus_outbound_flow_detection_d5842284.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/persistence/test_persistence_plus_outbound_flow_detection_d5842284.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.165-privilege-plus-persistence-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.165-privilege-plus-persistence-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/privilege_plus_persistence_detection_7e5ea8d0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/privilege_plus_persistence_detection_7e5ea8d0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/privilege_plus_persistence_detection_7e5ea8d0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_privilege_plus_persistence_detection_7e5ea8d0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.166-secret-access-plus-network-egress-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.166-secret-access-plus-network-egress-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/secret_access_plus_network_egress_detection_14d742bc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/secret_access_plus_network_egress_detection_14d742bc.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/secret_access_plus_network_egress_detection_14d742bc.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_secret_access_plus_network_egress_detection_14d742bc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.167-logs-plus-unknown-destination-detection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.167-logs-plus-unknown-destination-detection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/logs_plus_unknown_destination_detection_8a0291a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/logs_plus_unknown_destination_detection_8a0291a8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/logs_plus_unknown_destination_detection_8a0291a8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_logs_plus_unknown_destination_detection_8a0291a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.168-effect-graph-construction`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.168-effect-graph-construction.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/effect_graph_construction_77d1fe5b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/effect_graph_construction_77d1fe5b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/effect_graph_construction_77d1fe5b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_effect_graph_construction_77d1fe5b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.169-phase-42-risk-path-integration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.169-phase-42-risk-path-integration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/risk_path_integration_0a29e882/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/risk_path_integration_0a29e882.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/risk_path_integration_0a29e882.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_risk_path_integration_0a29e882.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.170-suspicious-request-decision-states`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.170-suspicious-request-decision-states.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/suspicious_request_decision_states_b2049cd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/suspicious_request_decision_states_b2049cd4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/suspicious_request_decision_states_b2049cd4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_suspicious_request_decision_states_b2049cd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.171-allow-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.171-allow-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/allow_decision_0282770f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/allow_decision_0282770f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/allow_decision_0282770f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_allow_decision_0282770f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.172-answer-only-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.172-answer-only-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/answer_only_decision_aa5bae93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/answer_only_decision_aa5bae93.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/answer_only_decision_aa5bae93.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_answer_only_decision_aa5bae93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.173-clarify-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.173-clarify-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/clarify_decision_654a321b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/clarify_decision_654a321b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/clarify_decision_654a321b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_clarify_decision_654a321b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.174-require-justification-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.174-require-justification-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/require_justification_decision_d3a330f3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/require_justification_decision_d3a330f3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/require_justification_decision_d3a330f3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_require_justification_decision_d3a330f3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.175-require-confirmation-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.175-require-confirmation-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/require_confirmation_decision_599db45c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/require_confirmation_decision_599db45c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/require_confirmation_decision_599db45c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_require_confirmation_decision_599db45c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.176-require-gordon-review-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.176-require-gordon-review-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/require_gordon_review_decision_662b17d0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/require_gordon_review_decision_662b17d0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/require_gordon_review_decision_662b17d0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_require_gordon_review_decision_662b17d0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.177-deny-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.177-deny-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/deny_decision_ed49f0dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/deny_decision_ed49f0dc.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/deny_decision_ed49f0dc.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_deny_decision_ed49f0dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.178-unknown-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.178-unknown-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unknown_decision_642dec82/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/unknown_decision_642dec82.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/unknown_decision_642dec82.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_unknown_decision_642dec82.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.179-decision-provenance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.179-decision-provenance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/decision_provenance_22f3d595/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/decision_provenance_22f3d595.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/decision_provenance_22f3d595.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_decision_provenance_22f3d595.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.180-decision-explanation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.180-decision-explanation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/decision_explanation_cd4d0e7d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/decision_explanation_cd4d0e7d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/decision_explanation_cd4d0e7d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_decision_explanation_cd4d0e7d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.181-justification-request-ux`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.181-justification-request-ux.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_request_ux_627ff182/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_request_ux_627ff182.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_request_ux_627ff182.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_justification_request_ux_627ff182.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.182-justification-schema`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.182-justification-schema.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_schema_81ab5f72/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/justification_schema_81ab5f72.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/justification_schema_81ab5f72.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_justification_schema_81ab5f72.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.183-justification-provenance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.183-justification-provenance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_provenance_abc5e699/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_provenance_abc5e699.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_provenance_abc5e699.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_justification_provenance_abc5e699.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.184-justification-minimization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.184-justification-minimization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_minimization_b5b35988/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_minimization_b5b35988.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_minimization_b5b35988.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_justification_minimization_b5b35988.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.185-justification-validation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.185-justification-validation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_validation_d134d522/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_validation_d134d522.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_validation_d134d522.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_justification_validation_d134d522.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.186-justification-consistency-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.186-justification-consistency-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_consistency_check_4750d224/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_consistency_check_4750d224.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_consistency_check_4750d224.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_justification_consistency_check_4750d224.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.187-justification-current-state-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.187-justification-current-state-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_current_state_check_b027f6d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/justification_current_state_check_b027f6d8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/justification_current_state_check_b027f6d8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/lifecycle/test_justification_current_state_check_b027f6d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.188-justification-policy-collision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.188-justification-policy-collision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_policy_collision_df328c57/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/justification_policy_collision_df328c57.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/justification_policy_collision_df328c57.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_justification_policy_collision_df328c57.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.189-fake-justification-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.189-fake-justification-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/fake_justification_resistance_0f49ada1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/fake_justification_resistance_0f49ada1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/fake_justification_resistance_0f49ada1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_fake_justification_resistance_0f49ada1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.190-vague-justification-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.190-vague-justification-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/vague_justification_handling_d924bb74/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/vague_justification_handling_d924bb74.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/vague_justification_handling_d924bb74.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_vague_justification_handling_d924bb74.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.191-contradictory-justification-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.191-contradictory-justification-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/contradictory_justification_handling_43d3e543/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/contradictory_justification_handling_43d3e543.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/contradictory_justification_handling_43d3e543.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_contradictory_justification_handling_43d3e543.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.192-justification-does-not-grant-authority`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.192-justification-does-not-grant-authority.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/justification_does_not_grant_authority_69f55a2f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_does_not_grant_authority_69f55a2f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/justification_does_not_grant_authority_69f55a2f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_justification_does_not_grant_authority_69f55a2f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.193-re-evaluation-after-justification`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.193-re-evaluation-after-justification.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/re_evaluation_after_justification_11ab2ea6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/re_evaluation_after_justification_11ab2ea6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/re_evaluation_after_justification_11ab2ea6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_re_evaluation_after_justification_11ab2ea6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.194-strong-confirmation-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.194-strong-confirmation-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/strong_confirmation_boundary_17690ebe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/strong_confirmation_boundary_17690ebe.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/strong_confirmation_boundary_17690ebe.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_strong_confirmation_boundary_17690ebe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.195-confirmation-expiry`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.195-confirmation-expiry.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/confirmation_expiry_744a2086/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/confirmation_expiry_744a2086.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/confirmation_expiry_744a2086.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_confirmation_expiry_744a2086.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.196-confirmation-scope`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.196-confirmation-scope.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/confirmation_scope_37db6eee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/confirmation_scope_37db6eee.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/confirmation_scope_37db6eee.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_confirmation_scope_37db6eee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.197-confirmation-binding-to-exact-plan`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.197-confirmation-binding-to-exact-plan.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/confirmation_binding_to_exact_plan_70edc8b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/confirmation_binding_to_exact_plan_70edc8b4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/confirmation_binding_to_exact_plan_70edc8b4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_confirmation_binding_to_exact_plan_70edc8b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.198-changed-plan-invalidates-confirmation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.198-changed-plan-invalidates-confirmation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/changed_plan_invalidates_confirmation_5410beb6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/changed_plan_invalidates_confirmation_5410beb6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/changed_plan_invalidates_confirmation_5410beb6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_changed_plan_invalidates_confirmation_5410beb6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.199-gordon-integration-foundation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.199-gordon-integration-foundation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_integration_foundation_ae509e3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/gordon_integration_foundation_ae509e3f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/gordon_integration_foundation_ae509e3f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_gordon_integration_foundation_ae509e3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.200-gordon-availability-discovery`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.200-gordon-availability-discovery.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_availability_discovery_0bf37ff3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/gordon_availability_discovery_0bf37ff3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/gordon_availability_discovery_0bf37ff3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_gordon_availability_discovery_0bf37ff3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.201-gordon-advisory-request-schema`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.201-gordon-advisory-request-schema.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_advisory_request_schema_11bc71cc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/gordon_advisory_request_schema_11bc71cc.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/gordon_advisory_request_schema_11bc71cc.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_gordon_advisory_request_schema_11bc71cc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.202-gordon-evidencebundle`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.202-gordon-evidencebundle.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_evidencebundle_d3703dec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_evidencebundle_d3703dec.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_evidencebundle_d3703dec.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_gordon_evidencebundle_d3703dec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.203-gordon-evidence-minimization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.203-gordon-evidence-minimization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_evidence_minimization_993a511b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_evidence_minimization_993a511b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_evidence_minimization_993a511b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_gordon_evidence_minimization_993a511b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.204-gordon-evidence-redaction`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.204-gordon-evidence-redaction.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_evidence_redaction_225b60f1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_evidence_redaction_225b60f1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_evidence_redaction_225b60f1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_gordon_evidence_redaction_225b60f1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.205-gordon-policy-projection`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.205-gordon-policy-projection.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_policy_projection_1fd4f013/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/gordon_policy_projection_1fd4f013.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/gordon_policy_projection_1fd4f013.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_gordon_policy_projection_1fd4f013.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.206-gordon-contextual-review`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.206-gordon-contextual-review.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_contextual_review_43c84547/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_contextual_review_43c84547.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_contextual_review_43c84547.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_contextual_review_43c84547.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.207-gordon-inconsistency-analysis`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.207-gordon-inconsistency-analysis.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_inconsistency_analysis_09ab1dc1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_inconsistency_analysis_09ab1dc1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_inconsistency_analysis_09ab1dc1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_inconsistency_analysis_09ab1dc1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.208-gordon-missing-evidence-suggestions`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.208-gordon-missing-evidence-suggestions.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_missing_evidence_suggestions_4c06c5e7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_missing_evidence_suggestions_4c06c5e7.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_missing_evidence_suggestions_4c06c5e7.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_gordon_missing_evidence_suggestions_4c06c5e7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.209-gordon-clarification-suggestions`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.209-gordon-clarification-suggestions.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_clarification_suggestions_909ad560/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_clarification_suggestions_909ad560.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_clarification_suggestions_909ad560.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_clarification_suggestions_909ad560.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.210-gordon-risk-explanation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.210-gordon-risk-explanation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_risk_explanation_67ac7816/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/gordon_risk_explanation_67ac7816.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/gordon_risk_explanation_67ac7816.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_gordon_risk_explanation_67ac7816.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.211-gordon-structured-advisory-response`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.211-gordon-structured-advisory-response.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_structured_advisory_response_bb977eb3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_structured_advisory_response_bb977eb3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_structured_advisory_response_bb977eb3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_structured_advisory_response_bb977eb3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.212-gordon-response-validation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.212-gordon-response-validation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_response_validation_84280867/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_response_validation_84280867.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_response_validation_84280867.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_response_validation_84280867.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.213-gordon-uncertainty-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.213-gordon-uncertainty-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_uncertainty_handling_1c932d27/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_uncertainty_handling_1c932d27.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_uncertainty_handling_1c932d27.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_uncertainty_handling_1c932d27.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.214-gordon-disagreement-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.214-gordon-disagreement-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_disagreement_handling_0c9df0ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_disagreement_handling_0c9df0ea.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_disagreement_handling_0c9df0ea.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_disagreement_handling_0c9df0ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.215-gordon-timeout`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.215-gordon-timeout.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_timeout_2c603707/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_timeout_2c603707.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_timeout_2c603707.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_timeout_2c603707.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.216-gordon-unavailable-fallback`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.216-gordon-unavailable-fallback.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_unavailable_fallback_c17337c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_unavailable_fallback_c17337c8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_unavailable_fallback_c17337c8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_unavailable_fallback_c17337c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.217-gordon-compromised-output-containment`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.217-gordon-compromised-output-containment.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_compromised_output_containment_a13c8c00/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_compromised_output_containment_a13c8c00.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_compromised_output_containment_a13c8c00.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_compromised_output_containment_a13c8c00.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.218-gordon-prompt-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.218-gordon-prompt-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_prompt_injection_resistance_08db95d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_prompt_injection_resistance_08db95d5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_prompt_injection_resistance_08db95d5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_prompt_injection_resistance_08db95d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.219-gordon-verdict-not-authorization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.219-gordon-verdict-not-authorization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_verdict_not_authorization_f40f1a70/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/gordon_verdict_not_authorization_f40f1a70.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/gordon_verdict_not_authorization_f40f1a70.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_gordon_verdict_not_authorization_f40f1a70.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.220-gordon-cannot-weaken-policy`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.220-gordon-cannot-weaken-policy.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_cannot_weaken_policy_4ab6f18e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/gordon_cannot_weaken_policy_4ab6f18e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/gordon_cannot_weaken_policy_4ab6f18e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_gordon_cannot_weaken_policy_4ab6f18e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.221-gordon-cannot-manufacture-evidence`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.221-gordon-cannot-manufacture-evidence.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_cannot_manufacture_evidence_aa958dfe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_cannot_manufacture_evidence_aa958dfe.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_cannot_manufacture_evidence_aa958dfe.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_gordon_cannot_manufacture_evidence_aa958dfe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.222-gordon-cannot-execute`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.222-gordon-cannot-execute.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_cannot_execute_2cbe0c70/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/gordon_cannot_execute_2cbe0c70.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/gordon_cannot_execute_2cbe0c70.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_gordon_cannot_execute_2cbe0c70.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.223-deterministic-operation-without-gordon`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.223-deterministic-operation-without-gordon.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/deterministic_operation_without_gordon_15983aee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/deterministic_operation_without_gordon_15983aee.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/deterministic_operation_without_gordon_15983aee.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_deterministic_operation_without_gordon_15983aee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.224-operator-input-provenance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.224-operator-input-provenance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/operator_input_provenance_4b06ca8b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/operator_input_provenance_4b06ca8b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/operator_input_provenance_4b06ca8b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_operator_input_provenance_4b06ca8b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.225-untrusted-evidence-provenance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.225-untrusted-evidence-provenance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/untrusted_evidence_provenance_c89f873d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/untrusted_evidence_provenance_c89f873d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/untrusted_evidence_provenance_c89f873d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_untrusted_evidence_provenance_c89f873d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.226-instruction-data-separation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.226-instruction-data-separation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/instruction_data_separation_04ad1860/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/instruction_data_separation_04ad1860.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/instruction_data_separation_04ad1860.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_instruction_data_separation_04ad1860.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.227-log-instruction-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.227-log-instruction-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/log_instruction_injection_resistance_14d51873/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/log_instruction_injection_resistance_14d51873.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/log_instruction_injection_resistance_14d51873.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_log_instruction_injection_resistance_14d51873.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.228-readme-instruction-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.228-readme-instruction-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/readme_instruction_injection_resistance_0d4c8477/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/readme_instruction_injection_resistance_0d4c8477.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/readme_instruction_injection_resistance_0d4c8477.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_readme_instruction_injection_resistance_0d4c8477.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.229-file-content-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.229-file-content-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/file_content_injection_resistance_b55d374a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/file_content_injection_resistance_b55d374a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/file_content_injection_resistance_b55d374a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_file_content_injection_resistance_b55d374a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.230-web-content-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.230-web-content-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/web_content_injection_resistance_e4d4e1ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/web_content_injection_resistance_e4d4e1ea.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/web_content_injection_resistance_e4d4e1ea.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_web_content_injection_resistance_e4d4e1ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.231-process-output-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.231-process-output-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/process_output_injection_resistance_187cd869/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/process_output_injection_resistance_187cd869.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/process_output_injection_resistance_187cd869.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_process_output_injection_resistance_187cd869.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.232-model-output-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.232-model-output-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/model_output_injection_resistance_e7cf077a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/model_output_injection_resistance_e7cf077a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/model_output_injection_resistance_e7cf077a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_model_output_injection_resistance_e7cf077a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.233-nested-quoted-instruction-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.233-nested-quoted-instruction-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/nested_quoted_instruction_handling_7f5f7f93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/nested_quoted_instruction_handling_7f5f7f93.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/nested_quoted_instruction_handling_7f5f7f93.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_nested_quoted_instruction_handling_7f5f7f93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.234-copied-command-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.234-copied-command-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/copied_command_handling_16d54d89/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/copied_command_handling_16d54d89.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/copied_command_handling_16d54d89.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_copied_command_handling_16d54d89.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.235-code-block-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.235-code-block-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/code_block_handling_f10418fd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/code_block_handling_f10418fd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/code_block_handling_f10418fd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_code_block_handling_f10418fd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.236-shell-syntax-input-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.236-shell-syntax-input-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/shell_syntax_input_handling_30cfcf45/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/shell_syntax_input_handling_30cfcf45.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/shell_syntax_input_handling_30cfcf45.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_shell_syntax_input_handling_30cfcf45.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.237-arbitrary-shell-intent-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.237-arbitrary-shell-intent-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/arbitrary_shell_intent_handling_7d6977c1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/arbitrary_shell_intent_handling_7d6977c1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/arbitrary_shell_intent_handling_7d6977c1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_arbitrary_shell_intent_handling_7d6977c1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.238-shell-metacharacter-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.238-shell-metacharacter-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/shell_metacharacter_handling_b51f3f68/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/shell_metacharacter_handling_b51f3f68.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/shell_metacharacter_handling_b51f3f68.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_shell_metacharacter_handling_b51f3f68.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.239-command-substitution-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.239-command-substitution-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/command_substitution_handling_a86c7acb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/command_substitution_handling_a86c7acb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/command_substitution_handling_a86c7acb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_command_substitution_handling_a86c7acb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.240-pipeline-syntax-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.240-pipeline-syntax-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/pipeline_syntax_handling_423e8a53/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/pipeline_syntax_handling_423e8a53.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/pipeline_syntax_handling_423e8a53.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_pipeline_syntax_handling_423e8a53.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.241-redirection-syntax-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.241-redirection-syntax-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/redirection_syntax_handling_c977c7d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/redirection_syntax_handling_c977c7d4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/redirection_syntax_handling_c977c7d4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_redirection_syntax_handling_c977c7d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.242-encoded-payload-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.242-encoded-payload-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/encoded_payload_handling_a041b24a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/encoded_payload_handling_a041b24a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/encoded_payload_handling_a041b24a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_encoded_payload_handling_a041b24a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.243-base64-obfuscation-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.243-base64-obfuscation-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/base64_obfuscation_handling_a881eaab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/base64_obfuscation_handling_a881eaab.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/base64_obfuscation_handling_a881eaab.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_base64_obfuscation_handling_a881eaab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.244-unicode-obfuscation-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.244-unicode-obfuscation-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unicode_obfuscation_handling_76e5962b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/unicode_obfuscation_handling_76e5962b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/unicode_obfuscation_handling_76e5962b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_unicode_obfuscation_handling_76e5962b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.245-homoglyph-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.245-homoglyph-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/homoglyph_handling_0291884e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/homoglyph_handling_0291884e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/homoglyph_handling_0291884e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_homoglyph_handling_0291884e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.246-whitespace-obfuscation-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.246-whitespace-obfuscation-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/whitespace_obfuscation_handling_399fb1c8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/whitespace_obfuscation_handling_399fb1c8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/whitespace_obfuscation_handling_399fb1c8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_whitespace_obfuscation_handling_399fb1c8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.247-natural-language-obfuscation-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.247-natural-language-obfuscation-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/natural_language_obfuscation_handling_52697afe/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/natural_language_obfuscation_handling_52697afe.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/natural_language_obfuscation_handling_52697afe.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_natural_language_obfuscation_handling_52697afe.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.248-indirect-harmful-effect-request-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.248-indirect-harmful-effect-request-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/indirect_harmful_effect_request_handling_c6de0bba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/indirect_harmful_effect_request_handling_c6de0bba.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/indirect_harmful_effect_request_handling_c6de0bba.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_indirect_harmful_effect_request_handling_c6de0bba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.249-multi-turn-escalation-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.249-multi-turn-escalation-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/multi_turn_escalation_boundary_ef3c82ea/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/multi_turn_escalation_boundary_ef3c82ea.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/multi_turn_escalation_boundary_ef3c82ea.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_multi_turn_escalation_boundary_ef3c82ea.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.250-context-laundering-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.250-context-laundering-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_laundering_resistance_12a261ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_laundering_resistance_12a261ce.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_laundering_resistance_12a261ce.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_laundering_resistance_12a261ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.251-authority-laundering-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.251-authority-laundering-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/authority_laundering_resistance_17078f3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/authority_laundering_resistance_17078f3a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/authority_laundering_resistance_17078f3a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_authority_laundering_resistance_17078f3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.252-semantic-to-shell-prohibition`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.252-semantic-to-shell-prohibition.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_to_shell_prohibition_9b94c5d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/semantic_to_shell_prohibition_9b94c5d9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/semantic_to_shell_prohibition_9b94c5d9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_semantic_to_shell_prohibition_9b94c5d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.253-typed-phase-40-intent-conversion`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.253-typed-phase-40-intent-conversion.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/typed_phase_40_intent_conversion_8520e64a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/typed_phase_40_intent_conversion_8520e64a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/typed_phase_40_intent_conversion_8520e64a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_typed_phase_40_intent_conversion_8520e64a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.254-typed-phase-45-plan-conversion`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.254-typed-phase-45-plan-conversion.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/typed_phase_45_plan_conversion_202ed153/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/typed_phase_45_plan_conversion_202ed153.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/typed_phase_45_plan_conversion_202ed153.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_typed_phase_45_plan_conversion_202ed153.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.255-phase-45-applicability-check`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.255-phase-45-applicability-check.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/applicability_check_d60e9091/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/applicability_check_d60e9091.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/applicability_check_d60e9091.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_applicability_check_d60e9091.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.256-phase-45-fresh-observation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.256-phase-45-fresh-observation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/fresh_observation_6f8303b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/fresh_observation_6f8303b0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/fresh_observation_6f8303b0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_fresh_observation_6f8303b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.257-phase-45-validation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.257-phase-45-validation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/validation_3d7c0b58/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/validation_3d7c0b58.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/validation_3d7c0b58.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_validation_3d7c0b58.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.258-phase-45-authorization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.258-phase-45-authorization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/authorization_75933410/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/authorization_75933410.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/authorization_75933410.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_authorization_75933410.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.259-phase-45-execution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.259-phase-45-execution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/execution_7f13b391/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/execution_7f13b391.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/execution_7f13b391.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_execution_7f13b391.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.260-phase-45-verification`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.260-phase-45-verification.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/verification_c7380d07/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/verification_c7380d07.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/verification_c7380d07.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_verification_c7380d07.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.261-phase-39-recording`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.261-phase-39-recording.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recording_2446f37a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/recording_2446f37a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/recording_2446f37a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_recording_2446f37a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.262-phase-41-workflow-handoff`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.262-phase-41-workflow-handoff.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/workflow_handoff_e79bff3e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/workflow_handoff_e79bff3e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/workflow_handoff_e79bff3e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_workflow_handoff_e79bff3e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.263-taskwarrior-provider-discovery`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.263-taskwarrior-provider-discovery.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_provider_discovery_3a1bee22/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/taskwarrior_provider_discovery_3a1bee22.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/taskwarrior_provider_discovery_3a1bee22.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_taskwarrior_provider_discovery_3a1bee22.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.264-taskwarrior-integration-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.264-taskwarrior-integration-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_integration_boundary_57251241/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/taskwarrior_integration_boundary_57251241.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/taskwarrior_integration_boundary_57251241.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_taskwarrior_integration_boundary_57251241.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.265-taskwarrior-natural-language-add`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.265-taskwarrior-natural-language-add.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_natural_language_add_3504b55b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_natural_language_add_3504b55b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_natural_language_add_3504b55b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_taskwarrior_natural_language_add_3504b55b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.266-taskwarrior-natural-language-query`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.266-taskwarrior-natural-language-query.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_natural_language_query_b808b78d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/taskwarrior_natural_language_query_b808b78d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/taskwarrior_natural_language_query_b808b78d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_taskwarrior_natural_language_query_b808b78d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.267-taskwarrior-natural-language-modify`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.267-taskwarrior-natural-language-modify.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_natural_language_modify_1250c5e9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_natural_language_modify_1250c5e9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_natural_language_modify_1250c5e9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_taskwarrior_natural_language_modify_1250c5e9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.268-taskwarrior-ambiguous-task-resolution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.268-taskwarrior-ambiguous-task-resolution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_ambiguous_task_resolution_17156740/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_ambiguous_task_resolution_17156740.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_ambiguous_task_resolution_17156740.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_taskwarrior_ambiguous_task_resolution_17156740.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.269-taskwarrior-destructive-bulk-change-safeguards`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.269-taskwarrior-destructive-bulk-change-safeguards.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_destructive_bulk_change_safeguards_3e930a3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_destructive_bulk_change_safeguards_3e930a3a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/taskwarrior_destructive_bulk_change_safeguards_3e930a3a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_taskwarrior_destructive_bulk_change_safeguards_3e930a3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.270-task-intent-versus-executable-workflow-distinction`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.270-task-intent-versus-executable-workflow-distinction.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/task_intent_versus_executable_workflow_distinction_16ad763f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/task_intent_versus_executable_workflow_distinction_16ad763f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/task_intent_versus_executable_workflow_distinction_16ad763f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_task_intent_versus_executable_workflow_distinction_16ad763f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.271-read-only-system-question-path`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.271-read-only-system-question-path.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/read_only_system_question_path_339bea56/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/read_only_system_question_path_339bea56.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/read_only_system_question_path_339bea56.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_read_only_system_question_path_339bea56.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.272-system-explanation-path`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.272-system-explanation-path.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/system_explanation_path_6745ae67/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/system_explanation_path_6745ae67.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/system_explanation_path_6745ae67.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_system_explanation_path_6745ae67.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.273-what-changed-query`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.273-what-changed-query.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/what_changed_query_9774d934/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/what_changed_query_9774d934.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/what_changed_query_9774d934.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_what_changed_query_9774d934.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.274-what-depends-on-this-query`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.274-what-depends-on-this-query.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/what_depends_on_this_query_85593ee1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/what_depends_on_this_query_85593ee1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/what_depends_on_this_query_85593ee1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_what_depends_on_this_query_85593ee1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.275-why-is-this-happening-query`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.275-why-is-this-happening-query.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/why_is_this_happening_query_627d5cba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/why_is_this_happening_query_627d5cba.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/why_is_this_happening_query_627d5cba.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_why_is_this_happening_query_627d5cba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.276-what-can-i-do-query`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.276-what-can-i-do-query.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/what_can_i_do_query_96f1ff0e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/what_can_i_do_query_96f1ff0e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/what_can_i_do_query_96f1ff0e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_what_can_i_do_query_96f1ff0e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.277-plan-preview-query`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.277-plan-preview-query.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/plan_preview_query_01c3d0d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/plan_preview_query_01c3d0d5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/plan_preview_query_01c3d0d5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_plan_preview_query_01c3d0d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.278-safe-action-request-path`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.278-safe-action-request-path.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/safe_action_request_path_c4ee8774/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/safe_action_request_path_c4ee8774.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/safe_action_request_path_c4ee8774.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_safe_action_request_path_c4ee8774.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.279-consequential-action-request-path`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.279-consequential-action-request-path.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/consequential_action_request_path_decd77ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/consequential_action_request_path_decd77ae.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/consequential_action_request_path_decd77ae.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_consequential_action_request_path_decd77ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.280-high-risk-action-request-path`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.280-high-risk-action-request-path.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/high_risk_action_request_path_462a3cd1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/high_risk_action_request_path_462a3cd1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/high_risk_action_request_path_462a3cd1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_high_risk_action_request_path_462a3cd1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.281-protected-resource-action-path`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.281-protected-resource-action-path.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/protected_resource_action_path_82e6fbdb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/protected_resource_action_path_82e6fbdb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/protected_resource_action_path_82e6fbdb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_protected_resource_action_path_82e6fbdb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.282-ask-dry-run`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.282-ask-dry-run.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_dry_run_907b0223/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_dry_run_907b0223.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_dry_run_907b0223.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_dry_run_907b0223.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.283-ask-explain-plan`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.283-ask-explain-plan.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_explain_plan_f5d14c94/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/ask_explain_plan_f5d14c94.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/ask_explain_plan_f5d14c94.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_ask_explain_plan_f5d14c94.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.284-ask-show-context`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.284-ask-show-context.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_show_context_f4c0e2f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_show_context_f4c0e2f4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_show_context_f4c0e2f4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_show_context_f4c0e2f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.285-ask-show-resolved-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.285-ask-show-resolved-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_show_resolved_intent_80e106ab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/ask_show_resolved_intent_80e106ab.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/ask_show_resolved_intent_80e106ab.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_ask_show_resolved_intent_80e106ab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.286-ask-show-policy-decision`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.286-ask-show-policy-decision.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_show_policy_decision_8b37a15d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/ask_show_policy_decision_8b37a15d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/ask_show_policy_decision_8b37a15d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_ask_show_policy_decision_8b37a15d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.287-ask-show-evidence`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.287-ask-show-evidence.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_show_evidence_bff98c23/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/ask_show_evidence_bff98c23.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/ask_show_evidence_bff98c23.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_ask_show_evidence_bff98c23.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.288-ask-privacy-controls`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.288-ask-privacy-controls.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_privacy_controls_163f4655/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_privacy_controls_163f4655.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_privacy_controls_163f4655.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_privacy_controls_163f4655.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.289-ask-history-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.289-ask-history-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_history_boundary_cfbadae5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_history_boundary_cfbadae5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_history_boundary_cfbadae5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_history_boundary_cfbadae5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.290-ask-audit-trail`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.290-ask-audit-trail.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_audit_trail_4986b99f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/ask_audit_trail_4986b99f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/ask_audit_trail_4986b99f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_ask_audit_trail_4986b99f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.291-ask-telemetry`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.291-ask-telemetry.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_telemetry_b293c279/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/ask_telemetry_b293c279.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/ask_telemetry_b293c279.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_ask_telemetry_b293c279.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.292-ask-performance-metrics`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.292-ask-performance-metrics.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_performance_metrics_ee5fa249/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/ask_performance_metrics_ee5fa249.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/ask_performance_metrics_ee5fa249.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_ask_performance_metrics_ee5fa249.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.293-ask-latency-budget`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.293-ask-latency-budget.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_latency_budget_f61b5935/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_latency_budget_f61b5935.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_latency_budget_f61b5935.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_latency_budget_f61b5935.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.294-ask-cancellation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.294-ask-cancellation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_cancellation_5ead3203/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_cancellation_5ead3203.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_cancellation_5ead3203.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_cancellation_5ead3203.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.295-ask-timeout`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.295-ask-timeout.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_timeout_5c697aa6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_timeout_5c697aa6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_timeout_5c697aa6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_timeout_5c697aa6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.296-ask-sigint-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.296-ask-sigint-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_sigint_handling_1fdc6973/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_sigint_handling_1fdc6973.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_sigint_handling_1fdc6973.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_sigint_handling_1fdc6973.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.297-ask-terminal-resize-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.297-ask-terminal-resize-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_terminal_resize_boundary_3972321e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_terminal_resize_boundary_3972321e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_terminal_resize_boundary_3972321e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_terminal_resize_boundary_3972321e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.298-ask-unicode-input`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.298-ask-unicode-input.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_unicode_input_ad0d5976/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_unicode_input_ad0d5976.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_unicode_input_ad0d5976.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_unicode_input_ad0d5976.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.299-ask-polish-language-input`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.299-ask-polish-language-input.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_polish_language_input_1c3b3a8f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_polish_language_input_1c3b3a8f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_polish_language_input_1c3b3a8f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_polish_language_input_1c3b3a8f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.300-ask-english-language-input`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.300-ask-english-language-input.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_english_language_input_1b3ac6d7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_english_language_input_1b3ac6d7.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_english_language_input_1b3ac6d7.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_english_language_input_1b3ac6d7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.301-multilingual-intent-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.301-multilingual-intent-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/multilingual_intent_boundary_7be57f3f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/multilingual_intent_boundary_7be57f3f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/multilingual_intent_boundary_7be57f3f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_multilingual_intent_boundary_7be57f3f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.302-locale-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.302-locale-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/locale_handling_e20785d8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/locale_handling_e20785d8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/locale_handling_e20785d8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_locale_handling_e20785d8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.303-date-time-parsing`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.303-date-time-parsing.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/date_time_parsing_c83eb7db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/date_time_parsing_c83eb7db.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/date_time_parsing_c83eb7db.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_date_time_parsing_c83eb7db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.304-relative-time-parsing`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.304-relative-time-parsing.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/relative_time_parsing_313cbac0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/relative_time_parsing_313cbac0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/relative_time_parsing_313cbac0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_relative_time_parsing_313cbac0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.305-timezone-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.305-timezone-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/timezone_handling_cc62ce2f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/timezone_handling_cc62ce2f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/timezone_handling_cc62ce2f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_timezone_handling_cc62ce2f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.306-phase-41-scheduled-task-handoff`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.306-phase-41-scheduled-task-handoff.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/scheduled_task_handoff_5a82a682/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/planning/scheduled_task_handoff_5a82a682.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/planning/scheduled_task_handoff_5a82a682.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/planning/test_scheduled_task_handoff_5a82a682.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.307-confirmation-for-scheduling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.307-confirmation-for-scheduling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/confirmation_for_scheduling_ecac3c81/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/confirmation_for_scheduling_ecac3c81.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/confirmation_for_scheduling_ecac3c81.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_confirmation_for_scheduling_ecac3c81.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.308-recurring-task-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.308-recurring-task-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recurring_task_intent_e12213b8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/recurring_task_intent_e12213b8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/recurring_task_intent_e12213b8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_recurring_task_intent_e12213b8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.309-condition-watch-intent`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.309-condition-watch-intent.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/condition_watch_intent_c98eb0eb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/condition_watch_intent_c98eb0eb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/condition_watch_intent_c98eb0eb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_condition_watch_intent_c98eb0eb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.310-context-aware-automation-request`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.310-context-aware-automation-request.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_aware_automation_request_67756b50/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_aware_automation_request_67756b50.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_aware_automation_request_67756b50.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_aware_automation_request_67756b50.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.311-automation-authority-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.311-automation-authority-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/automation_authority_boundary_f75fb5a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/automation_authority_boundary_f75fb5a4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/automation_authority_boundary_f75fb5a4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_automation_authority_boundary_f75fb5a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.312-persistent-automation-scrutiny`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.312-persistent-automation-scrutiny.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/persistent_automation_scrutiny_d3b0aa49/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/persistence/persistent_automation_scrutiny_d3b0aa49.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/persistence/persistent_automation_scrutiny_d3b0aa49.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/persistence/test_persistent_automation_scrutiny_d3b0aa49.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.313-unexpected-persistence-scrutiny`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.313-unexpected-persistence-scrutiny.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unexpected_persistence_scrutiny_54488881/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/persistence/unexpected_persistence_scrutiny_54488881.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/persistence/unexpected_persistence_scrutiny_54488881.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/persistence/test_unexpected_persistence_scrutiny_54488881.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.314-operator-preference-integration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.314-operator-preference-integration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/operator_preference_integration_2798a9b3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/operator_preference_integration_2798a9b3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/operator_preference_integration_2798a9b3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_operator_preference_integration_2798a9b3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.315-learned-preference-authority-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.315-learned-preference-authority-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/learned_preference_authority_boundary_05c8dd52/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/learned_preference_authority_boundary_05c8dd52.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/learned_preference_authority_boundary_05c8dd52.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_learned_preference_authority_boundary_05c8dd52.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.316-phase-44-contextual-profile-integration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.316-phase-44-contextual-profile-integration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/contextual_profile_integration_7ae7ebbd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/contextual_profile_integration_7ae7ebbd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/contextual_profile_integration_7ae7ebbd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_contextual_profile_integration_7ae7ebbd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.317-contextual-policy-adaptation-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.317-contextual-policy-adaptation-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/contextual_policy_adaptation_boundary_261ab1f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/contextual_policy_adaptation_boundary_261ab1f2.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/contextual_policy_adaptation_boundary_261ab1f2.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_contextual_policy_adaptation_boundary_261ab1f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.318-no-policy-self-modification`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.318-no-policy-self-modification.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/no_policy_self_modification_d99b455d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/no_policy_self_modification_d99b455d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/no_policy_self_modification_d99b455d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_no_policy_self_modification_d99b455d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.319-policy-modification-request-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.319-policy-modification-request-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_modification_request_handling_4c473434/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_modification_request_handling_4c473434.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_modification_request_handling_4c473434.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_modification_request_handling_4c473434.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.320-ask-configuration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.320-ask-configuration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_configuration_d4999631/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_configuration_d4999631.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_configuration_d4999631.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_configuration_d4999631.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.321-ask-policy-configuration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.321-ask-policy-configuration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_policy_configuration_c111531a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/ask_policy_configuration_c111531a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/ask_policy_configuration_c111531a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_ask_policy_configuration_c111531a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.322-per-user-ask-policy`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.322-per-user-ask-policy.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/per_user_ask_policy_f0058d32/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/per_user_ask_policy_f0058d32.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/per_user_ask_policy_f0058d32.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_per_user_ask_policy_f0058d32.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.323-per-session-ask-policy`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.323-per-session-ask-policy.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/per_session_ask_policy_52fced2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/per_session_ask_policy_52fced2e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/per_session_ask_policy_52fced2e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_per_session_ask_policy_52fced2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.324-system-wide-ask-policy`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.324-system-wide-ask-policy.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/system_wide_ask_policy_92291594/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/system_wide_ask_policy_92291594.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/system_wide_ask_policy_92291594.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_system_wide_ask_policy_92291594.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.325-policy-reload`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.325-policy-reload.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_reload_9777a662/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_reload_9777a662.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_reload_9777a662.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_reload_9777a662.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.326-policy-versioning`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.326-policy-versioning.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_versioning_79bb3458/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_versioning_79bb3458.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_versioning_79bb3458.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_versioning_79bb3458.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.327-policy-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.327-policy-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_audit_320baf88/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/policy_audit_320baf88.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/policy_audit_320baf88.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_policy_audit_320baf88.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.328-policy-simulation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.328-policy-simulation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_simulation_289a44a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_simulation_289a44a8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_simulation_289a44a8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_simulation_289a44a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.329-policy-test-harness`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.329-policy-test-harness.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_test_harness_7df2b9c2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/policy_test_harness_7df2b9c2.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/policy_test_harness_7df2b9c2.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_policy_test_harness_7df2b9c2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.330-safe-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.330-safe-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/safe_mode_cee57997/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/safe_mode_cee57997.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/safe_mode_cee57997.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_safe_mode_cee57997.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.331-read-only-safe-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.331-read-only-safe-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/read_only_safe_mode_793213dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/read_only_safe_mode_793213dc.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/read_only_safe_mode_793213dc.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_read_only_safe_mode_793213dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.332-semantic-provider-disabled-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.332-semantic-provider-disabled-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_provider_disabled_mode_60db728f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_disabled_mode_60db728f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_disabled_mode_60db728f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_semantic_provider_disabled_mode_60db728f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.333-gordon-disabled-mode`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.333-gordon-disabled-mode.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_disabled_mode_40809e3e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/gordon_disabled_mode_40809e3e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/gordon_disabled_mode_40809e3e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/lifecycle/test_gordon_disabled_mode_40809e3e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.334-emergency-ask-disable`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.334-emergency-ask-disable.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/emergency_ask_disable_df339f70/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/emergency_ask_disable_df339f70.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/lifecycle/emergency_ask_disable_df339f70.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/lifecycle/test_emergency_ask_disable_df339f70.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.335-rate-limiting`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.335-rate-limiting.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/rate_limiting_d4830c74/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/rate_limiting_d4830c74.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/rate_limiting_d4830c74.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_rate_limiting_d4830c74.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.336-request-size-limits`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.336-request-size-limits.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/request_size_limits_45bc6aed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/request_size_limits_45bc6aed.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/request_size_limits_45bc6aed.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_request_size_limits_45bc6aed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.337-context-size-limits`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.337-context-size-limits.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_size_limits_efd8fdbd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_size_limits_efd8fdbd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_size_limits_efd8fdbd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_size_limits_efd8fdbd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.338-semantic-inference-limits`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.338-semantic-inference-limits.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_inference_limits_f7f3dd3a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/semantic_inference_limits_f7f3dd3a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/semantic_inference_limits_f7f3dd3a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_semantic_inference_limits_f7f3dd3a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.339-resource-limits`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.339-resource-limits.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/resource_limits_392e19ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/resource_limits_392e19ec.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/resource_limits_392e19ec.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_resource_limits_392e19ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.340-phase-29-process-containment`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.340-phase-29-process-containment.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/process_containment_371e53ec/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/process_containment_371e53ec.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/process_containment_371e53ec.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_process_containment_371e53ec.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.341-phase-30-resource-containment`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.341-phase-30-resource-containment.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/resource_containment_70238804/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/resource_containment_70238804.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/resource_containment_70238804.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_resource_containment_70238804.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.342-bitnet-workload-placement`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.342-bitnet-workload-placement.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_workload_placement_a2797c7a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_workload_placement_a2797c7a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/bitnet_workload_placement_a2797c7a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_bitnet_workload_placement_a2797c7a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.343-gordon-workload-placement`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.343-gordon-workload-placement.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_workload_placement_515097b5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_workload_placement_515097b5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_workload_placement_515097b5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_workload_placement_515097b5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.344-gpu-placement-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.344-gpu-placement-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gpu_placement_boundary_5cd3a027/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gpu_placement_boundary_5cd3a027.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gpu_placement_boundary_5cd3a027.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gpu_placement_boundary_5cd3a027.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.345-cpu-only-fallback`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.345-cpu-only-fallback.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/cpu_only_fallback_3de4a486/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/cpu_only_fallback_3de4a486.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/cpu_only_fallback_3de4a486.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_cpu_only_fallback_3de4a486.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.346-concurrent-ask-requests`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.346-concurrent-ask-requests.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/concurrent_ask_requests_1380c3ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/concurrent_ask_requests_1380c3ed.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/concurrent_ask_requests_1380c3ed.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_concurrent_ask_requests_1380c3ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.347-session-isolation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.347-session-isolation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/session_isolation_a03b1175/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/session_isolation_a03b1175.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/session_isolation_a03b1175.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_session_isolation_a03b1175.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.348-race-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.348-race-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/race_handling_2022effd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/race_handling_2022effd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/race_handling_2022effd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_race_handling_2022effd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.349-toctou-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.349-toctou-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/toctou_handling_47f731ed/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/toctou_handling_47f731ed.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/toctou_handling_47f731ed.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_toctou_handling_47f731ed.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.350-state-drift-between-interpretation-and-execution`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.350-state-drift-between-interpretation-and-execution.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/state_drift_between_interpretation_and_execution_b0e1ab16/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/state_drift_between_interpretation_and_execution_b0e1ab16.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/state_drift_between_interpretation_and_execution_b0e1ab16.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_state_drift_between_interpretation_and_execution_b0e1ab16.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.351-re-authorization-after-drift`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.351-re-authorization-after-drift.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/re_authorization_after_drift_2dcb9ae8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/re_authorization_after_drift_2dcb9ae8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/re_authorization_after_drift_2dcb9ae8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_re_authorization_after_drift_2dcb9ae8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.352-re-clarification-after-semantic-change`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.352-re-clarification-after-semantic-change.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/re_clarification_after_semantic_change_91fb10bd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/re_clarification_after_semantic_change_91fb10bd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/re_clarification_after_semantic_change_91fb10bd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_re_clarification_after_semantic_change_91fb10bd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.353-secret-safe-logging`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.353-secret-safe-logging.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/secret_safe_logging_2b87a3a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/secret_safe_logging_2b87a3a4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/secret_safe_logging_2b87a3a4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_secret_safe_logging_2b87a3a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.354-secret-safe-prompts`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.354-secret-safe-prompts.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/secret_safe_prompts_af3f08af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/secret_safe_prompts_af3f08af.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/secret_safe_prompts_af3f08af.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_secret_safe_prompts_af3f08af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.355-secretref-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.355-secretref-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/secretref_handling_024baab6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/secretref_handling_024baab6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/secretref_handling_024baab6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_secretref_handling_024baab6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.356-credential-request-handling`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.356-credential-request-handling.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/credential_request_handling_2aecb0d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/credential_request_handling_2aecb0d4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/credential_request_handling_2aecb0d4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_credential_request_handling_2aecb0d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.357-credential-disclosure-denial`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.357-credential-disclosure-denial.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/credential_disclosure_denial_61dffb95/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/credential_disclosure_denial_61dffb95.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/credential_disclosure_denial_61dffb95.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_credential_disclosure_denial_61dffb95.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.358-sensitive-output-redaction`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.358-sensitive-output-redaction.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/sensitive_output_redaction_87a50a48/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/sensitive_output_redaction_87a50a48.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/sensitive_output_redaction_87a50a48.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_sensitive_output_redaction_87a50a48.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.359-terminal-escape-sanitization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.359-terminal-escape-sanitization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/terminal_escape_sanitization_36fe6f85/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/terminal_escape_sanitization_36fe6f85.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/terminal_escape_sanitization_36fe6f85.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_terminal_escape_sanitization_36fe6f85.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.360-control-character-sanitization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.360-control-character-sanitization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/control_character_sanitization_7f62bd5f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/control_character_sanitization_7f62bd5f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/control_character_sanitization_7f62bd5f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_control_character_sanitization_7f62bd5f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.361-output-injection-resistance`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.361-output-injection-resistance.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/output_injection_resistance_58f75276/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/output_injection_resistance_58f75276.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/output_injection_resistance_58f75276.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_output_injection_resistance_58f75276.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.362-audit-event-schema`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.362-audit-event-schema.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/audit_event_schema_0eab9fb0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/audit_event_schema_0eab9fb0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/audit_event_schema_0eab9fb0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_audit_event_schema_0eab9fb0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.363-phase-39-ask-events`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.363-phase-39-ask-events.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_events_efa85a78/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_events_efa85a78.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_events_efa85a78.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_events_efa85a78.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.364-phase-42-ask-graph-links`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.364-phase-42-ask-graph-links.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_graph_links_e9633fce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_graph_links_e9633fce.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_graph_links_e9633fce.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_graph_links_e9633fce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.365-phase-43-ask-intelligence-links`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.365-phase-43-ask-intelligence-links.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_intelligence_links_9c0fe34d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_intelligence_links_9c0fe34d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_intelligence_links_9c0fe34d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_intelligence_links_9c0fe34d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.366-phase-44-ask-adaptation-links`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.366-phase-44-ask-adaptation-links.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ask_adaptation_links_7acaa643/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_adaptation_links_7acaa643.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ask_adaptation_links_7acaa643.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ask_adaptation_links_7acaa643.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.367-operator-feedback`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.367-operator-feedback.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/operator_feedback_92c358db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/operator_feedback_92c358db.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/operator_feedback_92c358db.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_operator_feedback_92c358db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.368-false-positive-suspicious-use-feedback`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.368-false-positive-suspicious-use-feedback.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/false_positive_suspicious_use_feedback_7f0c65cd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/false_positive_suspicious_use_feedback_7f0c65cd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/false_positive_suspicious_use_feedback_7f0c65cd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_false_positive_suspicious_use_feedback_7f0c65cd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.369-false-negative-suspicious-use-feedback`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.369-false-negative-suspicious-use-feedback.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/false_negative_suspicious_use_feedback_2b446a67/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/false_negative_suspicious_use_feedback_2b446a67.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/false_negative_suspicious_use_feedback_2b446a67.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_false_negative_suspicious_use_feedback_2b446a67.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.370-feedback-does-not-override-policy`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.370-feedback-does-not-override-policy.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/feedback_does_not_override_policy_0ada7982/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/feedback_does_not_override_policy_0ada7982.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/feedback_does_not_override_policy_0ada7982.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_feedback_does_not_override_policy_0ada7982.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.371-context-anomaly-calibration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.371-context-anomaly-calibration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/context_anomaly_calibration_d6c956d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_anomaly_calibration_d6c956d1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/context_anomaly_calibration_d6c956d1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_context_anomaly_calibration_d6c956d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.372-legitimacy-calibration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.372-legitimacy-calibration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/legitimacy_calibration_0e86685e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/legitimacy_calibration_0e86685e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/legitimacy_calibration_0e86685e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_legitimacy_calibration_0e86685e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.373-semantic-parser-calibration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.373-semantic-parser-calibration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_parser_calibration_82f8e559/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/semantic_parser_calibration_82f8e559.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/semantic_parser_calibration_82f8e559.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_semantic_parser_calibration_82f8e559.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.374-holdout-intent-corpus`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.374-holdout-intent-corpus.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/holdout_intent_corpus_755d8760/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/holdout_intent_corpus_755d8760.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/holdout_intent_corpus_755d8760.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_holdout_intent_corpus_755d8760.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.375-benign-admin-corpus`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.375-benign-admin-corpus.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/benign_admin_corpus_202b8af7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/benign_admin_corpus_202b8af7.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/benign_admin_corpus_202b8af7.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_benign_admin_corpus_202b8af7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.376-suspicious-intent-corpus`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.376-suspicious-intent-corpus.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/suspicious_intent_corpus_21f74048/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/suspicious_intent_corpus_21f74048.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/suspicious_intent_corpus_21f74048.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_suspicious_intent_corpus_21f74048.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.377-ambiguous-request-corpus`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.377-ambiguous-request-corpus.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ambiguous_request_corpus_121bcbc6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/ambiguous_request_corpus_121bcbc6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/ambiguous_request_corpus_121bcbc6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_ambiguous_request_corpus_121bcbc6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.378-prompt-injection-corpus`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.378-prompt-injection-corpus.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/prompt_injection_corpus_c982187c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/prompt_injection_corpus_c982187c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/prompt_injection_corpus_c982187c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_prompt_injection_corpus_c982187c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.379-obfuscation-corpus`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.379-obfuscation-corpus.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/obfuscation_corpus_366d21d0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/obfuscation_corpus_366d21d0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/obfuscation_corpus_366d21d0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_obfuscation_corpus_366d21d0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.380-fork-bomb-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.380-fork-bomb-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/fork_bomb_adversarial_test_cfcc2c11/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/fork_bomb_adversarial_test_cfcc2c11.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/fork_bomb_adversarial_test_cfcc2c11.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_fork_bomb_adversarial_test_cfcc2c11.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.381-natural-language-fork-bomb-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.381-natural-language-fork-bomb-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/natural_language_fork_bomb_adversarial_test_fec30c5d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/natural_language_fork_bomb_adversarial_test_fec30c5d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/natural_language_fork_bomb_adversarial_test_fec30c5d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_natural_language_fork_bomb_adversarial_test_fec30c5d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.382-new-port-plus-log-export-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.382-new-port-plus-log-export-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/new_port_plus_log_export_adversarial_test_f0450248/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/new_port_plus_log_export_adversarial_test_f0450248.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/new_port_plus_log_export_adversarial_test_f0450248.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_new_port_plus_log_export_adversarial_test_f0450248.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.383-unknown-endpoint-exfiltration-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.383-unknown-endpoint-exfiltration-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/unknown_endpoint_exfiltration_adversarial_test_7636254b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/unknown_endpoint_exfiltration_adversarial_test_7636254b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/unknown_endpoint_exfiltration_adversarial_test_7636254b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_unknown_endpoint_exfiltration_adversarial_test_7636254b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.384-ssh-key-export-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.384-ssh-key-export-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ssh_key_export_adversarial_test_5b557dac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/ssh_key_export_adversarial_test_5b557dac.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/ssh_key_export_adversarial_test_5b557dac.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_ssh_key_export_adversarial_test_5b557dac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.385-environment-export-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.385-environment-export-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/environment_export_adversarial_test_dca50aa7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/environment_export_adversarial_test_dca50aa7.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/environment_export_adversarial_test_dca50aa7.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_environment_export_adversarial_test_dca50aa7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.386-home-http-exposure-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.386-home-http-exposure-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/home_http_exposure_adversarial_test_a7602df2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/home_http_exposure_adversarial_test_a7602df2.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/home_http_exposure_adversarial_test_a7602df2.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_home_http_exposure_adversarial_test_a7602df2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.387-persistent-outbound-service-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.387-persistent-outbound-service-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/persistent_outbound_service_adversarial_test_e11823bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/persistent_outbound_service_adversarial_test_e11823bb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/persistent_outbound_service_adversarial_test_e11823bb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_persistent_outbound_service_adversarial_test_e11823bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.388-security-disable-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.388-security-disable-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/security_disable_adversarial_test_d6a8101d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/security_disable_adversarial_test_d6a8101d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/security_disable_adversarial_test_d6a8101d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_security_disable_adversarial_test_d6a8101d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.389-authorized-but-unexpected-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.389-authorized-but-unexpected-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/authorized_but_unexpected_adversarial_test_94fe42e1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/authorized_but_unexpected_adversarial_test_94fe42e1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/authorized_but_unexpected_adversarial_test_94fe42e1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_authorized_but_unexpected_adversarial_test_94fe42e1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.390-plausible-justification-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.390-plausible-justification-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/plausible_justification_adversarial_test_f11679b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/plausible_justification_adversarial_test_f11679b0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/plausible_justification_adversarial_test_f11679b0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_plausible_justification_adversarial_test_f11679b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.391-fake-justification-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.391-fake-justification-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/fake_justification_adversarial_test_8a2bcf80/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/fake_justification_adversarial_test_8a2bcf80.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/fake_justification_adversarial_test_8a2bcf80.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_fake_justification_adversarial_test_8a2bcf80.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.392-policy-denied-despite-justification-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.392-policy-denied-despite-justification-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_denied_despite_justification_test_41a05900/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/policy_denied_despite_justification_test_41a05900.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/policy_denied_despite_justification_test_41a05900.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_policy_denied_despite_justification_test_41a05900.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.393-gordon-approves-but-policy-denies-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.393-gordon-approves-but-policy-denies-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_approves_but_policy_denies_test_eafdd709/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_approves_but_policy_denies_test_eafdd709.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/gordon_approves_but_policy_denies_test_eafdd709.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_gordon_approves_but_policy_denies_test_eafdd709.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.394-bitnet-suggests-shell-but-typed-path-rejects-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.394-bitnet-suggests-shell-but-typed-path-rejects-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/bitnet_suggests_shell_but_typed_path_rejects_test_944082bb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/bitnet_suggests_shell_but_typed_path_rejects_test_944082bb.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/bitnet_suggests_shell_but_typed_path_rejects_test_944082bb.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_bitnet_suggests_shell_but_typed_path_rejects_test_944082bb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.395-prompt-injection-from-log-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.395-prompt-injection-from-log-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/prompt_injection_from_log_test_f9f9821d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/prompt_injection_from_log_test_f9f9821d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/prompt_injection_from_log_test_f9f9821d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_prompt_injection_from_log_test_f9f9821d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.396-prompt-injection-from-readme-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.396-prompt-injection-from-readme-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/prompt_injection_from_readme_test_b5bcd8c3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/prompt_injection_from_readme_test_b5bcd8c3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/prompt_injection_from_readme_test_b5bcd8c3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_prompt_injection_from_readme_test_b5bcd8c3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.397-prompt-injection-from-process-output-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.397-prompt-injection-from-process-output-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/prompt_injection_from_process_output_test_750613b0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/prompt_injection_from_process_output_test_750613b0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/prompt_injection_from_process_output_test_750613b0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_prompt_injection_from_process_output_test_750613b0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.398-stale-context-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.398-stale-context-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/stale_context_adversarial_test_c7da77bd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/stale_context_adversarial_test_c7da77bd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/stale_context_adversarial_test_c7da77bd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_stale_context_adversarial_test_c7da77bd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.399-ambiguous-referent-adversarial-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.399-ambiguous-referent-adversarial-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/ambiguous_referent_adversarial_test_82723702/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/ambiguous_referent_adversarial_test_82723702.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/ambiguous_referent_adversarial_test_82723702.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_ambiguous_referent_adversarial_test_82723702.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.400-changed-state-after-confirmation-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.400-changed-state-after-confirmation-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/changed_state_after_confirmation_test_d6463505/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/changed_state_after_confirmation_test_d6463505.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/changed_state_after_confirmation_test_d6463505.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_changed_state_after_confirmation_test_d6463505.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.401-changed-plan-after-confirmation-test`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.401-changed-plan-after-confirmation-test.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/changed_plan_after_confirmation_test_60ec562f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/changed_plan_after_confirmation_test_60ec562f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/changed_plan_after_confirmation_test_60ec562f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_changed_plan_after_confirmation_test_60ec562f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.402-semantic-provider-compromise-simulation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.402-semantic-provider-compromise-simulation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_provider_compromise_simulation_a4072690/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_compromise_simulation_a4072690.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_compromise_simulation_a4072690.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_semantic_provider_compromise_simulation_a4072690.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.403-gordon-compromise-simulation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.403-gordon-compromise-simulation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_compromise_simulation_2bcb78f4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_compromise_simulation_2bcb78f4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/gordon_compromise_simulation_2bcb78f4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_gordon_compromise_simulation_2bcb78f4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.404-provider-outage-tests`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.404-provider-outage-tests.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/provider_outage_tests_3e49a8c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/provider_outage_tests_3e49a8c5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/provider_outage_tests_3e49a8c5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_provider_outage_tests_3e49a8c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.405-resource-exhaustion-tests`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.405-resource-exhaustion-tests.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/resource_exhaustion_tests_4d84dab5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/resource_exhaustion_tests_4d84dab5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/resource_exhaustion_tests_4d84dab5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_resource_exhaustion_tests_4d84dab5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.406-concurrency-tests`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.406-concurrency-tests.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/concurrency_tests_a77b7dc3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/concurrency_tests_a77b7dc3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/concurrency_tests_a77b7dc3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_concurrency_tests_a77b7dc3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.407-crash-restart-tests`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.407-crash-restart-tests.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/crash_restart_tests_97c6746d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/crash_restart_tests_97c6746d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/crash_restart_tests_97c6746d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_crash_restart_tests_97c6746d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.408-end-to-end-read-only-ask-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.408-end-to-end-read-only-ask-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_read_only_ask_scenario_281ae6db/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_read_only_ask_scenario_281ae6db.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_read_only_ask_scenario_281ae6db.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_read_only_ask_scenario_281ae6db.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.409-end-to-end-task-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.409-end-to-end-task-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_task_scenario_8e74b483/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_task_scenario_8e74b483.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_task_scenario_8e74b483.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_task_scenario_8e74b483.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.410-end-to-end-safe-action-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.410-end-to-end-safe-action-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_safe_action_scenario_76ddedd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_safe_action_scenario_76ddedd4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_safe_action_scenario_76ddedd4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_safe_action_scenario_76ddedd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.411-end-to-end-clarification-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.411-end-to-end-clarification-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_clarification_scenario_084da1c5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_clarification_scenario_084da1c5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_clarification_scenario_084da1c5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_clarification_scenario_084da1c5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.412-end-to-end-justification-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.412-end-to-end-justification-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_justification_scenario_09ef628a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_justification_scenario_09ef628a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_justification_scenario_09ef628a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_justification_scenario_09ef628a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.413-end-to-end-gordon-consultation-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.413-end-to-end-gordon-consultation-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_gordon_consultation_scenario_4d86e2fa/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_gordon_consultation_scenario_4d86e2fa.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_gordon_consultation_scenario_4d86e2fa.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_gordon_consultation_scenario_4d86e2fa.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.414-end-to-end-deny-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.414-end-to-end-deny-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_deny_scenario_5578ef29/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_deny_scenario_5578ef29.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_deny_scenario_5578ef29.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_deny_scenario_5578ef29.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.415-end-to-end-phase-45-execution-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.415-end-to-end-phase-45-execution-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_phase_45_execution_scenario_0a2cc70d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/execution/end_to_end_phase_45_execution_scenario_0a2cc70d.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/execution/end_to_end_phase_45_execution_scenario_0a2cc70d.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/execution/test_end_to_end_phase_45_execution_scenario_0a2cc70d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.416-end-to-end-taskwarrior-scenario`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.416-end-to-end-taskwarrior-scenario.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/end_to_end_taskwarrior_scenario_7535dd58/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_taskwarrior_scenario_7535dd58.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/end_to_end_taskwarrior_scenario_7535dd58.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_end_to_end_taskwarrior_scenario_7535dd58.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.417-cli-completion-boundary`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.417-cli-completion-boundary.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/cli_completion_boundary_c202a4f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/cli_completion_boundary_c202a4f0.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/cli_completion_boundary_c202a4f0.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_cli_completion_boundary_c202a4f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.418-man-page`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.418-man-page.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/man_page_87eb6db5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/man_page_87eb6db5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/man_page_87eb6db5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_man_page_87eb6db5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.419-help-text`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.419-help-text.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/help_text_005481ca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/help_text_005481ca.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/help_text_005481ca.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_help_text_005481ca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.420-operator-documentation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.420-operator-documentation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/operator_documentation_b511d687/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/operator_documentation_b511d687.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/operator_documentation_b511d687.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_operator_documentation_b511d687.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.421-security-documentation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.421-security-documentation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/security_documentation_b7c03198/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/security_documentation_b7c03198.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/security_documentation_b7c03198.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_security_documentation_b7c03198.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.422-policy-authoring-documentation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.422-policy-authoring-documentation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/policy_authoring_documentation_366b9345/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/security/policy_authoring_documentation_366b9345.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/security/policy_authoring_documentation_366b9345.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/security/test_policy_authoring_documentation_366b9345.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.423-semantic-provider-documentation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.423-semantic-provider-documentation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/semantic_provider_documentation_8f1e88ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_documentation_8f1e88ba.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/semantic_provider_documentation_8f1e88ba.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_semantic_provider_documentation_8f1e88ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.424-gordon-integration-documentation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.424-gordon-integration-documentation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/gordon_integration_documentation_48a39063/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/gordon_integration_documentation_48a39063.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/gordon_integration_documentation_48a39063.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_gordon_integration_documentation_48a39063.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.425-taskwarrior-integration-documentation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.425-taskwarrior-integration-documentation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/taskwarrior_integration_documentation_f0266703/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/taskwarrior_integration_documentation_f0266703.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/taskwarrior_integration_documentation_f0266703.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_taskwarrior_integration_documentation_f0266703.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.426-developer-documentation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.426-developer-documentation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/developer_documentation_3a4756e1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/developer_documentation_3a4756e1.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/developer_documentation_3a4756e1.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_developer_documentation_3a4756e1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.427-repository-source-tree-normalization`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.427-repository-source-tree-normalization.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/repository_source_tree_normalization_3098cea8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/repository_source_tree_normalization_3098cea8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/repository_source_tree_normalization_3098cea8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_repository_source_tree_normalization_3098cea8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.428-existing-nl-code-migration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.428-existing-nl-code-migration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/existing_nl_code_migration_2d24aaef/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/existing_nl_code_migration_2d24aaef.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/existing_nl_code_migration_2d24aaef.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_existing_nl_code_migration_2d24aaef.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.429-existing-semantic-command-code-migration`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.429-existing-semantic-command-code-migration.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/existing_semantic_command_code_migration_170ebeb5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/integration/existing_semantic_command_code_migration_170ebeb5.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/integration/existing_semantic_command_code_migration_170ebeb5.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/integration/test_existing_semantic_command_code_migration_170ebeb5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.430-duplicate-intent-parser-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.430-duplicate-intent-parser-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/duplicate_intent_parser_audit_24dc9885/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/duplicate_intent_parser_audit_24dc9885.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/duplicate_intent_parser_audit_24dc9885.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_duplicate_intent_parser_audit_24dc9885.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.431-duplicate-context-store-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.431-duplicate-context-store-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/duplicate_context_store_audit_ab8ea6da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/duplicate_context_store_audit_ab8ea6da.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/duplicate_context_store_audit_ab8ea6da.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_duplicate_context_store_audit_ab8ea6da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.432-duplicate-policy-path-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.432-duplicate-policy-path-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/duplicate_policy_path_audit_f2dc5de6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/duplicate_policy_path_audit_f2dc5de6.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/duplicate_policy_path_audit_f2dc5de6.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_duplicate_policy_path_audit_f2dc5de6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.433-direct-model-to-shell-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.433-direct-model-to-shell-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/direct_model_to_shell_audit_591f4458/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_model_to_shell_audit_591f4458.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_model_to_shell_audit_591f4458.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_direct_model_to_shell_audit_591f4458.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.434-direct-model-to-command-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.434-direct-model-to-command-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/direct_model_to_command_audit_1307f9a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_model_to_command_audit_1307f9a9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_model_to_command_audit_1307f9a9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_direct_model_to_command_audit_1307f9a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.435-direct-ask-to-shell-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.435-direct-ask-to-shell-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/direct_ask_to_shell_audit_e4feed2b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_ask_to_shell_audit_e4feed2b.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_ask_to_shell_audit_e4feed2b.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_direct_ask_to_shell_audit_e4feed2b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.436-direct-ask-to-privilege-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.436-direct-ask-to-privilege-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/direct_ask_to_privilege_audit_76a948da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_ask_to_privilege_audit_76a948da.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_ask_to_privilege_audit_76a948da.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_direct_ask_to_privilege_audit_76a948da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.437-direct-ask-to-domain-bypass-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.437-direct-ask-to-domain-bypass-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/direct_ask_to_domain_bypass_audit_9fbe7518/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_ask_to_domain_bypass_audit_9fbe7518.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/direct_ask_to_domain_bypass_audit_9fbe7518.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_direct_ask_to_domain_bypass_audit_9fbe7518.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.438-stale-python-control-ownership-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.438-stale-python-control-ownership-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/stale_python_control_ownership_audit_61a9227e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/stale_python_control_ownership_audit_61a9227e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/stale_python_control_ownership_audit_61a9227e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_stale_python_control_ownership_audit_61a9227e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.439-remaining-python-boundary-inventory`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.439-remaining-python-boundary-inventory.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/remaining_python_boundary_inventory_541e16bd/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/remaining_python_boundary_inventory_541e16bd.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/remaining_python_boundary_inventory_541e16bd.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_remaining_python_boundary_inventory_541e16bd.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.440-c-first-contract-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.440-c-first-contract-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/c_first_contract_audit_ec6c0b74/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/c_first_contract_audit_ec6c0b74.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/c_first_contract_audit_ec6c0b74.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_c_first_contract_audit_ec6c0b74.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.441-agents-md-ask-architecture-contract`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.441-agents-md-ask-architecture-contract.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/agents_md_ask_architecture_contract_c90584ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/agents_md_ask_architecture_contract_c90584ba.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/agents_md_ask_architecture_contract_c90584ba.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_agents_md_ask_architecture_contract_c90584ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.442-agents-md-semantic-no-authority-contract`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.442-agents-md-semantic-no-authority-contract.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/agents_md_semantic_no_authority_contract_f3869af4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/agents_md_semantic_no_authority_contract_f3869af4.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/agents_md_semantic_no_authority_contract_f3869af4.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_agents_md_semantic_no_authority_contract_f3869af4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.443-agents-md-contextual-legitimacy-contract`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.443-agents-md-contextual-legitimacy-contract.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/agents_md_contextual_legitimacy_contract_bcb3b5f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/contracts/agents_md_contextual_legitimacy_contract_bcb3b5f2.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/contracts/agents_md_contextual_legitimacy_contract_bcb3b5f2.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/contracts/test_agents_md_contextual_legitimacy_contract_bcb3b5f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.444-agents-md-untrusted-evidence-contract`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.444-agents-md-untrusted-evidence-contract.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/agents_md_untrusted_evidence_contract_568f281a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/agents_md_untrusted_evidence_contract_568f281a.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/agents_md_untrusted_evidence_contract_568f281a.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_agents_md_untrusted_evidence_contract_568f281a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.445-recursive-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.445-recursive-rediscovery-pass-one.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recursive_rediscovery_pass_one_d8f9c582/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/recursive_rediscovery_pass_one_d8f9c582.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/recursive_rediscovery_pass_one_d8f9c582.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_recursive_rediscovery_pass_one_d8f9c582.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.446-resolve-rediscovery-pass-one`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.446-resolve-rediscovery-pass-one.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/resolve_rediscovery_pass_one_c2cbba99/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/resolve_rediscovery_pass_one_c2cbba99.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/resolve_rediscovery_pass_one_c2cbba99.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_resolve_rediscovery_pass_one_c2cbba99.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.447-recursive-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.447-recursive-rediscovery-pass-two.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/recursive_rediscovery_pass_two_ed3d42d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/recursive_rediscovery_pass_two_ed3d42d9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/recursive_rediscovery_pass_two_ed3d42d9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_recursive_rediscovery_pass_two_ed3d42d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.448-resolve-rediscovery-pass-two`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.448-resolve-rediscovery-pass-two.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/resolve_rediscovery_pass_two_d5dfe77c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/resolve_rediscovery_pass_two_d5dfe77c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/resolve_rediscovery_pass_two_d5dfe77c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_resolve_rediscovery_pass_two_d5dfe77c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.449-adversarial-bypass-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.449-adversarial-bypass-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_bypass_audit_34d08be9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_bypass_audit_34d08be9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_bypass_audit_34d08be9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_bypass_audit_34d08be9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.450-adversarial-authority-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.450-adversarial-authority-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_authority_audit_77c0c7a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_authority_audit_77c0c7a8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_authority_audit_77c0c7a8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_authority_audit_77c0c7a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.451-adversarial-contextual-legitimacy-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.451-adversarial-contextual-legitimacy-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_contextual_legitimacy_audit_b58c6192/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_contextual_legitimacy_audit_b58c6192.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_contextual_legitimacy_audit_b58c6192.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_contextual_legitimacy_audit_b58c6192.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.452-adversarial-data-flow-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.452-adversarial-data-flow-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_data_flow_audit_c4760a2f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_data_flow_audit_c4760a2f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_data_flow_audit_c4760a2f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_data_flow_audit_c4760a2f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.453-adversarial-prompt-injection-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.453-adversarial-prompt-injection-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_prompt_injection_audit_d0dbc3b7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_prompt_injection_audit_d0dbc3b7.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_prompt_injection_audit_d0dbc3b7.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_prompt_injection_audit_d0dbc3b7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.454-adversarial-semantic-provider-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.454-adversarial-semantic-provider-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_semantic_provider_audit_c409102c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_semantic_provider_audit_c409102c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_semantic_provider_audit_c409102c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_semantic_provider_audit_c409102c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.455-adversarial-gordon-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.455-adversarial-gordon-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_gordon_audit_f7235b4f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_gordon_audit_f7235b4f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_gordon_audit_f7235b4f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_gordon_audit_f7235b4f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.456-adversarial-policy-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.456-adversarial-policy-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_policy_audit_7e1be4e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_policy_audit_7e1be4e3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_policy_audit_7e1be4e3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_policy_audit_7e1be4e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.457-adversarial-shell-authority-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.457-adversarial-shell-authority-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/adversarial_shell_authority_audit_ba891a04/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_shell_authority_audit_ba891a04.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/adversarial_shell_authority_audit_ba891a04.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_adversarial_shell_authority_audit_ba891a04.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.458-final-native-build`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.458-final-native-build.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_native_build_db259a93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_native_build_db259a93.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_native_build_db259a93.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_final_native_build_db259a93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.459-final-unit-tests`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.459-final-unit-tests.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_unit_tests_b255eee9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/final_unit_tests_b255eee9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/final_unit_tests_b255eee9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_final_unit_tests_b255eee9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.460-final-integration-tests`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.460-final-integration-tests.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_integration_tests_81f72c32/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/final_integration_tests_81f72c32.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/final_integration_tests_81f72c32.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_final_integration_tests_81f72c32.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.461-final-adversarial-suite`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.461-final-adversarial-suite.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_adversarial_suite_f38a91ae/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_adversarial_suite_f38a91ae.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_adversarial_suite_f38a91ae.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_final_adversarial_suite_f38a91ae.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.462-final-end-to-end-suite`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.462-final-end-to-end-suite.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_end_to_end_suite_be96597c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_end_to_end_suite_be96597c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_end_to_end_suite_be96597c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_final_end_to_end_suite_be96597c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.463-final-performance-validation`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.463-final-performance-validation.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_performance_validation_450a06a8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_performance_validation_450a06a8.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_performance_validation_450a06a8.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_final_performance_validation_450a06a8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.464-final-secret-safety-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.464-final-secret-safety-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_secret_safety_audit_7090557f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/final_secret_safety_audit_7090557f.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/final_secret_safety_audit_7090557f.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_final_secret_safety_audit_7090557f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.465-final-source-tree-audit`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.465-final-source-tree-audit.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_source_tree_audit_785ae607/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/verification/final_source_tree_audit_785ae607.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/verification/final_source_tree_audit_785ae607.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/verification/test_final_source_tree_audit_785ae607.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.466-final-production-call-graph-trace`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.466-final-production-call-graph-trace.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_production_call_graph_trace_2915272e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/observability/final_production_call_graph_trace_2915272e.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/observability/final_production_call_graph_trace_2915272e.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/observability/test_final_production_call_graph_trace_2915272e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.467-final-authority-graph`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.467-final-authority-graph.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_authority_graph_b4c2eac9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_authority_graph_b4c2eac9.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_authority_graph_b4c2eac9.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_final_authority_graph_b4c2eac9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.468-final-data-flow-graph`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.468-final-data-flow-graph.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_data_flow_graph_7113b9a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_data_flow_graph_7113b9a3.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_data_flow_graph_7113b9a3.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_final_data_flow_graph_7113b9a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.469-final-remaining-python-inventory`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.469-final-remaining-python-inventory.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_remaining_python_inventory_5b10656c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_remaining_python_inventory_5b10656c.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/final_remaining_python_inventory_5b10656c.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_final_remaining_python_inventory_5b10656c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.470-final-fixed-point-rediscovery`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.470-final-fixed-point-rediscovery.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/final_fixed_point_rediscovery_6bca61ba/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/resolution/final_fixed_point_rediscovery_6bca61ba.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/resolution/final_fixed_point_rediscovery_6bca61ba.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/resolution/test_final_fixed_point_rediscovery_6bca61ba.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `46.471-phase-46-closure-and-future-handoff`
- **Source:** `.phases/phases/phase-46-natural-language-operator-interface/prompts/46.471-phase-46-closure-and-future-handoff.md`
- **Structural package:** `src/operator/natural-language-operator-interface/subtask_packages/verification/closure_and_future_handoff_74b244ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/operator/natural-language-operator-interface/subtask_targets/requirements/closure_and_future_handoff_74b244ee.hpp`, `src/operator/natural-language-operator-interface/subtask_targets/requirements/closure_and_future_handoff_74b244ee.cpp`
- **Structural test target:** `tests/structural-closure/operator/natural-language-operator-interface/requirements/test_closure_and_future_handoff_74b244ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

