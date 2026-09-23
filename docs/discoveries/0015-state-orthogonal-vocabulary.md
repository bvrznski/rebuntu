# Discovery 0015 — State Orthogonal Vocabulary (Phase 0.14)

- **Status:** ACCEPTED
- **Date:** 2026-09-22
- **Author:** Phase 0.14

## Summary

This discovery documents the orthogonal state vocabulary established in Phase 0.14 for Rebuntu.

A single entity can simultaneously be:

```
lifecycle = RUNNING
activity = WAITING  
control = ENABLED
readiness = NOT_READY
health = HEALTHY
outcome = NONE
```

Therefore, one flat enum is usually wrong.

## Orthogonal State Dimensions

Rebuntu uses **six orthogonal state dimensions** that can be combined to describe any entity's complete state:

| Dimension | Values | Description |
|---|---|---|
| LifecycleState | created, initializing, ready, active, stopping, stopped, failed | Stage of existence/execution |
| WorkState | idle, processing, waiting, paused, jammed | Current activity type |
| ControlState | enabled, disabled, paused, frozen, locked | Administrative control state |
| ReadinessState | ready, not_ready | Can accept/perform work now? |
| HealthState | unknown, healthy, degraded, unhealthy | Sustained qualitative state |
| RecoveryState | none, retrying, rolling_back, restoring, repairing, failing_over | Corrective action in progress |

## Canonical Definitions

### LifecycleState
The stage of an entity's existence from definition to termination.

- kCreated: Defined but not yet initialized
- kInitializing: Initialization in progress  
- kReady: Initialized and ready for activation
- kActive: Running/operational
- kStopping: Shutdown initiated, pending cleanup
- kStopped: Fully stopped
- kFailed: Terminated due to error/failure

### WorkState
What the entity is currently doing.

- kIdle: Not actively working
- kProcessing: Processing a task/request
- kWaiting: Waiting for dependency/event
- kPaused: Temporarily suspended
- kJammed: Alive but failing to make forward progress (distinct from normal waiting)

### ControlState
Administrative control state imposed on the entity.

- kEnabled: Entity is enabled for operation
- kDisabled: Administratively disabled
- kPaused: Temporarily suspended by administrator
- kFrozen: Completely frozen (all activity suspended)
- kLocked: Locked (resource ownership conflict or security hold)

### ReadinessState
Can the entity correctly accept/perform work now?

- kReady: Can accept/perform work
- kNotReady: Cannot accept/perform work yet

### HealthState
The sustained qualitative state of the entity.

- kUnknown: Health has not been assessed
- kHealthy: Operating normally
- kDegraded: Operational but with reduced capability
- kUnhealthy: Impaired or non-functional

### RecoveryState
What recovery action, if any, is in progress.

- kNone: No recovery in progress
- kRetrying: Retry attempt in progress
- kRollingBack: Rollback in progress
- kRestoring: Restore from checkpoint in progress
- kReparing: Repair operation in progress
- kFailingOver: Failover to alternate in progress

## Readiness Predicate

ready() = (readiness == kReady) AND (health == kHealthy)

An entity can be:
- healthy but not ready (still initializing)
- ready but unhealthy (degraded mode)
- jammed (alive but making no forward progress)

## State vs Status

| Concept | Description |
|---|---|
| State | The complete set of runtime attributes across orthogonal dimensions |
| Status | A simplified summary of state for display/monitoring |

Never collapse all dimensions into a single Status enum.

## UNKNOWN Semantics

UNKNOWN is first-class:
- Not a negative observation
- Indicates acquisition failure or unobservable state
- Preserves honest uncertainty in the model

## Native Linux Mappings

| Rebuntu State | systemd | procfs |
|---|---|---|
| kCreated/kInitializing | activating | N/A |
| kReady | inactive (ready for activation) | N/A |
| kActive | active (running) | R, S |
| kStopping | deactivating | T |
| kStopped | inactive, not-found | Z, X |
| kFailed | failed | N/A |

## Implementation

State vocabulary is defined in:
- Header: cpp/include/system/runtime/contracts.hpp
- Tests: cpp/tests/test_runtime_contracts.cpp

Provider interface for native state mapping (Phase 0.14 extension):
- Header: cpp/include/system/state/provider.hpp

### New in Phase 0.14

Added ControlState and ReadinessState dimensions to the EntityState struct:

```cpp
struct EntityState {
    LifecycleState lifecycle;     // created -> failed
    WorkState work;               // idle, processing, waiting, paused, jammed
    ControlState control;         // enabled, disabled, paused, frozen, locked
    ReadinessState readiness;     // ready, not_ready
    HealthState health;           // unknown, healthy, degraded, unhealthy
    RecoveryState recovery;       // none, retrying, rolling_back, etc.
};
```

## Representative Scenarios

1. Service enabled but stopped: lifecycle=kReady, work=kIdle, control=kEnabled, readiness=kNotReady, health=kHealthy, recovery=kNone
2. Process alive but jammed: lifecycle=kActive, work=kJammed, control=kEnabled, readiness=kNotReady, health=kDegraded, recovery=kRetrying
3. Process Linux-zombie: lifecycle=kStopped, work=kIdle, control=kDisabled, readiness=kNotReady, health=kHealthy, recovery=kNone
4. Job waiting for lock: lifecycle=kReady, work=kWaiting, control=kLocked, readiness=kNotReady, health=kDegraded, recovery=kRetrying

## Tests Verified

All tests pass:
- unit.contracts: OK
- unit.runtime_contracts: OK  
- integration.cli: OK
- unit.operations: OK
- unit.work: OK

## Rejected Alternatives

1. Flat state enum - rejected because one entity has multiple independent dimensions
2. Combined state/status - rejected because summary loses precision for debugging
3. Boolean flags per state - rejected because enum provides type safety and exhaustive checking

## Deferred Work

- Full SystemdStateProvider implementation (requires D-Bus integration)
- ProcfsStateProvider /proc/[pid]/stat parsing
- SysfsStateProvider device state mapping

These are implementation details for Phase 0.15+.

---

**Status:** COMPLETE — Phase 0.14 establishes six orthogonal state dimensions with complete implementation in C++20.

## Implementation Summary

### Files Modified/Created
| File | Change |
|---|---|
| `cpp/include/system/runtime/contracts.hpp` | Added ControlState and ReadinessState enum types; updated EntityState struct to include all 6 dimensions |
| `cpp/tests/test_runtime_contracts.cpp` | Added tests for new state types (kJammed, ControlState, ReadinessState) |

### Tests Verified
- unit.contracts: OK
- unit.runtime_contracts: OK  
- integration.cli: OK
- unit.operations: OK
- unit.work: OK

### Representative Scenarios Verified
1. Service enabled but stopped: `lifecycle=kReady`, `control=kEnabled`, `readiness=kNotReady`
2. Process alive but jammed: `work=kJammed`, `health=kDegraded`, `recovery=kRetrying`
3. Zombie process: `lifecycle=kStopped`, `work=kIdle`
4. Locked job waiting for lock: `control=kLocked`, `readiness=kNotReady`