# Rebuntu — Ontology (Phase 0.0)

This document describes **relationships between concepts** in Rebuntu. It is
not philosophy. Concepts are related by **multiple relation types** (a graph,
not a single tree). All relations are **hypotheses** unless marked CURRENT.

## Structural types (first-class directories)

Rebuntu's structural taxonomy encodes *what kind of thing* something is, not
what it does or where it lives. Physical structure reflects **structural type**.

```
src/
├── system/         # primary package (System level)
│   ├── core/
│   ├── shell/
│   ├── runtime/
│   ├── state/
│   └── environment/
├── modules/        # reusable functional components
├── units/          # work/specification units
├── interfaces/     # typed contracts and protocols (NEW in 0.1)
├── adapters/       # native/external mechanism integration (NEW in 0.1)
└── support/        # reusable utilities (NEW in 0.1)
```

### System

A major coherent part of Rebuntu with broad responsibility, internal
organization, and lifecycle. The `system` package is the primary structural
package; it contains Modules.

### Module

A substantial reusable functional component belonging to or used by a System.
A Module may contain Units. A Module may implement Interfaces.

### Unit (Phase 0.7)

**Phase 0.7 Update**: A bounded, independently identifiable Rebuntu definition
representing a discrete piece of executable or operational functionality that
may be invoked, activated, composed, scheduled, inspected and verified.

A Unit should normally have:
- **identity** (stable semantic identifier like "filesystem.copy")
- **purpose** (what it does)
- **inputs** (explicit contract for parameters)
- **outputs** (structured result, not just stdout strings)
- **contract** (preconditions, postconditions, side effects)
- **execution semantics** (how it runs: in-process, subprocess, Service IPC)
- **dependencies** (what it needs to run)
- **result semantics** (outcome, verification status, evidence)

A Unit should NOT simply mean:
- any class
- any function
- any file
- any directory
- any systemd unit (.service, .timer, etc.)
- any Service.

**DISTINCTION: REBUNTU UNIT != SYSTEMD UNIT**
- Rebuntu Unit = semantic/operational definition (what can be done)
- systemd Unit = process lifecycle/deployment artifact (how to run it)

A Rebuntu Unit may be implemented or activated through systemd, but they are
fundamentally different concepts.

*Category:* structural family (smallest structural level).
*Status:* CURRENT (ComponentKind::kUnit exists in cpp/include/system/core/contracts.hpp).

### Interface (NEW in 0.1)

A declared contract that consumers depend on. Interfaces contain no runtime
implementation. An Interface may be implemented by an Adapter or Module.
*Directory:* `src/interfaces/`

### Adapter (NEW in 0.1)

Connects Rebuntu to a specific external/native mechanism. Adapters translate
between Rebuntu's semantic vocabulary and the underlying platform's API.
Adapters implement Interfaces declared elsewhere.
*Directory:* `src/adapters/`

### Support (NEW in 0.1)

Provides cross-cutting, non-semantic functionality: logging, configuration,
validation, serialization. Support modules may be used by any other structural
type but must not depend on high-level semantics.
*Directory:* `src/support/`

All structural types above are *semantic* levels. They do **not** require exact
directory containment, and a component may be realized as a C++ library,
a header-only contract set, or a service — the realization is orthogonal to the
level.

## Role (not a structural kind)

```
Module/Service  ─performs role─▶  {Monitor, Scheduler, Controller, Coordinator,
                                   Verifier, Maintainer, Regulator, ...}
```

Roles are **properties** of a component, not directories. They are represented
by metadata/registries when justified (see ARCHITECTURE §3, §8).

## Execution relations

```
Unit              ─may compose─▶ Composite Unit
                    ─executed by─▶ Job/Execution ─produces─▶ Result
Operation        : target ─subject to─▶ preconditions, policy
                   ─produces─▶ Outcome/Result ─carries─▶ Evidence
Task             ─references─▶ Unit (implementation)
Task             ─submit─▶  Job  ─execute─▶  Result
Procedure        ─uses─▶  Routine  ─produces─▶  Action
Workflow         ─invokes─▶  Unit(s)
```

### Unit Relationships (Phase 0.7)

| Relationship | Description |
|-------------|-------------|
| **Unit → Module** | Unit may depend on Modules for reusable infrastructure |
| **Module → Unit** | Module may contain or implement multiple Units |
| **Task → Unit** | Task is a parameterized work specification referring to a Unit's implementation |
| **Job → Unit** | Job is the concrete submitted/executing realization of work using a Unit |
| **Workflow → Unit** | Workflow composes execution by invoking Units as steps |
| **Service → Unit** | Service may expose Units through IPC/API; Unit may invoke Service |
| **Daemon → Unit** | Daemon may execute Units; process persistence is irrelevant to Unit identity |

### Distinction Summary (Phase 0.7)

| Concept | Relation to Unit |
|---------|-----------------|
| **systemd Unit** | Deployment artifact (.service, .timer, etc.). Rebuntu Unit may be implemented through systemd but they are fundamentally different concepts. |
| **Module** | Structural boundary that may contain Units. Do not create one Unit per Module automatically. |
| **Service** | Managed functionality with lifecycle semantics. A Service may expose or invoke Units. |
| **Daemon** | Persistent process role. A daemon may execute Units, but process persistence is irrelevant to Unit identity. |
| **Script** | Executable artifact. A Script may implement a Unit, but Unit identity is not determined by file type. |
| **Operation** | Contractual system action. Unit = execution definition; Operation = semantic contract (likely relation). |
| **Task** | Parameterized work specification. Task refers to Unit as its implementation (Unit is reusable; Task is parameterized). |
| **Job** | Runtime execution/submission of Task. Job is concrete; Unit is reusable definition. |
| **Workflow** | Composed execution. A Workflow may invoke Units but is not itself a Unit. |

- A **Unit** is an executable/operational definition that can be invoked,
  activated, composed, scheduled, inspected and verified.
  
  - An **Operation** (Phase 0.10) is a reusable, explicitly contracted system
    capability that observes, queries, changes, constructs, removes, transforms,
    or controls system state or resources with full contract semantics.

## Work Ontology Chain (Phase 0.8)

```
Unit (reusable definition)
    +
parameters
    ↓
Task (parameterized work specification)
    ↓ submit
Job (submitted/scheduled/executing realization)
    ↓ execute
Attempt 1 → (may fail, preserves failure evidence)
Attempt 2 → (may fail, preserves failure evidence)
Attempt N → (final attempt with outcome)
    ↓ produces
Result (outcome with status, evidence, verification)
```

### Distinctions

| Concept | Definition | Persistent? |
|---|---|---|
| **Task** | Bounded specification of work to be performed. Does not imply scheduling or execution instance. Reusable across invocations. | Optional - depends on use case |
| **Job** | Concrete submitted/scheduled/executing realization of a Task. Has lifecycle state and may have multiple attempts. | Optional - for async/schedulable work |
| **Execution** | Runtime occurrence of performing work. May be implemented by subprocess, thread, D-Bus call, etc. Unique identity independent from OS process. | NO - runtime transient |
| **Attempt** | One try to perform a Job. Each has unique ExecutionId. Preserves failure history for retry semantics. | Optional - for recovery evidence |

### Retry Semantics

Each Job can specify:
- `max_attempts`: Total attempts including initial (default: 1)
- `retry_policy`: Backoff and retry behavior
- `timeout_policy`: Operation and verification timeouts

Each Attempt has:
- Unique ExecutionId
- Attempt number within Job
- Start/finish timestamps
- Outcome with SemanticStatus

Previous failure history is preserved across retries - a later success does not erase earlier failures.
  
  An Operation defines:
    - WHAT it does (semantic purpose)
    - WHAT it acts upon (subject/target type)
    - WHAT it requires (preconditions)
    - WHAT it may change (expected effects, side effects)
    - HOW to verify success (postconditions, verification strategy)
    - WHAT evidence supports the result
    
  An Operation is NOT:
    - A shell command or script
    - A Unit (Units are structural execution definitions; Operations describe
      semantic capabilities that Units may implement)
    - A Task (Tasks parameterize Operations for concrete work)
    - A Provider (Providers supply implementations; Operations define contracts)
    
  **DISTINCTION: UNIT vs OPERATION**
    - Unit = structural/execution definition (how something is done)
    - Operation = contract describing a system action/query (what can be done)
    
  **DISTINCTION: OPERATION vs TASK**
    - Operation = reusable capability definition (filesystem.copy)
    - Task = parameterized work specification (copy /foo to /bar)
    
  **DISTINCTION: OPERATION vs PROVIDER**
    - Operation = semantic contract (package.install)
    - Provider = implementation capable of satisfying capability (apt, dpkg, snap)
    
  The canonical execution flow:
    ```
    DISCOVER -> RESOLVE TARGET -> OBSERVE CURRENT STATE ->
    EVALUATE PRECONDITIONS -> PLAN (if mutating) -> AUTHORIZE ->
    EXECUTE -> OBSERVE RESULTING STATE -> VERIFY POSTCONDITIONS ->
    GENERATE EVIDENCE -> RESULT
    ```
    
  Side effects are classified as:
    - NONE: read-only operation, no mutation
    - OBSERVATION: reads state but doesn't change it
    - MUTATING: changes system state
    - PRIVILEGED: requires elevated privilege (root or specific capability)
    - DESTRUCTIVE: irreversible or hard-to-reverse change
    
  Idempotency:
    - IDEMPOTENT: same result regardless of execution count
    - CONDITIONALLY_IDEMPOTENT: idempotent only if conditions met
    - NON_IDEMPOTENT: each execution is distinct
    - UNKNOWN: not specified or determined
    
  Reversibility:
    - REVERSIBLE: can be undone to restore prior state
    - CONDITIONALLY_REVERSIBLE: reversible only with specific conditions
    - IRREVERSIBLE: cannot be undone; prior state lost
    - UNKNOWN: not specified or determined
    
  **Status:** CURRENT (contracts implemented in cpp/include/system/core/contracts.hpp).

### Execution Chain (Phase 0.7)

```
Unit (reusable definition)
    +
parameters
    ↓
Task (parameterized work specification)
    ↓ submit
Job (submitted/scheduled/executing realization)
    ↓ execute
Execution (actual attempt to execute)
    ↓ produces
Result (outcome with status, evidence, verification)
```

## Workflow relations

```
Workflow ─contains─▶ Phase ─contains─▶ Stage ─contains─▶ Step
Thread   ─crosses / synchronizes─▶  (Phases, Stages)     [orthogonal]
```

- **Thread** is *not* a node in the containment tree; it is an independently
  progressing flow that may cross phases/stages and synchronize at **Barrier** /
  **Join**.
- Control: **Branch / Fork** diverge; **Join** converges; **Gate / Barrier**
  gate progress; **Path / Route** describe a sequence.
- Iteration: **Loop / Cycle** repeat; **Retry** re-attempts on failure.

## Communication relations

```
Request ─may initiate─▶ Call ─returns─▶ Response
Event   ─may trigger─▶  Automation ─initiates─▶ Operation/Workflow
Channel ─carries─▶ Stream ─delivers─▶ Message
```

- **Event ≠ Signal** (Signal is one Event source). **Call ≠ Request** (Request
  is unbound intent).
- An **InternalAlert** is produced by deterministic correlation of facts and may
  be *consumed* by a semantic model to yield a structured Assessment.

## Control / specification relations

```
Policy ─constrains─▶ Operation, Automation, Reconciliation
Constraint / Invariant ─bound─▶  valid states / solutions
Setting  (WHETHER) / Option (WHAT) / Preference (HOW) ─inform─▶ Configuration
```

- **Setup** (WHERE) and **Configuration** (WITH WHAT) are distinct from the
  WHETHER / WHAT / HOW qualities.
- **Property** (of a definition) and **Attribute** (of an instance) are distinct.

## State & Lifecycle relations (Phase 0.2)

```
Entity ─has─▶ {LifecycleState, WorkState, HealthState, RecoveryState} [orthogonal]
Ready() = (lifecycle == ready) AND (health == healthy)
State ─observed by─▶ Status [summary for monitoring]

HealthState: UNKNOWN < HEALTHY < DEGRADED < UNHEALTHY
RecoveryState: NONE < RETRYING < ROLLING_BACK < RESTORING < REPARING < FAILING_OVER

Lifecycle transitions:
  CREATED ─init─▶ INITIALIZING ─ready?─▶ READY ─activate─▶ ACTIVE
                     │                         │          │
                  failed                      fail     stop    FAILED
                     ▼                         ▼          ▼
                  STOPPED ◄─── stopping ◄─── STOPPING ◄─┘

## Execution & Result relations (Phase 0.2)

```
Request ─submit─▶ Job/TaskInstance ─execute─▶ Execution ─produces─▶ Result
                    │                                    │
               timeout?                                verification?
                    │                                    │
                 retry?                            verified? ─yes──▶ Evidence
                    │                                    │
                 retry_policy                         no ──▶ Outcome (not verified)

RetryPolicy:
  max_attempts, exponential_backoff, retryable_error_codes

TimeoutPolicy:
  operation_timeout, verification_timeout, cancel_on_timeout
```

## Communication & Trigger relations (Phase 0.2)

```
Event ─originates from─▶ {systemd, procfs, udev, kernel, filesystem, network}
   │
   └─evaluates_condition?──yes──▶ Trigger ─activates─▶ Job/Workflow

Trigger = Event + Condition + activation decision

SignalType: PAUSE < RESUME < CANCEL < TERMINATE < RECONFIGURE < HEARTBEAT
```

- **Event ≠ Signal** (Event reports occurrences; Signal is control indication).
- **Request ≠ Call** (Request is intent; Call is bound invocation).
- **Trigger ≠ Event** (Event = something happened; Trigger = activation decision).

## Control / specification relations (Phase 0.2)

```
Policy ─constrains─▶ Operation, Automation, Reconciliation
Condition ─evaluated by─▶ {Activation, Verification, Policy, Diagnostics}
Constraint / Invariant ─bound─▶  valid states / solutions
Setting  (WHETHER) / Option (WHAT) / Preference (HOW) ─inform─▶ Configuration

Specification ─instantiates─▶ Instance
Definition ─describes─▶ RuntimeInstance
```

- **Setup** (WHERE) and **Configuration** (WITH WHAT) are distinct from the
  WHETHER / WHAT / HOW qualities.
- **Property** (of a definition) and **Attribute** (of an instance) are distinct.

## Assurance relations

```
Observation ─produces─▶ Fact ─(declared)─▶ Assertion
Facts ─combine─▶ Condition ─evaluated false─▶ Violation
Operation ─then─▶ Verification ─(postconditions)─▶ verified Success / Evidence
Violation / Condition ─escalate─▶  Alert / InternalAlert
```

- **Fact ≠ Assertion** (observed vs declared).
- **Evidence** is carried by Facts and Outcomes; it is *data*, not *control*.
- **Health** and **Readiness** are separate dimensions of a component's state.
- **Execution success ≠ Verification success**: operation may complete but
  postconditions may fail verification.

## Boundary relations

```
Rebuntu ─via Adapter─▶  native mechanism (systemd, procfs, D-Bus, ...)
Rebuntu ─via Provider─▶  interchangeable capability (e.g. BitNet provider)
Rebuntu ─via Interface─▶  contract surface (no runtime inside)
Semantic model ─boundary─▶  deterministic core
   (model output is NOT authority; it may produce hypotheses / annotations)
```

- An **Adapter** isolates *mechanism*; a **Provider** supplies a *capability*.
- An **Interface** declares *what* but contains no runtime implementation.
- The **semantic model** is a component at an explicit boundary; it must not
  control policy, authorization, or verification.

## Dependency direction (intended)

```
high-level (operations, workflows, automation)
   → core contracts (Result/Outcome/Evidence, ComponentRegistry)
   → interfaces / adapters / providers
   → Linux / native / external facilities
```

### Allowed dependency directions

- **System** may depend on nothing (it's at the top)
- **Module** depends on: `system/core`, `interfaces/`
- **Unit** depends on: `modules/`, other `units/`
- **Interface** depends on: `core contracts` only
- **Adapter** depends on: `interfaces/`, `support/`, native mechanisms
- **Support** depends on: `core contracts` only

### Forbidden directions

- core→application; adapters owning semantics; interfaces holding implementation;
  semantic component controlling policy; experiments as production dependencies;
  support modules depending on high-level semantics.

## Status

All relations above are **hypotheses** (RESOLVED-HYPOTHESIS) except:
- the `ComponentRegistry` structural model (System/Module/Unit + dependencies)
  — **CURRENT** (implemented in `cpp/` and tested).
- the `Outcome`/`Result` + `Evidence` model — **CURRENT** (implemented).

Everything else awaits implementation in later phases (see ROADMAP.md).

## Phase 0.7 Implementation Notes

### Unit Definition vs Instance

A **Unit** is a reusable definition (static). Runtime execution produces:
- `Job` — submitted work
- `Execution` — actual attempt to execute  
- `Result` — outcome with status and evidence

### Unit Discovery

Units are registered in the ComponentRegistry with:
- stable id (e.g., "filesystem.copy")
- kind = kUnit
- dependencies on other Components
- native mechanism mapping where applicable

This enables "SEARCH BEFORE IMPLEMENTING" by allowing future agents to discover
existing Units.

### Unit Execution Semantics

A Unit may execute through:
- Direct invocation (in-process)
- Subprocess execution
- Service IPC
- systemd activation

The execution mode is orthogonal to Unit identity.

## Phase 0.2 Execution & Runtime Relations

### Specification vs Instance
```
Specification ─instantiates─▶ Instance
    ↓                       ↓
Definition                RuntimeInstance
    │                        │
    └───────describes───────┘
```

**Examples:**
- `TaskDefinition` → `Job` (runtime instance)
- `ServiceConfig` → `ServiceInstance`
- `WorkflowDefinition` → `WorkflowRun`

### Execution Chain
```
Unit (reusable definition) + parameters
    ↓
Task (parameterized work specification)
    ↓ submit
Job (submitted/scheduled/executing realization)
    ↓ execute
Execution (actual attempt to execute)
    ↓ produces
Result (outcome with status, evidence, verification)

Execution ─may have─▶ MultipleAttempts
Attempt ─produces─▶ Outcome ─with─▶ Evidence

RetryPolicy:
  max_attempts, exponential_backoff, retryable_error_codes

TimeoutPolicy:
  operation_timeout, verification_timeout, cancel_on_timeout
```

### State Dimensions (Orthogonal)
```
Entity ─has─▶ {LifecycleState, WorkState, ControlState, ReadinessState,
               HealthState, RecoveryState} [orthogonal dimensions]

Ready() = (lifecycle == ready) AND (health == healthy)

State ─observed by─▶ Status [summary for monitoring]
```

### Lifecycle Transitions
```
CREATED → INITIALIZING → READY → ACTIVE
    │              │          │        │
    └─failed───────┘          └─stop───→ STOPPED
                               failed ↓
                                    FAILED

READY ─readiness_check?──yes──▶ can accept work
ACTIVE ─health_check?──no──▶ may become DEGRADED/UNHEALTHY
```

### Activation & Triggering
```
Event ─originates from─▶ {systemd, procfs, udev, kernel, filesystem, network}
    │
    └─evaluates_condition?──yes──▶ Trigger ─activates─▶ Job/Workflow

Trigger = Event + Condition + activation decision

Schedule ─produces─▶ Activation ─at─▶ Time
```

### Control & Coordination
```
Controller ─makes─▶ CoordinationDecision
    ↓
   协调多个实体: start B after A is ready,
                prevent C while D is active,
                synchronize workflow threads,
                arbitrate competing resource requests

Coordinator ─evaluates─▶ Dependencies ─determines─▶ ExecutionOrder
```

### Verification & Evidence Chain
```
Operation ─executes─▶ Outcome
    ↓
Verification (postcondition evaluation)
    ↓
Evidence generated (provenance-bearing observations)
    ↓
Result with verification_status

Execution success ≠ Verification success:
  Operation may complete but postconditions may fail verification.
```

### Request/Event/Signal/Trigger Distinctions
```
Request ─submit─▶ Job ─execute─▶ Execution ─produces─▶ Result
                    │                                    │
               timeout?                            verification?
                    │                                    │
                 retry?                          verified? ─yes──▶ Evidence
                                                    no ──▶ Outcome (not verified)

Event ─may trigger─▶ Trigger
Signal ─controls─▶ Execution (pause/resume/cancel/reconfigure)
Trigger ─produces─▶ Activation of Workflow/Operation

Request ≠ Event: Request asks for action; Event reports occurrence.
Signal ≠ Event: Signal is control; Event is observation.
```

### Retry & Recovery Patterns
```
RetryPolicy ─controls─▶ RetryBehavior
  max_attempts, exponential_backoff, retryable_error_codes

RecoveryPattern:
  - Retry: attempt same operation again
  - Rollback: return to prior known state
  - Restore: recreate desired/known-good state from preserved source
  - Repair: modify damaged/inconsistent state to become valid
  - Failover: switch to alternate implementation/resource
  - Degrade: continue with reduced functionality

Reconciliation ─moves─▶ observed state toward desired state
Recovery ─responds─▶ to failure/degradation and attempts restoration
```

### Coordination & Dependencies
```
DependencyType:
  - Structural (code-level)
  - Implementation (runtime needs)
  - Runtime (lifecycle ordering)
  - Ordering (A must complete before B starts)
  - Readiness (B can start when A becomes ready)
  - Resource (shared lock/queue/buffer)

Chain ─connects─▶ Units in ordered/conditional relationship
Pipeline ─flows─▶ data/output from one stage into another

Workflow ─invokes─▶ Unit(s) as steps
```

### Automation vs Workflow
```
Automation: observes events/state/time, evaluates conditions,
            triggers operations/workflows when criteria satisfied
    ↓
Trigger ─activates─▶ Workflow/Operation

Workflow: describes how work progresses after activation
          (phases/steps that invoke Units)

Distinction:
  - Automation = "when/why" activation happens
  - Workflow = "how" execution progresses after activation
```

### Native Linux Mechanism Mappings
```
Rebuntu Runtime ─maps to─▶ Native Linux Mechanism

LifecycleState transitions ─systemd unit lifecycle, process lifecycle
Schedule (kOnce/kInterval/kCron) ─systemd timers, cron
Event ─inotify/fanotify (filesystem), udev/netlink (devices)
Signal ─D-Bus signals, Linux signals (for termination only)
Evidence ─procfs/sysfs observations, systemd state queries
Condition evaluation ─custom logic over observed state
Cancellation ─signalfd, pidfd, SIGTERM/SIGINT
Dispatch ─epoll, eventfd, timerfd
Shutdown coordination ─systemd shutdown ordering
```

### Result Types
```
Result<T>:
  - outcome: semantic conclusion (SUCCESS/FAILURE/PARTIAL/UNKNOWN/CANCELLED)
  - verification_status: verified/unverified/not_applicable
  - evidence: vector of provenance-bearing observations
  - timing: execution_duration, verification_duration

Outcome:
  - SemanticStatus::kSuccess: completed AND verified
  - SemanticStatus::kCompleted: completed but verification not applicable
  - SemanticStatus::kFailure: attempt ran but objective not met
  - SemanticStatus::kUnknown: outcome could not be determined
  - SemanticStatus::kCancelled: explicitly cancelled before completion
```

## Phase 0.2 Implementation Status

**Status:** CURRENT (contracts implemented)

All Phase 0.2 operational concepts are defined in:
- Header: `src/runtime/contracts.hpp`
- Runner: `src/runtime/runner.hpp`
- Executor: `src/runtime/executor.hpp`
- Dispatcher: `src/runtime/dispatcher.hpp`

Tests verify contracts work correctly.
