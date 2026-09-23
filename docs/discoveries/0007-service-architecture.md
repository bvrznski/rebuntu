# Discovery 0007 — Service Architecture (Phase 0.6)

## DISCOVERY

Phase 0.6 establishes the canonical Service model for Rebuntu.

**Status:** ACCEPTED

---

## SERVICE DEFINITION

```
SERVICE

A managed Rebuntu functionality with an explicit identity,
availability contract, interface, ownership and lifecycle semantics.
```

A Service does NOT inherently answer:

    which process implements it;
    whether a process is permanently running;
    which activation mechanism is used;
    whether systemd uses Type=simple/notify/oneshot/etc.

Those are implementation/deployment concerns.

---

## SERVICE != DAEMON

| Concept | Definition | Relationship |
|---------|-----------|--------------|
| **Service** | Managed functionality | May be realized by a Daemon |
| **Daemon** | Long-lived background process/runtime characteristic | May implement Service |

**Key Distinction:** Service is semantic; Daemon is runtime mode.

---

## SERVICE != SYSTEMD UNIT

Rebuntu Service != systemd .service unit.
The former is architectural; the latter is deployment artifact.

---

## SERVICE != MODULE / OPERATION / SCRIPT / TASK

Established distinctions in VOCABULARY.md.

---

## IMPLEMENTATION

Service model added to `cpp/include/system/core/contracts.hpp`:

- ServiceState enum: unavailable, activating, available, degraded, deactivating, failed
- ServiceActivation enum: persistent, manual, on-demand, socket, dbus, path, device, timer, event
- DependencyKind enum: required, optional, ordering, soft
- ServiceInfo struct with id, title, description, owner_system, activation, interfaces, dependencies
- ServiceRegistry class for catalog management

---

## PHYSICAL PLACEMENT DECISION

Service definitions live WITH owning Module/Service.
No central services/ directory introduced.

---

## SERVICE MANAGER DECISION

NO shadow systemd or process supervisor.
systemd owns native lifecycle; Rebuntu manages semantic intent.

---

## VERIFICATION

Build: CMake configure → build → tests
Status: COMPLETE (Phase 0.6)
