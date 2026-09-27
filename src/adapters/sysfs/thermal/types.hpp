// rebuntu::adapters::sysfs::thermal — Thermal Zone Observation Adapter (Phase 5.34)
//
// This module implements Rebuntu's sysfs-based thermal zone observation adapter:
//   - Observes thermal zones from /sys/class/thermal/
//   - Reads cooling device states, temperatures, and trip points
//   - Tracks thermal throttling and cooling activity
//
// Native Interfaces Used:
//   - /sys/class/thermal/thermal_zone* — Thermal zone attributes (type, temp, mode)
//   - /sys/class/thermal/cooling_device* — Cooling device states

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <memory>

namespace rebuntu::adapters::sysfs::thermal {

// ============================================================================
// ThermalZoneType — Type of thermal zone
//
// Represents different categories of thermal zones in Linux:
//   - Processor: CPU package or core temperature
//   - Battery: Battery pack temperature
//   - GPU: Graphics processor temperature
//   - Fan: Air/liquid cooling temperature
//   - Network: Network interface temperature
// ============================================================================
enum class ThermalZoneType {
    kUnknown,       // Type could not be determined
    kProcessor,     // CPU package or core temperature
    kBattery,       // Battery pack temperature
    kGpu,           // Graphics processor temperature
    kFan,           // Air/liquid cooling temperature
    kNetwork,       // Network interface temperature
};

inline std::string to_string(ThermalZoneType t) {
    switch (t) {
        case ThermalZoneType::kUnknown:   return "unknown";
        case ThermalZoneType::kProcessor: return "processor";
        case ThermalZoneType::kBattery:   return "battery";
        case ThermalZoneType::kGpu:       return "gpu";
        case ThermalZoneType::kFan:       return "fan";
        case ThermalZoneType::kNetwork:   return "network";
    }
    return "unknown";
}

// ============================================================================
// CoolingDeviceType — Type of cooling device
//
// Represents different cooling mechanisms in Linux:
//   - Processor: CPU throttling via frequency scaling
//   - Fan: Active cooling fan
//   - Passive: Passive cooling (thermal throttling)
// ============================================================================
enum class CoolingDeviceType {
    kUnknown,       // Type could not be determined
    kProcessor,     // CPU throttling (freq_scaling)
    kFan,           // Active cooling fan
    kPassive,       // Passive cooling (thermal throttling)
};

inline std::string to_string(CoolingDeviceType t) {
    switch (t) {
        case CoolingDeviceType::kUnknown: return "unknown";
        case CoolingDeviceType::kProcessor: return "processor";
        case CoolingDeviceType::kFan:       return "fan";
        case CoolingDeviceType::kPassive:   return "passive";
    }
    return "unknown";
}

// ============================================================================
// ThermalZoneIdentity — Stable identity for a thermal zone
//
// A thermal zone is uniquely identified by its number (0, 1, etc.)
// or name as it appears in /sys/class/thermal/.
// ============================================================================
struct ThermalZoneIdentity {
    int index{-1};              // Numeric index from sysfs (e.g., 0 from "thermal_zone0")
    std::string name;           // Human-readable name (from "type" file)
};

inline bool operator==(const ThermalZoneIdentity& a, const ThermalZoneIdentity& b) {
    return a.index == b.index && a.name == b.name;
}

// ============================================================================
// CoolingDeviceIdentity — Stable identity for a cooling device
//
// A cooling device is uniquely identified by its number (0, 1, etc.)
// or name as it appears in /sys/class/thermal/.
// ============================================================================
struct CoolingDeviceIdentity {
    int index{-1};              // Numeric index from sysfs
    std::string type;           // Type string from "type" file
};

inline bool operator==(const CoolingDeviceIdentity& a, const CoolingDeviceIdentity& b) {
    return a.index == b.index && a.type == b.type;
}

// ============================================================================
// ThermalTripPoint — A trip point in the thermal zone
//
// Trip points define temperature thresholds that trigger actions:
//   - Critical: Emergency shutdown threshold
//   - Hot: Warning threshold for heat-related actions
//   - Passive: Passive cooling activation (e.g., CPU throttling)
//   - Active: Active cooling activation (e.g., fan on)
// ============================================================================
struct ThermalTripPoint {
    int trip_type{-1};          // Trip type (-2 to -5 in Linux)
    int64_t temperature_millidegrees{};  // Temperature in millidegrees Celsius
};

// ============================================================================
// ThermalZoneObservation — Observation of a thermal zone
//
// Contains temperature and trip point information for a thermal zone.
// ============================================================================
struct ThermalZoneObservation {
    ThermalZoneIdentity identity;
    
    // Current state
    std::optional<int64_t> temperature_millidegrees;  // Temperature in millidegrees Celsius
    
    // Trip points (if available)
    std::vector<ThermalTripPoint> trip_points;
    
    // Operating mode
    std::optional<std::string> mode;            // "enabled" or "disabled"
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"sysfs"};
};

// ============================================================================
// CoolingDeviceObservation — Observation of a cooling device
//
// Contains current and maximum cooling states for a cooling device.
// ============================================================================
struct CoolingDeviceObservation {
    CoolingDeviceIdentity identity;
    
    // Current state
    int64_t current_state{};                    // Current cooling level (0 to max)
    int64_t max_state{};                        // Maximum cooling level
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"sysfs"};
};

// ============================================================================
// ThermalTopology — Relationship topology of thermal zones and cooling devices
//
// Represents how thermal zones relate to their cooling devices.
// ============================================================================
struct ThermalTopology {
    // All observed thermal zones indexed by index
    std::unordered_map<int, ThermalZoneObservation> zones_by_index;
    
    // All observed cooling devices indexed by index
    std::unordered_map<int, CoolingDeviceObservation> devices_by_index;
    
    // Top-level thermal status
    bool is_throttling{false};                  // True if any zone is at critical temp
    
    int64_t max_temperature_millidegrees{};     // Highest observed temperature
    
    std::chrono::system_clock::time_point captured_at{};
};

// ============================================================================
// ThermalObservationResult — Result of thermal observation
// ============================================================================
struct ThermalObservationResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description;
    
    // Raw observations
    std::vector<ThermalZoneObservation> zones;
    std::vector<CoolingDeviceObservation> cooling_devices;
    
    // Derived topology information
    std::optional<ThermalTopology> topology;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_zones{0};
    size_t total_cooling_devices{0};
    size_t observations_with_errors{0};
    
    // Provider provenance
    std::string provider_source{"sysfs"};
    
    std::optional<core::Error> error;
};

// ============================================================================
// ThermalAdapter — Interface for sysfs thermal observation
// ============================================================================
class ThermalAdapter {
public:
    virtual ~ThermalAdapter() = default;
    
    // Observe all thermal zones and cooling devices
    virtual ThermalObservationResult observe_thermal() = 0;
    
    // Get the full topology of thermal relationships
    virtual ThermalTopology get_topology() = 0;
    
    // Resolve a specific thermal zone by index
    virtual std::optional<ThermalZoneObservation> resolve_zone(int index) = 0;
    
    // Resolve a specific cooling device by index
    virtual std::optional<CoolingDeviceObservation> resolve_cooling_device(int index) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<ThermalAdapter> make_sysfs_thermal_adapter();

}  // namespace rebuntu::adapters::sysfs::thermal