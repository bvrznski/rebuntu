# Rebuntu — Vocabulary (Phase 0.7)
# Units Architecture, Taxonomy, Contracts, Composition & Execution Semantics

This file establishes how terms are used **in Rebuntu**. Definitions are
**initial hypotheses** subject to refinement through actual use. Do not treat
a term as implying a class, directory, or implementation. Vocabulary is
*semantic infrastructure*, not code generation.

**Status:** CURRENT (defined) unless marked **RESOLVED-HYPOTHESIS** (defined,
pending implementation) or **UNRESOLVED** (the distinction is not yet settled).

For each important term: definition · semantic family · relation to nearby
concepts · status. Ambiguous pairs get an explicit note, including when a
distinction is deliberately **not** drawn.

---

## Structural

- **Core** — the minimal set of functionality whose absence would prevent the
  basic Rebuntu runtime/model from existing coherently. *Family:* structural.
  *Rule:* Core is **not** "miscellaneous important code."
- **System** — a major coherent part of Rebuntu with broad responsibility,
  internal organization, and (where appropriate) lifecycle. *Relation:* a
  System contains Modules. *Status:* RESOLVED-HYPOTHESIS.
- **Module** — a substantial reusable functional component belonging to or used
  by a System. *Relation:* a Module may contain Units. *Status:*
  RESOLVED-HYPOTHESIS.

- **Unit** — a bounded, independently identifiable Rebuntu definition representing
  a discrete piece of executable or operational functionality that may be invoked,
  activated, composed, scheduled, inspected and verified.
  
  A Unit should normally have:
    - identity (stable semantic identifier like "filesystem.copy")
    - purpose (what it does)
    - inputs (explicit contract for parameters)
    - outputs (structured result, not just stdout strings)
    - contract (preconditions, postconditions, side effects)
    - execution semantics (how it runs: in-process, subprocess, Service IPC)
    - dependencies (what it needs to run)
    - result semantics (outcome, verification status, evidence)
  
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
  
  A Rebuntu Unit may be implemented or activated through systemd, but
  they are fundamentally different concepts.
  
  *Relation:* a Unit is the smallest structural level. A Module may contain
  or implement multiple Units. *Category:* structural family (directory).
  *Status:* CURRENT (ComponentKind::kUnit exists in cpp/include/system/core/contracts.hpp).

- **Component** — the generic registered thing (a System, Module, or Unit) in
  the `ComponentRegistry`. *Relation:* Component is the *type* of a registry
  entry; System/Module/Unit are its `kind`. *Status:* CURRENT (type exists).
- **Engine** — an implementation that *executes* a well-defined kind of
  behavior (e.g. a workflow engine executes Workflows). *Relation:* a role a
  Module can perform. *Status:* UNRESOLVED vs Module — an engine is usually a
  Module *performing* an execution role; we do not yet distinguish them as
  separate structural kinds.
- **Provider** — supplies an **interchangeable implementation** of a capability
  (e.g. a CPU-only BitNet provider). *Relation:* a Provider is selected for a
  capability. *Status:* RESOLVED-HYPOTHESIS.
- **Adapter** — connects Rebuntu to a specific external/native mechanism
  (systemd, procfs, D-Bus). *Relation:* an Adapter isolates *mechanism*; a
  Provider supplies a *capability*. *Status:* RESOLVED-HYPOTHESIS.
- **Interface** — a declared contract a consumer depends on (no runtime
  implementation inside it). An Interface is a structural type that lives in
  `src/interfaces/`. *Relation:* an Interface may be implemented by an Adapter
  or Module. *Category:* structural family (directory).
  *Status:* RESOLVED-HYPOTHESIS.

- **Service** — managed functionality exposed or maintained by the system with
  availability/lifecycle semantics (ready, active, degraded, failed).
  
  A Service may:
    - expose Units through IPC/API
    - be realized by a Daemon, oneshot process, socket-activated process, etc.
  
  **DISTINCTION: UNIT != SERVICE**
    - Unit = bounded executable/operational definition (what can be done)
    - Service = managed functionality with lifecycle semantics (availability model)
  
  A Unit may invoke a Service. A Service may expose Units. A Unit may execute
  entirely in-process with no Service.
  
  *Relation:* a Service may realize one or more Units; Units may invoke Services.
  *Status:* RESOLVED-HYPOTHESIS.

- **Daemon** — a long-running background *process/runtime characteristic* that
  continuously or repeatedly provides functionality, observes events, processes
  work, maintains runtime state, or serves requests.
  
  **SERVICE ≠ DAEMON.**
  **DISTINCTION: UNIT != DAEMON**
    - Unit = operational definition (what can be done)
    - Daemon = persistent process lifecycle (how it runs)
  
  A daemon may execute Units. A Unit may be executed by a daemon-backed Service.
  Process persistence is irrelevant to Unit identity.
  
  *Category:* runtime dimension (not structural type).
  *Status:* RESOLVED-HYPOTHESIS.

  **Key characteristics:**
  - long-lived process lifecycle (starts, runs, stops)
  - background/non-interactive execution
  - independently supervised (typically by systemd on Linux)
  - explicit lifecycle transitions

  **Valid use cases for persistent daemons:**
  - Persistent IPC endpoint (e.g., Unix domain socket)
  - Persistent in-memory state or expensive initialization
  - Continuous event stream consumption with low-latency response (<100ms)
  - Queue consumption or continuous aggregation
  - Long-running coordination
  - Kernel/event subscription requiring persistent consumer

  **Invalid use cases (use alternatives instead):**
  - Periodic work → systemd timers or cron
  - On-demand work → oneshot service or direct operation
  - Event-driven batch processing → event subscription + oneshot
  - Background polling without low-latency requirement → native events

- **Daemon Lifecycle** — orthogonal state dimensions for daemon processes:

  | Dimension | Values | Description |
  |---|---|---|
  | LifecycleState | created, initializing, ready, active, stopping, stopped, failed | stage of process existence |
  | WorkState | idle, processing, waiting, paused | current activity type |
  | HealthState | unknown, healthy, degraded, unhealthy | sustained quality |
  | RecoveryState | none, retrying, rolling_back, restoring, repairing, failing_over | corrective action in progress |

  **Readiness:** `ready() = (lifecycle == ready) AND (health == healthy)`

  Lifecycle transitions:
  ```
  CREATED → INITIALIZING → READY → ACTIVE
    │              │          │        │
    └─failed───────┘          └─stop───→ STOPPED
                               failed ↓
                                    FAILED
  ```

- **Readiness** — the ability to *perform now* (is it prepared/available?).
  Distinct from Health (is it well?) and LifecycleState (where is it in its existence?).
  A daemon may be healthy but not ready (still initializing), or ready but unhealthy
  (degraded mode). *Status:* RESOLVED-HYPOTHESIS.

- **Health** — a sustained qualitative state of a component. Distinct from
  lifecycle state. Process running does not imply component works correctly.
  States: UNKNOWN < HEALTHY < DEGRADED < UNHEALTHY.
  *Status:* RESOLVED-HYPOTHESIS.

## Structural Families (directories)

- **interfaces/** — directory for typed contracts, IPC protocols, and message
  formats. Interfaces declare *what* but contain no runtime implementation.
- **adapters/** — directory for native/external mechanism integration
  (systemd, procfs, D-Bus, shell commands). Adapters translate between Rebuntu's
  semantic vocabulary and the underlying platform's API.
- **support/** — directory for reusable utilities (logging, configuration,
  validation, serialization). Support modules provide cross-cutting,
  non-semantic functionality.

## Execution

- **Operation** — a contractual system-level change or query against a target,
  with inputs, preconditions, result, **verification**, and **evidence**.
  *Family:* execution. *Principle:* `COMMAND SUCCESS != OPERATION SUCCESS`.
  
  **DISTINCTION: UNIT vs OPERATION**
    - Unit = structural/execution definition (how something is done)
    - Operation = contract describing a system action/query (what can be done)
  
  A likely useful relation:
    - Unit represents the executable container/definition
    - Operation describes the semantic action exposed by it
  
  *Status:* CURRENT (contracts implemented in cpp/include/system/core/contracts.hpp).

- **Procedure** — a reusable *specification* describing how an objective is
  accomplished. *Relation:* a Procedure may coordinate Routines.
- **Routine** — a smaller reusable execution sequence used inside procedures.
  *Status:* RESOLVED-HYPOTHESIS.
- **Action** — an individual act/effect occurring during execution.
  *Status:* RESOLVED-HYPOTHESIS.

- **Task** — a bounded *specification* of work to be performed. Does not
  imply scheduling, an execution instance, a process, or a service.
  
  **DISTINCTION: UNIT vs TASK**
    - Unit = reusable executable definition (filesystem.copy)
    - Task = parameterized work specification (copy /foo to /bar)
  
  A Task refers to a Unit as its implementation. Task is the "what"; Unit is
  the "how".
  
  *Status:* RESOLVED-HYPOTHESIS.

- **Job** — the *submitted / scheduled / executing realization* of a Task.
  
  **DISTINCTION: UNIT vs JOB**
    - Unit = reusable definition (filesystem.copy)
    - Job = concrete submitted/executing realization
  
  Potential chain:
    ```
    Unit + parameters -> Task -> submit -> Job -> execute -> Result
    ```
  
  *Status:* RESOLVED-HYPOTHESIS.

- **Instance** — a concrete runtime occurrence of a defined thing. Distinct from
  its specification (e.g., TaskDefinition vs TaskInstance/Job). *Category:*
  runtime concept, not structural type. *Status:* RESOLVED-HYPOTHESIS.

## Runtime & Lifecycle Dimensions

| Dimension | Examples |
|---|---|
| lifecycle state | created, started, running, stopped, failed |
| activity state | idle, busy, processing |
| control state | enabled, disabled |
| readiness | prepared/available vs not |
| health | sustained qualitative state (is it well?) |
| outcome | final result/achieved objective |

*Note:* These dimensions describe *what a thing is doing or where it is in its
existence*, not *what kind of thing it is*. Structural types (System, Module,
Unit) are orthogonal to lifecycle/runtime attributes.

## Workflow

- **Workflow** — a composition describing execution flow toward an overall
  objective. *Relation:* Workflow → Phase → Stage → Step.
  
  **DISTINCTION: UNIT vs WORKFLOW**
    - Unit = atomic/reusable executable definition
    - Workflow = composed execution (phases/steps that invoke Units)
  
  A Unit may:
    - be invoked by a Workflow
    - form a Step within a Workflow
    - potentially wrap a reusable Workflow if architecture explicitly supports composite Units
  
  Do not automatically make every Workflow a Unit.
  
  *Status:* RESOLVED-HYPOTHESIS.

- **Phase** — a larger logical portion of a workflow whose character/purpose is
  meaningfully distinct. *Status:* RESOLVED-HYPOTHESIS.
- **Stage** — a group of Steps accomplishing one immediate execution objective.
- **Step** — the smallest meaningful element of sequential workflow execution.
- **Thread** — an *independently progressing* execution flow that may cross
  phases/stages and synchronize with others. **Thread is orthogonal to the
  Workflow/Phase/Stage/Step hierarchy** — it is not "a larger stage".
  *Category:* runtime dimension (not structural).
- **Branch / Path / Fork / Join / Barrier / Gate** — topology & control
  concepts. *Status:* RESOLVED-HYPOTHESIS.
- **Loop / Cycle / Retry** — iteration concepts.
- **Checkpoint / Rollback** — recovery affordances (see SAFETY.md).
- **Workflow** is a composition specification, not a runtime entity.

> None of the workflow terms imply a workflow *engine* in Phase 0.0.

## Structural vs Non-Structural Distinctions

| Dimension | Examples | Encoded in tree? |
|---|---|---|
| structural type | System, Module, Unit, Interface, Adapter, Support | YES (directories) |
| operational role | Monitor, Scheduler, Controller, Verifier | NO (metadata/registries) |
| target domain | filesystem, process, network, storage | NO (metadata/directives) |
| lifecycle state | created, started, stopped, failed | NO (runtime attribute) |
| activity state | idle, busy, processing | NO (runtime attribute) |

## Communication

- **Input / Output** — data crossing a boundary in/out of a component.
- **Source / Sink** — the producer / consumer end of a flow.
- **Channel** — a named, bounded conduit between components.
- **Stream** — an ordered, potentially unbounded flow of items over a Channel.
- **Pipe** — a specific (often OS-level) FIFO transport. *Relation:* a Pipe is
  one possible Channel implementation.
- **Message** — a discrete, self-contained unit of communication.
- **Call** — a request-for-service with an expected reply (synchronous-ish).
- **Request** — a statement of desired action, not yet bound to a specific call.
- **Response** — the reply to a Request/Call.
- **Event** — a notification that *something happened* (asynchronous).
- **Signal** — a specific (often OS-level) asynchronous notification. *Relation:*
  a Signal is one possible Event source. **Event ≠ Signal.**
- **InternalAlert** — an internal *structured* system message produced by
  deterministic correlation; it does **not** necessarily notify the human user.
  *Status:* CANDIDATE (see ARCHITECTURE §9).

## Control / Specification

- **Setup** — relatively non-variable installation/environment specification,
  generally established at install time. Shorthand: **WHERE / under what
  environment**.
- **Configuration** — variable specification evaluated/applied when an instance
  or service is initialized. Shorthand: **WITH WHAT parameters**.
  **Setup ≠ Configuration.**
- **Setting** — a quality determining **IF** an action/functionality should
  occur (WHETHER).
- **Option** — a quality determining **WHAT** alternative to select when
  mutually exclusive scenarios exist. **Setting ≠ Option.**
- **Preference** — a quality influencing **HOW** work is performed when several
  valid methods exist. **Option ≠ Preference.**
- **Property** — a characteristic **OF A DEFINITION** (code/component type).
- **Attribute** — a characteristic **OF A CONCRETE RUNTIME INSTANCE**.
  **Property ≠ Attribute.**
- **Policy** — rules describing what **MAY / MUST / SHOULD / MUST NOT** happen.
  Shorthand: **WHAT IS PERMITTED / REQUIRED**.
- **Constraint** — a restriction that a solution/state must satisfy.
- **Invariant** — a condition that must *always* hold for a system in a valid
  state. **Constraint ≠ Invariant** (a constraint bounds a choice; an
  invariant is a standing truth). *Status:* RESOLVED-HYPOTHESIS.

## Assurance / Observability

- **Observation** — the act of reading host state; produces a **Fact**.
- **Fact** — a single observed statement about state, carrying **Evidence**.
- **Assertion** — a *declared* statement expected to hold (may be true/false/unknown).
  **Fact ≠ Assertion** (a Fact is observed; an Assertion is claimed/checked).
- **Condition** — a combination of facts/assertions (possibly temporal) that
  may hold. *Status:* CANDIDATE.
- **Violation** — a Condition/Invariant that is evaluated **false** when it
  should hold.
- **Verification** — evaluation of **postconditions** after an operation;
  turns "completed" into "verified success".
- **Evidence** — a provenance-bearing, bounded, secret-free observation.
  **DATA, not CONTROL.**
- **Health** — a sustained qualitative state of a component (is it well?).
- **Readiness** — the ability to *perform now* (is it prepared/available?).
  **Health ≠ Readiness** (something can be healthy but not ready, or ready but
  unhealthy). *Status:* RESOLVED-HYPOTHESIS.
- **Status** — a coarse lifecycle/activity descriptor. *Rule:* do not collapse
  lifecycle, activity, control, readiness, health, and outcome into one Status.
  Use orthogonal dimensions instead:
  - LifecycleState: created, initializing, ready, active, stopping, stopped, failed
  - WorkState: idle, processing, waiting, paused
  - HealthState: unknown, healthy, degraded, unhealthy  
  - RecoveryState: none, retrying, rolling_back, restoring, repairing, failing_over
- **Alert / InternalAlert** — see Communication.

## Lifecycle & State (Phase 0.2)

These are orthogonal dimensions describing *what a thing is doing* or *where it is
in its existence*, not *what kind of thing it is*. They are runtime attributes,
not structural types.

### Orthogonal State Dimensions

| Dimension | Values | Meaning |
|---|---|---|
| lifecycle state | created, initializing, ready, active, stopping, stopped, failed | stage of existence |
| work state | idle, processing, waiting, paused | current activity |
| health state | unknown, healthy, degraded, unhealthy | sustained quality |
| recovery state | none, retrying, rolling_back, restoring, repairing, failing_over | corrective action |

### Key Distinctions

- **State** — the complete set of runtime attributes (lifecycle + work + health + recovery).
- **Status** — a simplified summary of state for display/monitoring.
- **Health ≠ Readiness**: something can be healthy but not ready (still initializing),
  or ready but unhealthy (degraded mode).
- **Health ≠ Lifecycle**: process running does not imply component works correctly.

## Runtime Concepts (Phase 0.2)

### Specification vs Instance
- **Definition/Specification** — the static declaration of what something is.
- **Instance** — a concrete runtime occurrence of that definition.
  *Example:* TaskDefinition → Job, ServiceConfig → ServiceInstance

### Request & Communication
- **Request** — semantic/system request for something to happen. Carries operation,
  target, parameters, timeout, priority, origin. Distinct from Call (invocation)
  and Command (user representation).
- **Event** — immutable statement that something occurred or was observed.
  Evidence-backed with provenance. Originates from Rebuntu, systemd, kernel,
  filesystem, network, etc. Not a request for action.
- **Signal** — lightweight control/notification indication (pause, resume, cancel,
  reconfigure). Distinct from Event which reports occurrences.
- **Trigger** — activation decision produced because activation criteria were
  satisfied. Example: udev event + condition match → trigger workflow.

### Execution & Result
- **Execution** — concrete runtime occurrence of work being performed.
- **Result** — structured outcome with value, status, evidence, diagnostics.
- **Outcome** — the semantic conclusion (SUCCESS, FAILURE, PARTIAL, etc.).
  Distinct from execution success: an operation may complete but verification fail.

### Retry & Timeout
- **RetryPolicy** — controls how failures trigger retries:
  - max_attempts: total attempts including initial
  - exponential_backoff: delay increases between attempts
  - retryable_error_codes: filter which errors trigger retry
- **TimeoutPolicy**: controls timeout behavior for operations vs verification.

## System behavior

- **Coordination** — making multiple components act consistently.
- **Scheduling** — deciding *when* work runs (Schedule ≠ Cron).
- **Automation** — a trigger + policy that initiates operations/workflows on
  events/conditions.
- **Reconciliation** — converging observed state toward desired state.
- **Recovery** — restoring a prior good state (checkpoint/rollback/quarantine).
- **Maintenance / Administration / Management** — ongoing upkeep / oversight /
  control of a component.

## Construction / Transformation

- **Builder** — constructs an object/artifact from parts.
- **Constructor** — the act/step of construction.
- **Modifier** — changes an existing artifact.
- **Publisher** — makes an artifact available to consumers.
- **Template** — a reusable pattern producing instances.

## Access / Exposure

- **Authorization** — a *policy decision* that an action is permitted.
  **Authorization ≠ Privilege** (privilege is a mechanism).
- **Permission** — a granted right to perform an action.
- **Public / Internal / Private / Protected** — exposure scopes.

## Interaction

- **Console** — a text terminal interface.
- **Panel** — a structured control surface (GUI/panel).
- **Menu** — a selection list.
- **Desktop** — a graphical session environment.
- **Help / Support** — guidance for the user.

---

## Explicitly **not** distinguished (to prevent over-normalization)

- **Engine vs Module** — not separate structural kinds yet.
- **Routine vs Procedure** — kept (Routine = smaller; Procedure = objective-level
  spec), but neither implies a directory.
- **Request vs Call** — kept (Request = intent; Call = bound service request).
- **Channel vs Stream** — kept (Channel = conduit; Stream = ordered flow over it).
- **Route vs Path** — *UNRESOLVED.* Both describe a sequence; we do not yet draw
  a stable distinction and will not force one.
- **Verification vs Validation** — kept (Validation = checking a *value/input*
  is well-formed; Verification = checking a *postcondition/outcome*).

## Phase 0.7 Unit Distinctions (new)

The following distinctions have been explicitly validated in Phase 0.7:

| Concept | Relation to Unit |
|---------|-----------------|
| **systemd Unit** | Deployment artifact (.service, .timer, etc.). Rebuntu Unit may be implemented through systemd but they are fundamentally different concepts. |
| **Module** | Structural boundary that may contain Units. Do not create one Unit per Module automatically. |
| **Service** | Managed functionality with lifecycle semantics. A Service may expose or invoke Units. |
| **Daemon** | Persistent process role. A daemon may execute Units, but process persistence is irrelevant to Unit identity. |
| **Script** | Executable artifact. A Script may implement a Unit, but Unit identity is not determined by file type. |
| **Operation** | Contractual system action. A likely useful relation: Unit = execution definition; Operation = semantic contract. |
| **Task** | Parameterized work specification. Task refers to Unit as its implementation. |
| **Job** | Runtime execution/submission of Task. Job is concrete; Unit is reusable definition. |
| **Workflow** | Composed execution. A Workflow may invoke Units but is not itself a Unit. |

## Structural Families Summary (Phase 0.1)

Rebuntu's first-class structural categories live in `src/` as directories:

```
src/
├── system/          # primary package (System level)
│   ├── core/
│   ├── shell/
│   ├── runtime/
│   ├── state/
│   └── environment/
├── modules/         # reusable functional components
├── units/           # work/specification units
├── interfaces/      # typed contracts and protocols (NEW in 0.1)
├── adapters/        # native/external mechanism integration (NEW in 0.1)
└── support/         # reusable utilities (NEW in 0.1)
```

**Key principle**: physical structure encodes *structural type*.
Operational roles, target domains, and lifecycle states are represented by
metadata, registries, or attributes—never by creating a directory per term.

## Historical distinctions to preserve (from the prior Rebuntu)

The Setup / Configuration / Setting / Option / Preference / Property /
Attribute / Policy shorthand above is **carried forward** from the historical
Rebuntu and is an intentional, evidence-backed choice — not a coincidence.
See `.phases/PHASES/` (1.x, 36.x) and ARCHAEOLOGY.md.

## Phase 0.7 Implementation Notes

### Unit in C++ Contracts

The Rebuntu C++ core provides structural support for Units via:
- `rebuntu::core::ComponentKind::kUnit` — enum value identifying Units
- `rebuntu::core::Component` — struct with `kind` field and dependency tracking
- `rebuntu::core::ComponentRegistry` — registry for structural registration and integrity validation

These contracts define the *structural* model. They do not implement execution,
composition, or runtime behavior—these belong in later phases.

### Unit Lifecycle States

A Unit (as a definition) is static. Runtime execution produces:
- `Job` — submitted work
- `Execution` — actual attempt to execute
- `Result` — outcome with status and evidence

The outcome may include:
- `SemanticStatus::kSuccess` — completed AND verified
- `SemanticStatus::kCompleted` — completed but verification not performed/applicable  
- `SemanticStatus::kFailure` — attempt ran but objective not met
- `SemanticStatus::kUnknown` — outcome could not be determined
- `SemanticStatus::kCancelled` — explicitly cancelled before completion

### Unit Discovery and Registration

Units are registered in the ComponentRegistry with:
- stable id (e.g., "filesystem.copy")
- kind = kUnit
- dependencies on other Components
- native mechanism mapping where applicable

This enables "SEARCH BEFORE IMPLEMENTING" by allowing future agents to discover
existing Units.
### Deferred Distinctions

**Unit vs Capability** — DEFERRED. 

The relationship between Unit (executable definition) and Capability (abstract ability)
has not been fully resolved in Phase 0.7. Potential future models include:
- Unit implements/exposes a Capability
- Unit and Capability are redundant concepts
- Other architectural relations

This will be resolved when actual consumers (external interfaces, IPC contracts,
agent discovery) require it.
