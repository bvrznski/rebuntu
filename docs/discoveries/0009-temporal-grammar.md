# Discovery 0009: Temporal Grammar (Phase 0.9)

## Status
ACCEPTED

## Date
2026-09-22

## Overview
This discovery establishes Rebuntu's canonical architecture and vocabulary for TIME, distinguishing between:
- **Time** as a dimension
- **Schedule** as a specification of WHEN something should activate
- **Work** (Task/Job/Execution) as WHAT is being done

The central principle: **WORK != TIME**

## 1. Core Distinctions

### 1.1 Schedule vs Scheduler
| Concept | Description |
|---------|-------------|
| **Schedule** | A specification describing WHEN something should activate. Declarative, data structure. |
| **Scheduler** | A mechanism responsible for realizing schedules (evaluating conditions, triggering activations). |

A Schedule can exist without Rebuntu implementing its own Scheduler.
Example:
```
Rebuntu Schedule → systemd timer → activation
```

### 1.2 Schedule vs Task
| Concept | Description |
|---------|-------------|
| **Task** | A specification of bounded work (WHAT should be done). Reusable definition. |
| **Schedule** | A specification describing WHEN a Task should become eligible for activation. |

A Task may be:
- executed immediately
- manually activated  
- event activated
- condition activated
- dependency activated
- **scheduled**

Scheduling is ONE activation mechanism, not the only one.

### 1.3 Schedule vs Job
| Concept | Description |
|---------|-------------|
| **Job** | A concrete managed realization of work (runtime instance). |
| **Schedule** | May CREATE or ACTIVATE Jobs at specific times. |

Example:
```
Schedule: every day at 03:00
Task: verify backup integrity

At 03:00:
    Schedule → Activation → Job #184 → Execution

Tomorrow:
    same Schedule → Job #185
```

### 1.4 Schedule vs Automation
| Concept | Description |
|---------|-------------|
| **Schedule** | Answers primarily WHEN? |
| **Automation** | Answers WHEN / WHY / UNDER WHAT CONDITIONS should something happen? |

A Schedule may be one trigger source for Automation, but they are different concepts.

### 1.5 Schedule vs Workflow
| Concept | Description |
|---------|-------------|
| **Workflow** | Describes how composed work progresses. |
| **Schedule** | Describes when activation occurs. |

A Workflow may be scheduled, but a Workflow is not a Schedule.

## 2. Temporal Vocabulary Matrix

| Concept | Definition | Absolute/Relative | Persistent/Transient | Clock Domain | Specification/Mechanism | Likely Owner |
|---------|------------|-------------------|----------------------|--------------|------------------------|--------------|
| **Time** | Dimension in which events occur sequentially | N/A | N/A | N/A | N/A | N/A |
| **Clock** | Mechanism for measuring time | N/A | N/A | wall/monotonic | mechanism | OS/kernel |
| **Timestamp** | Point in time (instant) | Absolute | Persistent where stored | CLOCK_REALTIME or CLOCK_MONOTONIC | data | caller |
| **Duration** | Amount of elapsed time | Relative | Transient | CLOCK_MONOTONIC | data | caller |
| **Delay** | Postponement of an action | Relative | Transient | CLOCK_MONOTONIC | specification | runtime |
| **Interval** | Temporal separation between events | Relative | Transient | CLOCK_MONOTONIC | data | caller |
| **Period** | Fixed interval for recurrence | Relative | Transient | CLOCK_MONOTONIC | specification | schedule |
| **Frequency** | Occurrences per unit time | Relative | Transient | N/A | specification | schedule |
| **Schedule** | Specification of temporal activation | Absolute/Relative | Persistent where stored | Depends on kind | specification | caller |
| **Recurrence** | Pattern of repeated activation | Relative | Transient | CLOCK_MONOTONIC | data | schedule |
| **Deadline** | Temporal boundary for objective completion | Absolute | Persistent where stored | CLOCK_REALTIME | specification | caller |
| **Timeout** | Maximum duration for an operation | Relative | Transient | CLOCK_MONOTONIC | specification | runtime |
| **Window** | Bounded temporal region for correlation | Relative | Transient | CLOCK_MONOTONIC | data | caller |
| **Timer** | Mechanism for measuring/delaying time | N/A | Transient | CLOCK_MONOTONIC | mechanism | OS/runtime |
| **Trigger** | Activation decision when criteria satisfied | N/A | Transient | N/A | event processing | automation |
| **Activation** | Concrete occurrence making work eligible | Absolute | Transient | CLOCK_REALTIME | runtime event | scheduler |
| **Expiration** | Time when something becomes invalid | Absolute | Persistent where stored | CLOCK_REALTIME | data | caller |
| **Retry** | Decision to attempt again after failure | Relative | Transient | CLOCK_MONOTONIC | policy | runtime |
| **Backoff** | Temporal spacing between retries | Relative | Transient | CLOCK_MONOTONIC | policy | retry engine |
| **Cooldown** | Period during which action should not repeat | Relative | Transient | CLOCK_MONOTONIC | policy | runtime |
| **Debounce** | Merging of rapid events into single activation | Relative | Transient | CLOCK_MONOTONIC | policy | event processor |

## 3. Clock Semantics

### 3.1 Wall-Clock Time (CLOCK_REALTIME)
Used for:
- Calendar scheduling (daily at 03:00)
- Absolute timestamps (created_at, deadline)
- Human-readable time references

**Properties:**
- Affected by system time adjustments (NTP, manual changes)
- May jump forward or backward
- Represents "wall clock" time

### 3.2 Monotonic Time (CLOCK_MONOTONIC)
Used for:
- Duration measurements
- Timeout calculations
- Retry delays
- Elapsed time logic

**Properties:**
- Never goes backwards
- Unaffected by system time adjustments
- Best for measuring elapsed time

### 3.3 Boot Time (CLOCK_BOOTTIME)
Used for:
- Schedules relative to boot
- Time including suspend duration
- System uptime calculations

## 4. Temporal Concepts in Detail

### 4.1 Timestamp
Different timestamp meanings:
- `created_at` — when entity was defined/recorded
- `requested_at` — when request was submitted
- `scheduled_for` — when activation is planned
- `activated_at` — when activation actually occurred
- `started_at` — when execution began
- `last_progress_at` — last observed progress
- `completed_at` — when main work finished
- `verified_at` — when verification completed
- `failed_at` — when failure was detected
- `cancelled_at` — when cancellation occurred

### 4.2 Duration vs Delay
| Concept | Use Case |
|---------|----------|
| **Duration** | Measuring elapsed time (execution took 4.2 seconds) |
| **Delay** | Postponing an action (retry after 5 seconds) |

Duration is a measurement; delay is an instruction to wait.

### 4.3 Interval vs Period
| Concept | Use Case |
|---------|----------|
| **Interval** | Separation between two events (sample every 5 seconds) |
| **Period** | Fixed interval for recurrence (run every hour) |

### 4.4 Deadline vs Timeout
| Concept | Description |
|---------|-------------|
| **Deadline** | Absolute temporal boundary ("complete before 18:00") |
| **Timeout** | Relative duration constraint ("operation may take at most 30 seconds") |

A deadline is "by when"; a timeout is "how long max".

### 4.5 Window
Used for correlation and observation:
- "service failed 3 times within 5 minutes"
- "5 minute" here is NOT a Schedule, it's an observation window

## 5. Schedule Kinds (Extended)

From `runtime/contracts.hpp` ScheduleKind:

| Kind | Description | Clock Domain |
|------|-------------|--------------|
| **kOnce** | Single execution at absolute time | CLOCK_REALTIME |
| **kInterval** | Recurring at fixed intervals | CLOCK_MONOTONIC |
| **kCron** | Cron-style calendar schedule | CLOCK_REALTIME |

### 5.1 kOnce
```
absolute_time: 2026-09-23T03:00:00Z
executes once at that time
```

### 5.2 kInterval
```
interval: 3600000ms (1 hour)
max_executions: -1 (unlimited)
runs every hour from activation
```

### 5.3 kCron
```
cron_expr: "0 3 * * *" (daily at 03:00)
timezone: "UTC"
```

## 6. Native Linux Mappings

| Requirement | Native Mechanism | Clock Domain |
|-------------|------------------|--------------|
| Persistent calendar schedule | systemd timer + OnCalendar | CLOCK_REALTIME |
| Boot-relative schedule | systemd timer + OnBootSec | CLOCK_BOOTTIME |
| Process-local timeout | event loop timers | CLOCK_MONOTONIC |
| Subprocess timeout | executor native API | CLOCK_MONOTONIC |
| Service startup timeout | systemd service configuration | CLOCK_MONOTONIC |
| IPC request timeout | IPC client runtime | CLOCK_MONOTONIC |
| Retry backoff | work policy/runtime | CLOCK_MONOTONIC |
| Event debounce | event processor | CLOCK_MONOTONIC |
| Filesystem change | inotify/path unit | N/A (event-driven) |
| Device appearance | udev/systemd | N/A (event-driven) |
| Duration measurement | monotonic clock | CLOCK_MONOTONIC |

## 7. Key Distinctions from Phase 0.8

### 7.1 State Axes
Each concept uses orthogonal state dimensions:

**JobState:**
- `kCreated` — submitted but not yet processed
- `kQueued` — waiting in queue
- `kReady` — ready to start
- `kRunning` — currently executing
- `kCompleted` — finished successfully
- `kFailed` — terminated with error
- `kCancelled` — cancelled during execution

**AttemptState:**
- `kCreated` — attempt created
- `kStarting` — initialization in progress
- `kRunning` — main work executing
- `kFinishing` — cleanup/verification phase
- `kFinished` — attempt complete

### 7.2 Timing in Work Ontology
From `runtime/work.hpp`:
```cpp
struct Attempt {
    ExecutionId id;
    JobId job_id;
    AttemptNumber number;
    std::chrono::system_clock::time_point started_at;      // wall-clock
    std::optional<std::chrono::system_clock::time_point> finished_at;
    // ...
};

struct AttemptResult {
    std::optional<std::chrono::milliseconds> preparation_duration;  // duration
    std::optional<std::chrono::milliseconds> execution_duration;    // duration
    std::optional<std::chrono::milliseconds> verification_duration; // duration
};
```

## 8. Temporal Policy

Some temporal semantics belong to Policy, not Schedule:

Examples:
- Backups may only run at night (time-of-day constraint)
- Expensive diagnostics must not run more than once per hour (rate limit)
- Updates must finish before shutdown window
- Recovery may retry at most three times in ten minutes

## 9. Completion Criteria Met

Phase 0.9 is complete when:

1. ✅ Schedule != Scheduler is explicit.
2. ✅ Schedule != Task is explicit.
3. ✅ Schedule != Job is explicit.
4. ✅ Schedule != Automation is explicit.
5. ✅ Schedule != Workflow is explicit.
6. ✅ Schedule != Daemon is explicit.
7. ⚠️ wall-clock and monotonic time are distinguished (documented here).
8. ⚠️ clock selection rules are documented (documented here).
9. ✅ Timestamp != Duration != Delay != Interval != Timeout != Deadline are distinguished.
10. ✅ recurrence semantics are defined (ScheduleKind variants).
11. ⚠️ missed-run/catch-up semantics have a place (policy domain, not schedule).
12. ⚠️ overlapping activation policy has a place (job policy domain).
13. ✅ retry/backoff temporal semantics integrate with Phase 0.8 Attempts.
14. ⚠️ WAITING integrates cleanly with Phase 0.8 state vocabulary (WorkState::kWaiting exists).
15. ⚠️ JAMMED can use temporal progress evidence without becoming a scheduling concept.
16. ⚠️ debounce/coalescing/throttle/cooldown are distinguished where useful.
17. ⚠️ temporal windows support future event correlation.
18. ✅ native Linux scheduling and event mechanisms have been investigated (systemd timers, inotify, udev).
19. ✅ persistent scheduling defaults toward systemd rather than a custom scheduler daemon.
20. ⚠️ polling is treated as a deliberate fallback, not a default.
21. ✅ no shadow cron/systemd scheduler has been created (Schedule is data, not mechanism).
22. ✅ no ontology-shaped directory/class explosion (Schedule is one struct in contracts.hpp).
23. ⚠️ any concrete implementation is tested (needs test file).
24. ⚠️ documentation reflects the actual architecture (this document).

## 10. Future Extensions

### 10.1 Temporal Conditions
Future capability for temporal assertions:
```
IF service failed 3 times within 5 minutes
IF filesystem unavailable for 30 seconds
IF no progress for 60 seconds
```

These are not ordinary Schedules; they are correlation conditions.

### 10.2 Temporal Sequences
Future sequence expressions:
```
A THEN B within 10 seconds
THEN C OR D within 30 seconds
WHILE NOT E
```

## 11. Files Created/Modified

| File | Purpose |
|------|---------|
| `docs/discoveries/0009-temporal-grammar.md` | This discovery document |
| `cpp/include/system/runtime/contracts.hpp` | Already exists with Schedule, TimeoutPolicy, RetryPolicy |
| `src/system/shell/sources/time/_init.sh` | Time helpers already exist |

## 12. Tests Required

Future tests should verify:

### 12.1 Duration Parsing
- Valid duration parsing (5s, 10m, 2h)
- Invalid duration rejection
- Monotonic timeout calculation

### 12.2 Timestamp Handling
- Wall-clock scheduling representation
- Timezone-aware timestamps
- Recurrence representation

### 12.3 Retry Backoff
- Fixed delay backoff
- Exponential backoff with max
- Jitter application

### 12.4 Deadline Comparison
- Absolute deadline evaluation
- Timeout expiration detection

### 12.5 Overlap Policy
- Skip overlapping activations
- Queue vs replace policies

## 13. Architecture Pressure Tests

### Scenario A — Daily maintenance
**Requirement:** run maintenance every day at 03:00  
**Expected:** systemd timer with OnCalendar expression (no Rebuntu daemon)

### Scenario B — Retry
**Requirement:** operation fails, retry after 5s, 10s, 20s  
**Implementation:** RetryPolicy with exponential backoff

### Scenario C — Timeout
**Requirement:** command may execute for at most 30 seconds  
**Expected:** monotonic timeout (unaffected by wall-clock changes)

### Scenario D — Missed timer
**Requirement:** machine off during scheduled maintenance  
**Policy:** configurable catch-up behavior (skip vs run-once vs reconcile)

### Scenario E — Event instead of polling
**Requirement:** react when storage device appears  
**Expected:** udev/systemd/device events (not polling every 5 seconds)

### Scenario F — Jam detection
**Requirement:** process alive but no progress for 60 seconds  
**Implementation:** use `last_progress_at` + inactivity threshold, mark as JAMMED

### Scenario G — Overlap
**Requirement:** backup scheduled hourly, previous still running  
**Policy:** configurable (skip/queue/coalesce/cancel-previous)

### Scenario H — Boot activation
**Requirement:** initialize component after network ready  
**Expected:** systemd dependencies (After=network.target), not sleep 30

### Scenario I — Correlation
**Requirement:** service fails three times within five minutes  
**Implementation:** temporal window (5 min) + count aggregation

### Scenario J — Suspend
**Requirement:** timeout and maintenance timer behave differently across suspend  
**Clock choice:** CLOCK_MONOTONIC for timeouts, CLOCK_BOOTTIME for some maintenance

## 14. Rejected Alternatives

### 14.1 Giant Timer Engine
**Rejected:** Building a custom scheduler daemon to manage all schedules.

**Reasoning:** systemd timers already provide robust scheduling with:
- Calendar expressions
- Monotonic timers
- Persistence
- Accuracy/randomized delay
- Service activation

Rebuntu's role: validate, translate, install, inspect, verify schedule definitions.

### 14.2 Shadow Cron/Timer Engine
**Rejected:** Creating parallel scheduling infrastructure.

**Reasoning:** Existing native mechanisms are sufficient; rebirth should integrate,
not duplicate.

### 14.3 Single "Time" Field
**Rejected:** Using one generic `time` field for all temporal concepts.

**Reasoning:** Different concepts have different semantics, constraints, and clock
requirements. Precision matters: seconds vs milliseconds vs nanoseconds.

## 15. Summary

Rebuntu's temporal grammar distinguishes:

| Question | Answer |
|----------|--------|
| WHAT? | Task / Operation / Workflow |
| WHEN? | Schedule / Activation |
| HOW OFTEN? | Recurrence / Interval / Frequency |
| HOW LONG? | Duration |
| NOT BEFORE? | Delay / eligibility time |
| NO LATER THAN? | Deadline |
| HOW LONG MAY IT TAKE? | Timeout |
| DURING WHAT PERIOD? | Window |
| WHEN DOES IT STOP BEING VALID? | Expiration |
| WHEN MAY IT BE TRIED AGAIN? | Retry / Backoff / Cooldown |

**TIME IS A DIMENSION, NOT A SUBSYSTEM BY DEFAULT.**
**A TASK IS WORK.**
**A SCHEDULE IS WHEN WORK BECOMES ELIGIBLE.**
**AN EXECUTION IS WHAT ACTUALLY RUNS.**

**USE WALL CLOCK FOR ABSOLUTE CALENDAR REFERENCES.**
**USE MONOTONIC CLOCK FOR ELAPSED-TIME LOGIC.**
**USE SYSTEMD TIMER FOR PERSISTENT NATIVE SCHEDULING WHERE IT FITS.**
