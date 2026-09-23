# src/adapters/ — native and external mechanism integration

Adapters isolate Linux-native and third-party mechanisms behind stable Rebuntu
contracts. They translate between Rebuntu's semantic vocabulary and the
underlying platform's API.

## Categories

| Subdirectory | Responsibility |
|---|---|
| `systemd/` | systemd D-Bus integration (service lifecycle, timer, socket activation) |
| `procfs/` | procfs observation providers (process, memory, CPU stats) |
| `sysfs/` | sysfs device and driver information |
| `cgroups/` | cgroups v2 resource control and observation |
| `dbus/` | generic D-Bus helpers (signals, calls, properties) |
| `netlink/` | netlink socket integration (network, routing, links) |
| `inotify/` | filesystem change notification |
| `fanotify/` | filesystem event monitoring |
| `shell/` | shell command execution abstractions (bounded argv, timeout, evidence) |

## Principles

- **Adapters isolate mechanism**: they never own semantics or policy.
- **Provider interface**: adapters usually implement an interface declared in
  `interfaces/` or within a module's contract surface.
- **Bounded output**: commands executed via shell adapters produce bounded
  stdout/stderr, not arbitrary text streams.

Status: PREPARED (Phase 0.1 infrastructure). No adapters defined yet.