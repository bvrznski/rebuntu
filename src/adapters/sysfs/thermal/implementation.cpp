// rebuntu::adapters::sysfs::thermal — Thermal Zone Observation Implementation (Phase 5.34)
//
// This module implements the sysfs-based thermal zone observation adapter:
//   - Reads temperatures from /sys/class/thermal/thermal_zone*
//   - Observes: type, temperature, trip points
//   - Tracks cooling device states

#include "adapters/sysfs/thermal/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace rebuntu::adapters::sysfs::thermal {

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
// Helper: Get list of thermal zones from /sys/class/thermal
// ============================================================================
static std::vector<std::pair<int, std::string>> get_thermal_zones() {
    std::vector<std::pair<int, std::string>> result;
    
    // Read directory entries manually using standard file operations
    std::ifstream dir("/sys/class/thermal");
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
        
        if (line.substr(0, 12) == "thermal_zone") {
            try {
                int index = std::stoi(line.substr(12));
                result.emplace_back(index, line);
            } catch (...) {
                // Not a valid thermal zone index
            }
        }
    }
    
    // Sort by index for consistent ordering
    std::sort(result.begin(), result.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });
    
    return result;
}

// ============================================================================
// Helper: Get list of cooling devices from /sys/class/thermal
// ============================================================================
static std::vector<std::pair<int, std::string>> get_cooling_devices() {
    std::vector<std::pair<int, std::string>> result;
    
    // Read directory entries manually using standard file operations
    std::ifstream dir("/sys/class/thermal");
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
        
        if (line.substr(0, 13) == "cooling_device") {
            try {
                int index = std::stoi(line.substr(13));
                result.emplace_back(index, line);
            } catch (...) {
                // Not a valid cooling device index
            }
        }
    }
    
    // Sort by index for consistent ordering
    std::sort(result.begin(), result.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });
    
    return result;
}

// ============================================================================
// Helper: Read thermal trip points from sysfs (if available)
// ============================================================================
static std::vector<ThermalTripPoint> read_trip_points(std::string_view zone_path) {
    std::vector<ThermalTripPoint> trip_points;
    
    // Linux thermal sysfs has trip_point_0_type, trip_point_0_temp, etc.
    for (int i = 0; i < 32; ++i) {  // Support up to 32 trip points
        std::string type_path = std::string(zone_path) + "/trip_point_" + std::to_string(i) + "_type";
        std::string temp_path = std::string(zone_path) + "/trip_point_" + std::to_string(i) + "_temp";
        
        if (!sysfs_file_exists(type_path)) {
            break;  // No more trip points
        }
        
        ThermalTripPoint tp;
        tp.trip_type = i;  // trip_point_N index
        
        auto temp_opt = read_sysfs_attribute(temp_path);
        if (temp_opt) {
            try {
                // Temperature is stored in millidegrees Celsius
                tp.temperature_millidegrees = std::stoll(*temp_opt);
            } catch (...) {}
        }
        
        trip_points.push_back(tp);
    }
    
    return trip_points;
}

// ============================================================================
// Helper: Read a single thermal zone observation
// ============================================================================
static std::optional<ThermalZoneObservation> read_thermal_zone(int index, std::string_view name) {
    std::string zone_path = "/sys/class/thermal/" + std::string{name};
    
    if (!sysfs_file_exists(zone_path)) {
        return std::nullopt;
    }
    
    ThermalZoneObservation obs;
    obs.identity.index = index;
    obs.observed_at = std::chrono::system_clock::now();
    obs.source = "sysfs";
    
    // Read type
    auto type_opt = read_sysfs_attribute(zone_path + "/type");
    if (type_opt) {
        obs.identity.name = *type_opt;
    }
    
    // Read temperature
    auto temp_opt = read_sysfs_attribute(zone_path + "/temp");
    if (temp_opt) {
        try {
            obs.temperature_millidegrees = std::stoll(*temp_opt);
        } catch (...) {}
    }
    
    // Read mode
    auto mode_opt = read_sysfs_attribute(zone_path + "/mode");
    if (mode_opt) obs.mode = *mode_opt;
    
    // Read trip points (if available)
    obs.trip_points = read_trip_points(zone_path);
    
    return obs;
}

// ============================================================================
// Helper: Read a single cooling device observation
// ============================================================================
static std::optional<CoolingDeviceObservation> read_cooling_device(int index, std::string_view name) {
    std::string device_path = "/sys/class/thermal/" + std::string{name};
    
    if (!sysfs_file_exists(device_path)) {
        return std::nullopt;
    }
    
    CoolingDeviceObservation obs;
    obs.identity.index = index;
    obs.observed_at = std::chrono::system_clock::now();
    obs.source = "sysfs";
    
    // Read type
    auto type_opt = read_sysfs_attribute(device_path + "/type");
    if (type_opt) {
        obs.identity.type = *type_opt;
    }
    
    // Read current state
    auto cur_state_opt = read_sysfs_attribute(device_path + "/cur_state");
    if (cur_state_opt) {
        try {
            obs.current_state = std::stoll(*cur_state_opt);
        } catch (...) {}
    }
    
    // Read max state
    auto max_state_opt = read_sysfs_attribute(device_path + "/max_state");
    if (max_state_opt) {
        try {
            obs.max_state = std::stoll(*max_state_opt);
        } catch (...) {}
    }
    
    return obs;
}

// ============================================================================
// ThermalAdapter Implementation
// ============================================================================

class SysfsThermalAdapter : public ThermalAdapter {
public:
    SysfsThermalAdapter() = default;
    ~SysfsThermalAdapter() override = default;
    
    ThermalObservationResult observe_thermal() override {
        ThermalObservationResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Get list of thermal zones from sysfs
        auto zones = get_thermal_zones();
        auto devices = get_cooling_devices();
        
        // Build topology structures
        ThermalTopology topology;
        topology.captured_at = std::chrono::system_clock::now();
        
        for (const auto& [index, name] : zones) {
            auto obs_opt = read_thermal_zone(index, name);
            if (!obs_opt) continue;
            
            auto& obs = *obs_opt;
            result.zones.push_back(std::move(obs));
            
            const auto& final_obs = result.zones.back();
            topology.zones_by_index[final_obs.identity.index] = final_obs;
            
            // Track maximum temperature
            if (final_obs.temperature_millidegrees.has_value()) {
                if (final_obs.temperature_millidegrees.value() > topology.max_temperature_millidegrees) {
                    topology.max_temperature_millidegrees = final_obs.temperature_millidegrees.value();
                }
                // Consider anything above 90°C (90000 millidegree) as throttling
                if (final_obs.temperature_millidegrees.value() > 90000) {
                    topology.is_throttling = true;
                }
            }
            
            result.total_zones++;
        }
        
        for (const auto& [index, name] : devices) {
            auto obs_opt = read_cooling_device(index, name);
            if (!obs_opt) continue;
            
            auto& obs = *obs_opt;
            result.cooling_devices.push_back(std::move(obs));
            
            const auto& final_obs = result.cooling_devices.back();
            topology.devices_by_index[final_obs.identity.index] = final_obs;
            
            result.total_cooling_devices++;
        }
        
        result.topology = std::move(topology);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.provider_source = "sysfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed thermal zones and cooling devices";
        
        return result;
    }
    
    ThermalTopology get_topology() override {
        auto result = observe_thermal();
        if (result.topology) {
            return *std::move(result.topology);
        }
        return ThermalTopology{};
    }
    
    std::optional<ThermalZoneObservation> resolve_zone(int index) override {
        auto result = observe_thermal();
        
        for (const auto& zone : result.zones) {
            if (zone.identity.index == index) {
                return zone;
            }
        }
        
        return std::nullopt;
    }
    
    std::optional<CoolingDeviceObservation> resolve_cooling_device(int index) override {
        auto result = observe_thermal();
        
        for (const auto& device : result.cooling_devices) {
            if (device.identity.index == index) {
                return device;
            }
        }
        
        return std::nullopt;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ThermalAdapter> make_sysfs_thermal_adapter() {
    return std::make_unique<SysfsThermalAdapter>();
}

}  // namespace rebuntu::adapters::sysfs::thermal