# rebuntu::adapters::hotplug — Hotplug Device State Management (Phase 5.48)

## Overview

This module implements Rebuntu's bounded, freshness-aware device state tracking system for handling hotplug events and removal races safely.

### Key Invariants

- **Observation != inference**: Direct sysfs reading is observation; pattern matching on names is inference
- **Cache != authority**: Observed state is cached data, not authoritative source (Linux kernel owns actual state)
- **MISSING_EVIDENCE != ABSENCE**: A device that hasn't been observed recently may still be present
- **UNKNOWN != PASS**: Acquisition failure is not a negative observation

### Hotplug Handling

1. **Device additions**: Fresh observation from sysfs scan
2. **Device removals**: Stale evidence marked as `kRemoved`, historical record preserved
3. **Removal races**: Use freshness timestamps to detect out-of-date state

## Native Interfaces Used

- `/sys/class/` — Linux device model (input, sound, display, block, network)
- `/sys/bus/usb/devices/` — USB device enumeration
- `/dev/dri/card*` — DRM/KMS card devices
- `/proc/asound/cards` — ALSA audio cards

## Typed Identities

### DeviceIdentity
- `sysfs_path`: /sys/class/... path (stable across hotplug cycles)
- `udev_path`: /dev/... node path (may change on reconnection)
- `vendor_id`, `product_id`: Hardware identifiers (where available)

**Critical**: Identity must be stable and unique. Path-based identity is preferred over name-based as it's more stable across reconnections.

## Device States

| State | Description |
|-------|-------------|
| `kUnknown` | State not yet determined (acquisition failure) |
| `kPresent` | Device is currently present and operational |
| `kRemoved` | Device has been removed (preserved in history) |
| `kStale` | Evidence exists but freshness threshold exceeded |

## Freshness Tracking

Each device record tracks:
- `first_seen`: When first observed
- `last_observed`: Last time state was confirmed present
- `removed_at`: When marked as removed (if applicable)

A device is considered stale if:
```cpp
now - last_observed > freshness_threshold_ms  // default: 5 minutes
```

## Bounded Discovery

Discovery is bounded by:
- Timeout limits (configurable, default 30 seconds)
- Maximum devices per category (default 500 each)
- Total maximum devices (default 2500)

## API Usage

```cpp
#include "adapters/hotplug/types.hpp"

using namespace rebuntu::adapters::hotplug;

auto observer = make_hotplug_observer();

// Start monitoring
observer->start();

// Discover current device state
auto result = observer->discover_devices();
if (result.status == core::SemanticStatus::kCompleted) {
    for (const auto& [key, record] : result.device_records) {
        std::cout << "Device: " << key 
                  << ", State: " << to_string(record.state) << "\n";
    }
}

// Get specific device
DeviceIdentity id;
id.sysfs_path = "/sys/class/input/event0";
auto record = observer->get_device_record(id);

// Stop monitoring
observer->stop();
```

## Removal Race Safety

When a device is removed:
1. The device is marked as `kRemoved` in the record
2. Historical evidence (last observation) is preserved
3. The device will not appear as "present" to callers
4. After the freshness threshold, stale devices are also marked appropriately

This ensures that:
- Removed devices don't falsely appear current
- Historical evidence can be audited for troubleshooting
- Race conditions between observation and removal are handled correctly

## Integration with Evidence Collection

Device observations can be used as evidence in diagnostic requests:

```cpp
EvidenceRequest req;
req.evidence_kinds.push_back(EvidenceKind::kHotplugState);
```

## Implementation Notes

- Uses C++17 filesystem API for directory enumeration
- No external dependencies beyond standard library
- Graceful error handling - individual device failures don't stop discovery
- Reads only from read-only filesystem paths (no privilege escalation needed)