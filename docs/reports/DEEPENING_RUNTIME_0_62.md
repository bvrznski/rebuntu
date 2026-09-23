# Rebuntu implementation deepening — runtime path 0–62

This pass replaces phase-coverage-only behavior with a concrete cross-cutting execution path used by the domain controllers.

## Added runtime layers

- `system/backend/backend.hpp`: backend execution contract plus deterministic dry-run backend for tests and planning.
- `system/persistence/journal.hpp`: durable append-only transaction journal with target history lookup.
- `system/telemetry/telemetry.hpp`: bounded event history and per-subsystem/operation counters with latency accounting.
- `system/recovery/recovery.hpp`: recovery coordinator that derives rollback actions from durable journal state.
- `system/orchestration/control_runtime.hpp`: integrated policy -> plan -> execute -> journal -> state update -> telemetry path.

The runtime uses the existing `DomainController`, `StateStore`, `ChangePlanner`, and `PolicyEngine`, rather than creating a parallel phase registry.

## Behavioral invariants

1. A denied policy decision cannot reach the backend.
2. State is updated only after backend success.
3. Every accepted execution is journaled, including failures.
4. Telemetry records both denied and executed operations.
5. Recovery uses persisted before-state and records the rollback as a new journal entry.
6. Privileged domains remain subject to elevation and destructive operations remain subject to interactive policy.

## Verification

A new `integration.deep_runtime` test exercises denial, authorized execution, state convergence, durable journaling, telemetry counters, and rollback.

Clean Debug build completed and the complete CTest suite passed: **48/48 tests**.
