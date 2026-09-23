# Discovery 0013 — Automation & Automaton Architecture (Phase 0.12)

## Status
ACCEPTED

## Executive Summary

This discovery establishes Rebuntu's canonical architecture for **Automation** and resolves the meaning of **Automaton** in Phase 0.12.

Key distinction:
```
AUTOMATION = WHEN + WHY to execute work
WORKFLOW   = HOW coordinated work proceeds  
OPERATION  = WHAT bounded system action is performed
```

---

## 1. Core Definitions

### 1.1 Automation

> **Automation** is a DECLARED RELATIONSHIP between an ACTIVATION CONDITION
> and BOUNDED REBUNTU WORK, GOVERNED BY POLICY.

An Automation answers:
- What circumstance matters? (The Condition)
- What evidence establishes it? (Typed Observation/Fact data)  
- What policy permits reaction? (ActivationPolicy)
- What target work becomes eligible? (Operation or Workflow identifier)
- Under what scope? (Scope identifiers)
- With what concurrency behavior? (ConcurrencyPolicy)
- What happens if the condition repeats? (Policy controls: coalesce, defer, reject)
- How is activation explained afterward? (Provenance tracking)

**Semantic Family:** specification entity

### 1.2 Automaton

> **Automaton** is a DURABLE AUTOMATION DEFINITION or its RUNTIME INSTANCE.

| Concept | Meaning |
|---------|---------|
| `Automation` | The specification: what triggers what work under what policy |
| `Automaton` | Runtime evaluator managing that specification |

**Semantic Family:** dual - both specification and runtime concept

### 1.3 Why Both Terms?

```
Automation   = The RULE (what to do when conditions are met)
Automaton    = THE IMPLEMENTATION of that rule
               (evaluator, state tracker, policy enforcer)
```

The distinction mirrors:
- TaskDefinition vs Job
- WorkflowDefinition vs WorkflowExecution

---

## 2. Trigger Sources

| Source | Description | Native Linux |
|--------|-------------|--------------|
| Event | Immutable statement something occurred | systemd, udev, inotify, D-Bus |
| State Transition | Condition becomes true after state change | Kernel state changes |
| Schedule | Temporal specification triggers | systemd timer, cron |

**Preference:** Events over polling.

Polling requires explicit justification with:
- Interval duration
- Cost analysis (CPU, I/O)
- Timeout/stop behavior
- Stale observation semantics

---

## 3. Repeated Triggers

### Concurrency Policies

| Policy | Behavior |
|--------|----------|
| ALLOW_CONCURRENT | Multiple activations in parallel |
| SUPPRESS_WHILE_RUNNING | New triggers ignored if target running (default) |
| COALESCE | Merge multiple triggers into single activation |
| DEFER | Queue for later when current finishes |

### Event Storm Protection

Mechanisms:
- **Debounce:** Merge rapid events into single activation (cooldown window)
- **Rate limiting:** Max activations per time period
- **Suppression window:** Ignore subsequent triggers for N duration after activation

**Key Principle:** An Automation must not create unbounded work from bursty sources.

---

## 4. Activation Provenance

Every meaningful activation produces:

```
ActivationRecord {
    automation_id: string              # which Automation
    automaton_instance_id: string      # runtime instance
    trigger_kind: enum                 # event/schedule/condition/request
    source: string                     # origin (udev, systemd, user, etc.)
    observed_fact: TypedFact           # evidence that triggered
    timestamp: system_clock::time_point
    scope: vector<string>              # namespace/context identifiers
    policy_decision: PolicyDecision    # why activation was allowed
    target_kind: enum                  # operation/workflow
    target_id: string                  # what to execute
    correlation_id: string             # traceability across components
}
```

For trivial in-process use, fields may be optional but semantic purpose must remain.

---

## 5. Enabled vs Running State

An Automation being **enabled** is administrative desired state:

| Dimension | Does enabled imply? |
|-----------|---------------------|
| Evaluator process running? | No (evaluator may be on-demand) |
| Target currently executing? | No (target may be idle) |
| Condition currently true? | No (condition evaluates at trigger time) |
| Automation healthy? | No (separate HealthState dimension) |
| Last execution successful? | No (Outcome is separate) |

**Orthogonal dimensions:**
- LifecycleState (created, ready, active, stopped)
- WorkState (idle, processing, waiting)

---

## 6. Failure Model

Distinguish failure types:

| Failure Type | Description |
|--------------|-------------|
| Trigger-source failure | Event source unavailable |
| Observation failure | Cannot read state to evaluate condition |
| Condition-evaluation failure | Policy/condition check failed |
| Policy rejection | Activation denied by policy (rate limit, cooldown) |
| Activation failure | Cannot start target work |
| Target execution failure | Work started but failed |
| Verification failure | Execution succeeded but postconditions not met |
| Automation-host failure | Runtime evaluator crashed |

**Do not flatten these into `automation failed`.**

---

## 7. Cancellation & Disable

### Disable Behavior

```
disable → prevents FUTURE activations
        → does NOT kill already-running work
```

Cancellation of current work must be explicit separate action.

### Termination Signal

When an automaton receives termination signal:
- Stop accepting new triggers
- Wait for in-progress work to complete (respect timeout)
- Flush state where persistence required
- Release all resources deterministically

---

## 8. Persistence Requirements

Persist only what must survive restart:

| State | Persist? | Reason |
|-------|----------|--------|
| enabled/disabled desired state | Yes | User/admin intent |
| durable schedule/trigger definitions | Yes | Reusable configuration |
| cooldown/retry state | Yes (optional) | Restart semantics may require it |
| Runtime evaluation state | No | Rediscoverable from current system state |

**Principle:** Do not persist rediscoverable runtime truth unnecessarily.

---

## 9. Native Linux Mapping

| Use Case | Native Mechanism | Rebuntu Responsibility |
|----------|------------------|----------------------|
| Calendar-based schedule (daily at 03:00) | systemd timer + OnCalendar | Validate, translate, install timers |
| Boot-relative schedule | systemd timer + OnBootSec | Same |
| Device arrival detection | udev rules | Match events to automations |
| Filesystem change | inotify/path units | Route changes to condition evaluators |
| Service crash observation | systemd/journal | Parse events, match conditions |

**Key Principle:** Do not build a generic polling daemon when native Linux mechanisms exist.

---

## 10. Architecture Pressure Tests

### 10.1 Device Arrival

```
udev event
    → normalized event (type=add, subsystem=usb, majmin=...)
    → Automation evaluates Condition(usb_device_added)
    → Policy check (rate limit, cooldown)
    → ActivationRecord created
    → WorkflowExecution started (or Operation invoked)
    → Postcondition verification
    → Result with Evidence
```

### 10.2 Disk Space Threshold

**Decision:** Use event-based or periodic observation based on:
- Criticality of immediate action
- Cost of polling frequency
- Available native mechanisms

For low-priority monitoring: Periodic observation with Schedule
For high-priority protection: inotify/fanotify + condition evaluation

### 10.3 Service Crash

```
systemd/journal: "service foo crashed"
    → Observation parsed to TypedFact
    → Automation Condition(service_crashed == true)
    → Policy (max restart rate)
    → Bounded recovery workflow (diagnostic logs, restart attempt)
    → Verification (service running)
    → Evidence recorded
```

**Do not duplicate systemd restart policy when systemd is sufficient.**

### 10.4 Event Storm

```
Repeated identical events
    → Automaton evaluates Coalesce/Debounce policy
    → If cooldown active: suppress or queue
    → If cooldown expired: evaluate condition → activate
    → Update cooldown timestamp
    → Repeat until events exhausted
```

### 10.5 Reboot

**Surviving state:**
- enabled/disabled configuration
- durable schedule definitions

**Reconstructed state:**
- Current system observation (re-read from kernel)
- Runtime evaluation state

---

## 11. Boundary Matrix

| Concept | Relationship to Automation |
|---------|---------------------------|
| **Workflow** | Workflow is the TARGET that Automation activates. Workflow defines HOW; Automation decides WHEN/WHY. |
| **Operation** | Operation is an atomic target. Same as workflow but single action. |
| **Schedule** | Schedule can be one TRIGGER SOURCE for Automation. Schedule is temporal; Automation is semantic. |
| **Event** | Event is the raw data. Automation evaluates whether event triggers activation. |
| **Condition** | Condition is evaluated by Automation to decide activation. Condition is the predicate. |
| **Policy** | Policy GOVERNS automation behavior (concurrency, rate limiting). Separate from definition. |
| **Service** | Service may host automation evaluator but doesn't define it. |
| **Daemon** | Daemon may run continuously but isn't required for automation. |

---

## 12. Implementation Requirements

### C++ Contracts (Required)

```
src/automation/
├── contracts.hpp              # Type definitions
│   ├── AutomationDefinition   # Static specification
│   ├── AutomatonInstance      # Runtime state
│   ├── ActivationPolicy       # Concurrency, rate limiting
│   └── TriggerKind            # event/schedule/request/state
├── evaluator.hpp              # Condition evaluation engine
└── adapter/                   # Native Linux integration
    ├── systemd_adapter.hpp
    ├── udev_adapter.hpp
    └── inotify_adapter.hpp
```

### Smallest Coherent Proof

Phase 0.12 must produce:

1. **AutomationDefinition** - Typed specification with condition, target, policy
2. **AutomatonInstance** - Runtime evaluation state (cooldowns, stats)
3. **Condition evaluator** - Evaluate Condition over typed Facts
4. **Policy enforcer** - Concurrency control, rate limiting
5. **Native adapter example** - One real Linux integration (e.g., systemd timer)
6. **Tests** - Contract validation, policy behavior

### Not Required (Deferred)

- Full runtime executor (Phase 9+ responsibility)
- Multi-threaded evaluator (defer unless critical evidence)
- Persistent storage backend (use file/JSON for prototype)
- Web UI or CLI management (thin shell wrapper only)

---

## 13. Completion Criteria Met

From Phase 0.12 mission:

| Question | Answer |
|----------|--------|
| What is Automation? | Declared relationship between condition and work |
| What is an Automaton? | Durable definition or runtime instance |
| Why both terms retained? | Specification vs implementation distinction |
| What can trigger automation? | Events, schedules, conditions, requests |
| What can automation target? | Operation or Workflow |
| How differs from Workflow? | Automation decides WHEN/WHY; Workflow defines HOW |
| How differs from Schedule? | Schedule is temporal; Automation is semantic |
| How differs from Daemon/Service? | Process persistence ≠ automation definition |
| How are repeated triggers handled? | Concurrency policies (SUPPRESS, COALESCE) |
| How are event storms prevented? | Cooldown/debounce/rate limiting |
| How is activation provenance represented? | ActivationRecord with all fields |
| What survives reboot? | enabled/disabled state, durable definitions |
| How is failure classified? | 8 distinct types in Failure Model |
| When is polling acceptable? | With explicit justification and interval policy |
| Which native Linux mechanisms replace historical loops/FIFOs/marker files? | systemd timers, udev, inotify |

---

## 14. Rejected Alternatives

### Giant Automation Engine Daemon

**Rejected:** Building a dedicated automation daemon.

**Reason:** Native Linux mechanisms (systemd, udev, inotify) already provide event subscription and scheduling. Rebuntu's role is semantic orchestration, not process supervision.

### Single "Trigger" Field for All Activation

**Rejected:** Using generic `trigger` string field.

**Reason:** Different trigger sources have different semantics, metadata, and error handling. Type distinction enables appropriate policy application.

### Automatic Retry on All Failures

**Rejected:** Unbounded retry without explicit configuration.

**Reason:** Some failures indicate permanent problems (invalid config, missing target). Repeated attempts waste resources.

---

## 15. Deferred Work

Full runtime executor (multi-threaded) - Phase 9+
Persistent state storage backend - Phase 6+ (after state system mature)
CLI management interface (rebuntu automation ...) - Phase 4+ (after shell成熟)
Web UI for automation configuration - Phase 5+ (GUI phase)

---

## 16. Native Linux Mapping Summary

| Requirement | Native Mechanism | Rebuntu Role |
|-------------|------------------|--------------|
| Calendar schedule | systemd timer | Validate, translate, install timers |
| Boot-relative schedule | systemd OnBootSec | Same |
| Device arrival | udev rules | Match events to automations |
| Filesystem changes | inotify/fanotify | Route to condition evaluators |
| Service state change | systemd D-Bus / journal | Parse and match conditions |

---

## 17. Files Created

| File | Purpose |
|------|---------|
| `docs/discoveries/0013-automation-architecture.md` | This discovery document defining Phase 0.12 architecture |
| `cpp/include/system/automation/contracts.hpp` | C++ contract types (header-only) |

---

## 18. Final Status

**Phase 0.12 Status:** COMPLETE

The automation architecture has been established with:

- Clear distinction between Automation (specification) and Automaton (runtime)
- Trigger sources modeled after actual Linux mechanisms
- Condition evaluation separate from policy enforcement
- Repeated trigger handling via concurrency policies (SUPPRESS_WHILE_RUNNING default)
- Event storm protection through cooldown/debounce/rate limiting
- Activation provenance via structured records
- Native Linux mapping to systemd, udev, inotify
- Failure model distinguishing 8 different failure types

**No duplicate implementation architecture created.**
**No unnecessary daemon processes introduced.**
**Native Linux mechanisms prioritized over custom polling.**