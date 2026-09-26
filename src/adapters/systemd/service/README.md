# Systemd Service Discovery Adapter (Phase 5.26)

This module implements Rebuntu's systemd-based service discovery adapter.

## Overview

Observes systemd units/services through the native systemctl interface, providing:

- **Typed observations**: Structured data with clear semantics
- **Bounded acquisition**: Timeout and output limits to prevent event storms
- **Freshness-aware**: Tracks when observation was performed
- **Provenance-preserving**: Source identification for every observation

## Key Distinctions

### ServiceUnit vs ServiceInstance

- **ServiceUnit** = UnitFile + SourcePath + FragmentPath (specification/definition)
  - What systemd knows about the unit from its configuration files
  - Persistent across reboots (until reconfigured)

- **ServiceInstance** = MainPID + ActiveState + SubState (runtime state)
  - The current runtime manifestation of the unit
  - Changes as the unit starts, stops, crashes

### Identity

A service is uniquely identified by:
- `name`: The unit name (e.g., "apache2.service", "ssh.socket")
- `type`: The unit type (service, socket, timer, target, etc.)

**Note**: UnitId != PID. PIDs are transient; unit names are durable identifiers.

## Native Interfaces

### Primary
- **systemctl list-units** — List all units currently in memory
  - Format: UNIT LOAD ACTIVE SUB DESCRIPTION TYPE SOURCE
  - Used to discover available units

- **systemctl show --property=...** — Query unit properties
  - Returns PROPERTY=VALUE pairs
  - Provides detailed state information

### Alternative (future)
- systemd D-Bus interface (for richer metadata)

## Data Model

### ServiceIdentity
```cpp
struct ServiceIdentity {
    std::string name;      // e.g., "apache2.service"
    std::string type;      // e.g., "service", "socket", "timer"
};
```

### State Enums

**ServiceActiveState**: Runtime availability
- `kActive`: Unit is running
- `kInactive`: Unit is not running  
- `kActivating`: Starting up
- `kDeactivating`: Shutting down
- `kFailed`: Failed or crashed

**ServiceUnitState**: Unit file state (systemd's view)
- `kEnabled`: Enabled at boot/on-demand
- `kDisabled`: Not enabled
- `kStatic`: Cannot be enabled/disabled
- `kIndirect`: Managed by other means
- `kMasked`: Cannot be started

**ServiceSubState**: More granular runtime state
- Varies by unit type (running, dead, start, stop, etc.)

### ServiceObservation
Complete observation combining specification and instance state with provenance.

## Adapter Interface

```cpp
class ServiceDiscoveryAdapter {
public:
    // Observe all services currently visible from systemd
    virtual ServiceDiscoveryResult observe_all_services() = 0;
    
    // Observe a specific service by identity
    virtual std::optional<ServiceObservation> observe_service(
        const ServiceIdentity& identity) = 0;
    
    // Get freshness timestamp of last observation
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cache and re-observe
    virtual ServiceDiscoveryResult force_refresh() = 0;
};
```

## Usage Example

```cpp
auto adapter = make_systemd_service_discovery_adapter();

// Discover all units
auto result = adapter->observe_all_services();
for (const auto& observation : result.services) {
    std::cout << observation.identity.name 
              << ": " << to_string(observation.active_state)
              << " (" << to_string(observation.unit_state) << ")\n";
}

// Observe specific unit
ServiceIdentity identity{"apache2.service", "service"};
auto optional_obs = adapter->observe_service(identity);
if (optional_obs) {
    // Check if running
    if (optional_obs->active_state == ServiceActiveState::kActive) {
        // Has a main process?
        if (optional_obs->runtime && optional_obs->runtime->main_pid > 0) {
            std::cout << "PID: " << optional_obs->runtime->main_pid << "\n";
        }
    }
}
```

## Invariants

- **No inference**: Only observed values from native interfaces
- **Bounded acquisition**: Timeouts and limits on output size
- **Freshness-aware**: Tracks when observation was performed
- **Provenance-preserving**: Source identification for every observation

## Error Handling

- Acquisition failures result in `core::SemanticStatus::kUnknown`
- Non-fatal errors are recorded in `ServiceDiscoveryResult.errors`
- Fatal errors set `ServiceDiscoveryResult.fatal_error`

## Performance Considerations

- Each observation calls `popen()` for systemctl commands
- Consider caching with freshness-aware invalidation
- Multiple concurrent observations may be slow; use batching

## Future Enhancements

- Caching layer with configurable TTL
- D-Bus integration for richer metadata (memory, CPU usage)
- Asynchronous observations