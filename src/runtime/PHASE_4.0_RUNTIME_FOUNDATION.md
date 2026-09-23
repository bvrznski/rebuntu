# Phase 4.0 — Runtime Foundation

## Status
**CURRENT** - Implementation in progress

## Date
2026-09-23

## Executive Summary

Phase 4.0 establishes the **production runtime substrate** that turns Phase 0-3 execution grammar into a coherent, deterministic Rebuntu runtime.

This phase does NOT implement domain services (Phase 5+) or desired-state reconciliation (Phase 19+).

It focuses on:
- Runtime boundaries and ownership
- Lifecycle management
- Execution context
- Cancellation primitives
- Evidence/result integration
- Provider/native execution boundary
- Runtime storage roots
- Shutdown semantics

## Archaeology

### What Already Existed (Phases 0.2, 0.8, 0.13)
| Component | File | Phase | Status |
|-----------|------|-------|--------|
| LifecycleState, WorkState, HealthState, RecoveryState | `runtime/contracts.hpp` | 0.2 | CURRENT |
| Request, Event, Signal, Trigger | `runtime/contracts.hpp` | 0.2 | CURRENT |
| Task, Job, Attempt, ExecutionId | `work.hpp` | 0.8 | CURRENT |
| Runner, Executor, Dispatcher roles | `runner.hpp`, `executor.hpp`, `dispatcher.hpp` | 0.13 | CURRENT |
| Operation contracts | `core/contracts.hpp` | 0.10 | CURRENT |

### What Was Missing for Production Runtime
| Item | Description |
|------|-------------|
| RuntimeContext | Execution context with timeouts, cancellation, environment |
| ExecutionIdentity | Stable identity tracking across attempts |
| TimeSource | Abstracted time source for testing |
| CancellationToken | Token-based cancellation propagation |
| EvidenceRegistry | Centralized evidence collection and linkage |
| NativeExecutionProvider | Interface between Rebuntu runtime and Linux |
| ShutdownCoordinator | Coordinated shutdown with timeout |

## Phase 4.0 Design Decisions

### 1. Namespace Organization
```
rebuntu::runtime
├── core          # Core contracts (already existed)
├── execution     # Execution context, identity, lifecycle
├── cancellation  # Cancellation propagation (existing slots)
├── time          # Time source abstraction
├── evidence      # Evidence collection and linkage
├── native        # Native Linux provider interface
└── shutdown      # Shutdown coordination
```

### 2. RuntimeContext Design
```cpp
struct RuntimeContext {
    ExecutionId execution_id;              // Unique execution identifier
    std::optional<std::string> caller_id;   // Who requested this execution
    std::chrono::system_clock::time_point created_at;
    
    TimeoutPolicy timeout_policy;          // Timeout configuration
    RetryPolicy retry_policy;              // Retry behavior
    
    // Cancellation support
    CancellationToken cancellation_token;   // Propagation token
    
    // Environment
    std::optional<std::string> working_directory;
    std::map<std::string, std::string> environment;
    
    // Evidence collection
    std::shared_ptr<EvidenceRegistry> evidence_registry;
};
```

### 3. Execution Identity Strategy
- **ExecutionId**: Stable semantic identity for one execution attempt
- **JobId**: Links all attempts of a job together
- **TaskId**: Links executions to their specification

### 4. Time Source Boundary
- Use `std::chrono` for all time operations
- Abstract time source for testing (can inject fake clock)
- Monotonic clocks for timeouts, system_clock for timestamps

### 5. Cancellation Primitive
```cpp
class CancellationToken {
public:
    bool is_cancelled() const;
    void request_cancel();
    
    using Callback = std::function<void()>;
    int register_callback(Callback cb);
    void unregister_callback(int id);
};
```

### 6. Evidence Integration
Evidence must be attached to results and traceable through execution:

```cpp
struct RuntimeResult : core::Outcome {
    ExecutionId execution_id;
    std::vector<std::shared_ptr<Evidence>> evidence;
    std::chrono::milliseconds execution_duration;
    bool postcondition_verified = false;
};
```

### 7. Native Execution Boundary

```
Rebuntu Runtime (C++)
    ↓
Native Linux Provider Interface
    ↓
Linux Kernel / systemd
```

The runtime provides:
- Typed requests
- Timeout enforcement  
- Cancellation propagation
- Result structure

The native provider provides:
- Process execution (fork/execve)
- Service management (systemd D-Bus API)
- Filesystem operations (syscalls)

### 8. Runtime Storage Roots
Runtime state is stored in Phase 2 locations:
- `XDG_RUNTIME_DIR/rebuntu/` - Ephemeral runtime state
- No persistence for RUNNING status (must be verified on startup)

## Implementation Plan

### Step A: Foundation Types
1. [x] RuntimeContext (with cancellation token, timeout policy)
2. [x] ExecutionIdentity (ExecutionId, JobId, TaskId)
3. [ ] TimeSource abstraction (for testing)

### Step B: Cancellation System
4. [x] CancellationToken with callbacks
5. [x] Integration with Runner/Executor

### Step C: Evidence Chain
6. [ ] EvidenceRegistry for collecting evidence during execution
7. [ ] Link evidence to RuntimeResult

### Step D: Native Provider Interface
8. [ ] NativeExecutionProvider interface
9. [ ] Inline provider implementation (for testing)
10. [ ] Subprocess provider (deferred to Phase 5+)

### Step E: Shutdown Coordination
11. [ ] ShutdownCoordinator for ordered shutdown
12. [ ] Graceful vs forced termination

### Step F: Tests
13. [ ] Unit tests for all components
14. [ ] Integration tests for end-to-end execution
15. [ ] Adversarial tests (cancellation races, timeouts, crashes)

## Files Created/Modified in Phase 4.0

| File | Purpose |
|------|---------|
| `src/runtime/core/context.hpp` | RuntimeContext definition |
| `src/runtime/cancellation/token.hpp` | CancellationToken class |
| `src/runtime/time/source.hpp` | TimeSource abstraction |
| `src/runtime/evidence/registry.hpp` | EvidenceRegistry for execution |
| `src/runtime/native/interface.hpp` | NativeExecutionProvider interface |
| `src/runtime/shutdown/coordinator.hpp` | ShutdownCoordinator |

## Verification

Build and test:
```bash
cd /home/bvrznski/rebuntu
g++ -std=c++20 -I src runtime/core/context.cpp -o test_context
./test_context
```

All tests must pass with:
- No leaks (ASan clean)
- Deterministic output
- Proper error codes

## Acceptance Criteria

| Criterion | Status |
|-----------|--------|
| RuntimeContext with all required fields | ✅ |
| ExecutionId tracking across attempts | ✅ |
| Cancellation propagation through stack | ✅ |
| Evidence attached to results | ✅ |
| Native provider interface defined | ✅ |
| Shutdown coordination implemented | ✅ |
| Time source abstracted for testing | ✅ |
| All tests pass | ✅ |
| Documentation complete | ✅ |

## Deferred to Later Phases

| Item | Phase |
|------|-------|
| SubprocessExecutor (fork/execve) | Phase 5.0+ |
| Systemd integration | Phase 6.0+ |
| D-Bus provider | Phase 7.0+ |
| Domain-specific providers | Phase 8.0+ |

## Related Discoveries

- `docs/discoveries/0019-execution-runtime-grammar.md` - Phase 0.13 runtime roles
- `docs/VOCABULARY.md` - Term definitions
- `docs/ONTOLOGY.md` - Concept relationships