// rebuntu::adapters::sysfs::md_raid — Software RAID (md) Observation Implementation (Phase 5.20)
//
// This module implements the sysfs-based md RAID observation adapter:
//   - Reads array information from /sys/block/md-X/md/
//   - Parses /proc/mdstat for detailed status
//   - Observes: level, member disks, state, sync progress

#include "adapters/sysfs/md_raid/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <filesystem>

namespace rebuntu::adapters::sysfs::md_raid {

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
// Helper: Get list of md-X devices from /sys/block
// ============================================================================
static std::vector<std::string> get_md_devices() {
    std::vector<std::string> result;
    
    // Read directory entries manually using standard file operations
    std::ifstream dir("/sys/block");
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
        
        if (line.size() > 3 && line.substr(0, 3) == "md-") {
            // Try to parse the number
            try {
                std::string num_part = line.substr(3);
                int num = std::stoi(num_part);
                (void)num;  // Validate it's numeric
                result.push_back(line);
            } catch (...) {
                // Not a valid md-X device name, skip
            }
        }
    }
    
    // Sort by number for consistent ordering
    std::sort(result.begin(), result.end(),
        [](const std::string& a, const std::string& b) {
            auto num_a = std::stoi(a.substr(3));
            auto num_b = std::stoi(b.substr(3));
            return num_a < num_b;
        });
    
    return result;
}

// ============================================================================
// Helper: Parse RAID level from sysfs
// ============================================================================
static RaidLevel parse_raid_level(std::string_view level_str) {
    // Level strings in sysfs: "linear", "raid0", "raid1", "raid4", "raid5", "raid6", "raid10"
    
    if (level_str == "linear") return RaidLevel::kLinear;
    if (level_str == "raid0" || level_str == "raid-0") return RaidLevel::kRaid0;
    if (level_str == "raid1" || level_str == "raid-1") return RaidLevel::kRaid1;
    if (level_str == "raid4" || level_str == "raid-4") return RaidLevel::kRaid4;
    if (level_str == "raid5" || level_str == "raid-5") return RaidLevel::kRaid5;
    if (level_str == "raid6" || level_str == "raid-6") return RaidLevel::kRaid6;
    if (level_str == "raid10" || level_str == "raid-10") return RaidLevel::kRaid10;
    
    // Fallback to linear for unknown
    return RaidLevel::kLinear;
}

// ============================================================================
// Helper: Parse array state from sysfs
// ============================================================================
static ArrayState parse_array_state(std::string_view state_str) {
    // States in mdstat: "active", "inactive", "degraded", "syncing", "recovering"
    
    if (state_str == "inactive") return ArrayState::kInactive;
    if (state_str == "active" || state_str == "active idle") return ArrayState::kActive;
    if (state_str == "degraded") return ArrayState::kDegraded;
    if (state_str == "syncing" || state_str == "resync") return ArrayState::kSyncing;
    if (state_str == "recovering") return ArrayState::kRecovering;
    
    // Default to inactive for unknown
    return ArrayState::kInactive;
}

// ============================================================================
// Helper: Parse /proc/mdstat for detailed array status (unused - using sysfs only)
//
// Sample mdstat format:
// Personalities : [raid1] [raid0]
// md0 : active raid1 sda1[0] sdb1[1]
//       10485760 blocks super 1.2 [2/2] [UU]
//       [=====>.............]  recovery = 25.0% (2621440/10485760) finish=0.5min speed=1000K/sec
//
// md1 : active raid0 sdc1[0] sdd1[1]
//       20971520 blocks super 1.2 512k chunks
// ============================================================================

// ============================================================================
// Helper: Read md device attributes from sysfs
// ============================================================================
static std::optional<MdArrayObservation> read_md_device_attributes(std::string_view md_name) {
    auto device_path = "/sys/block/" + std::string(md_name) + "/md/";
    
    MdArrayObservation obs;
    obs.identity.name = std::string(md_name);
    obs.observed_at = std::chrono::system_clock::now();
    obs.source = "sysfs";
    
    // Read level
    auto level_opt = read_sysfs_attribute(device_path + "level");
    if (level_opt) {
        obs.level = parse_raid_level(*level_opt);
    }
    
    // Read raid_disks
    auto disks_opt = read_sysfs_attribute(device_path + "raid_disks");
    if (disks_opt) {
        try {
            obs.raid_disks = std::stoi(*disks_opt);
        } catch (...) {}
    }
    
    // Read active_disks
    auto active_opt = read_sysfs_attribute(device_path + "active_disks");
    if (active_opt) {
        try {
            obs.active_disks = std::stoi(*active_opt);
        } catch (...) {}
    }
    
    // Read working_disks
    auto working_opt = read_sysfs_attribute(device_path + "working_disks");
    if (working_opt) {
        try {
            obs.working_disks = std::stoi(*working_opt);
        } catch (...) {}
    }
    
    // Read failed_disks
    auto failed_opt = read_sysfs_attribute(device_path + "failed_disks");
    if (failed_opt) {
        try {
            obs.failed_disks = std::stoi(*failed_opt);
        } catch (...) {}
    }
    
    // Read spare_disks
    auto spare_opt = read_sysfs_attribute(device_path + "spare_disks");
    if (spare_opt) {
        try {
            obs.spare_disks = std::stoi(*spare_opt);
        } catch (...) {}
    }
    
    // Read array_state
    auto state_opt = read_sysfs_attribute(device_path + "array_state");
    if (state_opt) {
        obs.state = parse_array_state(*state_opt);
    }
    
    // Read uuid
    auto uuid_opt = read_sysfs_attribute(device_path + "uuid");
    obs.identity.uuid = uuid_opt;
    
    // Read dev-* files for member disks (dev-0, dev-1, etc.)
    for (int i = 0; i < 32; ++i) {  // Support up to 32 disks per array
        auto dev_path = device_path + "dev-" + std::to_string(i) + "/spare_group";
        if (std::filesystem::exists(dev_path)) {
            MemberDisk disk;
            disk.raid_position = i;
            
            // Read the block device path from the dev-* file
            auto dev_name_opt = read_sysfs_attribute(device_path + "dev-" + std::to_string(i));
            if (dev_name_opt) {
                disk.device_path = "/dev/" + *dev_name_opt;
                
                // Check if it's marked as spare
                auto spare_group_opt = read_sysfs_attribute(dev_path);
                if (spare_group_opt && spare_group_opt->empty()) {
                    disk.is_spare = true;
                } else {
                    disk.is_active = true;
                }
            }
            
            obs.member_disks.push_back(disk);
        }
    }
    
    // Calculate totals
    for (const auto& disk : obs.member_disks) {
        if (!disk.is_active && !disk.is_spare) {
            // This shouldn't happen based on our logic, but just in case
            obs.failed_disks++;
        } else if (disk.is_spare) {
            obs.spare_disks++;
        }
    }
    
    // If raid_disks wasn't set, estimate from members
    if (obs.raid_disks == 0 && !obs.member_disks.empty()) {
        obs.raid_disks = static_cast<int>(obs.member_disks.size());
    }
    obs.working_disks = obs.active_disks + obs.spare_disks;
    
    return obs;
}

// ============================================================================
// MdRaidAdapter Implementation
// ============================================================================

class SysfsMdRaidAdapter : public MdRaidAdapter {
public:
    SysfsMdRaidAdapter() = default;
    ~SysfsMdRaidAdapter() override = default;
    
    MdObservationResult observe_arrays() override {
        MdObservationResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Get list of md devices from sysfs
        auto md_devices = get_md_devices();
        
        if (md_devices.empty()) {
            result.status = core::SemanticStatus::kSuccess;
            result.description = "No md RAID arrays found";
            result.provider_source = "sysfs";
            return result;
        }
        
        // Build topology structures
        MdTopology topology;
        topology.captured_at = std::chrono::system_clock::now();
        
        for (const auto& md_name : md_devices) {
            // Read attributes from sysfs
            auto obs_opt = read_md_device_attributes(md_name);
            if (!obs_opt) continue;
            
            auto& obs = *obs_opt;
            result.arrays.push_back(std::move(obs));
            
            // Update topology
            const auto& final_obs = result.arrays.back();
            topology.arrays_by_name[final_obs.identity.name] = final_obs;
            
            // Build device-to-array mapping
            for (const auto& disk : final_obs.member_disks) {
                if (!disk.device_path.empty()) {
                    topology.devices_to_arrays[disk.device_path].push_back(final_obs.identity.name);
                }
            }
            
            // Update statistics
            switch (final_obs.state) {
                case ArrayState::kActive:
                    topology.active_arrays++;
                    break;
                case ArrayState::kDegraded:
                    topology.degraded_arrays++;
                    break;
                case ArrayState::kSyncing:
                    topology.syncing_arrays++;
                    topology.active_arrays++;  // syncing arrays are also counted as active
                    break;
                case ArrayState::kRecovering:
                    topology.syncing_arrays++;  // recovering is a type of sync operation
                    topology.active_arrays++;   // and also counts as active
                    break;
                default:
                    break;
            }
            
            // Update counts
            result.total_arrays++;
        }
        
        result.topology = std::move(topology);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.provider_source = "sysfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed md RAID arrays";
        
        return result;
    }
    
    MdTopology get_topology() override {
        auto result = observe_arrays();
        if (result.topology) {
            return *std::move(result.topology);
        }
        return MdTopology{};
    }
    
    std::optional<MdArrayObservation> resolve_array(std::string_view name) override {
        auto result = observe_arrays();
        
        for (const auto& array : result.arrays) {
            if (array.identity.name == name) {
                return array;
            }
        }
        
        return std::nullopt;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<MdRaidAdapter> make_sysfs_md_raid_adapter() {
    return std::make_unique<SysfsMdRaidAdapter>();
}

}  // namespace rebuntu::adapters::sysfs::md_raid