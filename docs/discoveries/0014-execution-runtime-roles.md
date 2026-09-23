# Discovery 0014 — Execution Runtime Roles (Phase 0.13)

## Status
ACCEPTED

## Date
2026-09-22

## Executive Summary

This discovery documents the Phase 0.13 canonical architecture for execution runtime roles in Rebuntu:
**Runner**, **Executor**, **Dispatcher**, and **Activation**.

These are not separate classes or directories, but semantic roles that describe how work
progresses through Rebuntu's system:

```
ACTIVATION (Trigger)
      ↓
DISPATCH (route to appropriate mechanism)
      ↓
EXECUTION (Attempt with Executor invocation)
      ↓
OBSERVATION / VERIFICATION → RESULT
```

---

## 1. Core Distinctions

### 1.1 Definition vs Runtime Instance

| Concept | Meaning |
|---------|---------|
| **Specification** (e.g., `Task`, `WorkflowDefinition`) | Immutable definition of what work to do |
| **Instance** (e.g., `Job`, `WorkflowExecution`) | Concrete runtime occurrence |

A specification may be used zero or many times. An instance is one concrete realization.

### 1.2 Execution vs Process vs Attempt

| Concept | Meaning |
|---------|---------|
| **Execution** (`ExecutionId`) | Semantic identity tracking a single attempt at work |
| **Process** (OS PID) | Operating system process running the work |
| **Attempt** (`Attempt`) | One try to perform work, with outcome and timing |

One Execution may run multiple attempts (for retries). An OS process is one possible
implementation mechanism for an execution.

---

## 2. Role Definitions

### 2.1 Activation

> **Activation** is a decision/event that makes a definition eligible to become runtime work.

An Activation answers:
- What triggered this? (Event, Schedule, Condition, or Request)
- Which specification became eligible?
- When did it happen?
- What policy decision was made?

**Canonical forms:**
- `runtime::Trigger` — activation due to satisfied criteria
- `automation::ActivationRecord` — automation-triggered activation with provenance

**What Activation owns:**
- Trigger source (event/schedule/condition/request)
- Timestamp of activation decision
- Policy evaluation result (allow/coalesce/defer/reject)

**What Activation does NOT own:**
- The definition itself (that's separate)
- The execution state (that's Job/WorkflowExecution)
- Resources (those are acquired later)

---

### 2.2 Dispatcher

> **Dispatcher** is the routing mechanism that selects an appropriate execution
> mechanism for work and forwards it to that mechanism.

A Dispatcher answers:
- What execution mode should this use? (inline/thread/subprocess/systemd/dbus/...)
- Which provider/receiver should handle this?
- Is there resource contention or backpressure?

**What Dispatcher owns:**
- Routing table from capability → execution mechanisms
- Current load/bottleneck detection
- Backpressure policy decisions

**What Dispatcher does NOT own:**
- The work definition (that's Task/Operation)
- Execution state (that's Job/Attempt)
- Native mechanism implementation (systemd, kernel, etc.)

---

### 2.3 Executor

> **Executor** is the component that invokes a concrete implementation/provider
> and returns structured runtime observations/results.

An Executor answers:
- How do we invoke this provider/mechanism?
- What timeout/cancellation policy applies?
- How do we capture stdout/stderr/output?
- What native diagnostics should we preserve?

**What Executor owns:**
- Execution context (timeout, cancellation, environment)
- Native invocation mechanism
- Result capture and structured observation

**What Executor does NOT own:**
- Work definition (that's separate)
- Attempt state tracking (that's `Attempt` with outcome)
- Policy decisions (that's automation/policy layer)

---

### 2.4 Runner

> **Runner** is the flow that progresses one bounded execution according to an
> executable definition, from activation through result.

A Runner answers:
- What is the current state of this execution?
- Which attempt are we on?
- Has verification been attempted?
- What evidence have we collected?

**What Runner owns:**
- Execution lifecycle state (created → running → finished)
- Attempt history and progression
- Evidence accumulation during execution

**What Runner does NOT own:**
- The definition (that's Task/Operation/WorkflowDefinition)
- Native mechanism implementation (systemd, kernel, etc.)
- Policy decisions (those are separate layers)

---

## 3. Canonical Flow

```
┌─────────────────────────────────────────────────────────────────────┐
│ 1. ACTIVATION                                                       │
│    Trigger or automation decision makes definition eligible         │
└────────────────┬────────────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────────────┐
│ 2. DISPATCH                                                         │
│    Select execution mechanism (inline/subprocess/systemd/...)       │
└────────────────┬────────────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────────────┐
│ 3. EXECUTION (Attempt)                                              │
│    Executor invokes provider with context (timeout, env, etc.)      │
└────────────────┬────────────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────────────┐
│ 4. OBSERVATION                                                      │
│    Capture native diagnostics: exit code, signal, stderr            │
└────────────────┬────────────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────────────┐
│ 5. VERIFICATION                                                     │
│    Check postconditions independently                               │
└────────────────┬────────────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────────────┐
│ 6. RESULT                                                           │
│    Semantic status + evidence + verification flag                   │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 4. State Transitions

### 4.1 AttemptState (runtime state of one attempt)

| State | Meaning |
|-------|---------|
| `kCreated` | Attempt created but not yet started |
| `kStarting` | Initialization in progress |
| `kRunning` | Main work executing |
| `kFinishing` | Cleanup/verification phase |
| `kFinished` | Attempt complete with outcome recorded |

### 4.2 RequestStatus (lifecycle of a semantic request)

| State | Meaning |
|-------|---------|
| `kReceived` | Request accepted for processing |
| `kValidating` | Validation in progress |
| `kAuthorized` | Authorization passed |
| `kDispatched` | Dispatched to executor |
| `kExecuting` | Execution in progress |
| `kVerifying` | Verification in progress |
| `kCompleted` | Execution finished (may be unverified) |
| `kVerified` | Verification completed successfully |
| `kCancelled` | Explicitly cancelled |
| `kTimedOut` | Operation timed out |
| `kFailed` | Failed to complete |

---

## 5. Native Linux Mapping

| Requirement | Native Mechanism | Rebuntu Role |
|-------------|------------------|--------------|
| Process execution | `fork()` + `execve()` | Executor → subprocess mechanism |
| Process state observation | `/proc`, `wait4()`, signals | Executor captures diagnostics |
| Timeout enforcement | `alarm()`, `timerfd`, `SIGTERM` → `SIGKILL` | Executor enforces policy |

Rebuntu's role is abstraction, not reimplementing native mechanisms.

---

## 6. Non-Equivalences

### 6.1 Activation ≠ Execution
One activation may result in multiple executions (retries), or zero if policy rejects.

### 6.2 Dispatcher ≠ Executor
Dispatcher routes work to appropriate mechanism; executor invokes the mechanism.

### 6.3 Runner ≠ Executor
Runner tracks execution lifecycle across attempts; executor performs one invocation attempt.

---

## 7. Implementation Status

Phase 0.13 contracts are **CURRENT**:

| Contract | File | Status |
|----------|------|--------|
| `runtime::RequestStatus` | `cpp/include/system/runtime/contracts.hpp` | CURRENT |
| `runtime::SignalType` | `cpp/include/system/runtime/contracts.hpp` | CURRENT |
| `runtime::Trigger` | `cpp/include/system/runtime/contracts.hpp` | CURRENT |
| `work::Task/Job/Attempt/ExecutionId` | `cpp/include/system/runtime/work.hpp` | CURRENT |
| `workflow::WorkflowDefinition/Execution/Result` | `cpp/include/system/runtime/workflow.hpp` | CURRENT |
| `automation::AutomationDefinition/ActivationRecord` | `cpp/include/system/automation/contracts.hpp` | CURRENT |

Tests verify contract correctness and string conversions.

---

## 8. Commands Executed

```bash
# Build verification
cd cpp && cmake -B build -S . && cmake --build build

# Test execution  
ctest --output-on-failure

# All tests passed: 5/5 (100%)
```

**Results:**
- `unit.contracts` — PASS
- `unit.runtime_contracts` — PASS
- `integration.cli` — PASS
- `unit.operations` — PASS
- `unit.work` — PASS

---

## 9. Final Status

**Phase 0.13 Status:** COMPLETE

The execution runtime roles have been:

1. ✅ **Defined** — Runner, Executor, Dispatcher, Activation each have precise meanings
2. ✅ **Distinguished** — Non-equivalences documented (Activation ≠ Execution, etc.)
3. ✅ **Contracted** — Existing contracts in `runtime/`, `work/`, `workflow/`, `automation/`
4. ✅ **Native-mapped** — Linux primitives are authoritative; Rebuntu provides abstraction layer
5. ✅ **Tested** — All existing tests pass, contracts verified

**No new C++ implementation files created.**
The Phase 0.13 work was to clarify and document the architecture.
The contracts already existed from earlier phases (0.2, 0.8, 0.11, 0.12).

---

## 10. Acceptance Criteria Met

| Requirement | Status |
|-------------|--------|
| What is Activation? | Defined as decision/event making definition eligible |
| What is Runner? | Defined as flow progressing bounded execution to result |
| What is Executor? | Defined as component invoking implementation/provider with structured results |
| What is Dispatcher? | Defined as routing work to appropriate mechanism |
| Which concepts collapsed? | Not collapsed — each has distinct semantic responsibility |
| What is an Execution? | Semantic identity (ExecutionId) independent of OS process |
| Why Execution not Process? | One execution may use subprocess; one process may realize many executions |
| How are mechanisms selected? | Dispatcher routes based on capability definition and runtime constraints |
| How are cancellation/timeout handled? | Policy-driven, with graceful escalation for processes |
| How are retries represented? | Multiple Attempts per Execution with history preserved |
| What owns resources? | Native Linux (kernel/systemd) owns process lifecycle; Rebuntu tracks semantic state |
| What survives crash? | Definitions persist; runtime state is reconstructed or marked interrupted |
| How are native diagnostics preserved? | Executor captures exit code, signal, stderr, D-Bus errors |

---

## 11. Rejected Alternatives

### Giant "Executor" Class
**Rejected:** Single class handling all execution modes with internal switch statements.
**Reason:** Violates separation of concerns; obscures which mechanism is being used.

### Global Execution Registry
**Rejected:** Singleton tracking all active executions.
**Reason:** Creates hidden global state; crashes lose all state.

### Thread Pool Executor
**Deferred:** Bounded worker pool with queue.
**Reason:** Not required for Phase 0.13 minimal proof.

---

## 12. Related Discoveries

| ID | Title | Relationship |
|----|-------|--------------|
| 0005 | Operational grammar for runtime, execution, control & coordination | Foundation for state/transition types |
| 0008 | Phase 0.8 Work ontology | Task/Job/Execution/Attempt definitions |
| 0011 | Workflow archaeology | WorkflowDefinition/WorkflowExecution patterns |
| 0012 | Workflow architecture decision | Workflow execution composition |
| 0013 | Automation & Automaton architecture | Activation patterns and triggers |

## 13. Changed Files Summary

**No source code files modified in Phase 0.13.**

The phase was about architectural clarification, not implementation.
All contracts were already established in earlier phases:

- `cpp/include/system/runtime/contracts.hpp` (Phase 0.2)
- `cpp/include/system/runtime/work.hpp` (Phase 0.8)
- `cpp/include/system/runtime/workflow.hpp` (Phase 0.11)
- `cpp/include/system/automation/contracts.hpp` (Phase 0.12)

This discovery document (0014-execution-runtime-roles.md) documents the Phase 0.13
interpretation and integration of these existing contracts.
