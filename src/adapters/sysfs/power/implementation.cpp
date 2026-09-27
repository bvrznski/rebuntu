// rebuntu::adapters::sysfs::power — Power Supply Observation Implementation (Phase 5.34)
//
// This module implements the sysfs-based power supply observation adapter:
//   - Reads battery status from /sys/class/power_supply/
//   - Observes: type, status, capacity, voltage, current, energy
//   - Tracks AC/DC power relationships

#include "adapters/sysfs/power/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace rebuntu::adapters::sysfs::power {

// ============================================================================
// Helper: Read a single line from sysfs attribute file
// ============================================================================
static std::optional<std::string> read_sysfs_attribute(std::string_view path) {
    std::ifstream file(std::string{path});
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::string content;
    std::getline(file, content);
    
    // Trim trailing newline and whitespace
    while (!content.empty() && (content.back() == '\n' || content.back() == '\r')) {
        content.pop_back();
    }
    
    return content.empty() ? std::nullopt : std::make_optional(content);
}

// ============================================================================
// Helper: Check if file exists using stat
// ============================================================================
static bool sysfs_file_exists(std::string_view path) {
    std::ifstream file(std::string{path});
    return file.is_open();
}

// ============================================================================
// Helper: Parse battery status from sysfs
// ============================================================================
static BatteryStatus parse_battery_status(std::string_view status_str) {
    // Status strings in power_supply: "Full", "Charging", "Discharging", "Not charging"
    
    if (status_str == "Full") return BatteryStatus::kFull;
    if (status_str == "Charging") return BatteryStatus::kCharging;
    if (status_str == "Discharging") return BatteryStatus::kDischarging;
    if (status_str == "Not charging") return BatteryStatus::kNotCharging;
    
    // Fallback for unknown
    return BatteryStatus::kUnknown;
}

// ============================================================================
// Helper: Parse power supply type from sysfs
// ============================================================================
static PowerSupplyType parse_power_supply_type(std::string_view type_str) {
    // Type strings in power_supply: "Battery", "AC", "USB"
    
    if (type_str == "Battery") return PowerSupplyType::kBattery;
    if (type_str == "AC") return PowerSupplyType::kAc;
    if (type_str == "USB") return PowerSupplyType::kUsb;
    if (type_str == "Wireless") return PowerSupplyType::kWireless;
    
    // Fallback to unknown
    return PowerSupplyType::kUnknown;
}

// ============================================================================
// Helper: Get list of power supplies from /sys/class/power_supply
// ============================================================================
static std::vector<std::string> get_power_supplies() {
    std::vector<std::string> result;
    
    // Read directory entries manually using standard file operations
    std::ifstream dir("/sys/class/power_supply");
    if (!dir.is_open()) {
        return result;
    }
    
    std::string line;
    while (std::getline(dir, line)) {
        // Remove trailing whitespace/newline
        while (!line.empty() && (line.back() == ' ' || line.back() == '\t' || 
                line.back() == '\n' || line.back() == '\r')) {
            line.pop_back();
        }
        
        if (!line.empty()) {
            result.push_back(line);
        }
    }
    
    // Sort for consistent ordering
    std::sort(result.begin(), result.end());
    
    return result;
}

// ============================================================================
// Helper: Read battery metrics from sysfs (optional fields)
// ============================================================================
static BatteryObservation read_battery_metrics(std::string_view supply_path) {
    BatteryObservation obs;
    
    auto try_read_int64 = [&](std::string file, std::optional<int64_t>& out) {
        std::string path = std::string(supply_path) + "/" + file;
        auto opt = read_sysfs_attribute(path);
        if (opt) {
            try {
                out = std::stoll(*opt);
            } catch (...) {
                // Leave as nullopt
            }
        }
    };
    
    try_read_int64("voltage_now", obs.voltage_now);
    try_read_int64("current_now", obs.current_now);
    try_read_int64("charge_full_design", obs.charge_full_design);
    try_read_int64("charge_full", obs.charge_full);
    try_read_int64("charge_now", obs.charge_now);
    try_read_int64("energy_full_design", obs.energy_full_design);
    try_read_int64("energy_full", obs.energy_full);
    try_read_int64("energy_now", obs.energy_now);
    try_read_int64("power_now", obs.power_now);
    
    // Cycle count
    if (sysfs_file_exists(std::string(supply_path) + "/cycle_count")) {
        auto opt = read_sysfs_attribute(std::string(supply_path) + "/cycle_count");
        if (opt) {
            try {
                obs.cycle_count = std::stoi(*opt);
            } catch (...) {}
        }
    }
    
    // Chemistry
    if (sysfs_file_exists(std::string(supply_path) + "/chemistry")) {
        auto opt = read_sysfs_attribute(std::string(supply_path) + "/chemistry");
        if (opt) obs.chemistry = *opt;
    }
    
    // Temperature (if available)
    if (sysfs_file_exists(std::string(supply_path) + "/temp")) {
        std::optional<int64_t> temp_value;
        try_read_int64("temp", temp_value);
        if (temp_value.has_value()) {
            obs.temperature = static_cast<int>(temp_value.value());
        }
    }
    
    return obs;
}

// ============================================================================
// Helper: Read a single power supply observation
// ============================================================================
static std::optional<PowerSupplyObservation> read_power_supply(std::string_view name) {
    std::string supply_path = "/sys/class/power_supply/" + std::string{name};
    
    if (!sysfs_file_exists(supply_path)) {
        return std::nullopt;
    }
    
    PowerSupplyObservation obs;
    obs.identity.name = std::string{name};
    obs.observed_at = std::chrono::system_clock::now();
    obs.source = "sysfs";
    
    // Read type
    auto type_opt = read_sysfs_attribute(supply_path + "/type");
    if (type_opt) {
        obs.type = parse_power_supply_type(*type_opt);
    }
    
    // Read manufacturer
    if (sysfs_file_exists(supply_path + "/manufacturer")) {
        auto opt = read_sysfs_attribute(supply_path + "/manufacturer");
        if (opt) obs.manufacturer = *opt;
    }
    
    // Read model name
    if (sysfs_file_exists(supply_path + "/model_name")) {
        auto opt = read_sysfs_attribute(supply_path + "/model_name");
        if (opt) obs.model_name = *opt;
    }
    
    // Read serial number
    if (sysfs_file_exists(supply_path + "/serial_number")) {
        auto opt = read_sysfs_attribute(supply_path + "/serial_number");
        if (opt) obs.serial_number = *opt;
    }
    
    // Read hardware revision
    if (sysfs_file_exists(supply_path + "/hw_revision")) {
        auto opt = read_sysfs_attribute(supply_path + "/hw_revision");
        if (opt) obs.hw_revision = *opt;
    }
    
    // Read status (for batteries)
    auto status_opt = read_sysfs_attribute(supply_path + "/status");
    if (status_opt) {
        obs.status = parse_battery_status(*status_opt);
    }
    
    // Read online state
    auto online_opt = read_sysfs_attribute(supply_path + "/online");
    if (online_opt) {
        try {
            obs.online = std::stoi(*online_opt) != 0;
        } catch (...) {}
    }
    
    // Read capacity (percentage)
    auto capacity_opt = read_sysfs_attribute(supply_path + "/capacity");
    if (capacity_opt) {
        try {
            obs.capacity = std::stoi(*capacity_opt);
        } catch (...) {}
    }
    
    // Read capacity level
    auto cap_level_opt = read_sysfs_attribute(supply_path + "/capacity_level");
    if (cap_level_opt) obs.capacity_level = *cap_level_opt;
    
    // Read battery metrics if this is a battery
    if (obs.type == PowerSupplyType::kBattery) {
        obs.battery = read_battery_metrics(supply_path);
    }
    
    return obs;
}

// ============================================================================
// PowerSupplyAdapter Implementation
// ============================================================================

class SysfsPowerAdapter : public PowerSupplyAdapter {
public:
    SysfsPowerAdapter() = default;
    ~SysfsPowerAdapter() override = default;
    
    PowerObservationResult observe_supplies() override {
        PowerObservationResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Get list of power supplies from sysfs
        auto supplies = get_power_supplies();
        
        if (supplies.empty()) {
            result.status = core::SemanticStatus::kSuccess;
            result.description = "No power supplies found";
            result.provider_source = "sysfs";
            return result;
        }
        
        // Build topology structures
        PowerTopology topology;
        topology.captured_at = std::chrono::system_clock::now();
        
        for (const auto& name : supplies) {
            auto obs_opt = read_power_supply(name);
            if (!obs_opt) continue;
            
            auto& obs = *obs_opt;
            result.supplies.push_back(std::move(obs));
            
            const auto& final_obs = result.supplies.back();
            topology.supplies_by_name[final_obs.identity.name] = final_obs;
            
            // Update topology flags
            if (final_obs.type == PowerSupplyType::kAc && final_obs.online) {
                topology.has_ac_power = true;
            }
            if (final_obs.type == PowerSupplyType::kBattery) {
                topology.has_battery = true;
                if (final_obs.capacity.has_value()) {
                    // Use the first battery's capacity
                    if (!topology.battery_percentage.has_value()) {
                        topology.battery_percentage = final_obs.capacity.value();
                    }
                }
                if (final_obs.battery.energy_now.has_value()) {
                    if (!topology.battery_energy_now.has_value()) {
                        topology.battery_energy_now = final_obs.battery.energy_now.value();
                    }
                }
                if (final_obs.battery.energy_full.has_value()) {
                    if (!topology.battery_energy_full.has_value()) {
                        topology.battery_energy_full = final_obs.battery.energy_full.value();
                    }
                }
            }
            
            result.total_supplies++;
        }
        
        result.topology = std::move(topology);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.provider_source = "sysfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed power supplies";
        
        return result;
    }
    
    PowerTopology get_topology() override {
        auto result = observe_supplies();
        if (result.topology) {
            return *std::move(result.topology);
        }
        return PowerTopology{};
    }
    
    std::optional<PowerSupplyObservation> resolve_supply(std::string_view name) override {
        auto result = observe_supplies();
        
        for (const auto& supply : result.supplies) {
            if (supply.identity.name == name) {
                return supply;
            }
        }
        
        return std::nullopt;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<PowerSupplyAdapter> make_sysfs_power_adapter() {
    return std::make_unique<SysfsPowerAdapter>();
}

}  // namespace rebuntu::adapters::sysfs::power