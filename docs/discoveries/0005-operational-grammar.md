# 0005 — Operational grammar for runtime, execution, control & coordination

- phase: 0.2
- disposition: **ACCEPTED**
- observation: Rebuntu needed a precise operational grammar to describe how entities
  are instantiated, activated, executed, controlled, and coordinated.
- evidence: Phase 0.1 established structural taxonomy (SYSTEM/MODULE/UNIT) but left
  runtime semantics under-defined. Multiple concepts had overlapping or ambiguous meanings.
- decision: Establish explicit distinctions for operational concepts:
  - Specification vs Instance (definition vs runtime occurrence)
  - Execution vs Verification success (exit code ≠ semantic success)
  - State (lifecycle + work + health + recovery dimensions, orthogonal)
  - Request/Event/Signal/Trigger as distinct communication patterns
  - RetryPolicy with exponential backoff and error filtering
  - TimeoutPolicy for operation vs verification timeouts
- rationale: Clear semantics prevent implementation ambiguity. Future components can
  rely on these contracts without reinventing patterns.
- related concepts:
  * LifecycleState (created, initializing, ready, active, stopping, stopped, failed)
  * WorkState (idle, processing, waiting, paused)
  * HealthState (unknown, healthy, degraded, unhealthy)
  * RecoveryState (none, retrying, rolling_back, restoring, repairing, failing_over)
  * Request (semantic request with parameters, timeout, priority)
  * Event (immutable statement that something occurred, evidence-backed)
  * Signal (lightweight control indication: pause, resume, cancel, reconfigure)
  * Trigger (activation decision due to satisfied criteria)
  * Condition (proposition evaluated over state/context)
- native Linux relationship:
  * systemd timers → Schedule (kOnce, kInterval, kCron)
  * inotify/fanotify → Event (filesystem events)
  * D-Bus signals → Signal
  * procfs/sysfs observations → Evidence
  * process lifecycle → LifecycleState transitions

## Implementation

Contracts defined in `cpp/include/system/runtime/contracts.hpp`:
- LifecycleState, WorkState, HealthState, RecoveryState enums with to_string()
- Request struct for semantic requests
- Event struct with Evidence payload
- SignalType enum + Signal struct
- Trigger struct
- Condition (with operand and operator) + condition evaluation interface
- EntityState combining all four dimensions
- InstanceIdentity for runtime instance identity
- ExecutionIds for correlation across components
- ScheduleKind enum + Schedule struct
- TimeoutPolicy + RetryPolicy with exponential backoff
- WorkPriority levels (critical, high, normal, low, background)
- RequestStatus lifecycle stages

Tests in `cpp/tests/test_runtime_contracts.cpp` verify all contracts work correctly.