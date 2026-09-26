// rebuntu::adapters::systemd::service — Systemd Service Discovery Adapter (Phase 5.26)
//
// This module implements Rebuntu's systemd-based service discovery adapter:
//   - Observes systemd unit/services through the native provider
//   - Provides typed, bounded observation of service state without inference
//   - Distinguishes ServiceUnit (specification) from ServiceInstance (runtime)
//
// Native Interfaces Used:
//   - systemctl list-units --type=service — list all units in memory
//   - systemctl show UNIT — query unit properties
//   - systemd D-Bus interface (optional, for richer metadata)
//
// Key Distinctions:
//   - ServiceUnit = UnitFile + SourcePath + FragmentPath (specification/definition)
//   - ServiceInstance = MainPID + ActiveState + SubState (runtime state)
//   - UnitId = Name + Type (e.g., "apache2.service")
//
// Observation Invariants:
//   - No inference: only observed values from native interfaces
//   - Bounded acquisition: timeouts, limits on output size
//   - Freshness-aware: tracks when observation was performed
//   - Provenance-preserving: source identification for every observation

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <chrono>
#include <vector>

namespace rebuntu::adapters::systemd::service {

// ============================================================================
// ServiceIdentity — Stable identity for a systemd service unit
//
// A service is uniquely identified by:
//   - name: The unit name (e.g., "apache2.service", "ssh.socket")
//   - type: The unit type (service, socket, timer, etc.)
//
// Note: UnitId != PID. PIDs are transient; unit names are durable identifiers.
// ============================================================================
struct ServiceIdentity {
    std::string name;      // e.g., "apache2.service"
    std::string type;      // e.g., "service", "socket", "timer"
    
    bool is_valid() const {
        return !name.empty();
    }
};

inline bool operator==(const ServiceIdentity& a, const ServiceIdentity& b) {
    return a.name == b.name && a.type == b.type;
}

// ============================================================================
// ServiceUnitState — Unit file state (systemd's view of whether unit is enabled)
//
// From systemd: UnitFileState
//   enabled: unit is enabled (will start at boot or on demand)
//   disabled: unit is not enabled
//   static: unit has no [Install] section (cannot be enabled/disabled)
//   indirect: unit is managed by other means (e.g., symlinked)
//   masked: unit is masked (cannot be started manually or automatically)
// ============================================================================
enum class ServiceUnitState {
    kUnknown,       // State unknown (acquisition failed)
    kEnabled,       // Unit is enabled
    kDisabled,      // Unit is not enabled
    kStatic,        // Cannot be enabled/disabled (no [Install] section)
    kIndirect,      // Managed by other means
    kMasked,        // Masked (cannot be started)
};

inline std::string to_string(ServiceUnitState s) {
    switch (s) {
        case ServiceUnitState::kUnknown:   return "unknown";
        case ServiceUnitState::kEnabled:   return "enabled";
        case ServiceUnitState::kDisabled:  return "disabled";
        case ServiceUnitState::kStatic:    return "static";
        case ServiceUnitState::kIndirect:  return "indirect";
        case ServiceUnitState::kMasked:    return "masked";
    }
    return "unknown";
}

// ============================================================================
// ServiceActiveState — Active state (runtime availability)
//
// From systemd: ActiveState
//   active: unit is running
//   inactive: unit is not running
//   activating: unit is in the process of starting
//   deactivating: unit is in the process of stopping
//   failed: unit terminated with error or could not start
// ============================================================================
enum class ServiceActiveState {
    kUnknown,       // State unknown (acquisition failed)
    kActive,        // Unit is running
    kInactive,      // Unit is not running
    kActivating,    // Starting up
    kDeactivating,  // Shutting down
    kFailed,        // Failed to run or crashed
};

inline std::string to_string(ServiceActiveState s) {
    switch (s) {
        case ServiceActiveState::kUnknown:   return "unknown";
        case ServiceActiveState::kActive:    return "active";
        case ServiceActiveState::kInactive:  return "inactive";
        case ServiceActiveState::kActivating: return "activating";
        case ServiceActiveState::kDeactivating: return "deactivating";
        case ServiceActiveState::kFailed:    return "failed";
    }
    return "unknown";
}

// ============================================================================
// ServiceSubState — Sub-state (more granular runtime state)
//
// From systemd: SubState
//   Various states depending on unit type:
//     service: running, dead, start, stop, reload, restart, stop-sigterm, etc.
//     socket: listening, running, stopped
//     timer: waiting, running, elapsed
// ============================================================================
enum class ServiceSubState {
    kUnknown,       // Substate unknown (acquisition failed)
    kRunning,       // Process is running
    kDead,          // Process is dead
    kStart,         // Start operation is running
    kStop,          // Stop operation is running
    kReload,        // Reload operation is running
    kRestart,       // Restart operation is running
    kWaiting,       // Waiting for event (timers)
    kListening,     // Socket listening
    kStopped,       // Stopped
    kElapsed,       // Timer has elapsed
};

inline std::string to_string(ServiceSubState s) {
    switch (s) {
        case ServiceSubState::kUnknown:   return "unknown";
        case ServiceSubState::kRunning:   return "running";
        case ServiceSubState::kDead:      return "dead";
        case ServiceSubState::kStart:     return "start";
        case ServiceSubState::kStop:      return "stop";
        case ServiceSubState::kReload:    return "reload";
        case ServiceSubState::kRestart:   return "restart";
        case ServiceSubState::kWaiting:   return "waiting";
        case ServiceSubState::kListening: return "listening";
        case ServiceSubState::kStopped:   return "stopped";
        case ServiceSubState::kElapsed:   return "elapsed";
    }
    return "unknown";
}

// ============================================================================
// ServiceRuntimeInfo — Runtime instance information
//
// Represents the runtime state of a service unit:
//   - MainPID: The main process PID (if any)
//   - ExecMainPID: The process executing the command
//   - Memory usage, CPU time, etc.
//
// Note: These are BOUNDED observations. Values may be unavailable if
// the process terminates during observation or lacks permissions.
// ============================================================================
struct ServiceRuntimeInfo {
    int64_t main_pid{-1};                    // Main process PID
    int64_t exec_main_pid{-1};               // Process executing the command
    
    uint64_t memory_current_kb{0};           // Current memory usage
    std::optional<uint64_t> memory_max_kb;   // Memory limit (if configured)
    
    uint64_t cpu_usage_ns{0};                // CPU time in nanoseconds
    
    int64_t start_timestamp_ms{-1};          // When unit started (ms since epoch)
    int64_t active_enter_timestamp_ms{-1};   // When last became active
};

// ============================================================================
// ServiceObservation — Complete observation for a single service unit
//
// Combines all available information from systemctl with proper provenance.
// This is the primary output of the discovery adapter.
// ============================================================================
struct ServiceObservation {
    ServiceIdentity identity;                // Unit name + type
    
    // Specification state (unit file)
    std::string description;                 // Human-readable description
    ServiceUnitState unit_state{ServiceUnitState::kUnknown};
    
    // Runtime state (active state)
    ServiceActiveState active_state{ServiceActiveState::kUnknown};
    ServiceSubState sub_state{ServiceSubState::kUnknown};
    
    // Runtime instance info
    std::optional<ServiceRuntimeInfo> runtime;
    
    // Source information
    std::string source_path;                 // Where unit file is defined
    std::string fragment_path;               // Fragment path (if any)
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"systemd"};           // "systemd" for native observation
};

// ============================================================================
// ServiceDiscoveryResult — Result of service discovery operation
//
// Contains all observations, statistics, and timing information.
// ============================================================================
struct ServiceDiscoveryResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description{};
    
    // All observed services
    std::vector<ServiceObservation> services;
    
    // Statistics by state
    size_t total_services{0};
    size_t active_services{0};
    size_t inactive_services{0};
    size_t failed_services{0};
    size_t other_services{0};
    
    // Statistics by unit file state
    size_t enabled_units{0};
    size_t disabled_units{0};
    size_t masked_units{0};
    
    // Timing
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    // Provider provenance
    std::string provider_source{"systemd"};
    
    // Errors encountered during discovery (non-fatal)
    std::vector<std::pair<std::string, core::Error>> errors;  // unit_id -> error mapping
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// ServiceDiscoveryAdapter — Interface for systemd service discovery
//
// Provides bounded, cancellable, freshness-aware service observation:
//   - observe_all_services: Discover all services visible from systemd
//   - observe_service: Observe a specific service by identity
//   - get_freshness: Check when last observation was performed
// ============================================================================
class ServiceDiscoveryAdapter {
public:
    virtual ~ServiceDiscoveryAdapter() = default;
    
    // Observe all services currently visible from systemd
    // Returns observations sorted by unit name for deterministic iteration
    virtual ServiceDiscoveryResult observe_all_services() = 0;
    
    // Observe a specific service by its identity (name + type)
    // Returns std::nullopt if the unit is not found or inaccessible
    virtual std::optional<ServiceObservation> observe_service(
        const ServiceIdentity& identity) = 0;
    
    // Get freshness information about the last observation
    // Returns the timestamp of the last complete observation, if any
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from systemd
    // This is idempotent and safe to call multiple times
    virtual ServiceDiscoveryResult force_refresh() = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<ServiceDiscoveryAdapter> make_systemd_service_discovery_adapter();

}  // namespace rebuntu::adapters::systemd::service