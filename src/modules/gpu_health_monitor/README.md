# src/modules/gpu_health_monitor — GPU Health Monitor (Phase 5.10)

## Overview

This module provides comprehensive GPU health monitoring for Rebuntu:

- **Device presence and identity** - UUID, PCI bus ID detection
- **Driver state and reachability** - NVIDIA driver availability
- **Utilization metrics** - Graphics, memory, encoder, decoder utilization
- **Thermal monitoring** - Temperature readings, fan speed, throttling state
- **Power monitoring** - Power draw, limits, efficiency
- **Clock monitoring** - Graphics, memory, SM clock frequencies
- **ECC error tracking** - Where supported (NVIDIA enterprise GPUs)
- **Display ownership** - Display active state

**Architecture:** Provider-based design with native Linux source acquisition.

---

## Native Sources

| Source | Purpose |
|--------|---------|
| `/sys/class/drm/*/device/vendor` | PCI vendor ID (0x10de = NVIDIA) |
| `/sys/class/drm/*/device/uevent` | Device identity (PCI bus ID) |
| NVML API (optional) | Comprehensive GPU telemetry when available |

---

## Architecture

```
GPUMonitor
    ├── Config: Observation thresholds, retention policy
    ├── Assessment: Current state of all GPUs
    └── Events: Threshold crossings, warnings, alerts
```

### Provider Interface

```cpp
class GPUProvider {
public:
    virtual std::string provider_name() const = 0;
    virtual bool is_available() const = 0;
    virtual GPUGlobalState get_global_state() = 0;
    virtual std::optional<GPUDeviceAssessment> get_device_assessment(...) = 0;
};
```

---

## Quick Start

```cpp
#include "src/modules/gpu_health_monitor/monitor.hpp"

using namespace rebuntu::modules::gpu_health_monitor;

// Create monitor with default configuration
auto monitor = make_gpu_monitor();

// Start monitoring
auto result = monitor->start();
if (!result.is_completed()) {
    // Handle error
}

// Perform assessment
auto assessment_result = monitor->assess_gpu_health();

// Check results
if (assessment_result.outcome == GPUMonitorResult::Outcome::kSuccess) {
    for (const auto& device : assessment_result.assessment.devices) {
        std::cout << "GPU: " << device.identity.uuid << "\n";
        std::cout << "  State: " << to_string(device.state) << "\n";
        if (device.temperature.has_value()) {
            std::cout << "  Temp: " << device.temperature->gpu_celsius << "C\n";
        }
    }
}

// Get pending events
auto events = monitor->get_pending_events();

// Stop when done
monitor->stop();
```

---

## Configuration

```cpp
GPUMonitorConfig config;
config.utilization_warning_percent = 70;
config.utilization_critical_percent = 90;
config.temperature_warning_celsius = 75;
config.temperature_critical_celsius = 90;

auto monitor = make_gpu_monitor(config);
```

---

## Types

| Type | Description |
|------|-------------|
| `GPUState` | kUnknown, kAbsent, kIdle, kActive, kThrottled, kDegraded, kFault |
| `GPUGlobalState` | Provider availability and device list |
| `GPUDeviceAssessment` | Complete assessment for a single GPU |
| `GPUEvent` | Event triggered by threshold crossings |

---

## Events

Events are generated when thresholds are crossed:

- `kTemperatureWarning`, `kTemperatureCritical`
- `kUtilizationWarning`, `kUtilizationCritical`
- `kThrottlingStarted`, `kThrottlingStopped`
- `kPowerLimitActive`

Acknowledge events after handling to prevent duplicate alerts.

---

## Thread Safety

- `start()` / `stop()`: Safe to call from any thread
- `assess_gpu_health()`: Not thread-safe; use one monitor per assessment context
- `metrics()`, `get_pending_events()`: Safe for concurrent reading

---

## Resource Budget

- Idle CPU: ~1ms per assessment
- Memory: ~50KB idle, ~100KB with 5-minute history window
- File descriptors: Open during acquisition only

---

## Future Enhancements (Later Phases)

- NVML integration for comprehensive telemetry
- Xid error parsing from kernel logs
- ECC error aggregation
- Historical trend analysis
- Predictive failure detection

---

## See Also

- Phase 4 Runtime: `src/runtime/engine.hpp`
- Core Contracts: `src/system/core/contracts.hpp`