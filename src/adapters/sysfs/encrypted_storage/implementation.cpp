// rebuntu::adapters::sysfs::encrypted_storage — Encrypted Storage Observation Implementation (Phase 5.19)
//
// This module implements the sysfs-based encrypted storage observation adapter:
//   - Reads device-mapper information from /sys/block/dm-X/dm/
//   - Observes: name, uuid, major:minor numbers
//   - Identifies LUKS vs LVM via UUID prefixes
//   - Tracks dm-crypt relationships without exposing key material

#include "adapters/sysfs/encrypted_storage/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

namespace rebuntu::adapters::sysfs::encrypted_storage {

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
// Helper: Detect device type from UUID prefix
// ============================================================================
static EncryptedStorageKind detect_kind_from_uuid(std::string_view uuid) {
    if (uuid.size() >= 10 && uuid.substr(0, 10) == "CRYPT-LUKS") {
        return EncryptedStorageKind::kLUKS;
    }
    if (uuid.size() >= 4 && uuid.substr(0, 4) == "LVM-") {
        return EncryptedStorageKind::kLVM;
    }
    return EncryptedStorageKind::kOther;
}

// ============================================================================
// Helper: Parse major:minor from dev file content
// Format: "major:minor"
// ============================================================================
static void parse_major_minor(std::string_view dev_str, int& major, int& minor) {
    auto colon_pos = dev_str.find(':');
    if (colon_pos != std::string_view::npos && colon_pos > 0 && colon_pos + 1 < dev_str.size()) {
        try {
            major = std::stoi(std::string{dev_str.substr(0, colon_pos)});
            minor = std::stoi(std::string{dev_str.substr(colon_pos + 1)});
        } catch (...) {
            major = -1;
            minor = -1;
        }
    } else {
        major = -1;
        minor = -1;
    }
}

// ============================================================================
// Helper: Get list of dm-X devices from /sys/block
// ============================================================================
static std::vector<std::string> get_dm_devices() {
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
        
        if (line.size() > 3 && line.substr(0, 3) == "dm-") {
            // Try to parse the number
            try {
                std::string num_part = line.substr(3);
                int num = std::stoi(num_part);
                (void)num;  // Validate it's numeric
                result.push_back(line);
            } catch (...) {
                // Not a valid dm-X device name, skip
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
// EncryptedStorageAdapter Implementation
// ============================================================================

class SysfsEncryptedStorageAdapter : public EncryptedStorageAdapter {
public:
    SysfsEncryptedStorageAdapter() = default;
    ~SysfsEncryptedStorageAdapter() override = default;
    
    EncryptedStorageObservationResult observe_devices() override {
        EncryptedStorageObservationResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Get list of dm-X devices
        auto dm_devices = get_dm_devices();
        
        if (dm_devices.empty()) {
            result.status = core::SemanticStatus::kSuccess;
            result.description = "No encrypted storage devices found";
            result.provider_source = "sysfs";
            return result;
        }
        
        // Build topology structures
        EncryptedStorageTopology topology;
        topology.captured_at = std::chrono::system_clock::now();
        
        for (const auto& dm_name : dm_devices) {
            auto device_path = "/sys/block/" + dm_name + "/dm/";
            
            // Read the device name
            auto name_opt = read_sysfs_attribute(device_path + "name");
            if (!name_opt) continue;
            
            std::string name = *name_opt;
            
            // Read the UUID (if available)
            auto uuid_opt = read_sysfs_attribute(device_path + "uuid");
            
            // Read major:minor from dev file
            int major{-1}, minor{-1};
            auto dev_opt = read_sysfs_attribute("/sys/block/" + dm_name + "/dev");
            if (dev_opt) {
                parse_major_minor(*dev_opt, major, minor);
            }
            
            // Build observation
            EncryptedStorageObservation obs;
            obs.identity.name = name;
            obs.identity.uuid = uuid_opt;
            obs.identity.major = major;
            obs.identity.minor = minor;
            obs.observed_at = std::chrono::system_clock::now();
            obs.source = "sysfs";
            
            // Detect kind from UUID
            if (uuid_opt) {
                obs.kind = detect_kind_from_uuid(*uuid_opt);
                
                if (obs.kind == EncryptedStorageKind::kLUKS && 
                    uuid_opt->size() >= 10 && uuid_opt->substr(0, 10) == "CRYPT-LUKS") {
                    obs.luks_uuid = *uuid_opt;
                    obs.state = LUKSState::kOpen;  // If it's in /dev/mapper, it's open
                }
                
                if (obs.kind == EncryptedStorageKind::kLVM && 
                    uuid_opt->size() >= 4 && uuid_opt->substr(0, 4) == "LVM-") {
                    auto vg_id = parse_lvm_vg_id(*uuid_opt);
                    obs.lvm_vg_name = vg_id;
                    
                    // For LVM, extract logical volume name from device-mapper name
                    // Format: <vg-name>-<lv-name> or <vg-name><lv-id>
                    if (name.find('-') != std::string::npos) {
                        size_t dash_pos = name.find('-');
                        obs.lvm_vg_name = name.substr(0, dash_pos);
                        obs.lvm_lv_name = name.substr(dash_pos + 1);
                    }
                }
            }
            
            result.devices.push_back(std::move(obs));
            topology.devices_by_name[name] = result.devices.back();
            
            // Update statistics
            switch (result.devices.back().kind) {
                case EncryptedStorageKind::kLUKS:
                    topology.luks_devices++;
                    if (!uuid_opt || 
                        (uuid_opt->size() >= 4 && uuid_opt->substr(0, 4) != "LVM-")) {
                        topology.luks_root_devices.push_back(name);
                    }
                    break;
                case EncryptedStorageKind::kLVM:
                    topology.lvm_devices++;
                    // Track LVM volume groups
                    if (result.devices.back().lvm_vg_name) {
                        auto& vg = topology.volume_groups[*result.devices.back().lvm_vg_name];
                        vg.vg_name = *result.devices.back().lvm_vg_name;
                        if (result.devices.back().identity.uuid) {
                            // The UUID contains VG ID, but for now we just track the LVs
                        }
                        if (result.devices.back().lvm_lv_name) {
                            vg.lv_names.push_back(*result.devices.back().lvm_lv_name);
                        }
                    }
                    break;
                case EncryptedStorageKind::kOther:
                    topology.other_dm_devices++;
                    break;
            }
            topology.total_devices++;
        }
        
        result.topology = std::move(topology);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.total_devices = result.devices.size();
        result.provider_source = "sysfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed encrypted storage devices";
        
        return result;
    }
    
    EncryptedStorageTopology get_topology() override {
        auto result = observe_devices();
        if (result.topology) {
            return *std::move(result.topology);
        }
        return EncryptedStorageTopology{};
    }
    
    std::optional<EncryptedStorageObservation> resolve_device(std::string_view name) override {
        auto result = observe_devices();
        
        for (const auto& device : result.devices) {
            if (device.identity.name == name) {
                return device;
            }
        }
        
        return std::nullopt;
    }

private:
    // Helper: Parse LVM UUID to extract VG ID
    static std::optional<std::string> parse_lvm_vg_id(std::string_view uuid) {
        if (uuid.size() >= 12 && uuid.substr(0, 4) == "LVM-") {
            return std::string{uuid.substr(4)};
        }
        return std::nullopt;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<EncryptedStorageAdapter> make_sysfs_encrypted_storage_adapter() {
    return std::make_unique<SysfsEncryptedStorageAdapter>();
}

}  // namespace rebuntu::adapters::sysfs::encrypted_storage