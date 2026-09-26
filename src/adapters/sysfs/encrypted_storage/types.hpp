// rebuntu::adapters::sysfs::encrypted_storage — Encrypted Storage Observation Adapter (Phase 5.19)
//
// This module implements Rebuntu's sysfs-based encrypted storage observation adapter:
//   - Observes LUKS device-mapper relationships without exposing key material
//   - Identifies encrypted volumes via UUID prefixes
//   - Maps dm devices to their underlying sources where possible
//   - Tracks LUKS vs LVM relationships safely
//
// Native Interfaces Used:
//   - /sys/block/dm-X/dm/name — device-mapper device names
//   - /sys/block/dm-X/dm/uuid — device-mapper UUIDs (contains LUKS/LVM info)
//   - /dev/mapper — mapper symlinks (read-only, for name resolution)
//
// Key Distinctions:
//   - Encrypted storage = devices using dm-crypt/LUKS
//   - LVM volumes = logical volumes managed by device-mapper
//   - SecretRef != SecretMaterial — UUIDs don't contain keys

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <memory>

namespace rebuntu::adapters::sysfs::encrypted_storage {

// ============================================================================
// EncryptedStorageKind — Type of encrypted storage entity
//
// Represents different categories of device-mapper entities:
//   - kLUKS: LUKS-encrypted volumes (CRYPT-LUKS* UUID prefix)
//   - kLVM: LVM logical volumes (LVM-* UUID prefix)
//   - kOther: Other device-mapper entities without encryption
// ============================================================================
enum class EncryptedStorageKind {
    kLUKS,         // LUKS-encrypted volume (cryptsetup)
    kLVM,          // LVM logical volume
    kOther,        // Other dm entity (not encrypted storage relevant to Phase 5.19)
};

inline std::string to_string(EncryptedStorageKind k) {
    switch (k) {
        case EncryptedStorageKind::kLUKS: return "luks";
        case EncryptedStorageKind::kLVM:  return "lvm";
        case EncryptedStorageKind::kOther:return "other";
    }
    return "unknown";
}

// ============================================================================
// LUKSState — State of a LUKS volume
//
// Represents the lifecycle state of an encrypted volume:
//   - kConfigured: LUKS header configured, but not yet opened
//   - kOpen: Volume is open (mapped in /dev/mapper)
//   - kClosed: Volume is closed (no dm mapping)
// ============================================================================
enum class LUKSState {
    kConfigured,  // LUKS header exists on source device
    kOpen,        // Volume is currently mapped/open
    kClosed,      // Volume is closed (not mapped)
};

inline std::string to_string(LUKSState s) {
    switch (s) {
        case LUKSState::kConfigured: return "configured";
        case LUKSState::kOpen:       return "open";
        case LUKSState::kClosed:     return "closed";
    }
    return "unknown";
}

// ============================================================================
// DMDeviceIdentity — Stable identity for a device-mapper device
//
// A dm device is uniquely identified by its name and UUID.
// The major:minor numbers provide additional identification.
// ============================================================================
struct DMDeviceIdentity {
    std::string name;                 // Device-mapper name (e.g., "luks-abc123")
    std::optional<std::string> uuid;  // UUID if available
    int major{-1};                    // Major device number
    int minor{-1};                    // Minor device number
};

inline bool operator==(const DMDeviceIdentity& a, const DMDeviceIdentity& b) {
    return a.name == b.name && 
           a.uuid == b.uuid && 
           a.major == b.major && 
           a.minor == b.minor;
}

// ============================================================================
// EncryptedStorageObservation — Complete observation of an encrypted storage device
//
// Combines dm-device information with encryption-specific metadata.
// ============================================================================
struct EncryptedStorageObservation {
    DMDeviceIdentity identity;
    
    // Encryption type
    EncryptedStorageKind kind{EncryptedStorageKind::kOther};
    
    // LUKS-specific fields (only valid if kind == kLUKS)
    std::optional<std::string> luks_uuid;        // Full LUKS UUID from dm/uuid
    std::optional<std::string> source_device;    // Source block device path
    std::optional<LUKSState> state;              // Current LUKS state
    
    // LVM-specific fields (only valid if kind == kLVM)
    std::optional<std::string> lvm_vg_name;      // Volume group name
    std::optional<std::string> lvm_lv_name;      // Logical volume name
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"sysfs"};  // "sysfs" for /sys/block/dm-X/dm/
};

// ============================================================================
// EncryptedStorageTopology — Relationship topology of encrypted storage
//
// Represents how encrypted devices relate to each other:
//   - LUKS volumes may contain LVM PVs
//   - LVM VGs may have multiple LVs
//   - dm-crypt provides encryption layer for any underlying device
// ============================================================================
struct EncryptedStorageTopology {
    // All observed devices indexed by name
    std::unordered_map<std::string, EncryptedStorageObservation> devices_by_name;
    
    // Root encrypted devices (LUKS without LVM on top)
    std::vector<std::string> luks_root_devices;
    
    // LVM volume groups and their member devices
    struct VGInfo {
        std::string vg_name;
        std::optional<std::string> pv_device;  // Physical volume device (may be a LUKS device)
        std::vector<std::string> lv_names;     // Logical volume names
    };
    
    std::unordered_map<std::string, VGInfo> volume_groups;
    
    // Statistics
    size_t total_devices{0};
    size_t luks_devices{0};
    size_t lvm_devices{0};
    size_t other_dm_devices{0};
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// EncryptedStorageObservationResult — Result of encrypted storage observation
// ============================================================================
struct EncryptedStorageObservationResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual devices)
    std::vector<EncryptedStorageObservation> devices;
    
    // Topology graph derived from relationships
    std::optional<EncryptedStorageTopology> topology;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_devices{0};
    
    // Provider provenance
    std::string provider_source{"sysfs"};
    
    std::optional<core::Error> error;
};

// ============================================================================
// EncryptedStorageAdapter — Interface for sysfs encrypted storage observation
// ============================================================================
class EncryptedStorageAdapter {
public:
    virtual ~EncryptedStorageAdapter() = default;
    
    // Observe all encrypted storage devices
    virtual EncryptedStorageObservationResult observe_devices() = 0;
    
    // Get the full topology of encrypted storage relationships
    virtual EncryptedStorageTopology get_topology() = 0;
    
    // Resolve a dm device to its kind and details
    virtual std::optional<EncryptedStorageObservation> resolve_device(std::string_view name) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<EncryptedStorageAdapter> make_sysfs_encrypted_storage_adapter();

}  // namespace rebuntu::adapters::sysfs::encrypted_storage