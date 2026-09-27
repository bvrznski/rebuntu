// rebuntu::adapters::namespaces — Linux Namespace Observation Adapter (Phase 5.29)
//
// This module implements Rebuntu's namespace observation adapter:
//   - Reads Linux namespace relationships from /proc/[pid]/ns/
//   - Observes: namespace type, inode number, process-to-namespace bindings
//   - Provides bounded facts where available
//   - Namespace inode is identity within appropriate scope
//
// Native Interfaces Used:
//   - /proc/[pid]/ns/ — directory of symbolic links to namespace inodes
//   - readlink(2) — read namespace symlink targets (format: "ns/[type]: [inode]")
//   - stat(2) — get inode numbers from namespace files
//
// Key Distinctions:
//   - NamespaceIdentity = (namespace_type, inode_number) pair for durable identity
//   - Inode number is stable within a boot cycle
//   - Multiple processes may share the same namespace (clone with CLONE_NEW*)
//   - PID alone does NOT identify a process; requires boot context
//
// Use Cases:
//   - Determine if two processes are in the same PID namespace
//   - Identify network namespace isolation boundaries
//   - Understand process hierarchy across namespace boundaries

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>

namespace rebuntu::adapters::namespaces {

// ============================================================================
// NamespaceType — Linux namespace types
//
// Mirrors the namespace types from /proc/[pid]/ns/:
//   cgroup    - Cgroup namespace
//   uts       - UTS namespace (hostname/nodename)
//   ipc       - IPC namespace (shared memory, message queues, semaphores)
//   pid       - PID namespace (process ID space)
//   net       - Network namespace (network stack, interfaces, routes)
//   mnt       - Mount namespace (filesystem mount points)
//   user      - User namespace (UID/GID mapping)
//   time      - Time namespace (boot/timeofday offsets)
// ============================================================================
enum class NamespaceType {
    kUnknown,    // Unknown or unidentifiable namespace type
    kCgroup,     // Cgroup namespace
    kUts,        // UTS namespace
    kIpc,        // IPC namespace
    kPid,        // PID namespace
    kNet,        // Network namespace
    kMnt,        // Mount namespace
    kUser,       // User namespace
    kTime,       // Time namespace
};

inline std::string to_string(NamespaceType t) {
    switch (t) {
        case NamespaceType::kUnknown: return "unknown";
        case NamespaceType::kCgroup:  return "cgroup";
        case NamespaceType::kUts:     return "uts";
        case NamespaceType::kIpc:     return "ipc";
        case NamespaceType::kPid:     return "pid";
        case NamespaceType::kNet:     return "net";
        case NamespaceType::kMnt:     return "mnt";
        case NamespaceType::kUser:    return "user";
        case NamespaceType::kTime:    return "time";
    }
    return "unknown";
}

// ============================================================================
// NamespaceIdentity — Stable identity for a Linux namespace
//
// A namespace is uniquely identified by its type and inode number.
// The inode number is stable within a boot cycle (but may be reused after reboot).
// ============================================================================
struct NamespaceIdentity {
    NamespaceType type{NamespaceType::kUnknown};
    uint64_t inode_number{0};  // Inode number from stat(2)
    
    bool is_valid() const {
        return type != NamespaceType::kUnknown && inode_number > 0;
    }
};

inline bool operator==(const NamespaceIdentity& a, const NamespaceIdentity& b) {
    return a.type == b.type && a.inode_number == b.inode_number;
}

// For use as map key
inline bool operator<(const NamespaceIdentity& a, const NamespaceIdentity& b) {
    if (a.type != b.type) {
        return a.type < b.type;
    }
    return a.inode_number < b.inode_number;
}

// ============================================================================
// NamespaceRelationship — Process-to-namespace relationship
//
// Represents how a process is related to a namespace:
//   - The process is a member of this namespace
//   - The namespace provides isolation for the process
// ============================================================================
struct NamespaceRelationship {
    NamespaceIdentity namespace_identity;  // Which namespace
    std::string symlink_path;              // Path to the ns symlink (e.g., "/proc/1/ns/pid")
    bool is_current{false};                // True if this is the current process's namespace
};

// ============================================================================
// NamespaceObservation — Complete observation for a single namespace
//
// Combines namespace metadata with process membership information.
struct NamespaceObservation {
    NamespaceIdentity identity;
    
    // Process members (which processes belong to this namespace)
    std::vector<int> member_pids;  // PIDs of processes in this namespace
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"procfs"};  // "procfs" for /proc/[pid]/ns/
};

// ============================================================================
// NamespaceDiscoveryResult — Result of namespace discovery operation
struct NamespaceDiscoveryResult {
    core::SemanticStatus status;
    std::string description;
    
    // All observed namespaces
    std::vector<NamespaceObservation> namespaces;
    
    // Process-to-namespace mappings (which processes are in which namespaces)
    std::unordered_map<int, std::vector<NamespaceRelationship>> process_namespaces;
    
    // Statistics
    size_t total_namespaces{0};
    size_t total_processes_observed{0};
    
    // Counts by namespace type
    size_t cgroup_namespaces{0};
    size_t uts_namespaces{0};
    size_t ipc_namespaces{0};
    size_t pid_namespaces{0};
    size_t net_namespaces{0};
    size_t mnt_namespaces{0};
    size_t user_namespaces{0};
    size_t time_namespaces{0};
    
    // Timing
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    // Provider provenance
    std::string provider_source{"procfs"};
    
    // Errors encountered during discovery (non-fatal)
    std::vector<std::pair<std::string, core::Error>> errors;  // path -> error mapping
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// NamespaceDiscoveryAdapter — Interface for namespace observation
//
// Provides bounded, cancellable, freshness-aware namespace observation.
class NamespaceDiscoveryAdapter {
public:
    virtual ~NamespaceDiscoveryAdapter() = default;
    
    // Observe all namespaces visible from procfs
    // Returns observations sorted by (type, inode) for deterministic iteration
    virtual NamespaceDiscoveryResult observe_all_namespaces() = 0;
    
    // Observe a specific namespace by identity
    // Returns std::nullopt if the namespace is not found or inaccessible
    virtual std::optional<NamespaceObservation> observe_namespace(
        const NamespaceIdentity& identity) = 0;
    
    // Get processes in a specific namespace by type and inode
    virtual std::vector<int> get_namespace_members(NamespaceType type, uint64_t inode_number) = 0;
    
    // Check if two processes are in the same namespace of a given type
    virtual bool processes_share_namespace(int pid1, int pid2, NamespaceType type) = 0;
    
    // Get freshness information about the last observation
    // Returns the timestamp of the last complete observation, if any
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from procfs
    // This is idempotent and safe to call multiple times
    virtual NamespaceDiscoveryResult force_refresh() = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<NamespaceDiscoveryAdapter> make_namespace_discovery_adapter();

}  // namespace rebuntu::adapters::namespaces