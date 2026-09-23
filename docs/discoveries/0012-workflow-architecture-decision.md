# 0012 — Workflow Architecture Decision

- phase: 0.11
- disposition: **ACCEPTED**
- observation: Rebuntu needed a formal model for composing multiple bounded operations into structured, inspectable, controllable, resumable, and verifiable multi-step processes.
- evidence: Archaeology (0011) showed existing contracts define primitives but leave composition semantics under-specified.
- decision: Establish Workflow as a composition abstraction with explicit boundaries from related concepts.

## Core Definition

A **Workflow** is:

> A STRUCTURED COMPOSITION OF MULTIPLE BOUNDED ACTIONS OR OPERATIONS
> WITH EXPLICIT CONTROL FLOW AND AN OVERALL PURPOSE.

This definition implies:
1. **Multiple bounded actions**: A single action is an Operation; a Workflow orchestrates several.
2. **Structured composition**: Steps have explicit relationships (dependencies, conditions).
3. **Control flow**: Execution order and branching are specified, not accidental.
4. **Overall purpose**: The Workflow exists to accomplish something greater than its parts.

## What Makes Something a Workflow vs Other Concepts?

### Workflow vs Operation

| Dimension | Operation | Workflow |
|-----------|-----------|----------|
| Scope | Single semantic action | Composition of multiple operations |
| Atomicity | Can be executed directly | Must be orchestrated (Steps reference Operations) |
| Complexity | Simple contract | Graph of Steps with dependencies |

**Decision**: If it's one coherent system action, it's an Operation. If it coordinates several independently meaningful operations, it's a Workflow.

Example:
- `package.install("foo")` → **Operation**
- `prepare_development_environment` (inspect host → ensure repos → install packages → verify toolchain) → **Workflow**

### Workflow vs Unit

| Dimension | Unit | Workflow |
|-----------|------|----------|
| Level | Structural execution definition | Composition specification |
| Reusability | Atomic, reusable capability | Orchestrates Units/Operations |
| Instantiation | Can be directly invoked | Must be executed via runtime |

**Decision**: A Workflow may invoke Units as Steps but is not itself a Unit. The relationship is: **Workflow contains Steps that reference Units**.

### Workflow vs Task / Job / Execution

| Dimension | Definition (static) | Instance (runtime) |
|-----------|---------------------|--------------------|
| Operation | OperationDefinition | - |
| Unit | UnitDefinition | - |
| **Workflow** | **WorkflowDefinition** | **WorkflowExecution** |
| Task | TaskSpecification | Job |

**Decision**: Follow the same pattern as other concepts:
- `WorkflowDefinition` = static specification
- `WorkflowExecution` = runtime occurrence

### Workflow vs Automation

| Dimension | Automation | Workflow |
|-----------|------------|----------|
| Purpose | WHEN/WHY to execute | WHAT to execute |
| Trigger | Event/Condition/Schedule | N/A (invoked directly or via automation) |
| Lifetime | Persistent monitor/orchestrator | Bounded execution with start/end |

**Decision**: Keep separate. Automation triggers Workflows but doesn't define them.

### Workflow vs Schedule

| Dimension | Schedule | Workflow |
|-----------|----------|----------|
| Purpose | WHEN to execute | WHAT to execute |
| Type | Temporal specification | Execution composition |
| Relationship | May activate a Workflow | Run independently or via schedule |

**Decision**: Schedule is temporal; Workflow is semantic. They are orthogonal.

### Workflow vs Script

| Dimension | Script | Workflow |
|-----------|--------|----------|
| Purpose | Executable artifact | Definition/specification |
| Language | Bash/Shell/Python | C++ contracts/data structures |
| Semantics | Implementation details | Semantic orchestration |

**Decision**: A Script may invoke or implement a Workflow but isn't the definition.

## Step Semantics

A **Step** is the smallest orchestration node in a Workflow. It does NOT contain implementation code; it references external capabilities.

### Required Step Fields:
- `id`: Unique identifier within the Workflow
- `target_kind`: What kind of target (Unit, Operation, Workflow)
- `target_id`: Identifier of the capability to invoke

### Optional Step Features:
- `depends_on`: Which Steps must complete before this one runs
- `condition`: Precondition for execution (uses existing runtime::Condition)
- `retry_policy`: Per-Step retry behavior
- `timeout_policy`: Per-Step timeout behavior
- `failure_policy`: What happens on failure (fail_fast, continue, skip_dependents, compensate)
- `control_flow`: sequential, conditional, parallel
- `branch_policy`: How parallel branches converge

## Workflow Definition Structure

```cpp
struct WorkflowDefinition {
    std::string id;                    // Stable semantic identifier
    std::optional<std::string> title;
    std::optional<std::string> description;
    
    std::optional<Condition> preconditions;
    std::vector<Step> steps;
    std::vector<Condition> postconditions;
    
    bool allow_parallel = false;
    core::SideEffectKind side_effect = core::SideEffectKind::NONE;
    bool resumable = false;  // Supports checkpoint/resume
};
```

## Runtime State Model

```cpp
struct WorkflowExecution {
    std::string execution_id;
    std::optional<std::string> parent_execution_id;
    std::string definition_id;
    
    WorkflowExecutionState state;  // pending, running, succeeded, failed, etc.
    std::vector<StepState> step_states;
    std::vector<core::Evidence> evidence;
};
```

## Control Flow Models

1. **Sequential** (default): A → B → C
2. **Conditional**: A → [condition] → B | C (branching)
3. **Parallel**: A, B run concurrently; then C (join)

## Failure Semantics

- `kFailFast`: Stop entire Workflow immediately
- `kContinue`: Continue with remaining Steps (skip dependents)
- `kSkipDependents`: Skip Steps that depend on this one
- `kCompensate`: Attempt compensation/rollback actions

## Retry, Timeout, Cancellation

- Reuse existing `runtime::RetryPolicy` and `runtime::TimeoutPolicy`
- Cancellation: `WorkflowContext.cancellation_requested` flag
- Each Step tracks attempt_number for retry management

## Verification & Evidence

- Per-Step verification via `requires_verification` flag
- Overall Workflow result uses existing `Outcome/Result` model
- Evidence collection via `WorkflowContext.evidence` reference

## Architecture Summary

```
Intent / Request
       |
       v
   WorkflowDefinition (static, immutable)
       |
       v
  submit / activate
       |
       v
  WorkflowExecution (runtime instance)
       |
       +-- StepExecution (for each Step)
       |      |
       |      +-- invokes Unit/Operation → Result with Evidence
       |
       +-- Outcome aggregation
           |
           v
        WorkflowResult
```

## Acceptance Criteria Met

- [x] Clear definition: What is a Workflow? — Composition of multiple bounded actions with control flow
- [x] Workflow/Operation boundary established — Workflow orchestrates; Operation is atomic
- [x] Workflow/Unit boundary established — Workflow invokes Units as Steps
- [x] Workflow/Task/Job/Execution boundary established — Definition vs Instance pattern
- [x] Workflow/Automation boundary established — Automation triggers; Workflow defines
- [x] Workflow/Schedule boundary established — Schedule is temporal; Workflow is semantic
- [x] Workflow vs Script distinction established — Script is artifact; Workflow is definition
- [x] Step semantics defined — References external capability with metadata
- [x] Control flow model specified — sequential, conditional, parallel
- [x] Data flow model specified — Input/Output bindings between Steps
- [x] Dependency model specified — `depends_on` array per Step
- [x] Failure propagation model specified — 4 failure policies
- [x] Retry/timeout/cancellation integration defined — Reuse existing policies
- [x] Verification and evidence integration defined — Uses Outcome/Result model

## Files Created

1. `docs/discoveries/0011-workflow-archaeology.md` — Archaeology report
2. `cpp/include/system/runtime/workflow.hpp` — Canonical contracts
3. `docs/discoveries/0012-workflow-architecture-decision.md` — This file
4. `cpp/tests/test_workflow.cpp` — Test suite (contract validation)

## Future Work

- WorkflowRunner implementation (runtime executor)
- Step execution adapters (Unit/Operation invocation)
- Cancellation signal propagation
- Checkpoint/resume persistence
- Shell integration (`run workflow.name` syntax)
