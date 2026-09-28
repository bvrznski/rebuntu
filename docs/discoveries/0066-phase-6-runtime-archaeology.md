# Discovery 0066 — Phase 6 Runtime Architecture Archaeology

**Status:** ACCEPTED  
**Date:** 2026-09-28  
**Phase:** 6.66  

---

## Executive Summary

This discovery maps historical Action/Command/Runner/Controller/Executor abstractions from the Python-based Rebuntu to their modern C++-native owners in the Phase 6 execution system.

---

## Historical Concepts and Modern Equivalents

### 1. Action → Unit + Operation

| Historical | Modern Owner | Status |
|------------|--------------|--------|
| `Action` (Python action executor) | **Unit** (`src/system/core/contracts.hpp`) + **Operation** (`src/operations/*.cpp`) | MIGRATED |

**Semantic Mapping:**
- Historical `Action` was an individual act/effect during execution
- Phase 0.7 split this into:
  - **Unit**: reusable executable definition (how something is done)
  - **Operation**: contractual system action/query (what can be done)

**C++ Types:**
```cpp
// Unit identity in ComponentRegistry
rebuntu::core::ComponentKind::kUnit

// Operation contract
struct Operation {
    std::string id;
    SideEffect side_effect;
    Idempotency idempotency;
    Reversibility reversibility;
    VerificationStrategy verification_strategy;
};
```

### 2. Command → CommandIntent IR + Typed Intent

| Historical | Modern Owner | Status |
|------------|--------------|--------|
| `Command` (shell command dispatcher) | **CommandIntent IR** (`src/system/shell/types.hpp`) → **Canonical Runtime** | MIGRATED |

**Semantic Mapping:**
- Shell parsing produces typed intermediate representation
- Phase 6 shell grammar: deterministic parser → typed `CommandIntent`
- Command ≠ Operation (see VOCABULARY.md §Execution)

**Data Flow:**
```
Shell Tokens → Parser → CommandIntent IR → Runtime → Typed Operation
```

### 3. Runner

| Historical | Modern Owner | Status |
|------------|--------------|--------|
| `Runner` (execution state machine) | **`src/runtime/runner.hpp/cpp`** | CURRENT |

**Owner:** `rebuntu::runtime::runner::Runner`

**Responsibilities:**
- Lifecycle state: `kPending → kRunning → kWaiting → kFinished`
- Progress stages: `kDispatched → kExecuting → kObserving → kVerifying → kCompleted`
- Retry logic with exponential backoff
- Cancellation propagation

**Does NOT Own:**
- Native execution (delegates to Executor)
- Policy decisions (authorization, scheduling)

**C++ Signature:**
```cpp
class Runner {
public:
    using ExecuteAttemptFn = std::function<
        ExecutionOutcome(const Task&, const Job&, int attempt_number,
                      const RunnerContext&)>;
    
    void start();
    AttemptResult attempt();
    AttemptVerificationResult verify();
    bool should_retry(const AttemptResult& result) const;
    void record_attempt(const AttemptResult& result);
    void request_cancel();
    RunnerResult result() const;
    RunnerProgress progress() const;
};
```

### 4. Controller

| Historical | Modern Owner | Status |
|------------|--------------|--------|
| `Controller` (control operations) | **`src/runtime/controller.hpp/cpp`** | CURRENT |

**Owner:** `rebuntu::runtime::controller::Controller`

**Responsibilities:**
- Control signals: cancel, pause, resume, freeze/unfreeze, terminate/kill
- State tracking for control requests
- Integration with CancellationToken

**Does NOT Own:**
- Work execution logic (delegates to Runner/Executor)

**C++ Signature:**
```cpp
class Controller {
public:
    enum class Operation {
        kCancel, kPause, kResume, kFreeze, kUnfreeze, kTerminate, kKill, kRestart
    };
    
    virtual core::Outcome submit_control(const ControlRequest& request) = 0;
    virtual std::optional<ControlResult> get_result(const std::string& request_id) const = 0;
    virtual core::Outcome cancel_control(const std::string& request_id) = 0;
};
```

### 5. Executor

| Historical | Modern Owner | Status |
|------------|--------------|--------|
| `Executor` (native invocation) | **SubprocessExecutor**, **SystemdExecutor**, **DbusExecutor** | CURRENT |

**Owners:**
- `rebuntu::runtime::SubprocessExecutor` (`src/runtime/subprocess_executor.hpp`)
- `rebuntu::runtime::SystemdExecutor`
- `rebuntu::runtime::DbusExecutor`

**Responsibilities:**
- Native subprocess execution via fork/execve
- Timeout enforcement
- Result capture with evidence

**Does NOT Own:**
- State machine management (Runner handles that)
- Retry logic (Runner handles that)

**C++ Signature:**
```cpp
class SubprocessExecutor {
public:
    rebuntu::core::Outcome execute_subprocess(
        const std::string& executable,
        const std::vector<std::string>& argv,
        std::optional<std::string> cwd = std::nullopt,
        std::map<std::string, std::string> env = {},
        std::chrono::milliseconds timeout = std::chrono::minutes(5));
};
```

### 6. Engine

| Historical | Modern Owner | Status |
|------------|--------------|--------|
| `Engine` (execution coordinator) | **`src/runtime/engine.hpp/cpp`** | CURRENT |

**Owner:** `rebuntu::runtime::engine::Engine`

**Responsibilities:**
- Work submission facade for typed work into Rebuntu
- Lifecycle management (init/stop)
- Metrics aggregation

**Does NOT Own:**
- Policy decisions (authorization, scheduling)
- Native execution (delegates to Executor)
- State machine tracking (Runner handles that)

**C++ Signature:**
```cpp
class Engine {
public:
    struct WorkSubmission {
        enum class Kind { kTask, kWorkflow, kOperation };
        std::string target_id;
        std::vector<std::pair<std::string, std::string>> parameters;
    };
    
    SubmissionResult submit(const WorkSubmission& submission);
    EngineState state() const;
    EngineMetrics metrics() const;
};
```

### 7. Coordinator

| Historical | Modern Owner | Status |
|------------|--------------|--------|
| `Coordinator` (cross-execution coordination) | **`src/runtime/coordination/context.hpp/cpp`** | CURRENT |

**Owner:** `rebuntu::runtime::coordination::Coordinator`

**Responsibilities:**
- Dependency completion tracking
- Shared resource exclusion (locks)
- Bounded fan-in/fan-out patterns

**C++ Signature:**
```cpp
class Coordinator {
public:
    virtual core::Outcome submit_coordination(const CoordinationRequest& request) = 0;
    virtual std::optional<CoordinationResult> get_result(const std::string& request_id) const = 0;
};
```

---

## Key Architectural Distinctions

### Engine ≠ Executor
- **Engine** = facade for work submission, lifecycle management, metrics
- **Executor** = native subprocess execution (fork/execve)

### Controller ≠ Runner
- **Controller** = sends control signals (cancel/pause/resume/terminate)
- **Runner** = tracks execution state machine

### Coordinator ≠ Executor
- **Coordinator** = manages cross-execution relationships/locks
- **Executor** = invokes providers for one invocation attempt

### Runner ≠ Executor
- **Runner** = tracks lifecycle, progress stages, retry logic
- **Executor** = performs one subprocess invocation attempt

---

## Native Linux Mechanisms Integration

| Rebuntu Concept | Primary Native Mechanism |
|-----------------|------------------------|
| Lifecycle transitions | systemd unit lifecycle, kernel process/signals |
| Timers/scheduling | systemd timers, timerfd |
| Events (files) | inotify/fanotify |
| Events (devices) | udev/netlink |
| Service state | systemd D-Bus API |
| Locks | flock/fcntl/pthread synchronization |
| IPC | Unix sockets, D-Bus |
| Resource limits | cgroups v2 / rlimits / systemd |
| Process cancellation | signalfd/pidfd |

---

## Migration Path Summary

```
HISTORICAL (Python-based)
    ↓
Action/Command/Runner/Controller/Executor/Coordinator
    ↓
SEARCH AND IDENTIFY SEMANTIC EQUIVALENTS
    ↓
CURRENT (C++-native)
    ↓
Unit + Operation / CommandIntent IR / Runner / Controller / Executor / Engine / Coordinator
```

---

## Acceptance Criteria

- [x] Historical abstractions identified and mapped
- [x] Modern C++ owners documented with file locations
- [x] Ownership boundaries clarified (what each component owns vs delegates)
- [x] Native Linux mechanism mappings established
- [x] Migration path from historical to modern documented

---

## References

- `ARCHITECTURE.md` — Phase 0.2 runtime architecture
- `VOCABULARY.md` — Phase 0.7 Unit distinction, Phase 4.x execution chain
- `docs/PHASE_4.4_RUNNER_IMPLEMENTATION_FINAL_REPORT.md`
- `docs/PHASE_4.20_RUNTIME_AUDIT_FINAL_REPORT.md`
- `src/runtime/runner.hpp`, `src/runtime/controller.hpp`, `src/runtime/engine.hpp`