// rebuntu::adapters::procfs::mounts — Procfs Mounts Observation Adapter (Phase 5.17)
//
// This module implements Rebuntu's procfs-based filesystem observation adapter:
//   - Reads mount information from /proc/self/mountinfo
//   - Observes: source identity, target (mountpoint), filesystem type, options
//   - Supports capacity observation via statvfs(2) for mounted filesystems
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

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>

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
// Combines mount metadata with optional capacity information.
// ============================================================================

struct MountObservation {
    MountIdentity identity;
    
    int parent_id{-1};                // Parent mount ID (from mountinfo)
    std::string filesystem_type;      // e.g., "ext4", "xfs", "btrfs", "nfs"
    std::vector<std::string> options; // Mount options split by comma
    std::optional<FilesystemCapacity> capacity;  // Optional capacity info
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source;               // "procfs" for /proc/self/mountinfo
};

// ============================================================================
// MountObservationResult — Result of filesystem observation
// ============================================================================

struct MountObservationResult {
    core::SemanticStatus status;
    std::string description;
    
    std::vector<MountObservation> mounts;
    
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_mounts{0};
    size_t capacity_failures{0};      // Number of mounts where capacity failed
    
    std::optional<core::Error> error;
};

// ============================================================================
// MountsAdapter — Interface for procfs mount observation
// ============================================================================

class MountsAdapter {
public:
    virtual ~MountsAdapter() = default;
    
    // Observe all mounted filesystems
    virtual MountObservationResult observe_mounts() = 0;
    
    // Observe a specific mount by mountpoint
    virtual std::optional<MountObservation> observe_mount(std::string_view mountpoint) = 0;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<MountsAdapter> make_procfs_mounts_adapter();

}  // namespace rebuntu::adapters::procfs::mounts