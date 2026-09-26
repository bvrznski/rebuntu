// rebuntu::adapters::procfs::mounts — Procfs Mounts Observation Adapter (Phase 5.17)
// Mount Topology extension (Phase 5.18)
//
// This module implements Rebuntu's procfs-based filesystem observation adapter:
//   - Reads mount information from /proc/self/mountinfo
//   - Observes: source identity, target (mountpoint), filesystem type, options
//   - Supports capacity observation via statvfs(2) for mounted filesystems
//   - Represents layered mount relationships (bind/overlay/network mounts)
//
// Native Interfaces Used:
//   - /proc/self/mountinfo — detailed mount table with mount IDs, parent ID, flags
//   - statvfs(2) — filesystem capacity and usage information
//
// Key Distinctions:
//   - Source identity = block device path or remote source (NFS, etc.)
//   - Mountpoint = target directory where filesystem is mounted
//   - Filesystem type = ext4, xfs, btrfs, nfs, etc.
//   - Options = mount options (rw, ro, noatime, etc.)
//   - Capacity = total size, used space, available space, inode info
//   - Topology = layered relationships between mounts (binds, overlays, etc.)

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>

namespace rebuntu::adapters::procfs::mounts {

// ============================================================================
// MountIdentity — Stable identity for a mounted filesystem
//
// A mount is uniquely identified by the combination of source + mountpoint.
// The major:minor device numbers provide additional stable identification.
// ============================================================================

struct MountIdentity {
    int major{-1};                    // Major device number (or -1 for non-device)
    int minor{-1};                    // Minor device number (or -1 for non-device)
    std::string source;               // Source path (device, NFS server, etc.)
    std::string mountpoint;           // Target directory where mounted
};

inline bool operator==(const MountIdentity& a, const MountIdentity& b) {
    return a.major == b.major &&
           a.minor == b.minor &&
           a.source == b.source &&
           a.mountpoint == b.mountpoint;
}

// ============================================================================
// MountTopologyType — Type of mount relationship in the topology
//
// Represents how a mount is related to its base filesystem:
//   - kPrimary: Native mount from block device or remote source
//   - kBind: Bind mount (mirror of another directory within same filesystem)
//   - kOverlay: Overlay/union mount (layers multiple directories)
//   - kBindOverlay: Bind mount of an overlay
//   - kNetwork: Network-mounted filesystem (NFS, CIFS, etc.)
//   - kSpecial: Special filesystem (tmpfs, devpts, procfs, sysfs, etc.)
//
// This enables understanding mount hierarchy without flattening to a disk list.
// ============================================================================

enum class MountTopologyType {
    kPrimary,        // Native mount from block device or remote source
    kBind,           // Bind mount (mirror of another directory)
    kOverlay,        // Overlay/union mount (layers directories)
    kBindOverlay,    // Bind mount of an overlay filesystem
    kNetwork,        // Network-mounted filesystem (NFS, CIFS)
    kSpecial,        // Special in-memory filesystem (tmpfs, proc, sys, devpts)
};

inline std::string to_string(MountTopologyType t) {
    switch (t) {
        case MountTopologyType::kPrimary:     return "primary";
        case MountTopologyType::kBind:        return "bind";
        case MountTopologyType::kOverlay:     return "overlay";
        case MountTopologyType::kBindOverlay: return "bind-overlay";
        case MountTopologyType::kNetwork:     return "network";
        case MountTopologyType::kSpecial:     return "special";
    }
    return "unknown";
}

// ============================================================================
// MountRelationship — Relationship between mounts in the topology graph
//
// Represents how one mount relates to another:
//   - parent_mount_id: The mount ID of the parent/base filesystem (from mountinfo)
//   - base_source: The actual source path if different from identity
//   - relationship_type: How this mount is related (bind, overlay, etc.)
// ============================================================================

struct MountRelationship {
    int parent_mount_id{-1};          // Parent mount ID from mountinfo (0 = root of tree)
    std::string base_source;          // Base source filesystem path (if different)
    MountTopologyType relationship_type{MountTopologyType::kPrimary};
    
    // For overlay mounts, track the layers
    std::vector<std::string> overlay_layers;  // Upper/work/base directories if applicable
    
    // Provenance: where this relationship info came from
    std::string provenance_source{"procfs"};  // "procfs", "sysfs", "udev", etc.
};

// ============================================================================
// FilesystemCapacity — Capacity and usage information for a filesystem
//
// Obtained via statvfs(2) system call.
// ============================================================================

struct FilesystemCapacity {
    uint64_t block_size{0};           // Fundamental filesystem block size
    uint64_t total_blocks{0};         // Total blocks in filesystem
    uint64_t free_blocks{0};          // Free blocks available to non-privileged users
    uint64_t used_blocks{0};          // Used blocks (total - free)
    uint64_t available_blocks{0};     // Blocks available to non-privileged users
    
    uint64_t total_inodes{0};         // Total inodes
    uint64_t free_inodes{0};          // Free inodes
    uint64_t used_inodes{0};          // Used inodes (total - free)
    
    uint64_t capacity_bytes{0};       // Total capacity in bytes
    uint64_t used_bytes{0};           // Used capacity in bytes
    uint64_t available_bytes{0};      // Available capacity in bytes
    
    std::chrono::system_clock::time_point captured_at{};
};

// ============================================================================
// MountObservation — Complete filesystem observation for a single mount
//
// Combines mount metadata with optional capacity information and topology.
// ============================================================================

struct MountObservation {
    MountIdentity identity;
    
    int parent_id{-1};                // Parent mount ID (from mountinfo, used for topology)
    std::string filesystem_type;      // e.g., "ext4", "xfs", "btrfs", "nfs"
    std::vector<std::string> options; // Mount options split by comma
    
    // Topology information
    MountRelationship relationship;
    
    // Capacity info (optional - may fail for some mounts)
    std::optional<FilesystemCapacity> capacity;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source;               // "procfs" for /proc/self/mountinfo
    
    // Mount-specific metadata extracted from options
    bool is_read_only{false};
    bool is_noexec{false};
    bool isnosuid{false};
    bool isnodev{false};
    bool isnoatime{false};
    bool isbind{false};               // True if mount has 'bind' option
};

// ============================================================================
// MountTopology — Complete mount topology graph
//
// Represents all mounts as a directed graph showing relationships:
//   - Nodes: individual mounts (MountObservation)
//   - Edges: parent-child relationships from mountinfo
//   - Labels: relationship types (bind, overlay, network, etc.)
//
// The topology preserves the layered structure without flattening.
// ============================================================================

struct MountTopology {
    // All observed mounts indexed by their mount ID
    std::unordered_map<int, MountObservation> mounts_by_id;
    
    // Root mount IDs (those with parent_id == 0 or self-parent)
    std::vector<int> root_mount_ids;
    
    // Map of child mount IDs for each parent
    std::unordered_map<int, std::vector<int>> children_by_parent;
    
    // Statistics
    size_t total_mounts{0};
    size_t primary_mounts{0};         // Native mounts from devices/sources
    size_t bind_mounts{0};            // Bind mounts
    size_t overlay_mounts{0};         // Overlay mounts
    size_t network_mounts{0};         // Network-mounted filesystems
    size_t special_mounts{0};         // In-memory filesystems (tmpfs, proc, etc.)
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// MountObservationResult — Result of filesystem observation with topology
// ============================================================================

struct MountObservationResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual mounts)
    std::vector<MountObservation> mounts;
    
    // Topology graph derived from relationships
    std::optional<MountTopology> topology;
    
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_mounts{0};
    size_t capacity_failures{0};      // Number of mounts where capacity failed
    
    // Provider provenance - where this data came from
    std::string provider_source{"procfs"};  // Source: "procfs", "sysfs", etc.
    
    std::optional<core::Error> error;
};

// ============================================================================
// MountsAdapter — Interface for procfs mount observation with topology support
// ============================================================================

class MountsAdapter {
public:
    virtual ~MountsAdapter() = default;
    
    // Observe all mounted filesystems (basic)
    virtual MountObservationResult observe_mounts() = 0;
    
    // Observe a specific mount by mountpoint
    virtual std::optional<MountObservation> observe_mount(std::string_view mountpoint) = 0;
    
    // Get the full topology graph of all mounts
    virtual MountTopology get_topology() = 0;
    
    // Resolve a mount relationship to its base/source
    virtual std::optional<std::pair<int, MountIdentity>> resolve_to_source(int mount_id) = 0;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<MountsAdapter> make_procfs_mounts_adapter();

}  // namespace rebuntu::adapters::procfs::mounts