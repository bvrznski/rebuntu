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

### Enums
- **ServiceState**: unavailable, activating, available, degraded, deactivating, failed
  - Helpers: `is_available()`, `is_unavailable()`
- **ServiceActivation**: none, persistent, manual, boot, on-demand, socket-activated, dbus-activated, path-activated, device-activated, timer-triggered, event-triggered
- **DependencyKind**: required, optional, ordering, soft

### Structs
- **ServiceDependency**: { service_id: string, kind: DependencyKind }
- **ServiceInfo**: 
  - id (string)
  - title (string) - human-readable name
  - description (string) - human-readable description  
  - categories (set<string>) - category tags for grouping/discovery
  - activation (ServiceActivation) - how service is activated
  - enabled (bool) - desired state: should be available?
  - default_interface (optional<string>) - default IPC/interface endpoint
  - dependencies (vector<ServiceDependency>)
  - requires_root (bool)

### Class
- **ServiceRegistry**: 
  - `register_service(ServiceInfo)` - register a new service
  - `contains(std::string_view)` - check if service exists
  - `find(std::string_view)` - get service info by id
  - `size()` / `empty()` - container accessors
  - `all()` / `enabled()` / `by_category()` - querying methods
  - `validate()` - structural integrity validation (checks for duplicates and unknown dependencies)

### Features
- C++20 implementation with `<string_view>` support
- Header-only contracts following Rebuntu patterns
- Structural integrity validation (duplicate detection, dependency resolution)
- Sorted queries for deterministic output

---

## PHYSICAL PLACEMENT DECISION

Service definitions live WITH owning Module/Service.
No central services/ directory introduced.

Rationale: Ownership locality - concrete implementation belongs with its subsystem/module.
Rebuntu is C++-native; Service model is a data structure, not a process supervisor.

---

## SERVICE MANAGER DECISION

NO shadow systemd or process supervisor.
systemd owns native lifecycle; Rebuntu manages semantic intent.

Rebuntu provides:
- Data structures for service catalog (ServiceRegistry)
- State models (ServiceState, ServiceActivation, DependencyKind)
- Structural validation
- No runtime bus, event system, or process supervision

systemd provides:
- Process lifecycle (start/stop/restart)
- PID management
- Resource controls (cgroups)
- Watchdog integration
- journald logging

---

## VERIFICATION

### Build Verification
```
cd cpp
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release  # configure
cmake --build build -j$(nproc)                 # build: SUCCESS
```

### C++20 Standard
CMake configured with `-std=c++20` - all includes and types work correctly.

---

## PHASE 0.6 COMPLETION STATUS

**Status:** COMPLETE

Service architecture established with:
- [x] Service = managed functionality with availability/lifecycle semantics
- [x] Service != Daemon distinction (runtime dimension vs semantic entity)
- [x] Service != systemd .service unit (semantic vs deployment artifact)
- [x] Service != Module distinction (semantic vs structural boundary)
- [x] Activation models: persistent, socket, dbus, path, device, timer, event
- [x] Dependency kinds: required, optional, ordering, soft
- [x] ServiceRegistry data structure with validation
- [x] C++20 implementation in cpp/include/system/core/contracts.hpp
- [x] No shadow systemd or process supervisor introduced
- [x] Physical placement decided (with owning Module/Service)
