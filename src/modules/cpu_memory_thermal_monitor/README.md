# src/modules/cpu_memory_thermal_monitor — CPU / Memory / Thermal Monitor (Phase 5.9)

## Overview

This module provides comprehensive resource monitoring for Rebuntu:

- **CPU:** utilization, load average, run queue pressure
- **Memory:** availability, swap activity, PSI monitoring
- **Thermal:** temperature readings, throttling state

**Architecture:** Direct native Linux access — no shell command parsing.

---

## Quick Start

```cpp
#include "src/modules/cpu_memory_thermal_monitor/monitor.hpp"

using namespace rebuntu::modules::cpu_memory_thermal_monitor;

// Create monitor with default configuration
auto monitor = make_resource_monitor();

// Start monitoring
auto result = monitor->start();
if (!result.is_completed()) {
    // Handle error
}

// Perform assessment
auto assessment_result = monitor->assess_resources();

// Check results
if (assessment_result.outcome == ResourceMonitorResult::Outcome::kSuccess) {
    if (assessment_result.cpu_assessment.has_value()) {
        const auto& cpu = *assessment_result.cpu_assessment;
        std::cout << "CPU state: " << static_cast<int>(cpu.state) << "\n";
    }
}

// Get pending events
auto events = monitor->get_pending_events();

// Stop when done
monitor->stop();
```

---

## Native Sources

| Source | Purpose |
|--------|---------|
| `/proc/stat` | CPU statistics |
| `/proc/loadavg` | Load average |
| `/proc/cpuinfo` | CPU topology |
| `/proc/meminfo` | Memory info |
| `/sys/class/thermal/*/temp` | Thermal zones |
| `/sys/devices/system/cpu/cpu*/cpufreq/thermal_pressure` | Throttling |

---

## Assessment Outcome

- `kSuccess`: All assessments produced valid data
- `kPartial`: Some assessments failed (e.g., no thermal sensors)
- `kUnknown`: No data available from any source
- `kFailure`: Acquisition error occurred

---

## State Machine

```
ResourceState:
  kUnknown  ← No data
    ↓
  kNormal   ← Within thresholds
    ↓
  kPressured ← Elevated utilization
    ↓
  kConstrained ← Memory pressure (memory domain)
    ↓
  kCritical ← Threshold exceeded
```

---

## Configuration

```cpp
ResourceMonitorConfig config;
config.cpu_utilization_warning_percent = 70.0;
config.cpu_utilization_critical_percent = 90.0;
config.temperature_warning_celsius = 75;
config.temperature_critical_celsius = 90;

auto monitor = make_resource_monitor(config);
```

---

## Metrics

```cpp
auto metrics = monitor->metrics();
std::cout << "CPU observations: " << metrics.cpu_observations << "\n";
std::cout << "Memory observations: " << metrics.memory_observations << "\n";
std::cout << "Thermal observations: " << metrics.thermal_observations << "\n";
```

---

## Events

Events are generated when thresholds are crossed:

```cpp
// Check for events
auto events = monitor->get_pending_events();
for (const auto& event : events) {
    std::cout << "Event: " << event.event_id 
              << " (" << static_cast<int>(event.event_type) << ")\n";
}

// Acknowledge after handling
monitor->acknowledge_event(event.event_id);
```

---

## Thread Safety

- `start()` / `stop()`: Safe to call from any thread
- `assess_resources()`: Not thread-safe; use one monitor per assessment context or add external synchronization
- `metrics()`, `get_pending_events()`: Safe for concurrent reading

---

## Performance

Typical overhead on modern hardware:
- CPU: ~1-2ms per assessment
- Memory: ~0.5-1ms per assessment  
- Thermal: ~5-20ms (depends on number of thermal zones)

Memory usage: ~100KB idle, ~200KB with 60-second history window

---

## Error Handling

- Missing source file → `std::nullopt` returned for that domain
- Invalid data format → Unknown state for that assessment
- Thermal data unavailable → Partial outcome (CPU/Memory still valid)

---

## Testing

Run tests from the cpp build directory:

```bash
cd /home/bvrznski/rebuntu/cpp
make rebuntu-cpu-memory-thermal-monitor
```

Unit test binary: `cpp/tests/unit/cpu_memory_thermal_monitor_test.cpp`

---

## See Also

- Phase 5.9 Final Report: `docs/PHASE_5.9_CPU_MEMORY_THERMAL_MONITOR_FINAL_REPORT.md`
- Phase 4 Runtime: `src/runtime/engine.hpp`
- Core Contracts: `src/system/core/contracts.hpp`