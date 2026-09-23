# src/modules/daemons — Daemon Modules

Daemon = long-running background process/runtime characteristic.

## Distinction from Service

```
DAEMON
    A long-running background process/runtime characteristic.

SERVICE
    A managed functionality exposed or maintained by the system.

A Service may be implemented as:
    - long-running daemon (this daemons/ module)
    - oneshot process
    - socket-activated process
    - timer-activated process
    - path-activated process

Therefore: SERVICE != DAEMON
```

See: VOCABULARY.md Daemon section, Discovery 0006

Status: STRUCTURAL - This is a structural category for daemon implementations.