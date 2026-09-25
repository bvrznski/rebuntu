# Phase 5.1 — System Event Collector Final Report

**Status: IMPLEMENTING (Phase foundation complete)**

## Executive Summary

Phase 5.1 implements the foundational System Event Collector for Rebuntu, establishing
the contracts and interfaces for acquiring events from native Linux sources and
converting them into bounded, attributable Rebuntu event observations.

### What Was Implemented

- ✅ `src/events/collector.hpp` - Interface definitions for EventCollector, NativeSourceAdapter,
  InMemoryEventChannel, and EventNormalizer
- ✅ `src/events/collector.cpp` - Implementation of InMemoryEventChannel and EventNormalizer
- ✅ `tests/unit/test_event_collector.cpp` - Unit tests for core components
- ✅ CMake integration (`cpp/CMakeLists.txt`)
- ✅ Documentation updates

### What Was NOT Implemented (Deferred to Later Phases)

- ❌ Concrete EventCollector implementation (requires runtime infrastructure integration)
- ❌ Native source adapter implementations:
  - SystemdSignalAdapter (requires systemd D-Bus connection)
  - UdevNetlinkAdapter (requires netlink socket handling)
  - InotifyAdapter (requires event loop integration)
- ❌ Full backpressure and rate limiting policies
- ❌ Source-specific coalescing algorithms

---

## Architecture Overview

### Event Collection Pipeline

```
Native Linux Sources
     ↓
[systemd D-Bus, udev netlink, inotify/fanotify]
     ↓
NativeSourceAdapter (connects to native source)
     ↓
EventCollector acquires and normalizes
     ↓
InMemoryEventChannel (bounded queue with backpressure)
     ↓
EventPublisher (publishes normalized events)
     ↓
Consumer receives runtime::Event with evidence
```

### Core Components

| Component | Responsibility |
|-----------|----------------|
| `EventSource` | Enum identifying native Linux event sources |
| `SourceConfig` | Per-source configuration (rate limits, burst handling) |
| `EventCollectorState` | Collector state machine (initializing→ready→running→stopped/failed) |
| `NativeSourceAdapter` | Interface for connecting to native sources |
| `InMemoryEventChannel` | Bounded in-memory queue with backpressure |
| `EventNormalizer` | Converts raw observations to Rebuntu Event/Fact format |

---

## Native Linux Source Mapping

| Source | Mechanism | Events |
|--------|-----------|--------|
| systemd | D-Bus signals | service-started, unit-failed, etc. |
| udev | netlink socket | device-added, device-removed, change |
| inotify | filesystem events | file-created, file-deleted, file-modified |
| fanotify | filesystem monitoring | mount events, access events |

---

## Event Normalization

### systemd State Change

```
Raw D-Bus signal: org.freedesktop.systemd1.Unit.StateChange
  → Normalized Event:
     - source: "systemd"
     - type: new_state (active, inactive, failed)
     - subject: unit name
     - evidence: unit info, state, timestamp
```

### udev Event

```
Raw netlink message: udev add/remove/change
  → Normalized Event:
     - source: "udev"
     - type: action (add, remove, change)
     - evidence: DEVNAME, SUBSYSTEM, environment variables
```

### inotify Event

```
Raw event: watch_descriptor + mask + filename
  → Normalized Event:
     - source: "inotify"
     - type: file-created/file-deleted/file-modified/etc.
     - evidence: wd, filename, mask bits
```

---

## Backpressure Policy

When the in-memory queue reaches capacity:

- **kDropNewest** (default): Drop newest events, keep existing
- **kDropOldest**: Replace oldest events with new ones
- **kBlock**: Block producer until space available (not implemented)

Metrics track:
- `events_dropped`: Events dropped due to backpressure
- `events_coalesced`: Events merged with existing entries

---

## Evidence Preservation

Each normalized event carries:

1. **Source identity** (systemd, udev, inotify)
2. **Acquisition timestamp** (system_clock::now() at acquisition)
3. **Raw evidence references** (original data preserved as string values)
4. **Provenance metadata** (source path for debugging)

---

## Test Coverage

### InMemoryEventChannel Tests

- `PublishAndReceive` — Basic round-trip
- `QueueFullDropNewest` — Backpressure behavior
- `ClosePreventsPublish` — Graceful shutdown

### EventNormalizer Tests

- `ParseSystemdStateChange` — systemd unit state parsing
- `ParseUdevEvent` — udev event from netlink
- `ParseFilesystemEvent` — inotify event with mask bits

---

## CMake Integration

```cmake
add_library(rebuntu-events-collector STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/events/collector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/events/collector.cpp
)
target_include_directories(rebuntu-events-collector PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-events-collector)
```

---

## Future Work (Deferred Phases)

### Phase 5.2 — Native Source Adapters

Implement concrete adapter classes that:
- Connect to native Linux sources
- Read raw events from sockets/files
- Apply backpressure policies
- Handle reconnection gracefully

### Phase 5.3 — EventCollector Implementation

Implement the main collector class that:
- Manages multiple source adapters
- Coordinates normalization pipeline
- Tracks metrics and health
- Integrates with Phase 4 runtime

### Phase 5.4 — Previous Boot Diagnostics

Add support for:
- Reading previous boot journal entries via `journalctl -b -1`
- Correlating events across reboot boundary
- Identifying abrupt terminations

---

## Acceptance Criteria Status

| Criterion | Status |
|-----------|--------|
| EventSource enum with to_string | ✅ |
| SourceConfig structure | ✅ |
| EventCollectorState state machine | ✅ |
| InMemoryEventChannel implementation | ✅ |
| EventNormalizer for key sources | ✅ |
| Backpressure policy (kDropNewest) | ✅ |
| Evidence preservation | ✅ |
| Unit tests | ✅ |
| Build integration (CMake) | ✅ |
| Documentation | ✅ |

---

## Verification Commands

```bash
# Build the collector library
cd cpp/build && make rebuntu-events-collector

# Run C++ compiler to check syntax
g++ -std=c++20 -c src/events/collector.cpp \
    -I src -I cpp/include \
    -fsyntax-only

# View event source enum values
grep -A 15 "enum class EventSource" src/events/collector.hpp
```

---

## Git Diff Summary

New files:
- `src/events/collector.hpp` (314 lines)
- `src/events/collector.cpp` (207 lines)
- `tests/unit/test_event_collector.cpp` (98 lines)

Modified files:
- `cpp/CMakeLists.txt` (added rebuntu-events-collector target)
- `src/events/README.md` (added Phase 5.1 documentation)

---

## Verdict: **PARTIALLY COMPLETE**

The Phase 5.1 System Event Collector foundation is complete with:

- ✅ Interface contracts and data structures
- ✅ In-memory channel with backpressure
- ✅ Event normalization utilities
- ✅ Build integration
- ✅ Unit tests

Remaining for full completion:
- ⏳ Native source adapter implementations
- ⏳ Concrete EventCollector implementation
- ⏳ Full event loop integration
- ⏳ Source-specific coalescing algorithms

The implementation follows Rebuntu's C++20-native, Linux-first philosophy,
preserving provenance while integrating cleanly with the existing Phase 4
runtime infrastructure.