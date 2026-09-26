// rebuntu::adapters::sysfs::md_raid — Software RAID (md) Observation Adapter (Phase 5.20)
//
// This module implements Rebuntu's sysfs-based md RAID observation adapter:
//   - Observes md device topology from /sys/block/md*/
//   - Reads detailed array status from /proc/mdstat
//   - Identifies RAID levels, member disks, state, sync progress
//   - Tracks rebuild and recovery status
//
// Native Interfaces Used:
//   - /sys/block/md-X/ — md device attributes (level, raid_disks, etc.)
//   - /proc/mdstat — detailed array status with sync/rebuild info
//
// Key Distinctions:
//   - RAID level = md RAID configuration (linear,raid0,raid1,raid4,raid5,raid6,raid10)
//   - Array state = active/inactive/degraded/syncing/recovering
//   - Member disks = devices participating in the array
//   - Sync progress = rebuild/recovery percentage and ETA

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <memory>

namespace rebuntu::adapters::sysfs::md_raid {

// ============================================================================
// RaidLevel — Software RAID configuration level
//
// Represents md RAID levels supported by Linux kernel:
//   - kLinear: Linear concatenation of devices
//   - kRaid0: Striping without redundancy
//   - kRaid1: Mirroring with full redundancy
//   - kRaid4: Striping with dedicated parity
//   - kRaid5: Striping with distributed parity
//   - kRaid6: Striping with dual distributed parity
//   - kRaid10: Stripe of mirrors
// ============================================================================
enum class RaidLevel {
    kLinear,      // Linear concatenation
    kRaid0,       // Striping (no redundancy)
    kRaid1,       // Mirroring
    kRaid4,       // Striping with dedicated parity
    kRaid5,       // Striping with distributed parity
    kRaid6,       // Striping with dual distributed parity
    kRaid10,      // Stripe of mirrors (1+0)
};

inline std::string to_string(RaidLevel l) {
    switch (l) {
        case RaidLevel::kLinear:  return "linear";
        case RaidLevel::kRaid0:   return "raid0";
        case RaidLevel::kRaid1:   return "raid1";
        case RaidLevel::kRaid4:   return "raid4";
        case RaidLevel::kRaid5:   return "raid5";
        case RaidLevel::kRaid6:   return "raid6";
        case RaidLevel::kRaid10:  return "raid10";
    }
    return "unknown";
}

// ============================================================================
// ArrayState — Current state of an md RAID array
//
// Represents the operational state of a software RAID array:
//   - kInactive: Array is not active (not assembled)
//   - kActive: Array is active but may be degraded
//   - kDegraded: Array is active with failed member disks
//   - kSyncing: Array is syncing/rebuilding
//   - kRecovering: Array is recovering from failure
// ============================================================================
enum class ArrayState {
    kInactive,     // Not assembled/active
    kActive,       // Active but potentially degraded
    kDegraded,     // Active with failed disks
    kSyncing,      // Currently syncing (initial or resync)
    kRecovering,   // Recovering from disk failure
};

inline std::string to_string(ArrayState s) {
    switch (s) {
        case ArrayState::kInactive:   return "inactive";
        case ArrayState::kActive:     return "active";
        case ArrayState::kDegraded:   return "degraded";
        case ArrayState::kSyncing:    return "syncing";
        case ArrayState::kRecovering: return "recovering";
    }
    return "unknown";
}

// ============================================================================
// MdDeviceIdentity — Stable identity for an md RAID device
//
// An md device is uniquely identified by its name (md0, md1, etc.)
// and can be further distinguished by UUID.
// ============================================================================
struct MdDeviceIdentity {
    std::string name;                  // Device name: "md0", "md127", etc.
    std::optional<std::string> uuid;   // Array UUID if available
    int major{-1};                     // Major device number (typically 9)
    int minor{-1};                     // Minor device number
};

inline bool operator==(const MdDeviceIdentity& a, const MdDeviceIdentity& b) {
    return a.name == b.name && 
           a.uuid == b.uuid && 
           a.major == b.major && 
           a.minor == b.minor;
}

// ============================================================================
// MemberDisk — A disk participating in an md array
//
// Tracks individual member disks with their health and position.
// ============================================================================
struct MemberDisk {
    std::string device_path;           // Block device path (e.g., "/dev/sda1")
    int raid_position{-1};             // Position in RAID configuration
    bool is_active{false};             // Currently active in array
    bool is_failed{false};             // Marked as failed
    bool is_spare{false};              // Spare disk (not currently used)
};

// ============================================================================
// MdArrayObservation — Complete observation of an md RAID array
//
// Combines sysfs attributes with /proc/mdstat status.
// ============================================================================
struct MdArrayObservation {
    MdDeviceIdentity identity;
    
    // Basic configuration
    RaidLevel level{RaidLevel::kLinear};
    int raid_disks{0};                 // Total number of configured disks
    int active_disks{0};               // Number of active (non-failed) disks
    int working_disks{0};              // Number of working (active+spare) disks
    int failed_disks{0};               // Number of failed disks
    int spare_disks{0};                // Number of spare disks
    
    // Current state
    ArrayState state{ArrayState::kInactive};
    
    // Member disk details
    std::vector<MemberDisk> member_disks;
    
    // Sync/rebuild progress (if applicable)
    bool is_syncing{false};
    int sync_percent{0};               // 0-100
    std::optional<int64_t> sync_remaining_seconds;  // Estimated remaining time
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"sysfs"};       // "sysfs" for /sys/block/md*/md/
};

// ============================================================================
// MdTopology — Relationship topology of md RAID arrays
//
// Represents how arrays relate to their member devices.
// ============================================================================
struct MdTopology {
    // All observed arrays indexed by name
    std::unordered_map<std::string, MdArrayObservation> arrays_by_name;
    
    // Device-to-array mappings (which array uses which device)
    std::unordered_map<std::string, std::vector<std::string>> devices_to_arrays;
    
    // Statistics
    size_t total_arrays{0};
    size_t active_arrays{0};
    size_t degraded_arrays{0};
    size_t syncing_arrays{0};
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// MdObservationResult — Result of md RAID observation
// ============================================================================
struct MdObservationResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual arrays)
    std::vector<MdArrayObservation> arrays;
    
    // Topology graph derived from relationships
    std::optional<MdTopology> topology;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_arrays{0};
    size_t arrays_with_errors{0};      // Arrays where observation failed
    
    // Provider provenance
    std::string provider_source{"sysfs"};
    
    std::optional<core::Error> error;
};

// ============================================================================
// MdRaidAdapter — Interface for sysfs md RAID observation
// ============================================================================
class MdRaidAdapter {
public:
    virtual ~MdRaidAdapter() = default;
    
    // Observe all md RAID arrays
    virtual MdObservationResult observe_arrays() = 0;
    
    // Get the full topology of RAID relationships
    virtual MdTopology get_topology() = 0;
    
    // Resolve a specific md device by name
    virtual std::optional<MdArrayObservation> resolve_array(std::string_view name) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<MdRaidAdapter> make_sysfs_md_raid_adapter();

}  // namespace rebuntu::adapters::sysfs::md_raid