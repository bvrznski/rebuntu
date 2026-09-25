// rebuntu::modules::storage_health_monitor — Storage & Filesystem Health Monitor (Phase 5.8)
//
// This module provides comprehensive health monitoring for storage devices,
// filesystems, and mounts in Rebuntu.
//
// Key Responsibilities:
//   - Block device health assessment (NVMe SMART, SATA/SCSI health attributes)
//   - Filesystem health tracking (mounted state, read-only transitions, errors)
//   - Mount point observation (added, removed, state changes)
//   - I/O error detection and tracking
//   - Capacity monitoring with warning/critical thresholds
//
// Non-Responsibility:
//   - Does NOT perform repairs or mount remounts
//   - Does NOT interpret health data for users (that's Phase 14 UI/reporting)
//   - Does NOT make policy decisions about what to do with unhealthy devices

#pragma once

#include "types.hpp"
#include <runtime/engine.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>
#include <mutex>
#include <deque>

namespace rebuntu::modules::storage_health_monitor {

// ============================================================================
// StorageHealthMonitor — Main storage health monitoring engine
// ============================================================================

class StorageHealthMonitor {
public:
    explicit StorageHealthMonitor(const StorageHealthMonitorConfig& config);
    ~StorageHealthMonitor();
    
    // Lifecycle management
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const { return running_; }
    
    // Observation methods (called by adapters)
    
    /// Add observation for a block device from native sources
    core::Outcome observe_block_device(
        BlockDeviceHealth health,
        std::chrono::system_clock::time_point acquisition_time);
    
    /// Add observation for a filesystem/mount point
    core::Outcome observe_filesystem(
        FilesystemHealth fs_health,
        std::chrono::system_clock::time_point acquisition_time);
    
    /// Process raw mount table entries
    core::Outcome process_mount_entries(
        const std::vector<MountInfo>& entries,
        std::chrono::system_clock::time_point acquisition_time);
    
    // Query methods
    
    /// Get current health assessment for a specific block device
    std::optional<BlockDeviceHealth> get_block_device_health(const std::string& device_id) const;
    
    /// Get current health assessment for a filesystem mount point
    std::optional<FilesystemHealth> get_filesystem_health(const std::string& mount_point) const;
    
    /// Get complete storage subsystem health report
    StorageHealthAssessment assess_storage_health() const;
    
    // Metrics
    
    /// Get runtime metrics
    StorageMonitorMetrics metrics() const;
    
    /// Get pending events (events generated since last check)
    std::vector<StorageHealthEvent> get_pending_events();
    
    // Configuration
    const StorageHealthMonitorConfig& config() const { return config_; }

private:
    StorageHealthMonitorConfig config_;
    bool running_ = false;
    mutable std::mutex mutex_;
    
    // Block device state storage (bounded by observation count)
    struct DeviceStateEntry {
        BlockDeviceHealth last_health;
        std::chrono::system_clock::time_point observed_at;
        std::deque<IOErrorType> recent_io_errors;  // Rolling window for error patterns
    };
    std::unordered_map<std::string, DeviceStateEntry> block_device_states_;
    
    // Filesystem state storage
    struct FilesystemStateEntry {
        FilesystemHealth last_health;
        std::chrono::system_clock::time_point observed_at;
        MountState previous_mount_state = MountState::kUnknown;
    };
    std::unordered_map<std::string, FilesystemStateEntry> filesystem_states_;
    
    // Pending events buffer (bounded)
    std::deque<StorageHealthEvent> pending_events_;
    size_t max_pending_events_ = 256;
    
    // Metrics tracking
    StorageMonitorMetrics metrics_;
    
    // Internal helper methods
    
    /// Determine overall block device health state from attributes and errors
    BlockDeviceHealthState determine_block_health(const DeviceStateEntry& entry) const;
    
    /// Determine filesystem health state from mount state and errors
    FilesystemHealthState determine_fs_health(const FilesystemStateEntry& entry) const;
    
    /// Create a new event and add to pending buffer (with deduplication)
    void emit_event(StorageHealthEvent event);
    
    /// Check capacity thresholds and generate events if exceeded
    void check_capacity_thresholds(const std::string& mount_point, double usage_percent,
                                   std::chrono::system_clock::time_point timestamp);
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<StorageHealthMonitor> make_storage_health_monitor(
    const StorageHealthMonitorConfig& config = StorageHealthMonitorConfig{});

}  // namespace rebuntu::modules::storage_health_monitor