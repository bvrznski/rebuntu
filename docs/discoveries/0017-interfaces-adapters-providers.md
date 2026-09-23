# Discovery 0017 — Interfaces, Adapters, Providers & System Boundaries (Phase 0.16)

- **Status:** ACCEPTED
- **Date:** 2026-09-22
- **Author:** Phase 0.16

## Summary

This discovery establishes Rebuntu's external-boundary grammar: how semantic capabilities
remain stable while concrete Linux mechanisms/providers can vary.

Three structural families are established:

| Directory | Responsibility |
|-----------|----------------|
| interfaces/ | Typed contracts and protocols (what, not how) |
| adapters/ | Native mechanism integration (systemd, procfs, D-Bus) |
| support/ | Reusable utilities (logging, config, validation) |

## Canonical Definitions

### Interface
An Interface is a declared contract that consumers depend on. It contains:
- No implementation: Interfaces declare what, not how.
- Static definitions: Types, contracts, message formats, protocols.

### Adapter
An Adapter connects Rebuntu to a specific external/native mechanism. It:
- Isolates mechanism from semantics
- Translates between Rebuntu's semantic vocabulary and the underlying platform API

## Ownership Boundaries

```
High-level mechanisms (operations, workflows, automation)
         ↓
Stable Rebuntu contracts (core: Result/Outcome/Evidence)
         ↓
Interfaces / Adapters / Providers
         ↓
Linux / native / external facilities (systemd, procfs, D-Bus, ...)
```

## Native Linux Mappings

| Concern | Native Mechanism | Boundary Location |
|---------|------------------|-------------------|
| Service lifecycle/control | systemd (D-Bus) | adapters/systemd/ |
| Process observation | procfs, kernel interfaces | adapters/procfs/ |
| Device/hardware state | sysfs, udev | adapters/sysfs/ |

## Privilege Boundaries

**Providers are read-only observers:**
- No elevated privileges required
- No sudo or capability escalation needed
- No filesystem mutation (only reading)
- No process creation or termination
- State is observed, never owned or modified

**Security characteristics:**
- Providers only read from native Linux interfaces (/proc, /sys, D-Bus)
- No secret material handled (no secrets in output or errors)
- No network exposure
- No persistent state storage

## Persistence Requirements

**No persistence required:**
- State providers are transient observers
- State is observed fresh at query time
- No caching or state storage in the adapter layer
- Freshness tracked via timestamp in StateObservation

## Implementation Status

**Current State:**
- C++ provider interface exists at cpp/include/system/state/provider.hpp
- Providers implemented: SystemdStateProvider, ProcfsStateProvider, SysfsStateProvider
- Tests passing: unit.state_provider

## Tests Verified

All tests pass:
- unit.contracts: OK
- unit.runtime_contracts: OK
- integration.cli: OK
- unit.operations: OK
- unit.work: OK
- unit.state_provider: OK

## Remaining Work (Deferred)

**Phase 5+ deferred items:**
- Full D-Bus adapter with signal subscription and property watch
- Dynamic plugin architecture for provider discovery

These are not required for Phase 0.16 completion.

**Status:** COMPLETE — Structural foundation established, native providers implemented and tested.
