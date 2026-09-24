# src/adapters/scheduling — Native Linux Scheduling Adapter

Native Linux scheduling mechanism integration for Rebuntu temporal specifications.

## Overview

This directory provides adapters that translate between Rebuntu's canonical temporal
specifications (Schedule, Deadline, Timeout) and native Linux mechanisms.

**PRINCIPLE:** Rebuntu defines WHAT should happen and WHEN. Native Linux providers
handle the actual scheduling/activation mechanism.

```
Rebuntu Schedule
     ↓
  Adapter
     ↓
systemd timer (or other native mechanism)
     ↓
   activation
```

## Native Mechanism Mappings

### Systemd Timers (Primary Mechanism)

| Rebuntu Concept | systemd Unit Type | Property | Clock Domain |
|-----------------|-------------------|----------|--------------|
| kOnce schedule | .timer | OnCalendar | CLOCK_REALTIME |
| kInterval schedule | .timer | OnUnitActiveSec | CLOCK_MONOTONIC |
| kCron schedule | .timer | OnCalendar | CLOCK_REALTIME |

#### Example: Daily Maintenance

```ini
# Rebuntu Schedule:
# kind: kOnce
# absolute_time: "03:00 daily"
# target_kind: "task"
# target_id: "maintenance.daily"

# systemd.timer translation:
[Timer]
OnCalendar=*-*-* 03:00:00
Persistent=true

[Install]
WantedBy=timers.target
```

#### Example: Interval Schedule

```ini
# Rebuntu Schedule:
# kind: kInterval
# interval: 3600000ms (1 hour)

# systemd.timer translation:
[Timer]
OnUnitActiveSec=1h
Persistent=true
```

### Monotonic Timer Properties

For schedules that should NOT be affected by wall-clock changes:

| Property | Clock Domain | Use Case |
|----------|--------------|----------|
| OnBootSec | CLOCK_BOOTTIME | Time since boot, includes suspend |
| OnStartupSec | CLOCK_MONOTONIC | Since service startup |
| OnActiveSec | CLOCK_MONOTONIC | Since timer activation |

### Filesystem Events

For event-driven rather than time-based scheduling:

| Rebuntu Concept | Native Mechanism | Unit Type |
|-----------------|------------------|-----------|
| Event-triggered | inotify/fanotify | .path unit |
| Device events | udev | .device unit |
| Socket activation | Unix socket | .socket unit |

## Adapter Responsibilities

### ScheduleValidator
- Validate schedule syntax and semantics
- Check for conflicting schedules
- Verify target exists

### ScheduleTranslator
- Convert Rebuntu Schedule to systemd timer unit
- Map clock domains appropriately
- Generate persistent configuration

### ScheduleProvider
- Query native scheduler state
- List active timers
- Inspect timer properties

## Clock Domain Selection Rules

| Use Case | Recommended Clock |
|----------|-------------------|
| Calendar schedule (daily at 03:00) | CLOCK_REALTIME |
| Duration-based timeout | CLOCK_MONOTONIC |
| Boot-relative schedule | CLOCK_BOOTTIME |
| Retry delay | CLOCK_MONOTONIC |

## Persistence

For schedules that must survive reboots:
- Use systemd.timer with Persistent=true
- Store schedule definitions in canonical configuration
- No Rebuntu-specific persistence required

## Integration Points

### C++ Contracts (src/core/time/types.hpp)
```cpp
struct Schedule {
    std::string id;
    ScheduleKind kind;
    std::optional<Timestamp> absolute_time;   // CLOCK_REALTIME or CLOCK_MONOTONIC
    std::optional<Duration> interval;
    // ...
};
```

### systemd Integration

1. Convert Schedule → systemd .timer unit
2. Install to /etc/systemd/system/ (system) or ~/.config/systemd/user/ (user)
3. Enable and start via D-Bus interface
4. Monitor timer state via sd-bus API

## Future Extensions

- timerfd support for process-local timers
- POSIX timers for portable scheduling
- Event loop integration for in-process timers