# Rebuntu Phase 7.0 — Observation Architecture

## Executive Summary

Phase 7 establishes the canonical observation architecture through which Rebuntu learns current system facts without confusing observation with control, diagnosis, recovery, policy, or desired state.

**Status: COMPLETE**

### Key Distinctions Established

| Concept | Meaning |
|---------|---------|
| **Observation** | Raw, source-bound evidence obtained at a specific time |
| **Fact** | Typed claim derived from one or more observations under explicit rules |
| **CurrentState** | Composed snapshot of observations/facts for a bounded subject/domain/time |

### Architecture Overview

```text
Native Linux Sources (procfs/sysfs/systemd D-Bus/netlink)
    ↓
Acquisition (bounds-checked, timeout-limited)
    ↓
Raw Observation + Source Locator + Timestamp
    ↓
Parsing/Normalization (source-specific → canonical)
    ↓
Typed Fact (with provenance chain)
    ↓
Snapshot Composition (temporal coherence, freshness tracking)
    ↓
Query/Shell/Service Consumer
```

## 1. Core Types

### ObservationIdentity — Stable Identity for Observed Entities

```cpp
struct ObservationIdentity {
    std::string domain_id;      // e.g., "nginx.service", "proc:1234:boot:5678"
    ObservationDomain domain;
    std::optional<std::string> name;  // NOT used for identity
};
```

**Key Principles:**
- Transient properties (PIDs, names, paths) are NOT stable identifiers
- Use boot timestamp + PID for process identity to handle PID reuse
- Use unit name + type for systemd services

### Observation — Raw Evidence with Provenance

```cpp
struct Observation {
    ObservationIdentity subject;
    std::string field;                    // e.g., "state", "memory_kb"
    std::optional<std::string> raw_value;
    std::optional<std::string> normalized_value;  // Canonical form
    std::string source;                   // procfs, systemd, sysfs
    std::chrono::system_clock::time_point acquired_at;
    std::optional<std::chrono::system_clock::time_point> event_time;  // Source timestamp
    std::optional<std::chrono::steady_clock::time_point> monotonic_sample;
    ObservationQuality quality;
    std::optional<core::Error> error;
};
```

**Key Principles:**
- Raw evidence only (no inference)
- Timestamped acquisition time
- Source-identified provenance

### Fact — Typed Claim with Traceability

```cpp
struct Fact {
    ObservationIdentity subject;
    std::string predicate;                // e.g., "is_active", "running"
    std::optional<std::string> canonical_value;
    TruthValue truth;                     // kTrue, kFalse, kUnknown
    std::vector<ObservationIdentity> supporting_observations;
    bool direct_observation;
};
```

### Snapshot — Current-State Projection

```cpp
struct Snapshot {
    std::string snapshot_id;
    std::chrono::system_clock::time_point snapshot_time;
    std::optional<std::chrono::milliseconds> elapsed_ms;
    std::set<ObservationDomain> observed_domains;
    std::vector<Observation> observations;
    std::vector<Fact> facts;
    SnapshotState state;                  // kComplete, kPartial, kEmpty
    ObservationQuality overall_quality;
};
```

## 2. Domain Support

| Domain | Native Source | Fallback | Cost Class |
|--------|---------------|----------|------------|
| Process | `/proc/[pid]` | None | Cheap |
| Service | systemd D-Bus | systemctl (subprocess) | Moderate |
| Filesystem | `/proc/mounts`, sysfs | None | Cheap |
| Network | netlink/rtnetlink | None | Moderate |
| CPU | `/proc/cpuinfo`, sysfs | None | Cheap |
| Memory | `/proc/meminfo` | None | Cheap |
| Device | sysfs/udev | None | Moderate |
| GPU | vendor APIs, DRM | nvidia-smi (fallback) | Expensive/Waking |
| Power/Thermal | hwmon, sysfs | None | Cheap |

## 3. Freshness and Caching

```cpp
struct FreshnessPolicy {
    std::chrono::milliseconds max_age_ms{std::chrono::seconds(30)};
    bool allow_stale{false};
    bool fail_on_stale{false};
};
```

**Freshness Guidelines:**
- Static topology (CPU, memory): 1 hour or more
- Service state: 30 seconds
- Process state: 5-10 seconds
- GPU/thermal: 1-5 seconds

## 4. Error Handling and UNKNOWN Semantics

```cpp
enum class ObservationQuality {
    kUnknown,
    kPartial,
    kObserved,
    kAuthoritative,
};
```

**UNKNOWN is distinct from:**
- `false` — absence of evidence ≠ evidence of absence
- `0` / empty string — may indicate unavailable, not zero value
- `stale` — old data vs. no data

## 5. Interface Design

```cpp
// Factory functions
std::unique_ptr<SnapshotBuilder> make_snapshot_builder();
std::unique_ptr<CurrentStateView> make_current_state_view();

// Snapshot builder interface
class SnapshotBuilder {
    virtual core::Outcome start(const std::string& id = "") = 0;
    virtual core::Outcome configure_bounds(const ObservationBounds&) = 0;
    virtual core::Outcome add_observation(Observation) = 0;
    virtual core::Outcome add_fact(Fact) = 0;
    virtual std::optional<Snapshot> build() = 0;
};
```

## 6. Safety Guarantees

Observation is read-only:
- No service restarts
- No filesystem mutations
- No GPU clock/power changes
- No network probing
- No package modifications

## 7. Existing Architecture Integration

Phase 7 reuses existing components:

| Phase | Component | Reuse Pattern |
|-------|-----------|---------------|
| 5.24 | Procfs Process Adapter | `ProcessDiscoveryAdapter` interface reused |
| 5.26 | Systemd Service Adapter | `ServiceDiscoveryAdapter` interface reused |
| 5.52 | Observation Bounds | `ObservationBounds` type included from rebuntu::observation namespace |
| 6.52 | Provider Evidence | Pattern extended for observation-specific needs |

## 8. Tests

All tests pass:
```
test_observation_domain: PASS
test_observation_identity: PASS
test_observation_quality: PASS
test_freshness_policy: PASS
test_observation_factory: PASS
test_truth_value: PASS
test_fact: PASS
test_snapshot_state: PASS
test_truncation: PASS
test_snapshot: PASS
test_factory_functions_exist: PASS
```

## 9. Files

| File | Purpose |
|------|---------|
| `src/system/observation/types.hpp` | Core types and interfaces (header-only) |
| `src/system/observation/implementation.cpp` | Implementation of interfaces |
| `tests/unit/observation_architecture_test.cpp` | Unit tests |

## 10. Future Work

- [ ] Integrate procfs process discovery adapter
- [ ] Integrate systemd service discovery adapter  
- [ ] Implement snapshot caching with TTL invalidation
- [ ] Add change detection for historical tracking
- [ ] Implement query engine over snapshots