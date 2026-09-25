// rebuntu::modules::storage_health_monitor — Storage & Filesystem Health Monitor (Phase 5.8)
//
// Implementation of storage health monitoring for:
//   - Block device health assessment (NVMe SMART, SATA/SCSI attributes)
//   - Filesystem health tracking (mounted state, read-only transitions)
//   - Mount point observation and transitions
//   - I/O error detection and capacity monitoring

#include "storage_health_monitor.hpp"
#include <system/core/contracts.hpp>

#include <algorithm>
#include <sstream>
#include <unordered_set>

namespace rebuntu::modules::storage_health_monitor {

// ============================================================================
// Factory functions
// ============================================================================

BlockDeviceHealth make_initial_block_device_health(const std::string& device_id) {
    BlockDeviceHealth health;
    health.device_id = device_id;
    health.health_state = BlockDeviceHealthState::kUnknown;
    health.observed_at = std::chrono::system_clock::now();
    return health;
}

FilesystemHealth make_initial_filesystem_health(const std::string& mount_point) {
    FilesystemHealth fs;
    fs.mount_point = mount_point;
    fs.health_state = FilesystemHealthState::kUnknown;
    fs.mount_state = MountState::kUnknown;
    fs.observed_at = std::chrono::system_clock::now();
    return fs;
}

// ============================================================================
// StorageHealthMonitor implementation
// ============================================================================

StorageHealthMonitor::StorageHealthMonitor(const StorageHealthMonitorConfig& config)
    : config_(config), metrics_{} {
    metrics_.started_at = std::chrono::system_clock::now();
}

StorageHealthMonitor::~StorageHealthMonitor() {
    // Destructor - no special cleanup needed for bounded structures
}

core::Outcome StorageHealthMonitor::start() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (running_) {
        return core::Outcome::completed();
    }
    
    running_ = true;
    metrics_.started_at = std::chrono::system_clock::now();
    
    return core::Outcome::success();
}

core::Outcome StorageHealthMonitor::stop() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!running_) {
        return core::Outcome::completed();
    }
    
    running_ = false;
    
    return core::Outcome::success();
}

// Determine overall block device health state from attributes and errors
BlockDeviceHealthState StorageHealthMonitor::determine_block_health(
    const DeviceStateEntry& entry) const {
    
    const auto& attrs = entry.last_health.attributes;
    
    // Check NVMe percentage used if available
    if (attrs.percentage_used.has_value()) {
        double pct = *attrs.percentage_used;
        
        if (config_.nvme_percentage_used_critical.has_value() &&
            pct >= config_.nvme_percentage_used_critical.value()) {
            return BlockDeviceHealthState::kFailing;
        }
        if (config_.nvme_percentage_used_warning.has_value() &&
            pct >= config_.nvme_percentage_used_warning.value()) {
            // Still healthy but approaching end of life
            return BlockDeviceHealthState::kHealthy;
        }
    }
    
    // Check temperature if available
    if (attrs.temperature_celsius.has_value()) {
        int temp = *attrs.temperature_celsius;
        
        if (temp >= config_.temperature_critical_celsius) {
            return BlockDeviceHealthState::kFailing;
        }
    }
    
    // Check I/O error count
    if (entry.last_health.io_error_count >= config_.io_error_threshold) {
        return BlockDeviceHealthState::kFailing;
    }
    
    // If we have recent errors, check their type
    bool has_severe_errors = false;
    for (IOErrorType err : entry.recent_io_errors) {
        if (err == IOErrorType::kTimeout || err == IOErrorType::kReset ||
            err == IOErrorType::kWriteError) {
            has_severe_errors = true;
            break;
        }
    }
    
    if (has_severe_errors && entry.last_health.io_error_count >= 1) {
        return BlockDeviceHealthState::kDegraded;
    }
    
    // If we have any errors, at least degraded
    if (entry.last_health.io_error_count > 0) {
        return BlockDeviceHealthState::kDegraded;
    }
    
    return BlockDeviceHealthState::kHealthy;
}

// Determine filesystem health state from mount state and errors
FilesystemHealthState StorageHealthMonitor::determine_fs_health(
    const FilesystemStateEntry& entry) const {
    
    // If mount state is unknown, report as such
    if (entry.last_health.mount_state == MountState::kUnknown ||
        entry.last_health.mount_state == MountState::kUnmounted) {
        return FilesystemHealthState::kUnknown;
    }
    
    // Check for read-only remount
    if (entry.last_health.health_state == FilesystemHealthState::kReadOnly) {
        return FilesystemHealthState::kReadOnly;
    }
    
    // Check I/O error count
    if (entry.last_health.io_error_count >= config_.io_error_threshold) {
        return FilesystemHealthState::kFailed;
    }
    
    // If we have errors but still rw, report has_errors
    if (entry.last_health.io_error_count > 0) {
        return FilesystemHealthState::kHasErrors;
    }
    
    return FilesystemHealthState::kHealthy;
}

// Emit an event with deduplication
void StorageHealthMonitor::emit_event(StorageHealthEvent event) {
    // Check for duplicate within window (same event_id within recent time)
    auto now = std::chrono::system_clock::now();
    
    bool is_duplicate = false;
    for (const auto& existing : pending_events_) {
        if (existing.event_id == event.event_id) {
            // Check if within duplicate window
            auto diff = std::chrono::duration_cast<std::chrono::minutes>(
                now - existing.timestamp).count();
            if (diff < 5) {  // Within 5 minutes
                is_duplicate = true;
                break;
            }
        }
    }
    
    if (!is_duplicate) {
        pending_events_.push_back(std::move(event));
        
        // Trim old events if we have too many
        while (pending_events_.size() > max_pending_events_) {
            pending_events_.pop_front();
        }
    }
}

// Check capacity thresholds and generate events
void StorageHealthMonitor::check_capacity_thresholds(
    const std::string& mount_point, double usage_percent,
    std::chrono::system_clock::time_point timestamp) {
    
    if (usage_percent >= config_.capacity_critical_percent) {
        // Critical threshold exceeded
        StorageHealthEvent event;
        event.event_type = StorageHealthEventType::kCapacityCritical;
        event.event_id = "critical_capacity_" + mount_point;
        event.timestamp = timestamp;
        event.mount_point = mount_point;
        event.description = "Filesystem at " + std::to_string(usage_percent) +
                           "% capacity (critical threshold: " +
                           std::to_string(config_.capacity_critical_percent) + "%)";
        emit_event(std::move(event));
        
    } else if (usage_percent >= config_.capacity_warning_percent) {
        // Warning threshold exceeded
        StorageHealthEvent event;
        event.event_type = StorageHealthEventType::kCapacityWarning;
        event.event_id = "warning_capacity_" + mount_point;
        event.timestamp = timestamp;
        event.mount_point = mount_point;
        event.description = "Filesystem at " + std::to_string(usage_percent) +
                           "% capacity (warning threshold: " +
                           std::to_string(config_.capacity_warning_percent) + "%)";
        emit_event(std::move(event));
    }
}

core::Outcome StorageHealthMonitor::observe_block_device(
    BlockDeviceHealth health,
    std::chrono::system_clock::time_point acquisition_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!running_) {
        return core::Outcome::unknown("monitor is not running");
    }
    
    metrics_.block_device_observations++;
    
    // Create device state entry
    DeviceStateEntry& entry = block_device_states_[health.device_id];
    
    // Determine previous health for transition detection
    BlockDeviceHealthState old_health = entry.last_health.health_state;
    
    // Update the entry with new health
    entry.last_health = std::move(health);
    entry.observed_at = acquisition_time;
    
    // Add to I/O error history (bounded)
    for (IOErrorType err : entry.last_health.recent_errors) {
        if (err != IOErrorType::kNone) {
            entry.recent_io_errors.push_back(err);
            metrics_.io_error_count++;
        }
    }
    
    // Determine new health state
    BlockDeviceHealthState new_health = determine_block_health(entry);
    entry.last_health.health_state = new_health;
    
    // Generate event if health changed significantly
    if (old_health != new_health && old_health != BlockDeviceHealthState::kUnknown) {
        StorageHealthEvent event;
        event.event_type = StorageHealthEventType::kBlockDeviceStateChange;
        event.event_id = "block_health_" + entry.last_health.device_id + "_" +
                        std::to_string(entry.observed_at.time_since_epoch().count());
        event.timestamp = acquisition_time;
        event.device_id = entry.last_health.device_id;
        event.old_block_health = old_health;
        event.new_block_health = new_health;
        
        std::ostringstream desc;
        desc << "Block device health changed from " << to_string(old_health)
             << " to " << to_string(new_health);
        event.description = desc.str();
        
        emit_event(std::move(event));
    }
    
    return core::Outcome::success();
}

core::Outcome StorageHealthMonitor::observe_filesystem(
    FilesystemHealth fs_health,
    std::chrono::system_clock::time_point acquisition_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!running_) {
        return core::Outcome::unknown("monitor is not running");
    }
    
    metrics_.filesystem_observations++;
    
    FilesystemStateEntry& entry = filesystem_states_[fs_health.mount_point];
    
    // Save previous state for transition detection
    MountState prev_mount_state = entry.previous_mount_state;
    entry.previous_mount_state = entry.last_health.mount_state;
    
    // Update the entry with new health
    entry.last_health = std::move(fs_health);
    entry.observed_at = acquisition_time;
    
    // Determine filesystem health state
    FilesystemHealthState fs_health_state = determine_fs_health(entry);
    entry.last_health.health_state = fs_health_state;
    
    // Check for capacity warnings
    if (entry.last_health.usage_percent.has_value()) {
        check_capacity_thresholds(
            entry.last_health.mount_point,
            *entry.last_health.usage_percent,
            acquisition_time);
    }
    
    // Detect mount state transitions
    MountState curr_mount = entry.last_health.mount_state;
    
    if (prev_mount_state != MountState::kUnknown && prev_mount_state != curr_mount) {
        StorageHealthEvent event;
        
        if (curr_mount == MountState::kMounted) {
            event.event_type = StorageHealthEventType::kMountAdded;
            event.event_id = "mount_added_" + entry.last_health.mount_point;
            event.description = "Filesystem mounted at " + entry.last_health.mount_point;
            
        } else if (curr_mount == MountState::kUnmounted) {
            event.event_type = StorageHealthEventType::kMountRemoved;
            event.event_id = "mount_removed_" + entry.last_health.mount_point;
            event.description = "Filesystem unmounted from " + entry.last_health.mount_point;
            
        } else if (entry.last_health.health_state == FilesystemHealthState::kReadOnly) {
            // Read-only remount
            event.event_type = StorageHealthEventType::kReadOnlyRemountDetected;
            event.event_id = "readonly_remount_" + entry.last_health.mount_point;
            event.description = "Filesystem remounted read-only at " +
                               entry.last_health.mount_point;
        }
        
        if (!event.event_id.empty()) {
            event.timestamp = acquisition_time;
            event.mount_point = entry.last_health.mount_point;
            
            // Record state transitions
            std::ostringstream desc;
            desc << "Mount transition: " << to_string(prev_mount_state)
                 << " -> " << to_string(curr_mount);
            if (!event.description.empty()) {
                event.description += " (" + desc.str() + ")";
            } else {
                event.description = desc.str();
            }
            
            emit_event(std::move(event));
        }
    }
    
    return core::Outcome::success();
}

core::Outcome StorageHealthMonitor::process_mount_entries(
    const std::vector<MountInfo>& entries,
    std::chrono::system_clock::time_point acquisition_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!running_) {
        return core::Outcome::unknown("monitor is not running");
    }
    
    metrics_.mount_observations += entries.size();
    
    // Build set of current mount points
    std::unordered_set<std::string> current_mounts;
    for (const auto& entry : entries) {
        current_mounts.insert(entry.mount_point);
        
        FilesystemStateEntry& fs_entry = filesystem_states_[entry.mount_point];
        
        // Use previous mount state if needed in future
        (void)fs_entry.previous_mount_state;  // Suppress unused warning
        fs_entry.previous_mount_state = fs_entry.last_health.mount_state;
        
        // Build filesystem health from mount info
        FilesystemHealth fs;
        fs.mount_point = entry.mount_point;
        fs.source_device_id = entry.source;
        fs.filesystem_type = entry.filesystem_type;
        fs.mount_state = MountState::kMounted;
        fs.health_state = FilesystemHealthState::kHealthy;  // Assume healthy until we check
        fs.observed_at = acquisition_time;
        
        fs_entry.last_health = std::move(fs);
    }
    
    // Detect removed mounts (were observed before, not in current list)
    for (auto it = filesystem_states_.begin(); it != filesystem_states_.end();) {
        if (current_mounts.find(it->first) == current_mounts.end()) {
            // Mount was removed
            StorageHealthEvent event;
            event.event_type = StorageHealthEventType::kMountRemoved;
            event.event_id = "mount_removed_" + it->first;
            event.timestamp = acquisition_time;
            event.mount_point = it->first;
            event.description = "Filesystem mount point " + it->first +
                               " is no longer present in mount table";
            
            emit_event(std::move(event));
            
            // Keep the entry for a transition record
            it++;
        } else {
            it++;
        }
    }
    
    return core::Outcome::success();
}

std::optional<BlockDeviceHealth> StorageHealthMonitor::get_block_device_health(
    const std::string& device_id) const {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = block_device_states_.find(device_id);
    if (it == block_device_states_.end()) {
        return std::nullopt;
    }
    
    // Return a copy
    return it->second.last_health;
}

std::optional<FilesystemHealth> StorageHealthMonitor::get_filesystem_health(
    const std::string& mount_point) const {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = filesystem_states_.find(mount_point);
    if (it == filesystem_states_.end()) {
        return std::nullopt;
    }
    
    // Return a copy
    return it->second.last_health;
}

StorageHealthAssessment StorageHealthMonitor::assess_storage_health() const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    StorageHealthAssessment assessment;
    assessment.assessed_at = std::chrono::system_clock::now();
    
    // Collect all block device health
    for (const auto& [id, entry] : block_device_states_) {
        BlockDeviceHealth dev_health = entry.last_health;
        
        // Determine aggregate health state
        if (dev_health.health_state == BlockDeviceHealthState::kUnknown) {
            // Skip unknown for aggregation
            continue;
        }
        
        assessment.block_devices.push_back(dev_health);
        
        // Update aggregate health
        if (dev_health.health_state == BlockDeviceHealthState::kFailed ||
            dev_health.health_state == BlockDeviceHealthState::kFailing) {
            assessment.aggregate_block_health = dev_health.health_state;
        } else if (assessment.aggregate_block_health != BlockDeviceHealthState::kFailed &&
                   assessment.aggregate_block_health != BlockDeviceHealthState::kFailing) {
            if (dev_health.health_state == BlockDeviceHealthState::kDegraded ||
                dev_health.health_state == BlockDeviceHealthState::kHealthy) {
                // Keep current aggregate or set to healthy
                if (assessment.aggregate_block_health == BlockDeviceHealthState::kUnknown) {
                    assessment.aggregate_block_health = dev_health.health_state;
                }
            }
        }
    }
    
    // Collect all filesystem health
    for (const auto& [mp, entry] : filesystem_states_) {
        FilesystemHealth fs_health = entry.last_health;
        
        if (fs_health.mount_state == MountState::kUnknown ||
            fs_health.mount_state == MountState::kUnmounted) {
            continue;
        }
        
        assessment.filesystems.push_back(fs_health);
        
        // Update aggregate filesystem health
        if (fs_health.health_state == FilesystemHealthState::kFailed) {
            assessment.aggregate_fs_health = FilesystemHealthState::kFailed;
        } else if (assessment.aggregate_fs_health != FilesystemHealthState::kFailed &&
                   fs_health.health_state != FilesystemHealthState::kUnknown) {
            if (fs_health.health_state == FilesystemHealthState::kReadOnly ||
                fs_health.health_state == FilesystemHealthState::kHasErrors) {
                assessment.aggregate_fs_health = fs_health.health_state;
            } else if (assessment.aggregate_fs_health == FilesystemHealthState::kUnknown) {
                assessment.aggregate_fs_health = fs_health.health_state;
            }
        }
    }
    
    return assessment;
}

StorageMonitorMetrics StorageHealthMonitor::metrics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return metrics_;
}

std::vector<StorageHealthEvent> StorageHealthMonitor::get_pending_events() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Transfer from deque to vector
    std::vector<StorageHealthEvent> events;
    events.reserve(pending_events_.size());
    for (auto& event : pending_events_) {
        events.push_back(std::move(event));
    }
    
    // Clear the deque
    pending_events_.clear();
    
    return events;
}

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<StorageHealthMonitor> make_storage_health_monitor(
    const StorageHealthMonitorConfig& config) {
    return std::make_unique<StorageHealthMonitor>(config);
}

}  // namespace rebuntu::modules::storage_health_monitor