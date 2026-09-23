# src/units/schedules — Temporal Specification Units

Schedule = temporal specification for when work should be activated.

## Distinction from Cron

```
Schedule
    Rebuntu-level concept
    Can be implemented as:
        - systemd timer
        - cron
        - at
        - internal scheduler
        - external scheduler

Cron
    Particular scheduling implementation (Linux tool)
```

Therefore: Schedule ≠ Cron

The Schedule category describes the Rebuntu abstraction.
Implementation backends may use cron, systemd timers, or other mechanisms.

See: VOCABULARY.md kCron section

Status: STRUCTURAL - This is a structural category for temporal specifications.