# Discovery 0019: Execution Runtime Grammar (Phase 0.13)

## Status
ACCEPTED

## Problem Statement

Rebuntu needs a canonical execution-runtime grammar connecting validated definitions to actual runtime work:

    REQUEST / ACTIVATION → RESOLVE → VALIDATE → AUTHORIZE → DISPATCH → EXECUTE → OBSERVE → VERIFY → EVIDENCE → RESULT

Phase 0.13 establishes the minimal proof of this grammar, defining the responsibilities and contracts for:

- **Runner**: Progresses one bounded execution according to an executable definition
- **Executor**: Invokes concrete implementation/providers and returns structured runtime observations/results
- **Dispatcher**: Routes eligible work to appropriate execution mechanisms/providers
- **Activation**: A concrete occurrence making a definition eligible to become runtime work

## Archaeology

### What Already Existed (Phases 0.2, 0.8, 0.11, 0.12)
| Component | File | Phase |
|-----------|------|-------|
| LifecycleState, WorkState, HealthState, RecoveryState | `runtime/contracts.hpp` | 0.2 |
| Request, Event, Signal, Trigger | `runtime/contracts.hpp` | 0.2 |
| Task, Job, Attempt, ExecutionId | `work.hpp` | 0.8 |
| WorkflowDefinition, WorkflowExecution | `workflow.hpp` | 0.11 |
| AutomationDefinition, ActivationRecord | `automation/contracts.hpp` | 0.12 |

### What Was Missing
- Canonical Runner/Executor/Dispatcher class hierarchy
- Integration between runtime components
- Test coverage for new abstractions

## Architecture Decisions

### 1. Namespace Separation
Each major component has its own namespace:

```
rebuntu::runtime::executor   // Execution mechanism invocation
rebuntu::runtime::runner     // State progression through execution
rebuntu::runtime::dispatcher // Work routing decisions
```

This preserves semantic boundaries and avoids god-class antipatterns.

### 2. ExecutionModeSelector
Five canonical execution modes:

- `kInline`: In-process function calls (no subprocess)
- `kSubprocess`: OS process with fork/execve
- `kSystemdUnit`: Managed systemd transient/managed unit
- `kDBusMethod`: D-Bus remote method invocation
- `kThread`: Thread-based parallel execution

### 3. InlineExecutor as Minimal Proof
Only `InlineExecutor` is implemented in Phase 0.13:

```cpp
class InlineExecutor : public Executor {
public:
    core::Outcome execute_inline(const work::Task&, std::function<core::Outcome()> op);
};
```

Subprocess/systemd/dbus implementations are deferred to later phases where native Linux mechanisms can be integrated.

### 4. Runner as State Machine
Runner tracks execution progress through states:

- `kPending` → `kRunning` → `kWaiting`/`kFinished`
- Progress stages: `kDispatched` → `kExecuting` → `kObserving` → `kVerifying` → `kCompleted`

## Files Created/Modified

| File | Reason |
|------|--------|
| `cpp/include/system/runtime/dispatcher.hpp` | Dispatcher, ExecutionModeSelection, DispatcherContext definitions |
| `cpp/include/system/runtime/runner.hpp` | Runner class with state machine and attempt tracking |
| `cpp/include/system/runtime/executor.hpp` | Executor base class with InlineExecutor implementation |
| `cpp/src/executor.cpp` | Executor runtime implementation |
| `cpp/tests/test_executor.cpp` | Unit tests for executor contracts |
| `docs/discoveries/0019-execution-runtime-grammar.md` | This discovery document |

## Tests Executed
```
Test project /home/bvrznski/rebuntu/cpp/build
Start 1: unit.contracts ..................... Passed
Start 2: unit.runtime_contracts ............ Passed
Start 3: integration.cli .................. Passed
Start 4: unit.operations .................. Passed
Start 5: unit.work ....................... Passed
Start 6: unit.workflow ................... Passed
Start 7: unit.state_provider ............. Passed
Start 8: unit.automation ................. Passed
Start 9: unit.executor ................... Passed

100% tests passed, 0 tests failed out of 9
```

## Rejected Alternatives

### 1. Single Executor Class with All Mechanisms
**Rejected**: Would create a god class mixing subprocess, systemd, D-Bus logic.

**Preferred**: Separate execution mechanisms via policy/strategy patterns deferred to later phases.

### 2. Global Execution Registry
**Rejected**: Creates hidden global state, violates testability requirements.

**Preferred**: Local dispatcher instances passed as dependencies.

### 3. Unbounded Thread Pool
**Rejected**: Not required for minimal proof; could deadlock or consume resources unexpectedly.

**Preferred**: Bounded concurrency with explicit backpressure signals.

## Deferred Work (Later Phases)

| Item | Phase |
|------|-------|
| SubprocessExecutor (fork/execve) | Phase 0.14 |
| SystemdUnitExecutor | Phase 0.15 |
| D-Bus Executor | Phase 0.16 |
| Full Runner implementation with timeout/cancellation | Phase 0.17 |
| Integration tests for subprocess execution | Phase 0.18 |

## Remaining Risks/Open Questions

1. **Cancellation propagation**: How should cancellation be propagated through the runtime stack?
   - Current: Basic flag in Runner, no OS-level termination
   - Deferred: pidfd/signalfd integration for proper process group handling

2. **Native timeout enforcement**: Currently simulated via steady_clock polling
   - Deferred: timerfd integration for kernel-enforced timeouts

3. **Backpressure signaling**: Dispatcher tracks pending count but doesn't enforce limits yet
   - Deferred: Bounded work queue with caller blocking/rejection behavior

## Conclusion

Phase 0.13 establishes the canonical execution-runtime grammar with:
- ✅ Disjoint namespaces for Runner/Executor/Dispatcher semantics
- ✅ ExecutionModeSelector enum covering all native mechanisms
- ✅ InlineExecutor implementation as minimal proof
- ✅ Runner state machine tracking progress through execution lifecycle
- ✅ All existing tests continue to pass (8 → 9)
- ❌ Subprocess/systemd/dbus implementations deferred for native Linux integration phases

The runtime grammar is now ready for Phase 0.14+ where actual subprocess, systemd unit, and D-Bus execution mechanisms can be integrated.
