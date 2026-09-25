# src/modules/health_monitor — Process & Service Health Monitor (Phase 5.6)

This module provides comprehensive health monitoring for processes and systemd services in Rebuntu.

## Overview

The HealthMonitor:
- **Observes** process states from procfs (running, stopped, zombie)
- **Assesses** service health from systemd state + crash behavior analysis
- **Detects** crash loops, stalls, and resource issues
- **Does NOT perform recovery** - that belongs to Phase 12's recovery engine

## Architecture

```
HealthMonitor (main class)
    ├── Config (thresholds, hysteresis settings)
    ├── Assessment Engine
    │   ├── assess_process_health() → HealthAssessment
    │   └── assess_service_health() → HealthAssessment
    ├── Observation Buffers (bounded, for temporal analysis)
    ├── Crash Behavior Detection (crash loop/stall detection)
    ├── Event Generator (alerts with deduplication)
    └── Metrics (assessments performed, events generated)
```

## Key Types

| Type | Purpose |
|------|---------|
| `ProcessState` | kUnknown, kRunning, kStopped, kZombie, kWaiting, kIdle |
| `ServiceHealthState` | kUnknown, kHealthy, kDegraded, kUnhealthy |
| `CrashBehavior` | kNone, kSingleCrash, kIntermittent, kCrashLooping, kStalled |
| `HealthDimension` | Lifecycle, Readiness, Operational, Resource, Behavioral |
| `ProcessHealth` | Full process health assessment with resource usage |
| `ServiceHealth` | Full service health assessment from systemd |
| `HealthAssessment` | Complete health report per subject |
| `HealthEvent` | Events for diagnostics (crash detected, state change) |

## Design Principles

1. **Monitoring ≠ Recovery**: This module observes and assesses but does NOT repair
2. **UNKNOWN ≠ false**: Missing telemetry is reported honestly as UNKNOWN/PARTIAL
3. **Health ≠ State**: A service can be active but unhealthy
4. **Running ≠ Ready ≠ Healthy**: These are orthogonal dimensions

## Native Linux Sources

- procfs `/proc/[pid]/stat` and related files for process state
- systemd D-Bus API for service state, restart counts, main PID
- Event-driven observation (no polling)

## Public Interface

```cpp
// Create monitor with configuration
auto monitor = make_health_monitor(config);

// Lifecycle
monitor->start();
monitor->stop();

// Add observations from various sources
monitor->add_process_observation(process_health, time);
monitor->add_service_observation(service_health, time);

// Get health assessment for a subject
HealthAssessment process_health = monitor->assess_process_health("1234");
HealthAssessment service_health = monitor->assess_service_health("ssh.service");

// Get current health state (cached)
ServiceHealthState state = monitor->get_process_health_state("1234");

// Get pending events for diagnostics
std::vector<HealthEvent> events = monitor->get_pending_events();

// Monitor's own metrics
HealthMonitorMetrics metrics = monitor->metrics();
```

## Configuration

```cpp
struct HealthMonitorConfig {
    std::chrono::minutes crash_loop_window_minutes{2};  // Window for crash-loop detection
    
    int service_restart_threshold = 5;      // Restarts in window → degraded
    int process_crash_threshold = 3;        // Crashes in window → unhealthy
    
    double cpu_utilization_warning_percent = 80.0;
    double memory_utilization_warning_percent = 85.0;
    
    std::chrono::milliseconds readiness_timeout_ms{30000};
    
    bool enable_process_monitoring = true;
    bool enable_service_monitoring = true;
    bool enable_resource_monitoring = true;
    
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
    
    bool include_uncertainty_notes = true;
};
```

## Health Dimensions

Each subject is assessed across multiple dimensions:

1. **Lifecycle**: Process state (running, stopped, zombie)
2. **Readiness**: Can accept work (port open, dependencies ready)
3. **Operational**: Core functionality working
4. **Resource**: CPU/memory usage within bounds
5. **Behavioral**: Crash patterns (none, intermittent, crash-looping, stalled)

## State Transitions

```
Health Assessment: kUnknown → kHealthy → kDegraded → kUnhealthy
Crash Behavior:    kNone → kSingleCrash → kIntermittent → kCrashLooping
Process State:     kUnknown → kRunning → kZombie (failed)
```

## Testing

```bash
# Build with CMake
cmake -S cpp -B build
make rebuntu-health-monitor

# Run tests (requires gtest)
./tests/unit/test_health_monitor
```

## Later Phase Integration Points

- **Phase 5.6**: Native adapters for procfs, systemd D-Bus
- **Phase 12**: Recovery engine consumes health events from this module

## Status

**CURRENT**: Types and core logic implemented.

**RESERVED**: Native Linux adapters (procfs process observation, systemd D-Bus).