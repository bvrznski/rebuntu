// rebuntu::adapters::hotplug — Hotplug Device State Management Implementation (Phase 5.48)
//
// This module implements Rebuntu's bounded, freshness-aware device state
// tracking system for handling hotplug events and removal races safely.

#include "adapters/hotplug/types.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

namespace rebuntu::adapters::hotplug {

// ============================================================================
// Helper: Read a file line by line
// ============================================================================
static std::vector<std::string> read_file_lines(std::filesystem::path path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    
    if (!file.is_open()) {
        return {};
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    
    return lines;
}

// ============================================================================
// Helper: Read a single file value
// ============================================================================
static std::optional<std::string> read_file_value(std::filesystem::path path) {
    std::ifstream file(path);
    
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    // Trim whitespace
    size_t start = content.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return std::nullopt;
    
    size_t end = content.find_last_not_of(" \t\n\r");
    return content.substr(start, end - start + 1);
}

// ============================================================================
// Helper: Get device kind from sysfs class name
// ============================================================================
static DeviceKind get_device_kind_from_sysfs_path(const std::string& sysfs_path) {
    // Check for known device classes in the path
    if (sysfs_path.find("/class/input/") != std::string::npos ||
        sysfs_path.find("/input/event") != std::string::npos) {
        return DeviceKind::kInput;
    }
    
    if (sysfs_path.find("/class/sound/") != std::string::npos ||
        sysfs_path.find("/class/audio") != std::string::npos) {
        return DeviceKind::kAudio;
    }
    
    if (sysfs_path.find("/class/drm/") != std::string::npos ||
        sysfs_path.find("/class/graphics/") != std::string::npos) {
        return DeviceKind::kDisplay;
    }
    
    if (sysfs_path.find("/block/") != std::string::npos ||
        sysfs_path.find("/usb/storage") != std::string::npos) {
        return DeviceKind::kStorage;
    }
    
    if (sysfs_path.find("/class/net/") != std::string::npos) {
        return DeviceKind::kNetwork;
    }
    
    // Default to "other"
    return DeviceKind::kOther;
}

// ============================================================================
// Discover devices from /sys/class/ - current state scan
//
// Scans Linux device model for currently present devices without relying on
// hotplug events. This is used for initial discovery and resync.
// ============================================================================
static std::vector<DeviceObservation> discover_devices_from_sysfs() {
    std::vector<DeviceObservation> observations;
    
    auto class_path = std::filesystem::path("/sys/class");
    if (!std::filesystem::exists(class_path)) {
        return observations;
    }
    
    try {
        // Iterate over device classes
        for (const auto& entry : std::filesystem::directory_iterator(class_path)) {
            if (!entry.is_directory()) continue;
            
            auto class_name = entry.path().filename().string();
            if (class_name.empty()) continue;
            
            DeviceKind kind = get_device_kind_from_sysfs_path(entry.path().string());
            
            try {
                for (const auto& dev_entry : std::filesystem::directory_iterator(entry.path())) {
                    if (!dev_entry.is_directory()) continue;
                    
                    auto dev_name = dev_entry.path().filename().string();
                    if (dev_name.empty()) continue;
                    
                    DeviceObservation obs{};
                    obs.identity.sysfs_path = dev_entry.path().string();
                    obs.identity.kind = kind;
                    obs.observed_at = std::chrono::system_clock::now();
                    obs.source = "sysfs";
                    
                    // Read uevent for additional info
                    auto uevent_path = dev_entry.path() / "uevent";
                    if (std::filesystem::exists(uevent_path)) {
                        auto lines = read_file_lines(uevent_path);
                        for (const auto& line : lines) {
                            if (line.starts_with("DEVNAME=")) {
                                obs.identity.udev_path = "/dev" + line.substr(8);
                            } else if (line.starts_with("MAJOR=")) {
                                try {
                                    int major = std::stoi(line.substr(6));
                                    // Store in capabilities for now
                                    obs.capabilities.push_back("major:" + std::to_string(major));
                                } catch (...) {}
                            } else if (line.starts_with("MINOR=")) {
                                try {
                                    int minor = std::stoi(line.substr(6));
                                    obs.capabilities.push_back("minor:" + std::to_string(minor));
                                } catch (...) {}
                            }
                        }
                    }
                    
                    // Try to read device properties from sysfs
                    auto dev_prop_path = dev_entry.path() / "device" / "id";
                    if (std::filesystem::exists(dev_prop_path)) {
                        auto vendor_opt = read_file_value(dev_prop_path / "vendor");
                        auto product_opt = read_file_value(dev_prop_path / "product");
                        
                        if (vendor_opt && product_opt) {
                            try {
                                obs.identity.vendor_id = static_cast<uint16_t>(
                                    std::stoul(*vendor_opt, nullptr, 16));
                                obs.identity.product_id = static_cast<uint16_t>(
                                    std::stoul(*product_opt, nullptr, 16));
                            } catch (...) {}
                        }
                    }
                    
                    // Get manufacturer from udev-style properties
                    auto manuf_path = dev_entry.path() / "device" / "manufacturer";
                    if (std::filesystem::exists(manuf_path)) {
                        obs.manufacturer = read_file_value(manuf_path);
                    }
                    
                    observations.push_back(obs);
                }
            } catch (...) {
                // Continue with other device classes even if one fails
            }
        }
    } catch (...) {
        // Ignore errors during enumeration
    }
    
    return observations;
}

// ============================================================================
// Implementation class
// ============================================================================
class HotplugObserverImpl final : public HotplugObserver {
public:
    HotplugObserverImpl() = default;
    
    ~HotplugObserverImpl() override {
        stop();
    }
    
    core::Outcome start() override {
        if (running_) return core::Outcome::success();
        
        running_ = true;
        metrics_.started_at = std::chrono::system_clock::now();
        
        // Initial scan
        resync_devices();
        
        return core::Outcome::success();
    }
    
    core::Outcome stop() override {
        if (!running_) return core::Outcome::success();
        
        running_ = false;
        
        // Mark all devices as stale on shutdown
        for (auto& [key, record] : device_records_) {
            if (record.state == DeviceState::kPresent) {
                record.state = DeviceState::kStale;
            }
        }
        
        return core::Outcome::success();
    }
    
    bool is_running() const override {
        return running_;
    }
    
    HotplugResult discover_devices() override {
        HotplugResult result{};
        result.status = core::SemanticStatus::kCompleted;
        result.captured_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Get fresh observations from sysfs
        auto observations = discover_devices_from_sysfs();
        
        auto end_time = std::chrono::steady_clock::now();
        result.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        // Update device records with new observations
        for (const auto& obs : observations) {
            const std::string& key = obs.identity.key();
            
            auto it = device_records_.find(key);
            if (it == device_records_.end()) {
                // New device
                DeviceRecord record{};
                record.identity = obs.identity;
                record.state = DeviceState::kPresent;
                record.first_seen = obs.observed_at;
                record.last_observed = obs.observed_at;
                record.total_observations = 1;
                
                device_records_[key] = std::move(record);
            } else {
                // Update existing record
                it->second.state = DeviceState::kPresent;
                it->second.last_observed = obs.observed_at;
                it->second.total_observations++;
                if (!it->second.identity.udev_path.has_value()) {
                    it->second.identity.udev_path = obs.identity.udev_path;
                }
            }
        }
        
        // Mark devices as stale based on freshness
        auto now = std::chrono::system_clock::now();
        for (auto& [key, record] : device_records_) {
            if (record.state == DeviceState::kPresent) {
                auto age = now - record.last_observed;
                if (age > options_.freshness_threshold_ms) {
                    record.state = DeviceState::kStale;
                }
            }
        }
        
        // Build result
        for (const auto& [key, record] : device_records_) {
            result.device_records[key] = record;
            
            if (record.state == DeviceState::kPresent) {
                result.present_devices++;
            } else if (record.state == DeviceState::kRemoved) {
                result.removed_devices++;
            } else if (record.state == DeviceState::kStale) {
                stale_devices_++;
            }
        }
        
        // Copy observations for evidence
        result.observations = observations;
        result.total_devices = observations.size();
        stale_devices_ = 0;  // Reset per-call count
        
        return result;
    }
    
    std::unordered_map<std::string, DeviceRecord> get_all_device_records() override {
        // Apply freshness check before returning
        auto now = std::chrono::system_clock::now();
        for (auto& [key, record] : device_records_) {
            if (record.state == DeviceState::kPresent) {
                auto age = now - record.last_observed;
                if (age > options_.freshness_threshold_ms) {
                    record.state = DeviceState::kStale;
                }
            }
        }
        
        return device_records_;
    }
    
    std::optional<DeviceRecord> get_device_record(const DeviceIdentity& id) override {
        std::string key = id.key();
        
        auto it = device_records_.find(key);
        if (it == device_records_.end()) {
            // Try to find by alternative keys
            for (const auto& [k, r] : device_records_) {
                if (r.identity == id) {
                    return r;
                }
            }
            return std::nullopt;
        }
        
        return it->second;
    }
    
    core::Outcome resync_devices() override {
        if (!running_) {
            return core::Outcome::unknown("hotplug observer not running");
        }
        
        // Perform a fresh scan
        auto observations = discover_devices_from_sysfs();
        
        auto now = std::chrono::system_clock::now();
        metrics_.last_resync = now;
        
        for (const auto& obs : observations) {
            const std::string& key = obs.identity.key();
            
            auto it = device_records_.find(key);
            if (it == device_records_.end()) {
                // New device
                DeviceRecord record{};
                record.identity = obs.identity;
                record.state = DeviceState::kPresent;
                record.first_seen = obs.observed_at;
                record.last_observed = obs.observed_at;
                record.total_observations = 1;
                
                device_records_[key] = std::move(record);
                metrics_.devices_added++;
            } else {
                // Update existing record
                it->second.state = DeviceState::kPresent;
                it->second.last_observed = obs.observed_at;
                it->second.total_observations++;
                if (!it->second.identity.udev_path.has_value()) {
                    it->second.identity.udev_path = obs.identity.udev_path;
                }
            }
            
            metrics_.devices_observed++;
        }
        
        return core::Outcome::success();
    }
    
    Metrics metrics() const override {
        return metrics_;
    }

private:
    bool running_ = false;
    HotplugOptions options_{HotplugOptions::make_default()};
    std::unordered_map<std::string, DeviceRecord> device_records_;
    Metrics metrics_;
    size_t stale_devices_{0};
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<HotplugObserver> make_hotplug_observer() {
    return std::make_unique<HotplugObserverImpl>();
}

}  // namespace rebuntu::adapters::hotplug