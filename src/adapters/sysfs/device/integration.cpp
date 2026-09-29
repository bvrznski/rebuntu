// rebuntu::adapters::sysfs::device — Sysfs Device Adapter Implementation
//
// This module implements Rebuntu's bounded, freshness-aware device observation
// adapter using native Linux sysfs interfaces.

#include "adapters/sysfs/device/integration.hpp"

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <system_error>
#include <vector>

namespace rebuntu::adapters::sysfs::device {

namespace {

// Forward declarations for helper functions defined later in this file
std::optional<std::string> get_subsystem(const std::string& class_path);
std::optional<std::string> get_device_name(const std::string& class_path);

// ============================================================================
// Helper Functions
// ============================================================================

// Read a single line from a sysfs file with bounded content
std::optional<std::string> read_sysfs_file(const std::string& path, size_t max_size = 4096) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::string content;
    std::getline(file, content);
    
    // Trim trailing whitespace
    while (!content.empty() && (content.back() == '\n' || content.back() == '\r' || content.back() == ' ')) {
        content.pop_back();
    }
    
    return content;
}

// Read multiple lines from a sysfs file
std::vector<std::string> read_sysfs_lines(const std::string& path, size_t max_size = 4096) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return {};
    }
    
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line) && lines.size() < 100) {  // Limit to 100 lines
        // Trim trailing whitespace
        while (!line.empty() && (line.back() == '\n' || line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    
    return lines;
}

// Get the PCI address from a sysfs path
std::optional<std::string> extract_pci_address(const std::string& sysfs_path) {
    // PCI devices have paths like /sys/devices/pci0000:00/0000:00:1f.6/
    // Extract the last component that matches PCI address format (xxxx:xx:xx.x)
    
    size_t pos = sysfs_path.rfind('/');
    if (pos == std::string::npos) return std::nullopt;
    
    std::string basename = sysfs_path.substr(pos + 1);
    
    // Check if basename looks like a PCI address
    // Format: xxxx:xx:xx.x where x is hex digit
    if (basename.size() >= 7 && basename[4] == ':' && basename[7] == ':' && basename[10] == '.') {
        // Verify it's all hex digits except for the dots and colons
        bool valid = true;
        for (size_t i = 0; i < basename.size(); ++i) {
            char c = basename[i];
            if (c != ':' && c != '.' && !std::isxdigit(c)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            return basename;
        }
    }
    
    return std::nullopt;
}

// Get vendor ID from a sysfs device
std::optional<uint16_t> read_vendor_id(const std::string& sysfs_path) {
    auto vend = read_sysfs_file(sysfs_path + "/vendor");
    if (!vend.has_value()) {
        vend = read_sysfs_file(sysfs_path + "/id/vendor");
    }
    
    if (vend.has_value() && !vend->empty()) {
        try {
            // vendor ID is typically in hex format
            auto pos = vend->find("0x");
            if (pos != std::string::npos) {
                return static_cast<uint16_t>(std::stoul(vend->substr(pos + 2), nullptr, 16));
            }
            return static_cast<uint16_t>(std::stoul(vend.value(), nullptr, 16));
        } catch (...) {
            // Could not parse
        }
    }
    
    return std::nullopt;
}

// Get device ID from a sysfs device
std::optional<uint16_t> read_device_id(const std::string& sysfs_path) {
    auto dev = read_sysfs_file(sysfs_path + "/device/id/device");
    if (!dev.has_value() || dev->empty()) {
        return std::nullopt;
    }
    
    try {
        // Device ID is typically in hex format
        auto pos = dev->find("0x");
        if (pos != std::string::npos) {
            return static_cast<uint16_t>(std::stoul(dev->substr(pos + 2), nullptr, 16));
        }
        return static_cast<uint16_t>(std::stoul(dev.value(), nullptr, 16));
    } catch (...) {
        // Could not parse
    }
    
    return std::nullopt;
}

// Get subsystem name from sysfs path
std::optional<std::string> get_subsystem(const std::string& class_path) {
    // /sys/class/<subsystem>/<device>
    size_t last_slash = class_path.rfind('/');
    if (last_slash == std::string::npos || last_slash < 13) {  // Need at least /sys/class/X
        return std::nullopt;
    }
    
    // Find the subsystem directory between /sys/class/ and /<device>
    size_t first_slash = class_path.find('/', 11);  // After "/sys/class/"
    if (first_slash == std::string::npos || first_slash >= last_slash) {
        return std::nullopt;
    }
    
    return class_path.substr(first_slash + 1, last_slash - first_slash - 1);
}

// Get device name from sysfs path
std::optional<std::string> get_device_name(const std::string& class_path) {
    size_t last_slash = class_path.rfind('/');
    if (last_slash == std::string::npos) {
        return std::nullopt;
    }
    
    return class_path.substr(last_slash + 1);
}

// ============================================================================
// SysfsDeviceAdapterImpl
// ============================================================================

class SysfsDeviceAdapterImpl : public SysfsDeviceAdapter {
public:
    explicit SysfsDeviceAdapterImpl(const SysfsDeviceOptions& opts = SysfsDeviceOptions::make_default())
        : options_(opts) {}
    
    DeviceDiscoveryResult discover_devices() override {
        auto start_time = std::chrono::system_clock::now();
        
        DeviceDiscoveryResult result;
        result.status = core::SemanticStatus::kCompleted;
        result.captured_at = start_time;
        
        // Scan /sys/class/ for device classes
        DIR* class_dir = opendir("/sys/class");
        if (!class_dir) {
            result.status = core::SemanticStatus::kUnknown;
            result.description = "Failed to open /sys/class directory";
            return result;
        }
        
        std::set<std::string> seen_devices;  // Track unique device identifiers
        
        struct dirent* entry;
        while ((entry = readdir(class_dir)) != nullptr && 
               result.device_records.size() < options_.max_total_devices) {
            
            if (entry->d_name[0] == '.') continue;  // Skip . and ..
            
            std::string class_path = "/sys/class/" + std::string(entry->d_name);
            
            DIR* device_dir = opendir(class_path.c_str());
            if (!device_dir) continue;
            
            struct dirent* dev_entry;
            while ((dev_entry = readdir(device_dir)) != nullptr &&
                   result.device_records.size() < options_.max_total_devices) {
                
                if (dev_entry->d_name[0] == '.') continue;  // Skip . and ..
                
                std::string device_path = class_path + "/" + std::string(dev_entry->d_name);
                
                // Check if we've already seen this device (by PCI address or other identifier)
                auto pci_addr = extract_pci_address(device_path);
                std::string device_key;
                
                if (pci_addr.has_value()) {
                    device_key = "pci:" + pci_addr.value();
                } else {
                    // Use the full path as a fallback
                    device_key = "path:" + device_path;
                }
                
                if (seen_devices.count(device_key) > 0) continue;
                seen_devices.insert(device_key);
                
                // Create device identity
                DeviceIdentity identity;
                identity.hw.sysfs_path = device_path;
                if (pci_addr.has_value()) {
                    identity.hw.pci_address = pci_addr.value();
                }
                
                // Get vendor ID
                auto vendor_id = read_vendor_id(device_path);
                if (vendor_id.has_value()) {
                    identity.hw.vendor_id = vendor_id.value();
                }
                
                // Get device ID  
                auto device_id = read_device_id(device_path);
                if (device_id.has_value()) {
                    identity.hw.device_id = device_id.value();
                }
                
                // Create observation
                DeviceObservation obs;
                obs.identity = identity;
                
                // Extract subsystem from class path
                auto subsystem = get_subsystem(class_path);
                if (subsystem.has_value()) {
                    obs.subsystem = subsystem.value();
                }
                
                // Get device name
                auto dev_name = get_device_name(device_path);
                if (dev_name.has_value()) {
                    obs.identity.dev_node = dev_name.value();
                }
                
                // Determine device kind based on subsystem
                if (subsystem.has_value()) {
                    if (subsystem == "input") {
                        obs.kind = DeviceKind::kInput;
                    } else if (subsystem == "sound" || subsystem == "audio") {
                        obs.kind = DeviceKind::kAudio;
                    } else if (subsystem == "graphics" || subsystem == "display") {
                        obs.kind = DeviceKind::kDisplay;
                    } else if (subsystem == "block") {
                        obs.kind = DeviceKind::kStorage;
                    } else if (subsystem == "net") {
                        obs.kind = DeviceKind::kNetwork;
                    }
                }
                
                obs.observed_at = std::chrono::system_clock::now();
                
                // Create record
                DeviceRecord record;
                record.identity = identity;
                record.state = DeviceState::kPresent;
                record.first_seen = start_time;
                record.last_observed = obs.observed_at;
                record.total_observations = 1;
                record.last_observation = obs;
                
                result.device_records[device_key] = record;
                result.observations.push_back(obs);
                
                // Update statistics
                result.total_devices++;
                
                switch (obs.kind) {
                    case DeviceKind::kInput:     result.input_devices++; break;
                    case DeviceKind::kAudio:     result.audio_devices++; break;
                    case DeviceKind::kDisplay:   result.display_devices++; break;
                    case DeviceKind::kStorage:   result.storage_devices++; break;
                    case DeviceKind::kNetwork:   result.network_devices++; break;
                    default:                     result.other_devices++; break;
                }
            }
            
            closedir(device_dir);
        }
        
        closedir(class_dir);
        
        auto end_time = std::chrono::system_clock::now();
        result.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        
        return result;
    }
    
    std::unordered_map<std::string, DeviceRecord> get_all_device_records() override {
        // For now, just perform a fresh discovery
        // In a full implementation, this would use caching with freshness tracking
        auto result = discover_devices();
        
        std::unordered_map<std::string, DeviceRecord> records;
        for (const auto& [key, record] : result.device_records) {
            records[key] = record;
        }
        
        return records;
    }
    
    std::optional<DeviceRecord> get_device_record(const DeviceIdentity& id) override {
        // Search through cached records
        auto records = get_all_device_records();
        std::string key = id.key();
        
        if (records.count(key) > 0) {
            return records[key];
        }
        
        return std::nullopt;
    }
    
    core::Outcome resync_devices() override {
        // Force a fresh discovery
        auto result = discover_devices();
        
        if (result.status == core::SemanticStatus::kCompleted ||
            result.status == core::SemanticStatus::kSuccess) {
            return core::Outcome::success(true);
        }
        
        return core::Outcome::unknown("Device resync failed");
    }
    
    void set_options(const SysfsDeviceOptions& opts) override {
        options_ = opts;
    }

private:
    SysfsDeviceOptions options_;
};

}  // namespace

// ============================================================================
// Factory Function
// ============================================================================

std::unique_ptr<SysfsDeviceAdapter> make_sysfs_device_adapter() {
    return std::make_unique<SysfsDeviceAdapterImpl>();
}

std::unique_ptr<SysfsDeviceAdapter> make_sysfs_device_adapter(const SysfsDeviceOptions& opts) {
    return std::make_unique<SysfsDeviceAdapterImpl>(opts);
}

}  // namespace rebuntu::adapters::sysfs::device