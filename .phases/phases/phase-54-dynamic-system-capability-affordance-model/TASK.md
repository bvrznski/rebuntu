# Phase 54 — Dynamic System Capability Affordance Model — Aggregate Implementation Task

> **PHASE_EXECUTION_CONTRACT:** `.phases/EXECUTION_CONTRACT.md`  
> **EXECUTION_MODE:** `complete-phase`  
> **SCOPE:** every source prompt/subtask belonging to this phase  
> **COMPLETION:** evidence-based, per-subtask; representative-subset completion is forbidden  
> Executing this `TASK.md` means executing the **entire implementable phase scope** under the canonical contract, then updating this ledger for every subtask.


> **MANDATORY:** Before doing any work for this phase, read `.phases/AGENTS.md` completely. This `TASK.md` does not replace the source prompts. After every implementation pass affecting this phase, update this file with verified implementation and test evidence.

## Source specification
- Phase directory: `.phases/phases/phase-54-dynamic-system-capability-affordance-model/`
- Primary prompt location: `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/`
- Prompt/specification Markdown files currently present: **168**
- Architecture/support material, when present, is inside the same phase directory.

## How to execute this phase
1. Read `.phases/AGENTS.md`.
2. Read this task and then **all 168 Markdown specification files** in this phase (including architecture/support documents).
3. Convert prompt statements into an explicit requirement checklist; reconcile duplicates and later amendments rather than implementing them twice.
4. Inspect canonical `src/`, tests, CMake/build integration and callers for existing implementations.
5. Map each requirement to the canonical architecture. Do not create `src/phase_54` or a second subsystem.
6. Identify the native Linux authority for every OS-facing responsibility. Keep the provider narrow; place Rebuntu-specific semantics above it.
7. Prefer morphing/merging existing code over replacement. Preserve working behavior while migrating callers.
8. Implement missing behavior, integrate it, and add/extend tests for normal, failure, verification and recovery paths as applicable.
9. Run the narrow tests first, then the broadest build/test suite practical for the change. Record only results actually observed.
10. Update this `TASK.md`: depth, implemented/partial/missing items, evidence paths, test results, risks and update log. Update other phase tasks if the change crosses phase boundaries.

## Requirement cues from the phase specification
These headings are navigation cues, **not a substitute for reading the prompts**:
- Rebuntu Phase 54 — Dynamic System Capability & Affordance Model — FULL 2000+ LINE PROMPTS
- Rebuntu — Phase 54.26: Affordance ontology
- Mission
- Non-negotiable invariants
- Exhaustive repository discovery
- Execution stage 1: Repository discovery
- Repository discovery task matrix
- Execution stage 2: Concept normalization
- Concept normalization task matrix
- Execution stage 3: Ownership design
- Ownership design task matrix
- Execution stage 4: Contract implementation

## Structural skeleton / canonical destination
- Canonical skeleton: `src/semantics/dynamic-system-capability-affordance-model/`
- Structural files: `src/semantics/dynamic-system-capability-affordance-model/component.hpp`, `src/semantics/dynamic-system-capability-affordance-model/component.cpp`, `src/semantics/dynamic-system-capability-affordance-model/IMPLEMENTATION.json`
- **Status meaning:** structural coverage only; this is not behavioral implementation evidence.
- When implementing this phase, deepen/morph this canonical component or the already-existing canonical implementation; do not create a phase-numbered runtime subtree.

## Current implementation assessment
- **Overall status:** SKELETON
- **Implementation depth:** **2/5**
- **Assessment method:** conservative repository evidence scan. This is an initial ledger baseline and MUST be corrected by an agent after reading the complete prompts and inspecting behavior. Automatic matching never establishes phase completion.

### Existing implementation evidence
- No implementation evidence was matched automatically; inspect `src/` before concluding that the requirement is absent.

### Existing test evidence
- `tests/native/test_capability_state.cpp`

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

- Structural skeleton materialized at `src/semantics/dynamic-system-capability-affordance-model/`; this raises structural coverage only and does not claim prompt behavior.

## Inferred implementation targets — TREE DEEPENING I

These targets were inferred from this phase's aggregate task/specification cues to deepen the canonical tree. They are **structural targets, not completion evidence**. Before implementing any of them, read the source prompts and verify ownership against existing code.

- `src/semantics/dynamic-system-capability-affordance-model/model/`
- `src/semantics/dynamic-system-capability-affordance-model/contracts/`
- `src/semantics/dynamic-system-capability-affordance-model/integration/`
- `src/semantics/dynamic-system-capability-affordance-model/verification/`
- `src/semantics/dynamic-system-capability-affordance-model/lifecycle/`
- `src/semantics/dynamic-system-capability-affordance-model/state/`
- `src/semantics/dynamic-system-capability-affordance-model/execution/`
- `src/semantics/dynamic-system-capability-affordance-model/transactions/`
- `src/semantics/dynamic-system-capability-affordance-model/events/`
- `src/semantics/dynamic-system-capability-affordance-model/scheduling/`
- `src/semantics/dynamic-system-capability-affordance-model/recovery/`
- `src/semantics/dynamic-system-capability-affordance-model/principals/`
- `src/semantics/dynamic-system-capability-affordance-model/groups/`
- `src/semantics/dynamic-system-capability-affordance-model/roles/`
- `src/semantics/dynamic-system-capability-affordance-model/resolution/`
- `src/semantics/dynamic-system-capability-affordance-model/authorization/`
- `src/semantics/dynamic-system-capability-affordance-model/credentials/`
- `src/semantics/dynamic-system-capability-affordance-model/policy/`



## TREE DEEPENING II + SATURATION

This pass deepened inferred implementation targets into finer responsibility trees. These directories are **structural targets, not implementation evidence**. Before implementing any of them, read `.phases/AGENTS.md`, this TASK, and this phase's source prompts.

Shared executable infrastructure added in this pass:
- `src/core/state/state_machine.hpp` — explicit guarded state transitions.
- `src/core/evidence/evidence_store.hpp` — provenance-bearing evidence records.
- `src/core/verification/verification_report.hpp` — invariant findings and convergence result.
- `src/core/transactions/journal.hpp` — transaction stage journal with terminal-state protection.
- `tests/rebuntu/test_saturation_tree_ii.cpp` — strict C++20 verification of the shared primitives.

The shared infrastructure does **not** by itself increase this phase's implementation-depth score. Raise the score only when phase-specific prompt requirements are implemented, integrated and evidenced here. After every implementation pass, update this ledger.

## DOMAIN CONTROL SPINE INTEGRATION I

Implementation pass: services/processes/storage → shared reconciliation pipeline.

Implemented evidence:
- `src/control/reconciliation/bindings/domain_bindings.hpp`
- `src/control/reconciliation/bindings/domain_bindings.cpp`
- `src/control/reconciliation/pipeline/pipeline.hpp`
- `src/control/reconciliation/pipeline/pipeline.cpp`
- `tests/rebuntu/test_domain_pipeline_bindings.cpp`

Behavior now exercised through one common control path:
- authoritative domain observation through typed Linux providers;
- domain-specific plan synthesis;
- policy authorization boundary;
- typed `NativeOperation` execution;
- re-observation and convergence verification;
- service/systemd, process/procfs, and storage/filesystem bindings;
- process state is normalized semantically while retaining `raw_state`, avoiding leakage of procfs single-letter state into desired-state semantics.

Verification:
- `DOMAIN_PIPELINE_BINDINGS_PASS` with C++20 and `-Wall -Wextra -Wpedantic -Werror`.
- Existing process reconciliation regression test remains passing.

Remaining work:
- Do not treat this shared spine as completion of this phase. Read all phase prompts and implement phase-specific requirements.
- Extend policy from the test allow-policy to real security/policy decisions where required.
- Add transaction/recovery integration around domain mutations and richer failure evidence.
- Add further domain bindings only through typed native providers; never reproduce Linux mechanics.

Ledger rule: this section is implementation evidence, not an automatic maturity upgrade. Re-evaluate depth against the phase prompts before changing its score.


## MASS IMPLEMENTATION PASS — DOMAIN SEMANTICS + SYNTHESIS\n\nImplemented and verified in this pass:\n- canonical domain semantic model: stable identity, native authority/provenance, resources, relationships/topology, capabilities, requirements, desired state, operations and health;\n- concrete profiles/models for services, processes, storage, networking, software, configuration, identity and accelerators;\n- semantic projection adapter for reconciliation observations;\n- capability-aware typed operation synthesis;\n- requirement resolution and health aggregation;\n- tests: `test_domain_semantic_models.cpp`, `test_semantic_projection.cpp`, `test_domain_synthesis.cpp`, compiled with C++20 + `-Wall -Wextra -Wpedantic -Werror`.\n\nImplementation depth note: this is real reusable behavior and integration evidence, but does NOT by itself complete this phase. Phase-specific prompts, provider-specific execution, failure paths and E2E acceptance criteria remain authoritative. Native Linux mechanisms remain the source of truth.\n


## MASS IMPLEMENTATION II recovery + MASS IMPLEMENTATION III / SATURATION — 2026-09-23

### Verified implementation evidence
- `src/domains/common/capabilities/resolver.hpp`: deterministic capability/affordance resolution with contextual constraints and explicit blocker reasons.
- `src/domains/common/desired_state/differ.hpp`: typed desired-vs-observed attribute delta generation.
- `src/domains/common/topology/analyzer.hpp`: deterministic dependency ordering, dangling-edge reporting and dependency-cycle detection.
- `src/domains/common/health/evaluator.hpp`: evidence-backed healthy/degraded/failed/unknown aggregation.
- `src/domains/common/operations/planner.hpp`: diff-to-typed-native-operation synthesis gated by afforded verbs.
- `src/domains/common/reconciliation/domain_reconciler.hpp`: observe -> plan -> execute -> authoritative re-observe -> verify loop, including operation failure and compensating rollback callback.
- `src/domains/common/saturation.hpp`: domain-specific semantics/rules for services, processes, storage, networking, software, configuration, identity and accelerators. Native authorities are systemd, procfs/kernel, filesystems, Netlink, native package manager, native filesystem owner, NSS/PAM, and driver/sysfs respectively.
- `src/domains/{services,processes,storage,networking,software,configuration,identity,accelerators}/observation/translator.hpp`: native observation -> domain semantic model translation with provenance-aware health signals.
- `src/domains/{services,processes,storage,networking,software,configuration,identity,accelerators}/reconciliation/semantic_reconciler.hpp`: domain-specific reconciler construction over the shared semantic spine; no replacement Linux mechanics.

### Executed test evidence
- `tests/rebuntu/test_mass_implementation_ii_iii.cpp` compiled with `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -I src` and executed successfully. Observed markers: `CAPABILITY_RESOLVER_PASS`, `DESIRED_STATE_DIFF_PASS`, `TOPOLOGY_ANALYZER_PASS`, `HEALTH_EVALUATOR_PASS`, `OPERATION_PLANNER_PASS`, `DOMAIN_RECONCILER_PASS`, `DOMAIN_SATURATION_8_PASS`, `DEPENDENCY_CYCLE_PASS`, `ROLLBACK_PATH_PASS`.
- Header-integration TU covering all eight new domain reconcilers and translators compiled successfully with the same strict warning flags.
- Existing `tests/rebuntu/test_domain_synthesis.cpp` -> `DOMAIN_SYNTHESIS_PASS`.
- Existing `tests/rebuntu/test_domain_semantic_models.cpp` -> `DOMAIN_SEMANTIC_MODELS_PASS`.
- A standalone compile of `test_domain_pipeline_bindings.cpp` was not counted as PASS because it requires its implementation translation units at link time; the attempted one-file link produced unresolved symbols.

### Remaining implementation plan / depth constraint
This pass materially deepens shared domain semantics and all eight domain surfaces, but it does **not** make this phase complete. Full policy/security authorization, stale-evidence invalidation, provider-specific checkpoint construction, durable transaction journaling, richer per-domain rollback inverses, cross-domain orchestration/replanning, and complete prompt-by-prompt acceptance coverage remain. Existing maturity is therefore not promoted to 5/5 by this pass. Where the aggregate ledger was previously 0/5 due to skeleton-only evidence, this pass justifies at least **2/5 (partial concrete implementation)** for the requirements touched here; broader phase maturity must remain conservative until all prompt requirements are mapped and verified.

### Native Authority compliance
The new code performs Rebuntu-owned semantic evaluation, diffing, planning, health assessment, verification and reconciliation orchestration only. Actual machine mutation remains delegated through typed `core::NativeOperation` provider calls; no systemd/procfs/Netlink/filesystem/package/NSS/PAM/driver mechanism is reimplemented.


## MASS IMPLEMENTATION XVII / PHASE-54 CAPABILITY-AFFORDANCE SATURATION — 2026-09-23

### Concrete implementation evidence
- `src/semantics/affordances/model.hpp` now defines executable capability/affordance semantics rather than structural descriptors: tri-state truth, availability/degradation/UNKNOWN, evidence freshness/generation/trust, requirements, prerequisites, blockers, explicit authorization result and evaluation context.
- `src/semantics/affordances/evaluator.hpp` implements deterministic evaluation of target applicability, advertised verbs, mandatory requirements, prerequisite alternatives, evidence freshness/provenance, degraded/unknown provider behavior and the explicit `capability != permission` boundary. It also implements pre-execution generation revalidation and a bounded prerequisite graph with cycle detection/transitive missing discovery.
- `src/semantics/affordances/registry.hpp` implements bounded dynamic advertisement/query plus authority/generation invalidation. Stale entries are not returned as current affordances.
- `src/semantics/affordances/explanation.hpp` implements deterministic machine-derived why-not rendering from blocker evidence; no LLM is treated as authority.
- `tests/rebuntu/test_phase54_capability_affordance_saturation.cpp` exercises success, policy denial, stale evidence, pre-execution stale-result rejection, prerequisite cycles, registry invalidation and why-not explanations.

### Executed strict test evidence
Compiled and executed with `g++ -std=c++20 -Wall -Wextra -Wpedantic -Werror -Isrc`.
Observed markers:
- `AFFORDANCE_EXECUTABLE_PASS`
- `CAPABILITY_NOT_PERMISSION_PASS`
- `STALE_EVIDENCE_FAIL_CLOSED_PASS`
- `PRE_EXECUTION_REVALIDATION_PASS`
- `PREREQUISITE_CYCLE_PASS`
- `REGISTRY_INVALIDATION_PASS`
- `WHY_NOT_EXPLANATION_PASS`

Regression TUs `test_mass_implementation_ii_iii.cpp`, `test_saturation_xi.cpp`, `test_saturation_xii.cpp`, `test_saturation_xiii.cpp`, and `test_saturation_xiv.cpp` were also rebuilt and executed under the same strict warning policy; all emitted their previously recorded PASS markers.

### Native Authority / security compliance
Capability evidence remains observational metadata supplied by typed/native providers. The evaluator cannot execute Linux operations and deliberately cannot infer authorization from capability, availability, feasibility, context, evidence trust, or provider identity. `authorized_verbs` is an external security-policy decision supplied to the evaluation context. Generation mismatch and stale evidence fail closed before execution.

### Depth decision
Depth is raised from **1/5 to 2/5** because Phase 54 now has phase-specific concrete behavior and strict tests, not merely shared infrastructure. It is **not 3/5 yet**: distributed federation/trust, resource reservation/contention, temporal scheduling, full event-driven invalidation wiring, CLI/GUI query surfaces, associated-system integration, full provider population, adversarial matrix, and prompt-by-prompt closure remain incomplete.

### Remaining implementation plan
1. Bind invalidation to actual observation/timeline/topology/policy/security/resource/service events.
2. Add distributed advertisement expiry/trust boundaries without converting remote claims into local authority.
3. Integrate resource sufficiency/contention and temporal requirements with existing planning/control contracts.
4. Wire capability/affordance/why-not queries into CLI/operator/GUI surfaces.
5. Add adversarial tests for spoofing, target substitution, policy/security bypass, graph explosion and distributed trust.
6. Complete prompt-by-prompt acceptance mapping before considering 3/5+.

## Subtask Coverage Ledger
> This inventory is executable scope under `.phases/EXECUTION_CONTRACT.md`. Every entry MUST be individually inspected and updated with evidence during complete-phase execution. `UNCLASSIFIED` means no per-subtask evidence determination has yet been recorded; it is not implementation evidence.

### `54.0-rebuntu-phase-54-0-phase-bootstrap-and-capability-topology-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.0-rebuntu-phase-54-0-phase-bootstrap-and-capability-topology-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_bootstrap_and_capability_topology_audit_f7c1be17/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/phase_bootstrap_and_capability_topology_audit_f7c1be17.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/phase_bootstrap_and_capability_topology_audit_f7c1be17.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_phase_bootstrap_and_capability_topology_audit_f7c1be17.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.1-rebuntu-phase-54-1-capability-ontology`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.1-rebuntu-phase-54-1-capability-ontology.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_ontology_0fba2dbc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/capability_ontology_0fba2dbc.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/capability_ontology_0fba2dbc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/observability/test_capability_ontology_0fba2dbc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.10-rebuntu-phase-54-10-requirement-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.10-rebuntu-phase-54-10-requirement-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/requirement_model_a5ef0eca/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/requirement_model_a5ef0eca.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/requirement_model_a5ef0eca.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_requirement_model_a5ef0eca.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.100-rebuntu-phase-54-100-natural-language-capability-questions`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.100-rebuntu-phase-54-100-natural-language-capability-questions.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/natural_language_capability_questions_30e4e29a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/natural_language_capability_questions_30e4e29a.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/natural_language_capability_questions_30e4e29a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_natural_language_capability_questions_30e4e29a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.101-rebuntu-phase-54-101-natural-language-why-not-questions`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.101-rebuntu-phase-54-101-natural-language-why-not-questions.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/natural_language_why_not_questions_f46cf82c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/natural_language_why_not_questions_f46cf82c.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/natural_language_why_not_questions_f46cf82c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_natural_language_why_not_questions_f46cf82c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.102-rebuntu-phase-54-102-capability-search-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.102-rebuntu-phase-54-102-capability-search-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_search_integration_f1ebf4e2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/capability_search_integration_f1ebf4e2.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/capability_search_integration_f1ebf4e2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_capability_search_integration_f1ebf4e2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.103-rebuntu-phase-54-103-capability-query-filtering`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.103-rebuntu-phase-54-103-capability-query-filtering.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_query_filtering_2133dda6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/capability_query_filtering_2133dda6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/capability_query_filtering_2133dda6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_capability_query_filtering_2133dda6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.104-rebuntu-phase-54-104-capability-query-ranking-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.104-rebuntu-phase-54-104-capability-query-ranking-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_query_ranking_boundary_8e72c86e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/capability_query_ranking_boundary_8e72c86e.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/capability_query_ranking_boundary_8e72c86e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_capability_query_ranking_boundary_8e72c86e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.105-rebuntu-phase-54-105-semantic-candidate-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.105-rebuntu-phase-54-105-semantic-candidate-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/semantic_candidate_boundary_a8125256/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/semantic_candidate_boundary_a8125256.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/semantic_candidate_boundary_a8125256.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_semantic_candidate_boundary_a8125256.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.106-rebuntu-phase-54-106-model-assisted-explanation-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.106-rebuntu-phase-54-106-model-assisted-explanation-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/model_assisted_explanation_boundary_738af569/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/model_assisted_explanation_boundary_738af569.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/model_assisted_explanation_boundary_738af569.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_model_assisted_explanation_boundary_738af569.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.107-rebuntu-phase-54-107-data-to-control-capability-gate`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.107-rebuntu-phase-54-107-data-to-control-capability-gate.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/data_to_control_capability_gate_82f5b7a3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/data_to_control_capability_gate_82f5b7a3.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/data_to_control_capability_gate_82f5b7a3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_data_to_control_capability_gate_82f5b7a3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.108-rebuntu-phase-54-108-affordance-is-not-authorization-enforcement`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.108-rebuntu-phase-54-108-affordance-is-not-authorization-enforcement.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_is_not_authorization_enforcement_e29f9899/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/affordance_is_not_authorization_enforcement_e29f9899.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/affordance_is_not_authorization_enforcement_e29f9899.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_affordance_is_not_authorization_enforcement_e29f9899.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.109-rebuntu-phase-54-109-capability-is-not-permission-enforcement`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.109-rebuntu-phase-54-109-capability-is-not-permission-enforcement.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_is_not_permission_enforcement_d305badc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/capability_is_not_permission_enforcement_d305badc.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/capability_is_not_permission_enforcement_d305badc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_capability_is_not_permission_enforcement_d305badc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.11-rebuntu-phase-54-11-precondition-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.11-rebuntu-phase-54-11-precondition-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/precondition_model_9f2cd918/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/precondition_model_9f2cd918.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/precondition_model_9f2cd918.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_precondition_model_9f2cd918.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.110-rebuntu-phase-54-110-availability-is-not-readiness-enforcement`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.110-rebuntu-phase-54-110-availability-is-not-readiness-enforcement.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/availability_is_not_readiness_enforcement_e856b34b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/availability_is_not_readiness_enforcement_e856b34b.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/availability_is_not_readiness_enforcement_e856b34b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_availability_is_not_readiness_enforcement_e856b34b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.111-rebuntu-phase-54-111-feasibility-is-not-authorization-enforcement`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.111-rebuntu-phase-54-111-feasibility-is-not-authorization-enforcement.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/feasibility_is_not_authorization_enforcement_5eca9c30/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/feasibility_is_not_authorization_enforcement_5eca9c30.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/feasibility_is_not_authorization_enforcement_5eca9c30.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_feasibility_is_not_authorization_enforcement_5eca9c30.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.112-rebuntu-phase-54-112-context-is-not-authority-enforcement`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.112-rebuntu-phase-54-112-context-is-not-authority-enforcement.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/context_is_not_authority_enforcement_972a00d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/context_is_not_authority_enforcement_972a00d5.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/context_is_not_authority_enforcement_972a00d5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_context_is_not_authority_enforcement_972a00d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.113-rebuntu-phase-54-113-trust-is-not-execution-authority-enforcement`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.113-rebuntu-phase-54-113-trust-is-not-execution-authority-enforcement.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/trust_is_not_execution_authority_enforcement_6cabfcf5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/trust_is_not_execution_authority_enforcement_6cabfcf5.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/trust_is_not_execution_authority_enforcement_6cabfcf5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_trust_is_not_execution_authority_enforcement_6cabfcf5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.114-rebuntu-phase-54-114-capability-evaluation-concurrency`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.114-rebuntu-phase-54-114-capability-evaluation-concurrency.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_evaluation_concurrency_f6ef3203/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_evaluation_concurrency_f6ef3203.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_evaluation_concurrency_f6ef3203.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_evaluation_concurrency_f6ef3203.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.115-rebuntu-phase-54-115-evaluation-deadlines-and-cancellation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.115-rebuntu-phase-54-115-evaluation-deadlines-and-cancellation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/evaluation_deadlines_and_cancellation_4a5881d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/evaluation_deadlines_and_cancellation_4a5881d9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/evaluation_deadlines_and_cancellation_4a5881d9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_evaluation_deadlines_and_cancellation_4a5881d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.116-rebuntu-phase-54-116-evaluation-resource-bounds`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.116-rebuntu-phase-54-116-evaluation-resource-bounds.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/evaluation_resource_bounds_0b1c8b19/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/evaluation_resource_bounds_0b1c8b19.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/evaluation_resource_bounds_0b1c8b19.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_evaluation_resource_bounds_0b1c8b19.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.117-rebuntu-phase-54-117-evaluation-memoization-safety`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.117-rebuntu-phase-54-117-evaluation-memoization-safety.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/evaluation_memoization_safety_983721e9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/evaluation_memoization_safety_983721e9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/evaluation_memoization_safety_983721e9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_evaluation_memoization_safety_983721e9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.118-rebuntu-phase-54-118-hotplug-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.118-rebuntu-phase-54-118-hotplug-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/hotplug_invalidation_026ff997/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/hotplug_invalidation_026ff997.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/hotplug_invalidation_026ff997.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_hotplug_invalidation_026ff997.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.119-rebuntu-phase-54-119-topology-change-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.119-rebuntu-phase-54-119-topology-change-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/topology_change_invalidation_991916ac/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/topology_change_invalidation_991916ac.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/topology_change_invalidation_991916ac.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/observability/test_topology_change_invalidation_991916ac.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.12-rebuntu-phase-54-12-postcondition-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.12-rebuntu-phase-54-12-postcondition-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/postcondition_model_68b04298/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/postcondition_model_68b04298.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/postcondition_model_68b04298.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_postcondition_model_68b04298.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.120-rebuntu-phase-54-120-policy-change-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.120-rebuntu-phase-54-120-policy-change-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/policy_change_invalidation_5ccccaab/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/policy_change_invalidation_5ccccaab.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/policy_change_invalidation_5ccccaab.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_policy_change_invalidation_5ccccaab.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.121-rebuntu-phase-54-121-security-label-change-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.121-rebuntu-phase-54-121-security-label-change-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/security_label_change_invalidation_884c77d9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/security_label_change_invalidation_884c77d9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/security_label_change_invalidation_884c77d9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_security_label_change_invalidation_884c77d9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.122-rebuntu-phase-54-122-resource-change-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.122-rebuntu-phase-54-122-resource-change-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/resource_change_invalidation_553f26ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_change_invalidation_553f26ee.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_change_invalidation_553f26ee.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_resource_change_invalidation_553f26ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.123-rebuntu-phase-54-123-service-state-change-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.123-rebuntu-phase-54-123-service-state-change-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/service_state_change_invalidation_aa928db3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/service_state_change_invalidation_aa928db3.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/service_state_change_invalidation_aa928db3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/lifecycle/test_service_state_change_invalidation_aa928db3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.124-rebuntu-phase-54-124-distributed-change-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.124-rebuntu-phase-54-124-distributed-change-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/distributed_change_invalidation_6dea4c9a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/distributed_change_invalidation_6dea4c9a.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/distributed_change_invalidation_6dea4c9a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_distributed_change_invalidation_6dea4c9a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.125-rebuntu-phase-54-125-stale-result-rejection`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.125-rebuntu-phase-54-125-stale-result-rejection.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/stale_result_rejection_03c7e1e8/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/stale_result_rejection_03c7e1e8.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/stale_result_rejection_03c7e1e8.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_stale_result_rejection_03c7e1e8.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.126-rebuntu-phase-54-126-toctou-protection-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.126-rebuntu-phase-54-126-toctou-protection-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/toctou_protection_boundary_6eea205a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/toctou_protection_boundary_6eea205a.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/toctou_protection_boundary_6eea205a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_toctou_protection_boundary_6eea205a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.127-rebuntu-phase-54-127-pre-execution-affordance-revalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.127-rebuntu-phase-54-127-pre-execution-affordance-revalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/pre_execution_affordance_revalidation_2f3762a9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/execution/pre_execution_affordance_revalidation_2f3762a9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/execution/pre_execution_affordance_revalidation_2f3762a9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/execution/test_pre_execution_affordance_revalidation_2f3762a9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.128-rebuntu-phase-54-128-post-execution-capability-refresh`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.128-rebuntu-phase-54-128-post-execution-capability-refresh.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/post_execution_capability_refresh_0749d7b4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/execution/post_execution_capability_refresh_0749d7b4.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/execution/post_execution_capability_refresh_0749d7b4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/execution/test_post_execution_capability_refresh_0749d7b4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.129-rebuntu-phase-54-129-failure-classification`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.129-rebuntu-phase-54-129-failure-classification.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/failure_classification_a326b87c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/failure_classification_a326b87c.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/failure_classification_a326b87c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_failure_classification_a326b87c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.13-rebuntu-phase-54-13-constraint-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.13-rebuntu-phase-54-13-constraint-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/constraint_model_0d2e1c98/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/constraint_model_0d2e1c98.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/constraint_model_0d2e1c98.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_constraint_model_0d2e1c98.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.130-rebuntu-phase-54-130-degraded-capability-behavior`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.130-rebuntu-phase-54-130-degraded-capability-behavior.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/degraded_capability_behavior_fcf4bab9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/degraded_capability_behavior_fcf4bab9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/degraded_capability_behavior_fcf4bab9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_degraded_capability_behavior_fcf4bab9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.131-rebuntu-phase-54-131-provider-failure-behavior`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.131-rebuntu-phase-54-131-provider-failure-behavior.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/provider_failure_behavior_472b72da/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/provider_failure_behavior_472b72da.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/provider_failure_behavior_472b72da.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_provider_failure_behavior_472b72da.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.132-rebuntu-phase-54-132-partial-evidence-behavior`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.132-rebuntu-phase-54-132-partial-evidence-behavior.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/partial_evidence_behavior_1c5d8763/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/partial_evidence_behavior_1c5d8763.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/partial_evidence_behavior_1c5d8763.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_partial_evidence_behavior_1c5d8763.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.133-rebuntu-phase-54-133-conflicting-evidence-behavior`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.133-rebuntu-phase-54-133-conflicting-evidence-behavior.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/conflicting_evidence_behavior_35382ecc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/conflicting_evidence_behavior_35382ecc.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/conflicting_evidence_behavior_35382ecc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_conflicting_evidence_behavior_35382ecc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.134-rebuntu-phase-54-134-capability-recovery-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.134-rebuntu-phase-54-134-capability-recovery-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_recovery_semantics_a8a970f0/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/recovery/capability_recovery_semantics_a8a970f0.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/recovery/capability_recovery_semantics_a8a970f0.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/recovery/test_capability_recovery_semantics_a8a970f0.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.135-rebuntu-phase-54-135-affordance-recovery-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.135-rebuntu-phase-54-135-affordance-recovery-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_recovery_semantics_40218ba6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/recovery/affordance_recovery_semantics_40218ba6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/recovery/affordance_recovery_semantics_40218ba6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/recovery/test_affordance_recovery_semantics_40218ba6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.136-rebuntu-phase-54-136-audit-and-event-emission`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.136-rebuntu-phase-54-136-audit-and-event-emission.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/audit_and_event_emission_02b80012/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/audit_and_event_emission_02b80012.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/audit_and_event_emission_02b80012.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_audit_and_event_emission_02b80012.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.137-rebuntu-phase-54-137-privacy-and-secret-safety-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.137-rebuntu-phase-54-137-privacy-and-secret-safety-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/privacy_and_secret_safety_audit_c47fabb6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/privacy_and_secret_safety_audit_c47fabb6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/privacy_and_secret_safety_audit_c47fabb6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_privacy_and_secret_safety_audit_c47fabb6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.138-rebuntu-phase-54-138-capability-spoofing-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.138-rebuntu-phase-54-138-capability-spoofing-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_spoofing_adversarial_audit_ec618a52/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/capability_spoofing_adversarial_audit_ec618a52.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/capability_spoofing_adversarial_audit_ec618a52.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_capability_spoofing_adversarial_audit_ec618a52.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.139-rebuntu-phase-54-139-target-substitution-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.139-rebuntu-phase-54-139-target-substitution-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/target_substitution_adversarial_audit_519d4246/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/target_substitution_adversarial_audit_519d4246.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/target_substitution_adversarial_audit_519d4246.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_target_substitution_adversarial_audit_519d4246.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.14-rebuntu-phase-54-14-blocker-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.14-rebuntu-phase-54-14-blocker-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/blocker_model_e45930bf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/blocker_model_e45930bf.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/blocker_model_e45930bf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_blocker_model_e45930bf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.140-rebuntu-phase-54-140-stale-affordance-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.140-rebuntu-phase-54-140-stale-affordance-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/stale_affordance_adversarial_audit_4dfc270f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/stale_affordance_adversarial_audit_4dfc270f.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/stale_affordance_adversarial_audit_4dfc270f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_stale_affordance_adversarial_audit_4dfc270f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.141-rebuntu-phase-54-141-policy-bypass-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.141-rebuntu-phase-54-141-policy-bypass-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/policy_bypass_adversarial_audit_91ee00ff/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/policy_bypass_adversarial_audit_91ee00ff.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/policy_bypass_adversarial_audit_91ee00ff.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_policy_bypass_adversarial_audit_91ee00ff.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.142-rebuntu-phase-54-142-security-bypass-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.142-rebuntu-phase-54-142-security-bypass-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/security_bypass_adversarial_audit_6cd53ea3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/security_bypass_adversarial_audit_6cd53ea3.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/security_bypass_adversarial_audit_6cd53ea3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_security_bypass_adversarial_audit_6cd53ea3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.143-rebuntu-phase-54-143-distributed-trust-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.143-rebuntu-phase-54-143-distributed-trust-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/distributed_trust_adversarial_audit_1b0f3032/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/distributed_trust_adversarial_audit_1b0f3032.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/distributed_trust_adversarial_audit_1b0f3032.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_distributed_trust_adversarial_audit_1b0f3032.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.144-rebuntu-phase-54-144-resource-race-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.144-rebuntu-phase-54-144-resource-race-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/resource_race_adversarial_audit_1ff24f4d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/resource_race_adversarial_audit_1ff24f4d.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/resource_race_adversarial_audit_1ff24f4d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_resource_race_adversarial_audit_1ff24f4d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.145-rebuntu-phase-54-145-prerequisite-cycle-adversarial-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.145-rebuntu-phase-54-145-prerequisite-cycle-adversarial-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_cycle_adversarial_audit_2462bfd1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/prerequisite_cycle_adversarial_audit_2462bfd1.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/prerequisite_cycle_adversarial_audit_2462bfd1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_prerequisite_cycle_adversarial_audit_2462bfd1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.146-rebuntu-phase-54-146-graph-explosion-and-boundedness-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.146-rebuntu-phase-54-146-graph-explosion-and-boundedness-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/graph_explosion_and_boundedness_audit_0476a0a1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/graph_explosion_and_boundedness_audit_0476a0a1.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/graph_explosion_and_boundedness_audit_0476a0a1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_graph_explosion_and_boundedness_audit_0476a0a1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.147-rebuntu-phase-54-147-capability-registry-boundedness-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.147-rebuntu-phase-54-147-capability-registry-boundedness-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_registry_boundedness_audit_e4d53ac7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/capability_registry_boundedness_audit_e4d53ac7.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/capability_registry_boundedness_audit_e4d53ac7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_capability_registry_boundedness_audit_e4d53ac7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.148-rebuntu-phase-54-148-evaluation-performance-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.148-rebuntu-phase-54-148-evaluation-performance-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/evaluation_performance_audit_ca650312/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/evaluation_performance_audit_ca650312.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/evaluation_performance_audit_ca650312.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_evaluation_performance_audit_ca650312.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.149-rebuntu-phase-54-149-python-authority-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.149-rebuntu-phase-54-149-python-authority-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/python_authority_audit_6816bd87/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/python_authority_audit_6816bd87.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/python_authority_audit_6816bd87.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_python_authority_audit_6816bd87.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.15-rebuntu-phase-54-15-dependency-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.15-rebuntu-phase-54-15-dependency-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/dependency_model_53f0516c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/dependency_model_53f0516c.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/dependency_model_53f0516c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_dependency_model_53f0516c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.150-rebuntu-phase-54-150-shell-authority-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.150-rebuntu-phase-54-150-shell-authority-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/shell_authority_audit_c6a183b1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/shell_authority_audit_c6a183b1.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/shell_authority_audit_c6a183b1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_shell_authority_audit_c6a183b1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.151-rebuntu-phase-54-151-duplicate-capability-model-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.151-rebuntu-phase-54-151-duplicate-capability-model-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/duplicate_capability_model_audit_780a3bb6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/duplicate_capability_model_audit_780a3bb6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/duplicate_capability_model_audit_780a3bb6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_duplicate_capability_model_audit_780a3bb6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.152-rebuntu-phase-54-152-build-and-runtime-reachability-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.152-rebuntu-phase-54-152-build-and-runtime-reachability-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/build_and_runtime_reachability_audit_7608d815/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/build_and_runtime_reachability_audit_7608d815.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/build_and_runtime_reachability_audit_7608d815.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_build_and_runtime_reachability_audit_7608d815.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.153-rebuntu-phase-54-153-integration-test-matrix`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.153-rebuntu-phase-54-153-integration-test-matrix.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/integration_test_matrix_a363b4e1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/integration_test_matrix_a363b4e1.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/integration_test_matrix_a363b4e1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_integration_test_matrix_a363b4e1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.154-rebuntu-phase-54-154-documentation-and-agents-synchronization`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.154-rebuntu-phase-54-154-documentation-and-agents-synchronization.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/documentation_and_agents_synchronization_657aca9d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/documentation_and_agents_synchronization_657aca9d.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/documentation_and_agents_synchronization_657aca9d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_documentation_and_agents_synchronization_657aca9d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.155-rebuntu-phase-54-155-independent-capability-rediscovery`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.155-rebuntu-phase-54-155-independent-capability-rediscovery.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/independent_capability_rediscovery_da0a6949/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/independent_capability_rediscovery_da0a6949.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/independent_capability_rediscovery_da0a6949.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_independent_capability_rediscovery_da0a6949.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.156-rebuntu-phase-54-156-independent-affordance-rediscovery`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.156-rebuntu-phase-54-156-independent-affordance-rediscovery.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/independent_affordance_rediscovery_fdedafd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/independent_affordance_rediscovery_fdedafd4.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/independent_affordance_rediscovery_fdedafd4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_independent_affordance_rediscovery_fdedafd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.157-rebuntu-phase-54-157-fixed-point-architecture-audit`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.157-rebuntu-phase-54-157-fixed-point-architecture-audit.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/fixed_point_architecture_audit_bc89359a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/fixed_point_architecture_audit_bc89359a.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/fixed_point_architecture_audit_bc89359a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_fixed_point_architecture_audit_bc89359a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.158-rebuntu-phase-54-158-phase-54-final-closure`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.158-rebuntu-phase-54-158-phase-54-final-closure.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_54_final_closure_48c87ab7/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/phase_54_final_closure_48c87ab7.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/phase_54_final_closure_48c87ab7.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_phase_54_final_closure_48c87ab7.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.16-rebuntu-phase-54-16-prerequisite-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.16-rebuntu-phase-54-16-prerequisite-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_model_775c6d39/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/prerequisite_model_775c6d39.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/prerequisite_model_775c6d39.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_prerequisite_model_775c6d39.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.17-rebuntu-phase-54-17-capability-composition`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.17-rebuntu-phase-54-17-capability-composition.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_composition_22e7192a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_composition_22e7192a.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_composition_22e7192a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_composition_22e7192a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.18-rebuntu-phase-54-18-capability-alternatives`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.18-rebuntu-phase-54-18-capability-alternatives.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_alternatives_c00dbc88/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_alternatives_c00dbc88.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_alternatives_c00dbc88.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_alternatives_c00dbc88.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.19-rebuntu-phase-54-19-provider-alternatives`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.19-rebuntu-phase-54-19-provider-alternatives.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/provider_alternatives_5e73bf31/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/provider_alternatives_5e73bf31.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/provider_alternatives_5e73bf31.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_provider_alternatives_5e73bf31.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.2-rebuntu-phase-54-2-capability-identity`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.2-rebuntu-phase-54-2-capability-identity.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_identity_2ff1b811/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_identity_2ff1b811.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_identity_2ff1b811.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_capability_identity_2ff1b811.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.20-rebuntu-phase-54-20-capability-degradation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.20-rebuntu-phase-54-20-capability-degradation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_degradation_e82a30be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_degradation_e82a30be.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_degradation_e82a30be.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_degradation_e82a30be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.21-rebuntu-phase-54-21-unknown-capability-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.21-rebuntu-phase-54-21-unknown-capability-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/unknown_capability_semantics_42724fe5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/unknown_capability_semantics_42724fe5.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/unknown_capability_semantics_42724fe5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_unknown_capability_semantics_42724fe5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.22-rebuntu-phase-54-22-capability-evidence-and-provenance`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.22-rebuntu-phase-54-22-capability-evidence-and-provenance.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_evidence_and_provenance_4413ac01/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/capability_evidence_and_provenance_4413ac01.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/capability_evidence_and_provenance_4413ac01.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_capability_evidence_and_provenance_4413ac01.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.23-rebuntu-phase-54-23-capability-freshness-and-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.23-rebuntu-phase-54-23-capability-freshness-and-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_freshness_and_invalidation_09999958/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_freshness_and_invalidation_09999958.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_freshness_and_invalidation_09999958.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_freshness_and_invalidation_09999958.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.24-rebuntu-phase-54-24-capability-snapshot-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.24-rebuntu-phase-54-24-capability-snapshot-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_snapshot_model_035e7125/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/persistence/capability_snapshot_model_035e7125.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/persistence/capability_snapshot_model_035e7125.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/persistence/test_capability_snapshot_model_035e7125.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.25-rebuntu-phase-54-25-dynamic-capability-registry-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.25-rebuntu-phase-54-25-dynamic-capability-registry-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/dynamic_capability_registry_boundary_d220f389/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/dynamic_capability_registry_boundary_d220f389.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/dynamic_capability_registry_boundary_d220f389.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_dynamic_capability_registry_boundary_d220f389.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.26-rebuntu-phase-54-26-affordance-ontology`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.26-rebuntu-phase-54-26-affordance-ontology.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_ontology_bcdd4dbf/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/affordance_ontology_bcdd4dbf.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/affordance_ontology_bcdd4dbf.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/observability/test_affordance_ontology_bcdd4dbf.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.27-rebuntu-phase-54-27-affordance-identity-and-scope`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.27-rebuntu-phase-54-27-affordance-identity-and-scope.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_identity_and_scope_4b902fb9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/affordance_identity_and_scope_4b902fb9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/affordance_identity_and_scope_4b902fb9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_affordance_identity_and_scope_4b902fb9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.28-rebuntu-phase-54-28-affordance-evaluation-request`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.28-rebuntu-phase-54-28-affordance-evaluation-request.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_evaluation_request_90e5b586/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_evaluation_request_90e5b586.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_evaluation_request_90e5b586.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_affordance_evaluation_request_90e5b586.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.29-rebuntu-phase-54-29-affordance-evaluation-result`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.29-rebuntu-phase-54-29-affordance-evaluation-result.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_evaluation_result_ad1c3bd4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_evaluation_result_ad1c3bd4.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_evaluation_result_ad1c3bd4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_affordance_evaluation_result_ad1c3bd4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.3-rebuntu-phase-54-3-capability-definition-contract`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.3-rebuntu-phase-54-3-capability-definition-contract.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_definition_contract_8cd9a067/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_definition_contract_8cd9a067.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_definition_contract_8cd9a067.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_capability_definition_contract_8cd9a067.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.30-rebuntu-phase-54-30-affordance-evaluator-architecture`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.30-rebuntu-phase-54-30-affordance-evaluator-architecture.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_evaluator_architecture_3d728d25/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_evaluator_architecture_3d728d25.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_evaluator_architecture_3d728d25.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_affordance_evaluator_architecture_3d728d25.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.31-rebuntu-phase-54-31-affordance-evidence-binding`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.31-rebuntu-phase-54-31-affordance-evidence-binding.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_evidence_binding_1fa9aa1a/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/affordance_evidence_binding_1fa9aa1a.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/affordance_evidence_binding_1fa9aa1a.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_affordance_evidence_binding_1fa9aa1a.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.32-rebuntu-phase-54-32-affordance-freshness`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.32-rebuntu-phase-54-32-affordance-freshness.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_freshness_1e24fba6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_freshness_1e24fba6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_freshness_1e24fba6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_affordance_freshness_1e24fba6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.33-rebuntu-phase-54-33-affordance-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.33-rebuntu-phase-54-33-affordance-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_invalidation_65c4705e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_invalidation_65c4705e.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_invalidation_65c4705e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_affordance_invalidation_65c4705e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.34-rebuntu-phase-54-34-affordance-caching-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.34-rebuntu-phase-54-34-affordance-caching-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_caching_boundary_531cfa17/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_caching_boundary_531cfa17.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/affordance_caching_boundary_531cfa17.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_affordance_caching_boundary_531cfa17.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.35-rebuntu-phase-54-35-target-state-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.35-rebuntu-phase-54-35-target-state-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/target_state_integration_cc93ce1b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/target_state_integration_cc93ce1b.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/target_state_integration_cc93ce1b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_target_state_integration_cc93ce1b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.36-rebuntu-phase-54-36-phase-5-observation-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.36-rebuntu-phase-54-36-phase-5-observation-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_5_observation_integration_e77d0187/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_5_observation_integration_e77d0187.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_5_observation_integration_e77d0187.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_5_observation_integration_e77d0187.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.37-rebuntu-phase-54-37-phase-39-timeline-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.37-rebuntu-phase-54-37-phase-39-timeline-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_39_timeline_integration_8d14eb3b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_39_timeline_integration_8d14eb3b.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_39_timeline_integration_8d14eb3b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_39_timeline_integration_8d14eb3b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.38-rebuntu-phase-54-38-phase-42-knowledge-graph-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.38-rebuntu-phase-54-38-phase-42-knowledge-graph-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_42_knowledge_graph_integration_bffceb41/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_42_knowledge_graph_integration_bffceb41.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_42_knowledge_graph_integration_bffceb41.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_42_knowledge_graph_integration_bffceb41.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.39-rebuntu-phase-54-39-phase-48-context-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.39-rebuntu-phase-54-39-phase-48-context-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_48_context_integration_b91f1f2e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_48_context_integration_b91f1f2e.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_48_context_integration_b91f1f2e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_48_context_integration_b91f1f2e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.4-rebuntu-phase-54-4-capability-instance-contract`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.4-rebuntu-phase-54-4-capability-instance-contract.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_instance_contract_eef29e49/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_instance_contract_eef29e49.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_instance_contract_eef29e49.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_capability_instance_contract_eef29e49.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.40-rebuntu-phase-54-40-phase-47-task-policy-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.40-rebuntu-phase-54-40-phase-47-task-policy-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_47_task_policy_integration_005d9b8b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/phase_47_task_policy_integration_005d9b8b.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/phase_47_task_policy_integration_005d9b8b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_phase_47_task_policy_integration_005d9b8b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.41-rebuntu-phase-54-41-phase-53-mandatory-security-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.41-rebuntu-phase-54-41-phase-53-mandatory-security-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_53_mandatory_security_integration_ab7bff17/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/phase_53_mandatory_security_integration_ab7bff17.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/phase_53_mandatory_security_integration_ab7bff17.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_phase_53_mandatory_security_integration_ab7bff17.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.42-rebuntu-phase-54-42-phase-50-platform-capability-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.42-rebuntu-phase-54-42-phase-50-platform-capability-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_50_platform_capability_integration_9adcb495/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_50_platform_capability_integration_9adcb495.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_50_platform_capability_integration_9adcb495.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_50_platform_capability_integration_9adcb495.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.43-rebuntu-phase-54-43-phase-30-resource-capacity-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.43-rebuntu-phase-54-43-phase-30-resource-capacity-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_30_resource_capacity_integration_56416bf6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_30_resource_capacity_integration_56416bf6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_30_resource_capacity_integration_56416bf6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_30_resource_capacity_integration_56416bf6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.44-rebuntu-phase-54-44-privilege-requirement-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.44-rebuntu-phase-54-44-privilege-requirement-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/privilege_requirement_integration_ee7c13ee/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/privilege_requirement_integration_ee7c13ee.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/privilege_requirement_integration_ee7c13ee.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_privilege_requirement_integration_ee7c13ee.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.45-rebuntu-phase-54-45-phase-45-control-plane-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.45-rebuntu-phase-54-45-phase-45-control-plane-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_45_control_plane_integration_dc1ae5c4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_45_control_plane_integration_dc1ae5c4.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_45_control_plane_integration_dc1ae5c4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_45_control_plane_integration_dc1ae5c4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.46-rebuntu-phase-54-46-phase-40-command-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.46-rebuntu-phase-54-46-phase-40-command-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_40_command_integration_c054e083/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_40_command_integration_c054e083.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_40_command_integration_c054e083.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_40_command_integration_c054e083.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.47-rebuntu-phase-54-47-phase-46-natural-language-operator-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.47-rebuntu-phase-54-47-phase-46-natural-language-operator-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_46_natural_language_operator_integration_25db873c/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_46_natural_language_operator_integration_25db873c.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_46_natural_language_operator_integration_25db873c.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_46_natural_language_operator_integration_25db873c.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.48-rebuntu-phase-54-48-phase-49-gui-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.48-rebuntu-phase-54-48-phase-49-gui-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_49_gui_integration_fea53b33/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_49_gui_integration_fea53b33.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_49_gui_integration_fea53b33.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_49_gui_integration_fea53b33.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.49-rebuntu-phase-54-49-phase-41-automation-workflow-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.49-rebuntu-phase-54-49-phase-41-automation-workflow-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_41_automation_workflow_integration_668b1c6b/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_41_automation_workflow_integration_668b1c6b.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_41_automation_workflow_integration_668b1c6b.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_41_automation_workflow_integration_668b1c6b.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.5-rebuntu-phase-54-5-capability-provider-binding`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.5-rebuntu-phase-54-5-capability-provider-binding.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_provider_binding_eb217ae6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/capability_provider_binding_eb217ae6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/capability_provider_binding_eb217ae6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_capability_provider_binding_eb217ae6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.50-rebuntu-phase-54-50-phase-51-distributed-capability-discovery`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.50-rebuntu-phase-54-50-phase-51-distributed-capability-discovery.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_51_distributed_capability_discovery_ca0f3066/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/phase_51_distributed_capability_discovery_ca0f3066.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/phase_51_distributed_capability_discovery_ca0f3066.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_phase_51_distributed_capability_discovery_ca0f3066.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.51-rebuntu-phase-54-51-phase-52-associated-system-capability-integration`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.51-rebuntu-phase-54-51-phase-52-associated-system-capability-integration.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/phase_52_associated_system_capability_integration_76b967be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_52_associated_system_capability_integration_76b967be.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/integration/phase_52_associated_system_capability_integration_76b967be.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/integration/test_phase_52_associated_system_capability_integration_76b967be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.52-rebuntu-phase-54-52-remote-capability-trust-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.52-rebuntu-phase-54-52-remote-capability-trust-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/remote_capability_trust_boundary_4bbb3372/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/remote_capability_trust_boundary_4bbb3372.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/remote_capability_trust_boundary_4bbb3372.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_remote_capability_trust_boundary_4bbb3372.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.53-rebuntu-phase-54-53-capability-advertisement-contract`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.53-rebuntu-phase-54-53-capability-advertisement-contract.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_advertisement_contract_45a4fd69/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_advertisement_contract_45a4fd69.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_advertisement_contract_45a4fd69.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_capability_advertisement_contract_45a4fd69.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.54-rebuntu-phase-54-54-capability-discovery-federation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.54-rebuntu-phase-54-54-capability-discovery-federation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_discovery_federation_2f7a36dc/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/capability_discovery_federation_2f7a36dc.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/capability_discovery_federation_2f7a36dc.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_capability_discovery_federation_2f7a36dc.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.55-rebuntu-phase-54-55-capability-provenance-across-nodes`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.55-rebuntu-phase-54-55-capability-provenance-across-nodes.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_provenance_across_nodes_0d64d8d1/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_provenance_across_nodes_0d64d8d1.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_provenance_across_nodes_0d64d8d1.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_provenance_across_nodes_0d64d8d1.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.56-rebuntu-phase-54-56-remote-freshness-and-expiry`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.56-rebuntu-phase-54-56-remote-freshness-and-expiry.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/remote_freshness_and_expiry_cd6c656e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/remote_freshness_and_expiry_cd6c656e.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/remote_freshness_and_expiry_cd6c656e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_remote_freshness_and_expiry_cd6c656e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.57-rebuntu-phase-54-57-remote-unknown-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.57-rebuntu-phase-54-57-remote-unknown-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/remote_unknown_semantics_e3deb6a4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/remote_unknown_semantics_e3deb6a4.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/remote_unknown_semantics_e3deb6a4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_remote_unknown_semantics_e3deb6a4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.58-rebuntu-phase-54-58-resource-requirement-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.58-rebuntu-phase-54-58-resource-requirement-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/resource_requirement_model_abd98159/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/resource_requirement_model_abd98159.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/resource_requirement_model_abd98159.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_resource_requirement_model_abd98159.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.59-rebuntu-phase-54-59-resource-sufficiency-evaluation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.59-rebuntu-phase-54-59-resource-sufficiency-evaluation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/resource_sufficiency_evaluation_17b12a69/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_sufficiency_evaluation_17b12a69.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_sufficiency_evaluation_17b12a69.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_resource_sufficiency_evaluation_17b12a69.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.6-rebuntu-phase-54-6-capability-availability-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.6-rebuntu-phase-54-6-capability-availability-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_availability_semantics_c6bf5852/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_availability_semantics_c6bf5852.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_availability_semantics_c6bf5852.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_availability_semantics_c6bf5852.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.60-rebuntu-phase-54-60-resource-contention-blocker`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.60-rebuntu-phase-54-60-resource-contention-blocker.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/resource_contention_blocker_57396bf9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_contention_blocker_57396bf9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_contention_blocker_57396bf9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_resource_contention_blocker_57396bf9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.61-rebuntu-phase-54-61-resource-reservation-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.61-rebuntu-phase-54-61-resource-reservation-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/resource_reservation_boundary_30d559ce/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_reservation_boundary_30d559ce.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/resource_reservation_boundary_30d559ce.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_resource_reservation_boundary_30d559ce.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.62-rebuntu-phase-54-62-temporal-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.62-rebuntu-phase-54-62-temporal-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/temporal_requirements_f753838f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/temporal_requirements_f753838f.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/temporal_requirements_f753838f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_temporal_requirements_f753838f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.63-rebuntu-phase-54-63-schedule-dependent-affordances`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.63-rebuntu-phase-54-63-schedule-dependent-affordances.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/schedule_dependent_affordances_764c204e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/schedule_dependent_affordances_764c204e.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/schedule_dependent_affordances_764c204e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_schedule_dependent_affordances_764c204e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.64-rebuntu-phase-54-64-service-state-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.64-rebuntu-phase-54-64-service-state-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/service_state_requirements_ccf7110f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/service_state_requirements_ccf7110f.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/service_state_requirements_ccf7110f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/lifecycle/test_service_state_requirements_ccf7110f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.65-rebuntu-phase-54-65-storage-state-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.65-rebuntu-phase-54-65-storage-state-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/storage_state_requirements_713782f9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/storage_state_requirements_713782f9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/storage_state_requirements_713782f9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/lifecycle/test_storage_state_requirements_713782f9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.66-rebuntu-phase-54-66-network-state-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.66-rebuntu-phase-54-66-network-state-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/network_state_requirements_2b29bb93/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/network_state_requirements_2b29bb93.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/lifecycle/network_state_requirements_2b29bb93.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/lifecycle/test_network_state_requirements_2b29bb93.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.67-rebuntu-phase-54-67-gpu-accelerator-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.67-rebuntu-phase-54-67-gpu-accelerator-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/gpu_accelerator_requirements_6710d478/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/gpu_accelerator_requirements_6710d478.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/gpu_accelerator_requirements_6710d478.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_gpu_accelerator_requirements_6710d478.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.68-rebuntu-phase-54-68-process-workload-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.68-rebuntu-phase-54-68-process-workload-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/process_workload_requirements_764368c9/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/process_workload_requirements_764368c9.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/process_workload_requirements_764368c9.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_process_workload_requirements_764368c9.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.69-rebuntu-phase-54-69-user-session-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.69-rebuntu-phase-54-69-user-session-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/user_session_requirements_62ea5cd5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/user_session_requirements_62ea5cd5.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/user_session_requirements_62ea5cd5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_user_session_requirements_62ea5cd5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.7-rebuntu-phase-54-7-target-applicability-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.7-rebuntu-phase-54-7-target-applicability-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/target_applicability_semantics_d97653af/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/target_applicability_semantics_d97653af.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/target_applicability_semantics_d97653af.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_target_applicability_semantics_d97653af.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.70-rebuntu-phase-54-70-configuration-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.70-rebuntu-phase-54-70-configuration-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/configuration_requirements_696335b6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/configuration_requirements_696335b6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/configuration_requirements_696335b6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_configuration_requirements_696335b6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.71-rebuntu-phase-54-71-secret-reference-requirements`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.71-rebuntu-phase-54-71-secret-reference-requirements.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/secret_reference_requirements_f6570837/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/secret_reference_requirements_f6570837.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/security/secret_reference_requirements_f6570837.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/security/test_secret_reference_requirements_f6570837.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.72-rebuntu-phase-54-72-capability-conflict-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.72-rebuntu-phase-54-72-capability-conflict-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_conflict_model_79e3605f/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_conflict_model_79e3605f.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/contracts/capability_conflict_model_79e3605f.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/contracts/test_capability_conflict_model_79e3605f.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.73-rebuntu-phase-54-73-mutual-exclusion-constraints`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.73-rebuntu-phase-54-73-mutual-exclusion-constraints.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/mutual_exclusion_constraints_3d3e3a8e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/mutual_exclusion_constraints_3d3e3a8e.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/mutual_exclusion_constraints_3d3e3a8e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_mutual_exclusion_constraints_3d3e3a8e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.74-rebuntu-phase-54-74-capability-dependency-graph`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.74-rebuntu-phase-54-74-capability-dependency-graph.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_dependency_graph_b1a09e47/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_dependency_graph_b1a09e47.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/capability_dependency_graph_b1a09e47.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_capability_dependency_graph_b1a09e47.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.75-rebuntu-phase-54-75-prerequisite-graph`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.75-rebuntu-phase-54-75-prerequisite-graph.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_graph_de1bec42/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_graph_de1bec42.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_graph_de1bec42.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_graph_de1bec42.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.76-rebuntu-phase-54-76-prerequisite-graph-construction`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.76-rebuntu-phase-54-76-prerequisite-graph-construction.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_graph_construction_177f95ad/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_graph_construction_177f95ad.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_graph_construction_177f95ad.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_graph_construction_177f95ad.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.77-rebuntu-phase-54-77-prerequisite-cycle-detection`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.77-rebuntu-phase-54-77-prerequisite-cycle-detection.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_cycle_detection_699afcbb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_cycle_detection_699afcbb.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_cycle_detection_699afcbb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_cycle_detection_699afcbb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.78-rebuntu-phase-54-78-prerequisite-alternative-paths`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.78-rebuntu-phase-54-78-prerequisite-alternative-paths.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_alternative_paths_1c85147d/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_alternative_paths_1c85147d.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_alternative_paths_1c85147d.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_alternative_paths_1c85147d.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.79-rebuntu-phase-54-79-prerequisite-satisfiability`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.79-rebuntu-phase-54-79-prerequisite-satisfiability.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_satisfiability_903128d5/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_satisfiability_903128d5.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_satisfiability_903128d5.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_satisfiability_903128d5.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.8-rebuntu-phase-54-8-feasibility-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.8-rebuntu-phase-54-8-feasibility-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/feasibility_semantics_329930be/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/feasibility_semantics_329930be.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/feasibility_semantics_329930be.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_feasibility_semantics_329930be.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.80-rebuntu-phase-54-80-prerequisite-blocker-propagation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.80-rebuntu-phase-54-80-prerequisite-blocker-propagation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_blocker_propagation_b5ae0948/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_blocker_propagation_b5ae0948.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_blocker_propagation_b5ae0948.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_blocker_propagation_b5ae0948.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.81-rebuntu-phase-54-81-prerequisite-evidence-propagation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.81-rebuntu-phase-54-81-prerequisite-evidence-propagation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_evidence_propagation_6863f4f2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/prerequisite_evidence_propagation_6863f4f2.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/verification/prerequisite_evidence_propagation_6863f4f2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/verification/test_prerequisite_evidence_propagation_6863f4f2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.82-rebuntu-phase-54-82-prerequisite-freshness-propagation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.82-rebuntu-phase-54-82-prerequisite-freshness-propagation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_freshness_propagation_cc367185/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_freshness_propagation_cc367185.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_freshness_propagation_cc367185.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_freshness_propagation_cc367185.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.83-rebuntu-phase-54-83-prerequisite-graph-invalidation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.83-rebuntu-phase-54-83-prerequisite-graph-invalidation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_graph_invalidation_1f7cd346/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_graph_invalidation_1f7cd346.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/prerequisite_graph_invalidation_1f7cd346.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_prerequisite_graph_invalidation_1f7cd346.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.84-rebuntu-phase-54-84-prerequisite-planning-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.84-rebuntu-phase-54-84-prerequisite-planning-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/prerequisite_planning_boundary_6585cda6/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/prerequisite_planning_boundary_6585cda6.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/prerequisite_planning_boundary_6585cda6.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_prerequisite_planning_boundary_6585cda6.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.85-rebuntu-phase-54-85-plan-synthesis-boundary`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.85-rebuntu-phase-54-85-plan-synthesis-boundary.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/plan_synthesis_boundary_7be10c62/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/plan_synthesis_boundary_7be10c62.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/plan_synthesis_boundary_7be10c62.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_plan_synthesis_boundary_7be10c62.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.86-rebuntu-phase-54-86-why-not-query-contract`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.86-rebuntu-phase-54-86-why-not-query-contract.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/why_not_query_contract_f2a2e842/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/why_not_query_contract_f2a2e842.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/why_not_query_contract_f2a2e842.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_why_not_query_contract_f2a2e842.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.87-rebuntu-phase-54-87-why-not-explanation-engine`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.87-rebuntu-phase-54-87-why-not-explanation-engine.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/why_not_explanation_engine_83127c28/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/why_not_explanation_engine_83127c28.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/why_not_explanation_engine_83127c28.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_why_not_explanation_engine_83127c28.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.88-rebuntu-phase-54-88-blocked-by-explanation-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.88-rebuntu-phase-54-88-blocked-by-explanation-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/blocked_by_explanation_model_22430451/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/blocked_by_explanation_model_22430451.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/blocked_by_explanation_model_22430451.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_blocked_by_explanation_model_22430451.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.89-rebuntu-phase-54-89-missing-requirement-explanation-model`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.89-rebuntu-phase-54-89-missing-requirement-explanation-model.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/missing_requirement_explanation_model_a21577d4/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/missing_requirement_explanation_model_a21577d4.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/missing_requirement_explanation_model_a21577d4.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_missing_requirement_explanation_model_a21577d4.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.9-rebuntu-phase-54-9-readiness-semantics`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.9-rebuntu-phase-54-9-readiness-semantics.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/readiness_semantics_5bd0b83e/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/readiness_semantics_5bd0b83e.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/readiness_semantics_5bd0b83e.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_readiness_semantics_5bd0b83e.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.90-rebuntu-phase-54-90-alternative-capability-explanation`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.90-rebuntu-phase-54-90-alternative-capability-explanation.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/alternative_capability_explanation_abbff018/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/alternative_capability_explanation_abbff018.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/alternative_capability_explanation_abbff018.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_alternative_capability_explanation_abbff018.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.91-rebuntu-phase-54-91-capability-explainability`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.91-rebuntu-phase-54-91-capability-explainability.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/capability_explainability_750633a2/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/capability_explainability_750633a2.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/capability_explainability_750633a2.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/observability/test_capability_explainability_750633a2.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.92-rebuntu-phase-54-92-affordance-explainability`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.92-rebuntu-phase-54-92-affordance-explainability.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/affordance_explainability_d0bcea39/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/affordance_explainability_d0bcea39.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/observability/affordance_explainability_d0bcea39.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/observability/test_affordance_explainability_d0bcea39.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.93-rebuntu-phase-54-93-machine-readable-explanation-schema`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.93-rebuntu-phase-54-93-machine-readable-explanation-schema.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/machine_readable_explanation_schema_6e8f26cb/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/machine_readable_explanation_schema_6e8f26cb.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/machine_readable_explanation_schema_6e8f26cb.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_machine_readable_explanation_schema_6e8f26cb.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.94-rebuntu-phase-54-94-human-readable-explanation-renderer`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.94-rebuntu-phase-54-94-human-readable-explanation-renderer.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/human_readable_explanation_renderer_6d200f97/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/human_readable_explanation_renderer_6d200f97.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/planning/human_readable_explanation_renderer_6d200f97.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/planning/test_human_readable_explanation_renderer_6d200f97.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.95-rebuntu-phase-54-95-cli-capability-query`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.95-rebuntu-phase-54-95-cli-capability-query.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/cli_capability_query_d2d821e3/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/cli_capability_query_d2d821e3.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/cli_capability_query_d2d821e3.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_cli_capability_query_d2d821e3.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.96-rebuntu-phase-54-96-cli-affordance-query`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.96-rebuntu-phase-54-96-cli-affordance-query.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/cli_affordance_query_e83f5462/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/cli_affordance_query_e83f5462.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/resolution/cli_affordance_query_e83f5462.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/resolution/test_cli_affordance_query_e83f5462.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.97-rebuntu-phase-54-97-cli-why-not-command`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.97-rebuntu-phase-54-97-cli-why-not-command.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/cli_why_not_command_d92ac717/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/execution/cli_why_not_command_d92ac717.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/execution/cli_why_not_command_d92ac717.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/execution/test_cli_why_not_command_d92ac717.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.98-rebuntu-phase-54-98-gui-capability-explorer`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.98-rebuntu-phase-54-98-gui-capability-explorer.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/gui_capability_explorer_e4b1e725/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/gui_capability_explorer_e4b1e725.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/gui_capability_explorer_e4b1e725.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_gui_capability_explorer_e4b1e725.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

### `54.99-rebuntu-phase-54-99-gui-blocker-prerequisite-visualization`
- **Source:** `.phases/phases/phase-54-dynamic-system-capability-affordance-model/prompts/54.99-rebuntu-phase-54-99-gui-blocker-prerequisite-visualization.md`
- **Structural package:** `src/semantics/dynamic-system-capability-affordance-model/subtask_packages/verification/gui_blocker_prerequisite_visualization_903ca032/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit
- **Structural targets:** `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/gui_blocker_prerequisite_visualization_903ca032.hpp`, `src/semantics/dynamic-system-capability-affordance-model/subtask_targets/requirements/gui_blocker_prerequisite_visualization_903ca032.cpp`
- **Structural test target:** `tests/structural-closure/semantics/dynamic-system-capability-affordance-model/requirements/test_gui_blocker_prerequisite_visualization_903ca032.cpp`
- **Structural mapping:** `SKELETON_MATERIALIZED` — zero behavioral maturity credit; preserve and implement in place
- **Status:** `UNCLASSIFIED`
- **Depth:** `0/5 pending evidence classification`
- **Implementation:** not yet reconciled at per-subtask granularity
- **Evidence:** none recorded at per-subtask granularity
- **Missing / blocker:** inspect source prompt and repository; implement all applicable missing requirements
- **Native Authority:** `REQUIRES_REVIEW`

## Structural saturation note — XXIV
The repository-wide XXIV pass materialized compile-visible `.cpp` ownership points for structural skeleton headers. This is **zero behavioral maturity credit**: no phase/subtask status or depth is raised by `.hpp`/`.cpp` pairing alone. Future work must replace or extend these translation units with prompt-derived behavior, integration, and tests before claiming implementation evidence.

