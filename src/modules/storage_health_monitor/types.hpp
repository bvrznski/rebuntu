// rebuntu::modules::storage_health_monitor — Storage & Filesystem Health Monitor Types (Phase 5.8)
//
// This header defines core types for storage and filesystem health monitoring in Rebuntu:
//   - Block device health states (NVMe, SATA, SCSI)
//   - Filesystem health states (mounted, read-only, errors)
//   - Mount states and transitions
//   - I/O error evidence and patterns
//
// Design Philosophy:
//   * Monitoring ≠ Recovery (this module observes, does not repair)
//   * UNKNOWN ≠ false (missing telemetry must be reported honestly)
//   * Evidence-based assessment, not heuristic scores
//   * Preserve raw evidence while adding structured analysis

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <optional>

namespace rebuntu::modules::storage_health_monitor {

// ============================================================================
// MountInfo — Raw mount entry from /proc/mounts or similar sources
// ============================================================================

struct MountInfo {
    std::string source;       // Block device source (e.g., "/dev/sda1", "UUID=...")
    std::string mount_point;  // Mount point path (e.g., "/", "/home")
    std::string filesystem_type;  // Filesystem type (e.g., "ext4", "xfs", "btrfs")
    std::optional<std::string> options;  // Mount options as string
};

// ============================================================================
// BlockDeviceHealthState — Health assessment of a block device
// ============================================================================

enum class BlockDeviceHealthState {
    kUnknown,          // Device state unknown (missing evidence)
    kHealthy,          // Device healthy, no issues detected
    kDegraded,         // Device degraded (rebuild in progress, degraded array)
    kFailing,          // Device showing signs of imminent failure
    kFailed,           // Device has failed
};

inline std::string to_string(BlockDeviceHealthState s) {
    switch (s) {
        case BlockDeviceHealthState::kUnknown:   return "unknown";
        case BlockDeviceHealthState::kHealthy:   return "healthy";
        case BlockDeviceHealthState::kDegraded:  return "degraded";
        case BlockDeviceHealthState::kFailing:   return "failing";
        case BlockDeviceHealthState::kFailed:    return "failed";
    }
    return "unknown";
}

// ============================================================================
// FilesystemHealthState — Health assessment of a filesystem
// ============================================================================

enum class FilesystemHealthState {
    kUnknown,          // Filesystem state unknown (missing evidence)
    kHealthy,          // Filesystem healthy
    kReadOnly,         // Filesystem remounted read-only
    kHasErrors,        // Filesystem has errors but mounted rw
    kFailed,           // Filesystem mount failed or corrupted
};

inline std::string to_string(FilesystemHealthState s) {
    switch (s) {
        case FilesystemHealthState::kUnknown:   return "unknown";
        case FilesystemHealthState::kHealthy:   return "healthy";
        case FilesystemHealthState::kReadOnly:  return "read_only";
        case FilesystemHealthState::kHasErrors: return "has_errors";
        case FilesystemHealthState::kFailed:    return "failed";
    }
    return "unknown";
}

// ============================================================================
// MountState — State of a mount point
// ============================================================================

enum class MountState {
    kUnknown,          // Mount state unknown
    kMounted,          // Currently mounted
    kUnmounted,        // Not currently mounted
    kMounting,         // In process of mounting
    kUnmounting,       // In process of unmounting
};

inline std::string to_string(MountState s) {
    switch (s) {
        case MountState::kUnknown:   return "unknown";
        case MountState::kMounted:   return "mounted";
        case MountState::kUnmounted: return "unmounted";
        case MountState::kMounting:  return "mounting";
        case MountState::kUnmounting:return "unmounting";
    }
    return "unknown";
}

// ============================================================================
// DeviceType — Type of block device
// ============================================================================

enum class DeviceType {
    kUnknown,      // Unknown device type
    kNVMe,         // NVMe device
    kSATA,         // SATA device (including SATA-SSD)
    kSCSI,         // SCSI/SAS device
    kUSB,          // USB mass storage
    kLoop,         // Loop device
    kDM,           // Device-mapper (LVM, LUKS, etc.)
};

inline std::string to_string(DeviceType t) {
    switch (t) {
        case DeviceType::kUnknown: return "unknown";
        case DeviceType::kNVMe:    return "nvme";
        case DeviceType::kSATA:    return "sata";
        case DeviceType::kSCSI:    return "scsi";
        case DeviceType::kUSB:     return "usb";
        case DeviceType::kLoop:    return "loop";
        case DeviceType::kDM:      return "dm";
    }
    return "unknown";
}

// ============================================================================
// I/O Error Type
// ============================================================================

enum class IOErrorType {
    kNone,              // No I/O errors detected
    kReadError,         // Read operation failed
    kWriteError,        // Write operation failed
    kDiscardError,      // Discard/TRIM operation failed
    kTimeout,           // Operation timed out
    kReset,             // Device/controller reset occurred
};

inline std::string to_string(IOErrorType t) {
    switch (t) {
        case IOErrorType::kNone:         return "none";
        case IOErrorType::kReadError:    return "read_error";
        case IOErrorType::kWriteError:   return "write_error";
        case IOErrorType::kDiscardError: return "discard_error";
        case IOErrorType::kTimeout:      return "timeout";
        case IOErrorType::kReset:        return "reset";
    }
    return "unknown";
}

// ============================================================================
// SMART/NVMe Health Attributes
// ============================================================================

struct DeviceHealthAttributes {
    // NVMe-specific attributes
    std::optional<int> temperature_celsius;              // Current device temperature
    std::optional<double> percentage_used;               // NVMe: Percentage used (100 = end of life)
    std::optional<bool> critical_warnings;               // NVMe: Critical warnings status
    
    // SMART attributes
    std::optional<int> reallocated_sector_count;         // Sectors remapped due to errors
    std::optional<int> pending_sectors;                  // Sectors waiting to be remapped
    std::optional<int> current_pending_sector;           // Current pending sector count
    std::optional<double> wear_leveling_count;           // NAND erase cycles (SSD)
    
    // General device attributes
    std::optional<uint64_t> total_bytes_read;            // Total bytes read from device
    std::optional<uint64_t> total_bytes_written;         // Total bytes written to device
    std::optional<uint64_t> power_on_hours;              // Hours since powered on
};

// ============================================================================
// BlockDeviceHealth — Complete health assessment for a block device
// ============================================================================

struct BlockDeviceHealth {
    // Identity (stable identifiers)
    std::string device_id;                               // Stable ID (WWN/serial/UUID)
    std::optional<std::string> device_path;              // Current kernel path (/dev/nvme0n1, etc.)
    DeviceType device_type = DeviceType::kUnknown;
    
    // Health state
    BlockDeviceHealthState health_state = BlockDeviceHealthState::kUnknown;
    
    // Attributes (may be incomplete)
    DeviceHealthAttributes attributes;
    
    // I/O error tracking
    std::chrono::system_clock::time_point last_io_error_at;
    int io_error_count = 0;
    std::vector<IOErrorType> recent_errors;              // Last N errors
    
    // Timing
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::chrono::milliseconds> observation_duration_ms;
    
    // Evidence references (for forensic recovery)
    std::vector<std::string> evidence_ids;
};

// ============================================================================
// FilesystemHealth — Complete health assessment for a filesystem
// ============================================================================

struct FilesystemHealth {
    // Identity
    std::string mount_point;                             // Mount point path
    std::optional<std::string> source_device_id;         // Source block device ID
    std::optional<std::string> filesystem_type;          // e.g., "ext4", "xfs"
    
    // Health state
    FilesystemHealthState health_state = FilesystemHealthState::kUnknown;
    MountState mount_state = MountState::kUnknown;
    
    // Capacity (may be incomplete)
    std::optional<uint64_t> total_bytes;                 // Total filesystem size
    std::optional<uint64_t> available_bytes;             // Available space
    std::optional<double> usage_percent;                 // 0.0 - 100.0
    std::optional<uint64_t> total_inodes;                // Total inodes
    std::optional<uint64_t> available_inodes;            // Available inodes
    
    // I/O error tracking
    std::chrono::system_clock::time_point last_io_error_at;
    int io_error_count = 0;
    
    // Timing
    std::chrono::system_clock::time_point observed_at;
    
    // Evidence references
    std::vector<std::string> evidence_ids;
};

// ============================================================================
// MountTransition — A mount state change event
// ============================================================================

enum class MountTransitionType {
    kNone,               // No transition
    kMount,              // Mount added/created
    kUnmount,            // Mount removed/destroyed
    kReadOnlyRemount,    // Filesystem remounted read-only
};

struct MountTransition {
    std::string mount_point;
    MountState previous_state = MountState::kUnknown;
    MountState current_state = MountState::kUnknown;
    MountTransitionType transition_type = MountTransitionType::kNone;
    
    std::chrono::system_clock::time_point timestamp;
    std::vector<std::string> evidence_ids;
};

// ============================================================================
// StorageHealthAssessment — Complete storage subsystem health report
// ============================================================================

struct StorageHealthAssessment {
    // Subsystems assessed
    std::vector<BlockDeviceHealth> block_devices;
    std::vector<FilesystemHealth> filesystems;
    std::vector<MountTransition> mount_transitions;
    
    // Aggregate states
    BlockDeviceHealthState aggregate_block_health = BlockDeviceHealthState::kUnknown;
    FilesystemHealthState aggregate_fs_health = FilesystemHealthState::kUnknown;
    
    // Timing
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::chrono::milliseconds> assessment_duration_ms;
    
    // Evidence references
    std::vector<std::string> evidence_ids;
};

// ============================================================================
// StorageMonitorMetrics — Runtime metrics for the storage monitor
// ============================================================================

struct StorageMonitorMetrics {
    std::chrono::system_clock::time_point started_at;
    
    size_t block_device_observations = 0;
    size_t filesystem_observations = 0;
    size_t mount_observations = 0;
    size_t io_error_count = 0;
    size_t mount_transitions_detected = 0;
};

// ============================================================================
// StorageHealthMonitorConfig — Configuration for the storage monitor
// ============================================================================

struct StorageHealthMonitorConfig {
    // Observation windows
    std::chrono::milliseconds observation_interval_ms{5000};      // Default: 5 seconds
    
    // Thresholds
    int io_error_threshold = 5;                                    // Errors in window → degraded/failing
    double capacity_warning_percent = 90.0;                        // Usage > this → warning
    double capacity_critical_percent = 95.0;                       // Usage > this → critical
    
    // Health thresholds
    std::optional<int> nvme_percentage_used_warning{80};          // NVMe wear warning threshold
    std::optional<int> nvme_percentage_used_critical{90};         // NVMe wear critical threshold
    int temperature_warning_celsius = 70;                         // Temperature warning
    int temperature_critical_celsius = 85;                        // Temperature critical
    
    // Retention
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
    
    // Sources
    bool enable_nvme_health = true;                               // Read NVMe SMART data
    bool enable_smart_health = true;                              // Read ATA SMART data
    bool enable_mount_observation = true;                         // Observe mount table
};

// ============================================================================
// StorageHealthEvent — Event generated by the storage health monitor
// ============================================================================

enum class StorageHealthEventType {
    kBlockDeviceStateChange,
    kFilesystemStateChange,
    kMountAdded,
    kMountRemoved,
    kReadOnlyRemountDetected,
    kIOErrorThresholdExceeded,
    kCapacityWarning,
    kCapacityCritical,
};

struct StorageHealthEvent {
    StorageHealthEventType event_type = StorageHealthEventType::kBlockDeviceStateChange;
    
    std::string event_id;
    std::chrono::system_clock::time_point timestamp;
    
    // Subject
    std::optional<std::string> device_id;                         // For block device events
    std::optional<std::string> mount_point;                       // For filesystem/mount events
    
    // State transition
    std::optional<BlockDeviceHealthState> old_block_health;
    BlockDeviceHealthState new_block_health = BlockDeviceHealthState::kUnknown;
    
    std::optional<FilesystemHealthState> old_fs_health;
    FilesystemHealthState new_fs_health = FilesystemHealthState::kUnknown;
    
    // Evidence
    std::vector<std::string> evidence_ids;
    std::string description;
};

// ============================================================================
// Factory functions
// ============================================================================

BlockDeviceHealth make_initial_block_device_health(const std::string& device_id);
FilesystemHealth make_initial_filesystem_health(const std::string& mount_point);

}  // namespace rebuntu::modules::storage_health_monitor