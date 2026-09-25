# src/modules/storage_health_monitor — Storage & Filesystem Health Monitor (Phase 5.8)

This module provides comprehensive health monitoring for storage devices, filesystems,
and mounts in Rebuntu.

## Overview

The StorageHealthMonitor:
- **Observes** block device health from NVMe SMART, SATA/SCSI attributes
- **Tracks** filesystem health states (mounted, read-only transitions, errors)
- **Monitors** mount point state changes and capacity usage
- **Detects** I/O errors with configurable thresholds
- **Does NOT perform repairs** - that belongs to Phase 12's recovery engine

## Architecture

```
StorageHealthMonitor (main class)
    ├── Config (thresholds, retention settings)
    ├── Block Device Health Assessment Engine
    │   ├── NVMe SMART data parsing (if enabled)
    │   ├── I/O error tracking and aggregation
    │   └── Capacity monitoring
    ├── Filesystem Health Assessment Engine
    │   ├── Mount state observation from /proc/mounts
    │   ├── Read-only transition detection
    │   └── Error pattern analysis
    ├── Event Buffer (bounded, with deduplication)
    └── Metrics (observations, events generated)
```

## Key Types

| Type | Purpose |
|------|---------|
| `BlockDeviceHealthState` | kUnknown, kHealthy, kDegraded, kFailing, kFailed |
| `FilesystemHealthState` | kUnknown, kHealthy, kReadOnly, kHasErrors, kFailed |
| `MountState` | kUnknown, kMounted, kUnmounted, kMounting, kUnmounting |
| `DeviceType` | NVMe, SATA, SCSI, USB, Loop, DM (device-mapper) |
| `BlockDeviceHealth` | Full device health with attributes and error counts |
| `FilesystemHealth` | Full filesystem health with capacity info |
| `StorageHealthAssessment` | Complete storage subsystem report |
| `StorageHealthEvent` | Events for diagnostics and alerting |

## Design Principles

1. **Monitoring ≠ Recovery**: This module observes and assesses but does NOT repair
2. **UNKNOWN ≠ false**: Missing telemetry is reported honestly as UNKNOWN/PARTIAL
3. **Health ≠ State**: A filesystem can be mounted but unhealthy (read-only, errors)
4. **Mount ≠ Filesystem**: Mount state (present/absent) separate from fs health

## Native Linux Sources

- `/proc/mounts` for mount table observation
- NVMe SMART data via `nvme-cli` or `/sys/class/nvme/`
- SATA/SCSI SMART via `smartctl` or `/sys/block/*/device/`
- Kernel journal logs via journald adapter (for I/O errors)

## Public Interface

```cpp
// Create monitor with configuration
auto monitor = make_storage_health_monitor(config);

// Lifecycle
monitor->start();
monitor->stop();

// Add observations from adapters
monitor->observe_block_device(device_health, time);
monitor->observe_filesystem(fs_health, time);
monitor->process_mount_entries(mount_info_list, time);

// Query health states
std::optional<BlockDeviceHealth> device = monitor->get_block_device_health("DEV001");
std::optional<FilesystemHealth> fs = monitor->get_filesystem_health("/home");

// Get full assessment report
StorageHealthAssessment assessment = monitor->assess_storage_health();

// Get pending events (events since last check)
std::vector<StorageHealthEvent> events = monitor->get_pending_events();

// Monitor's own metrics
StorageMonitorMetrics metrics = monitor->metrics();
```

## Configuration

```cpp
struct StorageHealthMonitorConfig {
    std::chrono::milliseconds observation_interval_ms{5000};  // Observation frequency
    
    int io_error_threshold = 5;           // Errors → degraded/failing
    double capacity_warning_percent = 90.0;
    double capacity_critical_percent = 95.0;
    
    std::optional<int> nvme_percentage_used_warning{80};
    std::optional<int> nvme_percentage_used_critical{90};
    int temperature_warning_celsius = 70;
    int temperature_critical_celsius = 85;
    
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
    
    bool enable_nvme_health = true;
    bool enable_smart_health = true;
    bool enable_mount_observation = true;
};
```

## Event Types

- `kBlockDeviceStateChange`: Device health state changed
- `kFilesystemStateChange`: Filesystem health state changed
- `kMountAdded`: New mount point appeared
- `kMountRemoved`: Mount point disappeared
- `kReadOnlyRemountDetected`: Filesystem remounted read-only
- `kIOErrorThresholdExceeded`: I/O errors exceed threshold
- `kCapacityWarning`: Capacity > warning threshold
- `kCapacityCritical`: Capacity > critical threshold

## State Transitions

```
BlockDeviceHealth: kUnknown → kHealthy → kDegraded → kFailing → kFailed
FilesystemHealth:  kUnknown → kHealthy → kReadOnly/HasErrors → kFailed
MountState:        kUnmounted → kMounted (or kMounting) → kUnmounted
```

## Testing

```bash
# Build with CMake
cmake -S cpp -B build
make rebuntu-storage-health-monitor

# Run tests (requires gtest)
./tests/unit/test_storage_health_monitor
```

## Later Phase Integration Points

- **Phase 5.8**: Native adapters for procfs mounts, NVMe SMART, SATA/SCSI SMART
- **Phase 12**: Recovery engine consumes storage health events from this module

## Status

**CURRENT**: Types and core logic implemented.

**RESERVED**: Native Linux adapters (procfs mount observation, NVMe SMART, ATA SMART).