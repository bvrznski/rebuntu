# src/modules/stability_monitor — System Stability Monitor (Phase 5.5)

This module provides a foundational stability monitor that combines service/
process/kernel/storage/resource observations into a conservative view of
host stability.

## Overview

The StabilityMonitor:

- **Observes** systemd services, kernel events, and system resources
- **Assesses** overall system stability: stable, degraded, unstable, unknown
- **Generates** internal alerts for significant issues
- **Does NOT perform recovery** - that belongs to Phase 12's recovery engine

## Architecture

```
StabilityMonitor (main class)
    ├── Config (thresholds, hysteresis settings)
    ├── Assessment Engine
    │   ├── assess_systemd_services() → SubsystemAssessment
    │   ├── assess_kernel_events() → SubsystemAssessment  
    │   └── assess_resource_usage() → SubsystemAssessment
    ├── Observation Buffers (bounded, for temporal analysis)
    ├── Hysteresis State (prevents flapping between states)
    └── Metrics (assessments performed, observations received, alerts generated)
```

## Key Types

| Type | Purpose |
|------|---------|
| `StabilityState` | kUnknown, kStable, kDegraded, kUnstable |
| `Subsystem` | kSystemdServices, kKernelEvents, kCpuResource, etc. (8 total) |
| `FailureClass` | 12 failure categories (service-failure, oom-event, kernel-error, etc.) |
| `StabilityAssessment` | Complete system stability assessment with subsystem breakdown |
| `InternalAlert` | Alert for diagnostics with severity and evidence chain |

## Design Principles

1. **Monitoring ≠ Recovery**: This module observes and assesses but does NOT repair
2. **UNKNOWN ≠ false**: Missing telemetry is reported honestly as UNKNOWN/PARTIAL
3. **Evidence-based assessment**: Uses `rebuntu::core::Evidence` (provenance-bearing, bounded data)
4. **Hysteresis prevents flapping**: State changes require sustained conditions

## Native Linux Sources

- systemd D-Bus API (service state, restart counts)
- kernel logs (/var/log/journal, dmesg) for error events
- procfs/sysfs for resource utilization metrics

## Public Interface

```cpp
// Create monitor with configuration
auto monitor = make_stability_monitor(config);

// Lifecycle
monitor->start();
monitor->stop();

// Add observations from various sources
monitor->add_service_state_observation(...);
monitor->add_kernel_event_observation(...);
monitor->add_resource_observation(...);

// Get current assessment
auto assessment = monitor->assess_stability();
StabilityState state = monitor->get_overall_state();

// Get pending alerts for diagnostics
std::vector<InternalAlert> alerts = monitor->get_pending_alerts();

// Monitor's own metrics
auto metrics = monitor->metrics();
```

## Configuration

```cpp
struct StabilityMonitorConfig {
    // Assessment windows (durations)
    std::chrono::minutes event_window_minutes{10};
    std::chrono::minutes degradation_window_minutes{5};
    
    // Thresholds
    int service_restart_threshold = 5;
    std::chrono::minutes service_restart_window_minutes{2};
    
    int kernel_error_rate_threshold = 10;
    int disk_io_error_threshold = 3;
    
    // Hysteresis (prevents flapping between states)
    std::chrono::minutes hysteresis_interval_minutes{5};
    
    // Resource thresholds
    double cpu_utilization_warning_percent = 80.0;
    double memory_pressure_warning_percent = 85.0;
    double disk_capacity_warning_percent = 90.0;
    
    // Evidence retention
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
    
    // Native source configuration
    bool enable_systemd_monitoring = true;
    bool enable_kernel_monitoring = true;
    bool enable_resource_monitoring = true;
};
```

## State Transitions

```
┌─────────┐     ┌──────────┐     ┌──────────┐     ┌─────────┐
│ Unknown │────>│  Stable  │────>│ Degraded │────>│Unstable │
└─────────┘     └──────────┘     └──────────┘     └─────────┘
    ^             │      ▲            │      ▲
    │             ▼      │            ▼      │
    └────────────────────┴─────────────┴─────┘
```

## Testing

```bash
# Build with CMake
cmake -S cpp -B build
make rebuntu-stability-monitor

# Run tests (requires gtest)
./tests/unit/test_stability_monitor
```

## Later Phase Integration Points

- **Phase 5.6**: Native adapter for systemd D-Bus service monitoring
- **Phase 5.7**: Kernel event adapter for dmesg/journal parsing
- **Phase 5.8**: Resource monitor for procfs/sysfs metrics
- **Phase 12**: Recovery engine consumes alerts from this module

## Status

**CURRENT**: Header types and core logic implemented.

**RESERVED**: Native Linux adapters (systemd, procfs, sysfs integration).