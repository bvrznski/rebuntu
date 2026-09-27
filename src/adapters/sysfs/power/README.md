# adapters / sysfs / power

Power Supply Observation Adapter - Phase 5.34.

## Responsibility

Provides observation of Linux power supplies from `/sys/class/power_supply/` using native sysfs interfaces.

## Native Interfaces Used

- `/sys/class/power_supply/*/` — Power supply attributes (type, status, capacity, voltage, current, energy)

## Observation Capabilities

### Power Supplies
- **Type**: Battery, AC, USB, Wireless
- **Status**: Full, Charging, Discharging, Not charging
- **Identity**: Name, manufacturer, model name, serial number

### Battery Metrics (where available)
- Voltage, current, charge/energy levels
- Capacity percentage (0-100)
- Cycle count and chemistry information
- Temperature monitoring

## Topology
- Tracks relationships between AC adapters and batteries
- Reports overall power state (has AC, has battery)

## Key Distinctions

| Concept | Implementation |
|---------|---------------|
| **Power Supply Type** | Hardware classification from sysfs (Battery/AC/USB) |
| **Status** | Current charge operation (Charging/Discharging/Full) |
| **Capacity** | Percentage of current vs full charge |
| **Energy** | Actual energy in microWatt-hours |

## Provenance

All observations include:
- Source: `sysfs`
- Timestamp: When observation was captured
- Freshness-aware results (re-reads from sysfs on each call)

## Architecture

```
SysfsPowerAdapter (implementation)
    └── PowerSupplyAdapter (interface)
            ├── observe_supplies() → PowerObservationResult
            ├── get_topology() → PowerTopology  
            └── resolve_supply(name) → optional<PowerSupplyObservation>
```

## Implementation Notes

- Uses only native Linux interfaces (sysfs, procfs)
- No external dependencies or shell commands
- Deterministic: same input → same output
- Bounded discovery: only reads existing supplies, no configuration changes