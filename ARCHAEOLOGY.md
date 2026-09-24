# Rebuntu — Archaeology (Phase 0.0)

Historical Rebuntu is a **source** of terminology, problems, requirements,
design ideas, failed experiments, and useful abstractions. It is **not**
implementation authority.

## The corpus

- `.phases/PHASES/` — ~thousands of phase specification files (0.0 → 45.x),
  including `0.0.md`, `0.1.md` (structural taxonomy), `1.x` (installation /
  user definition), `2.x` (system foundation), `3.x` (semantic / BitNet /
  containers), `4.x` (core runtime & coordination), and per-domain systems
  (5.x observation, 12.x process, 31.x service, 32.x storage, 33.x network,
  36.x configuration, 37.x secrets, 39.x event timeline, 40.x–45.x
  search/automation/knowledge-graph/control-plane).
- `.phases/roadmap` — the full historical phase plan.
- `.phases/TASK`, `.phases/shell.md` — migration and shell-language material.
- `.phases/*.zip` and `.phases/PHASES/BACKUP/` — archived / backup material.

## The archaeology rules

**Status is not the same thing. Do not conflate them:**

```
IDEA EXISTS
   !=  STUB EXISTS
   !=  IMPLEMENTATION EXISTS
   !=  IMPLEMENTATION VERIFIED
   !=  PRODUCTION-WORTHY CAPABILITY
```

A historical spec describing a system does **not** mean that system exists,
works, or is desired in the current architecture.

**Preserve the problem; re-evaluate the implementation.**

When mining the corpus:
1. Extract the *problem* being solved and the *evidence* for it.
2. Re-derive the solution against the **current** architecture (C++20, native,
   the `system` package) and the current AGENTS.md invariants.
3. Record any architectural discovery in `docs/discoveries/` with a
   DISCOVERY / CANDIDATE / ACCEPTED / DEFERRED / REJECTED / SUPERSEDED
   disposition.
4. **Do not** mechanically port a historical implementation.
5. **Do not** treat a historical directory layout as the current layout.

## Terminology mining

Historical terms (Setup / Configuration / Setting / Option / Preference /
Property / Attribute / Policy; Service vs Daemon; Task vs Job vs Operation vs
Procedure; Workflow / Phase / Stage / Step; Thread; Fact / Assertion /
Condition; Health vs Readiness) are **carried into VOCABULARY.md** as
evidence-backed starting hypotheses — preserved because they express distinct
concepts, not because they are old.

## What to do with the corpus

- Use it for **vocabulary**, **problem discovery**, and **native-mechanism
  mapping** (which Linux primitive underlies each historical capability).
- Keep it **read-only**. Do not modify, clean, or "fix" the corpus in Phase
  0.0. It is a primary source.
- If a future phase re-implements a historical capability, cite the source
  phase in a discovery record.

## Disposition

Phase 0.0 **records** the corpus as HISTORICAL and establishes how to use it.
It does **not** reconstruct historical Rebuntu.

## Historical Unit Architecture (Phase 0.1 → Phase 0.7)

### Historical Concepts

Historical Rebuntu had a `Unit` concept based on:
- File-based discovery (`main.sh`, `main.py`) in specific directories
- State machine with states: `locked`, `disabled`, `inactive`, `guarded`, `active`, `stop`
- Chain relationships between Units for composed execution
- `pass/register/activate` lifecycle phases

### Translation to Phase 0.7

| Historical State/Concept | Modern Equivalent |
|--------------------------|-------------------|
| `locked` | Mutual exclusion / policy check |
| `disabled` | Configuration availability (off) |
| `inactive` | No active execution pending |
| `guarded` | Policy/precondition checks |
| `active` | Execution currently running |
| `stop` | Cancellation request |
| `pass/register/activate` | Discovery → Validation → Registration |
| `chain` | Workflow / Pipeline |

### Historical Unit → Phase 0.7 Mapping

- **Unit as executable plugin** → Deprecated
- **Unit as Task** → Deprecated (Task is now parameterized work specification)
- **Unit as process** → Process lifecycle managed by systemd/daemon, Unit is semantic contract
- **Unit as Automaton** → Merged into Workflow semantics
- **Unit as Service** → Service remains separate with availability/lifecycle
- **Unit as Script container** → Scripts remain separate; Unit may invoke Scripts

### Discovery Mechanism

| Historical | Modern |
|------------|--------|
| `main.sh` / `main.py` files in directories | ComponentRegistry with kUnit kind, stable IDs |

### Implementation Language Neutrality

Historical Rebuntu experimented with:
- SH/PY units (hybrid execution)
- Bilingual execution

The modern Phase 0.7 architecture preserves the useful principle that **Unit semantics should not depend on implementation language**, while standardizing on C++20 for authoritative runtime.

## Phase 0.2 Runtime Architecture Archaeology

### Historical Concepts

Phase 4.x historical Rebuntu had early runtime/execution concepts:
- `runtime/controller.cpp` — Runtime controller subsystem
- `runtime/engine.cpp` — Runtime engine
- `runtime/dispatcher.cpp` — Command dispatcher
- `runtime/executor.cpp` — Execution subsystem
- `runtime/runner.cpp` — Execution runner

### Archaeology of Deferred Implementations

These Phase 4.x files were found in `src/system/` but are:
1. Not referenced in cpp/CMakeLists.txt (not built)
2. In directories marked as "RESERVED" per ARCHITECTURE.md
3. Claiming Phase 4.x implementations in their headers

**Decision:** Deferred until operational architecture phase (Phase 0.2+).

| Historical File | Modern Equivalent | Status |
|-----------------|-------------------|--------|
| runtime/controller.cpp | Controller coordination logic | Deferred to Phase 4.6 |
| runtime/engine.cpp | Runtime engine (execution coordinator) | Deferred to Phase 4.2 |
| runtime/dispatcher.cpp | Work dispatcher (route to mechanisms) | Deferred to operational architecture |
| runtime/executor.cpp | Execution invocation mechanism | Deferred to operational architecture |
| runtime/runner.cpp | Execution runner (state machine) | Deferred to operational architecture |
| state/provider_*.cpp | Native state providers | Deferred to state management phase |

### Translation to Phase 0.2

The operational grammar established in Phase 0.2 reinterprets these concepts:

| Historical Concept | Modern Operational Grammar Equivalent |
|-------------------|---------------------------------------|
| Runtime controller | Coordination decisions across components |
| Runtime engine | Infrastructure for instantiation/execution |
| Work dispatcher | Dispatcher: routes work to execution mechanisms |
| Executor | Invokes concrete implementation/providers |
| Runner | Progresses execution according to plan |

### Native Linux Mechanisms Mapping

The modern Phase 0.2 operational grammar maps historical concepts to native mechanisms:

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

### Phase 0.2 Acceptance Criteria

The operational grammar is **CURRENT** and established via:
- `src/runtime/contracts.hpp` — State dimensions, Request/Event/Signal/Trigger
- `src/runtime/runner.hpp` — Runner state machine and progress tracking
- `src/runtime/executor.hpp` — Executor base class with InlineExecutor implementation
- `src/runtime/dispatcher.hpp` — Dispatcher and execution mode selection

**Phase 0.2 Status:** COMPLETE — Operational grammar defined and implemented.

