# 0011 — Workflow Architecture Archaeology Report

- phase: 0.11
- disposition: **ACCEPTED**
- observation: Phase 0.11 must establish Rebuntu's Workflow architecture while distinguishing it from related concepts (Operation, Unit, Task, Job, Automation, Schedule, Script).
- evidence: Existing contracts in `cpp/include/system/core/contracts.hpp` and `cpp/include/system/runtime/contracts.hpp` define core primitives but leave composition semantics under-specified.
- decision: Establish Workflow as a first-class composition abstraction for orchestrating multiple Operations or Units toward an overall objective.

## Repository Survey

### Existing Concepts

| Concept | Status | Description |
|---------|--------|-------------|
| **Unit** (kUnit) | CURRENT | Structural execution definition. Smallest structural level. May be invoked by Workflows. |
| **OperationDefinition** | CURRENT | Contractual system capability. Describes WHAT a system action does, not HOW it's composed. |
| **Task** | RESOLVED-HYPOTHESIS | Parameterized work specification referencing a Unit. |
| **Job** | RESOLVED-HYPOTHESIS | Runtime execution/submission of Task. |
| **Instance/Execution** | RESOLVED-HYPOTHESIS | Concrete runtime occurrence vs static definition. |
| **Outcome/Result** | CURRENT | Semantic outcome with status, evidence, verification status. |
| **Event** | CURRENT | Immutable statement that something occurred (evidence-backed). |
| **Trigger** | CURRENT | Activation decision when criteria are satisfied. May activate Workflows. |
| **ScheduleKind** (kOnce/kInterval/kCron) | CURRENT | Temporal specification for activation timing. |
| **RetryPolicy** | CURRENT | Controls retry behavior with exponential backoff. |
| **TimeoutPolicy** | CURRENT | Controls timeout behavior for operations/verification. |
| **LifecycleState** | CURRENT | Stage of existence: created, initializing, ready, active, stopping, stopped, failed. |
| **WorkState** | CURRENT | Current activity: idle, processing, waiting, paused. |
| **HealthState** | CURRENT | Sustained quality: unknown, healthy, degraded, unhealthy. |
| **RecoveryState** | CURRENT | Corrective action in progress: none, retrying, rolling_back, restoring, repairing, failing_over. |

### Shell Script Evidence

`src/system/shell/sources/flow/_init.sh` contains shell primitives:
- `rebuntu_chain_if_success()` — Chain commands with success condition
- Pipeline composition utilities for shell-native workflow construction

These are **adapter layer** utilities (bridge between Rebuntu and shell), not the canonical Workflow model.

### C++ Evidence

The core contracts already define:
1. State dimensions: lifecycle, work, health, recovery (orthogonal)
2. Execution IDs: request_id, execution_id, parent_execution_id for correlation
3. Retry/timeout policies: exponential backoff, bounded delays
4. Result with metadata: includes timing, executor_id, duration

## Key Discoveries

### 1. Existing Primitives Are Sufficient
The core contracts already provide the semantic primitives needed for Workflow:
- State dimensions for execution tracking
- Execution IDs for tracing across steps
- RetryPolicy/TimeoutPolicy for failure handling
- Outcome/Result with verification status and evidence

**Decision**: Do NOT duplicate these semantics in the Workflow model. Reuse existing contracts.

### 2. Distinction: Definition vs Instance
The pattern is already established:
- **WorkflowDefinition** (static specification)
- **WorkflowExecution** (runtime occurrence)
- **StepExecution** (per-step runtime state)

This mirrors:
- TaskDefinition -> Job -> Execution -> Result

### 3. Trigger != Workflow
Trigger exists in contracts.hpp as an activation decision.
A Trigger may activate a Workflow but is not part of the Workflow model.

**Decision**: Keep Trigger orthogonal to Workflow semantics.

### 4. Schedule != Workflow
Schedule specifies WHEN to run, Workflow defines WHAT to run.
Schedules may activate Workflows via Triggers or direct activation.

**Decision**: Schedule remains temporal specification only. Not embedded in Workflow.

## Open Questions from Archaeology

1. Phase/Stage/Step hierarchy: Is this necessary or can we simplify?
2. Data flow between Steps: How are outputs passed as inputs to subsequent Steps?
3. Parallel composition: Should Workflows support explicit parallel branches?
4. Checkpoint/resume: What persistence semantics are needed?

## Next Steps

Based on archaeology, Phase 0.11 should:
1. Define WorkflowDefinition (static) and WorkflowExecution (runtime)
2. Define Step as the smallest orchestration node
3. Establish how Steps reference Units/Operations
4. Specify control flow models (sequential, conditional, parallel)
5. Integrate with existing retry/timeout policies
6. Use Outcome/Result for step outcomes

## Related Historical Concepts

Historical Rebuntu .phases/ contained:
- chain — Workflow/Pipeline semantics
- pass/register/activate lifecycle phases
- disabled/inactive/guarded/active states

These inform but do not dictate the modern model.

---

## Workflow vs Other Concepts (Summary)

| Concept | Relationship to Workflow |
|---------|--------------------------|
| **Unit** | Atomic/reusable executable. Steps may invoke Units. |
| **Operation** | Contractual capability. Steps may invoke Operations. |
| **Task** | Parameterized work. May be invoked by Steps. |
| **Job** | Execution instance. WorkflowExecution contains StepExecutions. |
| **Automation** | Trigger + policy that initiates Workflows. Not part of Workflow. |
| **Schedule** | Temporal specification for when to invoke Workflow. Not part of Workflow. |
| **Script** | Executable artifact. May invoke or implement a Workflow, but not the definition. |
| **Service** | Managed functionality. May expose Units invoked by Workflows. |

---

## Acceptance Criteria for Phase 0.11

- [ ] Clear definition: What is a Workflow?
- [ ] Workflow/Operation boundary established
- [ ] Workflow/Unit boundary established
- [ ] Workflow/Task/Job/Execution boundary established
- [ ] Workflow/Automation boundary established
- [ ] Workflow/Schedule boundary established
- [ ] Workflow vs Script distinction established
- [ ] Step semantics defined (what is a Step?)
- [ ] Control flow model specified (sequential, branching)
- [ ] Data flow model specified (how outputs pass between Steps)
- [ ] Dependency model specified (Step ordering)
- [ ] Failure propagation model specified
- [ ] Retry/timeout/cancellation integration defined
- [ ] Verification and evidence integration defined
- [ ] Architecture documentation updated
