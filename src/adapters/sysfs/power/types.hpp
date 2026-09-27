// rebuntu::adapters::sysfs::power — Power Supply Observation Adapter (Phase 5.34)
//
// This module implements Rebuntu's sysfs-based power supply observation adapter:
//   - Observes power supplies from /sys/class/power_supply/
//   - Reads battery status, capacity, health, and charging state
//   - Tracks AC/DC power sources
//
// Native Interfaces Used:
//   - /sys/class/power_supply/*/ — Power supply attributes (status, type, capacity)

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <memory>

namespace rebuntu::adapters::sysfs::power {

// ============================================================================
// PowerSupplyType — Type of power supply device
//
// Represents different categories of power supplies in Linux:
//   - Battery: Rechargeable or non-rechargeable battery
//   - AC: Alternating current (wall outlet) adapter
//   - USB: USB power source
//   - Wireless: Wireless charging pad
// ============================================================================
enum class PowerSupplyType {
    kUnknown,       // Type could not be determined
    kBattery,       // Rechargeable or non-rechargeable battery
    kAc,            // AC power adapter (wall outlet)
    kUsb,           // USB power source
    kWireless,      // Wireless charging pad
};

inline std::string to_string(PowerSupplyType t) {
    switch (t) {
        case PowerSupplyType::kUnknown:  return "unknown";
        case PowerSupplyType::kBattery:  return "battery";
        case PowerSupplyType::kAc:       return "ac";
        case PowerSupplyType::kUsb:      return "usb";
        case PowerSupplyType::kWireless: return "wireless";
    }
    return "unknown";
}

// ============================================================================
// BatteryStatus — Current charge status of a battery
//
// Represents the state of charge operation:
//   - Full: Battery is fully charged
//   - Charging: Battery is currently charging
//   - Discharging: Battery is discharging (powering system)
//   - NotCharging: Battery is not charging (may be full or disabled)
//   - Unknown: Status could not be determined
// ============================================================================
enum class BatteryStatus {
    kFull,           // Battery fully charged, AC present
    kCharging,       // Battery currently charging
    kDischarging,    // Battery discharging (powering system)
    kNotCharging,    // Not charging (may be full or disabled)
    kUnknown,        // Status could not be determined
};

inline std::string to_string(BatteryStatus s) {
    switch (s) {
        case BatteryStatus::kFull:         return "full";
        case BatteryStatus::kCharging:     return "charging";
        case BatteryStatus::kDischarging:  return "discharging";
        case BatteryStatus::kNotCharging:  return "not_charging";
        case BatteryStatus::kUnknown:      return "unknown";
    }
    return "unknown";
}

// ============================================================================
// PowerSupplyIdentity — Stable identity for a power supply device
//
// A power supply is uniquely identified by its name in sysfs.
// The name corresponds to the directory under /sys/class/power_supply/.
// ============================================================================
struct PowerSupplyIdentity {
    std::string name;         // Name as it appears in sysfs (e.g., "BAT0", "AC0")
};

inline bool operator==(const PowerSupplyIdentity& a, const PowerSupplyIdentity& b) {
    return a.name == b.name;
}

// ============================================================================
// BatteryObservation — Observation of a battery power supply
//
// Contains detailed information about a rechargeable battery.
// ============================================================================
struct BatteryObservation {
    std::optional<int64_t> voltage_now;           // Voltage in microvolts (µV)
    std::optional<int64_t> current_now;           // Current in microamperes (µA)
    std::optional<int64_t> charge_full_design;    // Design capacity in µAh
    std::optional<int64_t> charge_full;           // Last full capacity in µAh
    std::optional<int64_t> charge_now;            // Current charge in µAh
    std::optional<int64_t> energy_full_design;    // Design energy in µWh
    std::optional<int64_t> energy_full;           // Last full energy in µWh
    std::optional<int64_t> energy_now;            // Current energy in µWh
    std::optional<int64_t> power_now;             // Current power in µW
    
    std::optional<int> cycle_count;               // Number of charge cycles
    std::optional<std::string> chemistry;         // Battery chemistry (e.g., "Li-ion")
    
    std::optional<int> temperature;               // Temperature in millidegrees Celsius
};

// ============================================================================
// PowerSupplyObservation — Complete observation of a power supply
//
// Combines basic attributes with detailed battery information where applicable.
// ============================================================================
struct PowerSupplyObservation {
    PowerSupplyIdentity identity;
    
    // Basic identification
    std::optional<std::string> manufacturer;      // Manufacturer name
    std::optional<std::string> model_name;        // Model/product name
    std::optional<std::string> serial_number;     // Serial number
    std::optional<std::string> hw_revision;       // Hardware revision
    
    // Type classification
    PowerSupplyType type{PowerSupplyType::kUnknown};
    
    // State information (for batteries)
    BatteryStatus status{BatteryStatus::kUnknown};
    bool online{false};                           // True if power source is connected/active
    
    // Capacity information (for batteries)
    std::optional<int> capacity;                  // Percentage (0-100)
    std::optional<std::string> capacity_level;    // Human-readable level (e.g., "Full", "Low")
    
    // Detailed battery metrics
    BatteryObservation battery;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"sysfs"};                  // Source identifier
};

// ============================================================================
// PowerTopology — Relationship topology of power supplies
//
// Represents how different power sources relate to each other.
// ============================================================================
struct PowerTopology {
    // All observed power supplies indexed by name
    std::unordered_map<std::string, PowerSupplyObservation> supplies_by_name;
    
    // Power relationships
    bool has_ac_power{false};                     // True if AC adapter is online
    bool has_battery{false};                      // True if battery is present
    
    // Battery statistics (if battery present)
    std::optional<int> battery_percentage;        // Overall battery percentage
    std::optional<int64_t> battery_energy_now;    // Current energy in µWh
    std::optional<int64_t> battery_energy_full;   // Full capacity in µWh
    
    std::chrono::system_clock::time_point captured_at{};
};

// ============================================================================
// PowerObservationResult — Result of power supply observation
// ============================================================================
struct PowerObservationResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description;
    
    // Raw observations (individual power supplies)
    std::vector<PowerSupplyObservation> supplies;
    
    // Derived topology information
    std::optional<PowerTopology> topology;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_supplies{0};
    size_t supplies_with_errors{0};               // Supplies where observation failed
    
    // Provider provenance
    std::string provider_source{"sysfs"};
    
    std::optional<core::Error> error;
};

// ============================================================================
// PowerSupplyAdapter — Interface for sysfs power supply observation
// ============================================================================
class PowerSupplyAdapter {
public:
    virtual ~PowerSupplyAdapter() = default;
    
    // Observe all power supplies
    virtual PowerObservationResult observe_supplies() = 0;
    
    // Get the full topology of power relationships
    virtual PowerTopology get_topology() = 0;
    
    // Resolve a specific power supply by name
    virtual std::optional<PowerSupplyObservation> resolve_supply(std::string_view name) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<PowerSupplyAdapter> make_sysfs_power_adapter();

}  // namespace rebuntu::adapters::sysfs::power