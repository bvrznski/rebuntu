// rebuntu::adapters::cgroups::hierarchy — Cgroup v2 Hierarchy Observation Adapter (Phase 5.28)
//
// This module implements Rebuntu's cgroup v2 hierarchy observation adapter:
//   - Observes the hierarchical cgroup structure at /sys/fs/cgroup/
//   - Reports: cgroup identities, resource controller availability, parent-child relationships
//   - Tracks: nr_descendants, nr_dying_descendants, active controllers per cgroup
//
// Native Interfaces Used:
//   - /sys/fs/cgroup/ — cgroup v2 hierarchy root
//   - /sys/fs/cgroup/*/*.controllers — per-cgroup available controllers
//   - /sys/fs/cgroup/cgroup.stat — global cgroup statistics
//
// Key Distinctions:
//   - Cgroup path = absolute path within the hierarchy (e.g., "/system.slice/ssh.service")
//   - Cgroup identity = unique identifier derived from cgroup ID and path
//   - Controller = resource control domain (cpu, memory, io, pids, etc.)
//   - Topology = parent-child relationships between cgroups
//   - Hierarchy depth = number of levels from root to this cgroup

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <chrono>
#include <memory>
#include <unordered_map>

namespace rebuntu::adapters::cgroups::hierarchy {

// ============================================================================
// CGroupIdentity — Stable identity for a cgroup
//
// A cgroup is uniquely identified by its absolute path within the hierarchy.
// The kernel assigns an internal ID that can also be used for tracking.
// ============================================================================

struct CGroupIdentity {
    int64_t id{-1};                     // Kernel-assigned cgroup ID (if available)
    std::string path;                   // Absolute path within hierarchy
};

inline bool operator==(const CGroupIdentity& a, const CGroupIdentity& b) {
    return a.id == b.id && a.path == b.path;
}

// ============================================================================
// ControllerType — Type of resource controller in cgroup v2
//
// Represents the available controllers:
//   - cpu: CPU time allocation and shares
//   - memory: Memory usage limits and statistics
//   - io: I/O bandwidth limits
//   - pids: Process count limits
//   - cpuset: CPU/MEM affinity (if enabled)
//   - hugetlb: Huge page limits
//   - rdma: RDMA limits
//   - misc: Miscellaneous controls
// ============================================================================

enum class ControllerType {
    kCpu,           // CPU time allocation and shares
    kMemory,        // Memory usage limits and statistics
    kIo,            // I/O bandwidth limits
    kPids,          // Process count limits
    kCpuset,        // CPU/MEM affinity (if enabled)
    kHugetlb,       // Huge page limits
    kRdma,          // RDMA limits
    kMisc,          // Miscellaneous controls
};

inline std::string to_string(ControllerType t) {
    switch (t) {
        case ControllerType::kCpu:     return "cpu";
        case ControllerType::kMemory:  return "memory";
        case ControllerType::kIo:      return "io";
        case ControllerType::kPids:    return "pids";
        case ControllerType::kCpuset:  return "cpuset";
        case ControllerType::kHugetlb: return "hugetlb";
        case ControllerType::kRdma:    return "rdma";
        case ControllerType::kMisc:    return "misc";
    }
    return "unknown";
}

// ============================================================================
// CGroupControllerInfo — Available controllers and their state for a cgroup
// ============================================================================

struct CGroupControllerInfo {
    std::vector<ControllerType> enabled;     // Controllers that are active in this cgroup
    std::vector<ControllerType> available;   // Controllers available at this level
    
    bool has_cpu() const { return contains_controller(enabled, ControllerType::kCpu); }
    bool has_memory() const { return contains_controller(enabled, ControllerType::kMemory); }
    bool has_io() const { return contains_controller(enabled, ControllerType::kIo); }
    bool has_pids() const { return contains_controller(enabled, ControllerType::kPids); }
    
private:
    static bool contains_controller(const std::vector<ControllerType>& vec, ControllerType t) {
        for (auto v : vec) if (v == t) return true;
        return false;
    }
};

// ============================================================================
// CGroupStatistics — Statistics for a cgroup from cgroup.stat
//
// Global cgroup statistics available at any hierarchy level:
//   - nr_descendants: number of child cgroups below this one
//   - nr_dying_descendants: cgroups in the process of being removed
//   - memory.current: current memory usage (if memory controller active)
//   - cpu.usage_usec: CPU time used (if cpu controller active)
// ============================================================================

struct CGroupStatistics {
    int64_t nr_descendants{0};            // Number of descendant cgroups
    int64_t nr_dying_descendants{0};      // Dying descendants being cleaned up
    
    // Controller-specific stats (optional, only if controller is active)
    std::optional<int64_t> memory_current_bytes;     // Current memory usage
    std::optional<int64_t> cpu_usage_usec;           // CPU time used in microseconds
    std::optional<int64_t> io_weight;                // I/O weight for this cgroup
    
    std::chrono::system_clock::time_point captured_at{};
};

// ============================================================================
// CGroupObservation — Complete observation of a single cgroup
//
// Combines identity, controller information, and statistics.
// ============================================================================

struct CGroupObservation {
    CGroupIdentity identity;
    
    // Hierarchy relationship
    std::optional<std::string> parent_path;  // Absolute path of parent, if any
    
    // Controller info for this cgroup
    CGroupControllerInfo controllers;
    
    // Statistics
    CGroupStatistics statistics;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"cgroupfs"};        // "cgroupfs" for /sys/fs/cgroup
};

// ============================================================================
// CGroupHierarchy — Complete cgroup topology graph
//
// Represents the full hierarchy:
//   - Nodes: individual cgroups (CGroupObservation)
//   - Edges: parent-child relationships from cgroup structure
//   - Labels: controller availability per node
//
// The hierarchy is rooted at "/" with system.slice, user.slice, init.scope as children.
// ============================================================================

struct CGroupHierarchy {
    // All observed cgroups indexed by path
    std::unordered_map<std::string, CGroupObservation> cgroups_by_path;
    
    // Root paths (cgroups with no parent or self-parent)
    std::vector<std::string> root_paths;
    
    // Map of child paths for each parent
    std::unordered_map<std::string, std::vector<std::string>> children_by_parent;
    
    // Global statistics from /sys/fs/cgroup/cgroup.stat
    CGroupStatistics global_statistics;
    
    // Statistics about the hierarchy itself
    size_t total_cgroups{0};
    size_t leaf_cgroups{0};               // Cgroups with no descendants
    int max_depth{0};                     // Maximum hierarchy depth
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// CGroupHierarchyResult — Result of cgroup hierarchy observation
// ============================================================================

struct CGroupHierarchyResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual cgroups)
    std::vector<CGroupObservation> cgroups;
    
    // Hierarchy graph derived from parent-child relationships
    std::optional<CGroupHierarchy> hierarchy;
    
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_cgroups{0};
    size_t controller_failures{0};        // Number of cgroups where controller reading failed
    
    // Provider provenance - where this data came from
    std::string provider_source{"cgroupfs"};
    
    // Global cgroup statistics (from /sys/fs/cgroup/cgroup.stat)
    CGroupStatistics global_statistics;
    
    std::optional<core::Error> error;
};

// ============================================================================
// CGroupHierarchyAdapter — Interface for cgroup v2 hierarchy observation
// ============================================================================

class CGroupHierarchyAdapter {
public:
    virtual ~CGroupHierarchyAdapter() = default;
    
    // Observe all cgroups in the hierarchy (basic)
    virtual CGroupHierarchyResult observe_hierarchy() = 0;
    
    // Observe a specific cgroup by path
    virtual std::optional<CGroupObservation> observe_cgroup(std::string_view path) = 0;
    
    // Get the full hierarchy graph of all cgroups
    virtual CGroupHierarchy get_hierarchy() = 0;
    
    // Resolve parent path for a given cgroup
    virtual std::optional<std::string> resolve_parent(std::string_view path) = 0;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<CGroupHierarchyAdapter> make_cgroup_hierarchy_adapter();

}  // namespace rebuntu::adapters::cgroups::hierarchy