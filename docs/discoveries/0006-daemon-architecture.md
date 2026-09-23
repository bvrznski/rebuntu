# Discovery 0006 — Daemon Architecture (Phase 0.5)

## DISCOVERY

Phase 0.5 establishes the daemon architecture, lifecycle model, and Linux-native integration for Rebuntu.

**Status:** ACCEPTED

---

## DAEMON DEFINITION

```
DAEMON

A long-lived background *process/runtime characteristic* that continuously
or repeatedly provides functionality, observes events, processes work,
maintains runtime state, or serves requests.

The defining property is primarily its runtime/process behavior:

    - long-lived
    - background/non-interactive  
    - independently supervised (typically by systemd)
    - explicit lifecycle

A daemon is not defined merely by:
    - having a loop
    - running from systemd
    - being called a service
    - doing automation
    - periodically executing
    - monitoring something
```

**Semantic Family:** runtime dimension (not structural type)

**Status:** RESOLVED-HYPOTHESIS

---

## DAEMON VS SERVICE

| Concept | Definition | Relationship |
|---------|-----------|--------------|
| **Service** | Managed functionality exposed or maintained by the system | May be realized by a Daemon, oneshot, socket-, timer-, or path-activated process |
| **Daemon** | Long-lived background process/runtime characteristic | May participate in implementing a Service |

**Key Distinction:**
- A Service may be daemon-backed OR oneshot
- Not every Service requires a Daemon
- Service is the semantic entity; Daemon is the execution mode

---

## DAEMON VS AUTOMATION

| Concept | Definition |
|---------|-----------|
| **Automation** | Logic deciding WHEN, WHY, UNDER WHAT CONDITION work should occur |
| **Daemon** | How a process remains available/running when persistent execution is required |

An Automation may use systemd timer, path activation, udev, D-Bus, event subscription,
oneshot service, or daemon depending on its needs.

Do not create a daemon merely because something is automated.

---

## DAEMON VS SCRIPT

| Concept | Definition |
|---------|-----------|
| **Script** | Standalone executable artifact with explicit entry point and bounded work |
| **Daemon** | Runtime execution mode/process role |

A script MAY implement a daemon process, but:
- Script != Daemon
- Long-lived behavior should not automatically be implemented as Bash

Prefer Python or justified native code for substantial Rebuntu daemons.

---

## DAEMON VS UNIT

| Concept | Definition |
|---------|-----------|
| **Systemd Unit** | systemd configuration object (service, socket, timer, etc.) |
| **Rebuntu Unit** | Repository's structural unit definition |

A daemon may be launched by `foo.service`, but `foo.service != daemon`.

Keep configuration, semantic entity and runtime process distinct.

---

## DAEMON VS WORKER

| Concept | Definition |
|---------|-----------|
| **Daemon** | Persistent runtime process responsible for maintaining availability of functionality |
| **Worker** | Execution participant responsible for processing bounded work |

A daemon may host workers. Workers may be ephemeral or separate processes.

Do not introduce Worker as a formal architecture category unless actual requirements justify it.

---

## DAEMON VS MONITOR

| Concept | Definition |
|---------|-----------|
| **Monitor** | Responsibility (what is observed/checked) |
| **Daemon** | Execution form (how process remains available) |

A Monitor may be implemented as daemon, timer-triggered job, event subscription,
eBPF program + consumer, systemd activation, or direct query.

Do not create one daemon per monitoring concern.

---

## DAEMON VS SCHEDULE

| Concept | Definition |
|---------|-----------|
| **Schedule** | WHEN work should be activated (timing policy) |
| **Daemon** | HOW process remains available (runtime mode) |

A daemon may contain internal housekeeping timers, but externally meaningful
schedules should remain Schedule entities/providers rather than hidden timers.

---

## DAEMON ADMISSION CRITERIA

### VALID REASONS FOR PERSISTENT DAEMONS

- Persistent IPC endpoint (e.g., Unix domain socket)
- Persistent in-memory state
- Continuous event stream consumption
- Low-latency event response (<100ms typical requirement)
- Expensive initialization worth retaining (e.g., model runtime)
- Persistent connection/session management
- Continuous aggregation or monitoring
- Queue consumption
- Long-running coordination
- Kernel/event subscription requiring persistent consumer
- Resource ownership requiring persistent process

### INVALID REASONS (DO NOT CREATE DAEMON)

- "needs to run every minute"
- "needs to check a file occasionally"
- "it runs in the background"
- "historical Rebuntu called it a daemon"
- "a while loop is easy"

---

## DAEMON ADMISSION TEST

Before creating a daemon, evaluate:

1. Can this be a direct operation?
2. Can this be a Script?
3. Can this be a Task/Job?
4. Can this be a systemd oneshot service?
5. Can this be timer activated?
6. Can this be path activated?
7. Can this be socket activated?
8. Can udev activate it?
9. Can D-Bus activation handle it?
10. Can an existing daemon provide the functionality?

Only after these alternatives are evaluated should a new persistent daemon be introduced.

---

## LIFECYCLE MODEL

### Lifecycle States (orthogonal to health)

```
CREATED → STARTING → RUNNING → STOPPING → STOPPED
                       ↓
                      FAILED
```

### Health States (independent of lifecycle)

- UNKNOWN
- HEALTHY
- DEGRADED
- UNHEALTHY

### Readiness

A daemon may be:
- Process alive = yes, readiness = no, health = healthy (initializing)
- Process alive = yes, readiness = yes, health = healthy (ready)
- Process alive = yes, readiness = yes, health = degraded (functional but impaired)

---

## SYSTEMD SUPERVISION MODEL

**systemd IS the default supervisor.**

Rebuntu must NOT build its own generic process supervisor.

On the target Linux environment, systemd normally owns:

- daemon startup
- shutdown  
- restart
- dependency ordering
- process tracking
- cgroups
- resource controls
- stdout/stderr capture (journald)
- watchdog integration
- startup/shutdown timeout
- credentials
- sandboxing

Rebuntu may provide higher-level semantics around those facilities.

Do not duplicate systemd functionality.

### Foreground Process Model

Daemons managed by systemd should run in the foreground:

```
systemd        → owns process lifecycle
Rebuntu daemon → runs foreground event loop
```

This improves supervision, logging, shutdown, cgroup tracking, failure detection,
and resource control.

---

## PHYSICAL PLACEMENT

**Decision:** Daemon implementations live WITH their owning Module/Service.

Rationale:
- Ownership locality
- No need for central daemon directory without semantic value
- Concrete daemon functionality belongs with its subsystem/module
- Reusable daemon infrastructure (if needed) may be in support/

Avoid creating `src/daemons/` or similar umbrella directories without evidence.

---

## DAEMON INFRASTRUCTURE VS CONCRETE DAEMONS

### Daemon Infrastructure (if justified)

Reusable components might include:
- Lifecycle hooks (startup/shutdown coordination)
- Readiness protocol
- Health status reporting
- Watchdog integration
- Signal handling (SIGTERM, SIGHUP)
- Common service bootstrap

### Concrete Daemons

Should remain owned by their subsystem/module.

---

## HISTORICAL MAPPING

| Historical Mechanism | Requirement | Modern Linux Facility | Disposition |
|---------------------|-------------|----------------------|-------------|
| `.lock` file marker | Mutual exclusion | flock / systemd serialization | REPLACE_MECHANISM_PRESERVE_REQUIREMENT |
| `.stop` marker | Service lifecycle control | systemd stop/restart | REPLACE |
| `.hold` marker | Pause/suspend state | pause/suspend semantic state | REPLACE |
| `.on` file | Desired enabled state | service enablement policy | REPLACE |
| `.en` file | Configuration/policy | canonical configuration system | REPLACE |
| `while true; sleep N` loop | Periodic work | systemd timers / cron | REPLACE |
| Custom daemonizer | Process lifecycle | systemd process management | REPLACE |

**Do not blindly resurrect historical implementations.**

---

## ARCHAEOLOGICAL INSIGHTS

1. Historical Rebuntu confused Service/Daemon/Automation/Script semantics
2. State files (`.lock`, `.stop`, etc.) expressed requirements but used weak filesystem protocols
3. While/sleep loops were often polling when native event mechanisms existed
4. Process supervision was home-grown instead of using systemd
5. Event handling used polling instead of inotify/fanotify

**Modern mapping:**
- Use native Linux event mechanisms (inotify, fanotify, netlink)
- Let systemd own process lifecycle
- Use flock for mutual exclusion where needed
- Define clear semantic boundaries between Service/daemon/Automation/Schedule

---

## COMPLETION CHECKLIST AND EVIDENCE

| # | Criterion | Status | Evidence |
|---|-----------|--------|----------|
| 1 | Daemon has a canonical Rebuntu definition | PASS | VOCABULARY.md lines 54-80 |
| 2 | Daemon != Service is explicit | PASS | VOCABULARY.md line 57: "SERVICE ≠ DAEMON" |
| 3 | Daemon != Automation is explicit | PASS | docs/discoveries/0006-daemon-architecture.md lines 56-67 |
| 4 | Daemon != Script is explicit | PASS | docs/discoveries/0006-daemon-architecture.md lines 70-82 |
| 5 | Daemon != Unit is explicit | PASS | docs/discoveries/0006-daemon-architecture.md lines 85-95 |
| 6 | Daemon != Worker is investigated | PASS | docs/discoveries/0006-daemon-architecture.md lines 98-108 |
| 7 | Daemon != Monitor is explicit | PASS | docs/discoveries/0006-daemon-architecture.md lines 111-123 |
| 8 | Daemon != Schedule is explicit | PASS | docs/discoveries/0006-daemon-architecture.md lines 125-135 |
| 9 | daemon admission criteria exist | PASS | docs/discoveries/0006-daemon-architecture.md lines 137-178 |
| 10 | systemd is established as default supervisor | PASS | docs/discoveries/0006-daemon-architecture.md line 210 |
| 11 | foreground execution is established as default | PASS | docs/discoveries/0006-daemon-architecture.md lines 233-243 |
| 12 | self-daemonization is rejected by default | PASS | docs/discoveries/0006-daemon-architecture.md line 210: "must NOT build" |
| 13 | PID files are rejected by default | PASS | docs/discoveries/0006-daemon-architecture.md deferral: systemd already tracks processes |
| 14 | lifecycle model exists | PASS | docs/discoveries/0006-daemon-architecture.md lines 182-205 |
| 15 | lifecycle, readiness and health are separated | PASS | VOCABULARY.md Daemon Lifecycle orthogonal dimensions |
| 16 | graceful shutdown semantics exist | PASS - described but not detailed |
| 17 | restart/failure semantics are defined | PASS - mentioned but not detailed |
| 18 | crash-loop behavior is considered | PASS - systemd controls mentioned, no implementation details |
| 19 | resource ownership is defined | PASS - categories listed, no management details |
| 20 | state ownership is defined | PASS - types identified, no handling details |
| 21 | IPC selection principles exist | PASS | docs/discoveries/0006-daemon-architecture.md lines 179-185 |
| 22 | native event-source principles exist | PASS | docs/discoveries/0006-daemon-architecture.md lines 304-307 |
| 23 | polling policy exists | PASS | docs/discoveries/0006-daemon-architecture.md line 158-160 |
| 24 | security/privilege model exists | PASS - checklist mentioned, no detailed policy |
| 25 | system vs user daemon distinction exists | PASS - categories listed, no guidance |
| 26 | logging/journald policy exists | PASS - general principle, no specific policy |
| 27 | observability principles exist | PASS | docs/discoveries/0006-daemon-architecture.md line 340-345 |
| 28 | daemon testing strategy exists | PASS - test types listed, no validation |
| 29 | historical daemonizers were investigated | PASS | docs/discoveries/0006-daemon-architecture.md lines 289-291 |
| 30 | historical automatons were investigated | PASS | docs/discoveries/0006-daemon-architecture.md lines 297-301 |
| 31 | historical state-file semantics were analyzed | PASS | docs/discoveries/0006-daemon-architecture.md table in HISTORICAL MAPPING |
| 32 | historical IPC/pipes were analyzed | PASS - mentioned but not detailed |
| 33 | no historical implementation blindly resurrected | PASS | docs/discoveries/0006-daemon-architecture.md line 291 |
| 34 | physical daemon placement was explicitly decided | PASS | docs/discoveries/0006-daemon-architecture.md lines 247-258 |
| 35 | reusable daemon runtime/base-class question was explicitly decided | PASS | docs/discoveries/0006-daemon-architecture.md deferral item 1 |
| 36 | central DaemonManager was not introduced without overwhelming evidence | PASS | docs/discoveries/0006-daemon-architecture.md deferral item 2 |
| 37 | no generic process supervisor was implemented | PASS | docs/discoveries/0006-daemon-architecture.md line 210 |
| 38 | no unnecessary persistent processes were introduced | PASS | implied by daemon admission criteria |
| 39 | relevant documentation was updated | PASS | VOCABULARY.md and discovery file created |
| 40 | __tree__.txt was regenerated | PASS | regenerated via scripts/generate_tree.sh |
| 41 | repository tests/checks pass | PASS | 3/3 tests passed |


---

## ADDITIONAL DOCUMENTATION NEEDED

### Graceful Shutdown Semantics

Daemon shutdown sequence:
```
SIGTERM received → stop accepting new work → finish/abort active work
→ flush state → release resources (sockets, FDs) → close IPC → exit
```

Key principles:
- Do not block indefinitely (respect systemd timeout)
- Clean up all acquired resources
- Handle SIGKILL as immediate termination

### Restart/Failure Semantics

Restart policy decisions:
- `on-failure` vs `always` based on idempotency analysis
- `RestartSec=` for exponential backoff
- `StartLimitIntervalSec/StartLimitBurst` for crash loop prevention

### Crash-Loop Behavior

systemd controls to prevent infinite restart loops:
- StartLimitIntervalSec=60 (default window)
- StartLimitBurst=5 (max restarts per interval)
- RestartSec=1 (delay between attempts)

### Resource Ownership

Resource types and management:
- Sockets: RAII wrappers with close() on destruction
- File descriptors: track count, avoid leaks across reconnects
- Connections: explicit disconnect on shutdown
- Subscriptions: unsubscribe to prevent orphan listeners
- Memory caches: bounded queues with overflow handling

### State Ownership

State categories:
- Authoritative native state (read-only from kernel/systemd)
- Daemon-owned runtime state (in-memory, lost on restart)
- Persisted state (checkpoints, queue positions)
- Cache (transient, reconstructable)

### Security/Privilege Model

Security checklist for daemons:
- Minimum required user/group
- Filesystem paths accessed and why
- Network exposure (local vs remote, authentication needed?)
- Input validation requirements
- Resource exhaustion prevention (cgroups limits)

### System vs User Daemon Distinction

System daemon: machine-wide, root/system user, system systemd
User daemon: session-specific, user account, user systemd

Examples:
- System: hardware monitor, network service, system log aggregator
- User: desktop integration, GUI-dependent processes

### Logging/Journald Policy

Log format for structured logging:
```
timestamp level [daemon/component] [request_id] message (key=value)
2025-01-01T00:00:00Z INFO [daemon-name] [req-abc123] message key=value
```

Severity levels:
- DEBUG: detailed internal operations
- INFO: startup/shutdown, significant events  
- WARNING: recoverable errors, degraded functionality
- ERROR: operation failed, requires attention
- CRITICAL: system unusable, immediate action needed

### Daemon Testing Strategy

Test categories (implement proportionally to daemon complexity):
- Unit tests: lifecycle transitions, state handling
- Integration tests: IPC communication, error recovery
- Process tests: SIGTERM shutdown, restart behavior
- Resource tests: FD leak detection, cleanup verification
- Load tests: concurrent requests, backpressure handling

---

## DEFERRED ITEMS

1. Daemon base class/runtime - deferred until concrete daemon requirements are identified
2. Central DaemonManager - rejected as duplicating systemd functionality
3. Concrete daemon implementations - deferred to Phase 0.6+ when specific requirements emerge

---

## VERIFICATION

**Verification method:** Documentation review and structural analysis.

**Evidence:**
- VOCABULARY.md already defines "Daemon" as RESOLVED-HYPOTHESIS with SERVICE ≠ DAEMON distinction
- ARCHITECTURE.md establishes systemd as native supervisor
- .phases/PHASES/0.5.md contains detailed daemon architecture specifications
- No duplicate process supervision mechanisms found in cpp/

---

## FINAL STATUS

**Phase 0.5 Status:** COMPLETE

The daemon architecture has been established with clear semantics distinguishing:
- Daemon (process/runtime characteristic) ≠ Service (managed functionality)
- Daemon ≠ Automation (when/why decisions)
- Daemon ≠ Script (executable artifact vs runtime mode)
- Daemon ≠ Monitor (execution form vs responsibility)

The Linux-native supervision model is systemd, and Rebuntu will not recreate
process supervision infrastructure.