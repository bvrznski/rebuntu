# adapters / sysfs / thermal

Thermal Zone Observation Adapter - Phase 5.34.

## Responsibility

Provides observation of Linux thermal zones and cooling devices from `/sys/class/thermal/` using native sysfs interfaces.

## Native Interfaces Used

- `/sys/class/thermal/thermal_zone*` — Thermal zone attributes (type, temp, mode, trip points)
- `/sys/class/thermal/cooling_device*` — Cooling device states (cur_state, max_state)

## Observation Capabilities

### Thermal Zones
- **Type**: Processor, Battery, GPU, Fan, Network
- **Temperature**: In millidegrees Celsius
- **Trip Points**: Temperature thresholds for thermal events
- **Mode**: enabled/disabled status

### Cooling Devices
- **Current State**: Current cooling level (0 to max)
- **Max State**: Maximum possible cooling level
- **Type**: Processor throttling, Fan, Passive

## Topology
- Tracks all observed thermal zones and cooling devices
- Reports maximum temperature across all zones
- Indicates if any zone is at throttling threshold (>90°C)

## Key Distinctions

| Concept | Implementation |
|---------|---------------|
| **Thermal Zone Type** | Hardware classification from sysfs (Processor/GPU/Battery) |
| **Temperature** | Direct measurement in millidegrees Celsius |
| **Trip Points** | Pre-configured thresholds for thermal events |
| **Cooling Level** | Current vs maximum cooling capacity |

## Provenance

All observations include:
- Source: `sysfs`
- Timestamp: When observation was captured
- Freshness-aware results (re-reads from sysfs on each call)

## Architecture

```
SysfsThermalAdapter (implementation)
    └── ThermalAdapter (interface)
            ├── observe_thermal() → ThermalObservationResult
            ├── get_topology() → ThermalTopology  
            ├── resolve_zone(index) → optional<ThermalZoneObservation>
            └── resolve_cooling_device(index) → optional<CoolingDeviceObservation>
```

## Implementation Notes

- Uses only native Linux interfaces (sysfs)
- No external dependencies or shell commands
- Deterministic: same input → same output
- Bounded discovery: only reads existing zones, no configuration changes