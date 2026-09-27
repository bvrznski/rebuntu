// rebuntu::adapters::cgroups::hierarchy — Cgroup v2 Hierarchy Observation Implementation (Phase 5.28)
//
// This module implements the cgroup v2 hierarchy observation adapter:
//   - Reads cgroup information from /sys/fs/cgroup/
//   - Observes: cgroup paths, controller availability, statistics
//   - Builds parent-child hierarchy relationships

#include "adapters/cgroups/hierarchy/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstring>
#include <dirent.h>

// C++20 includes for string_view and optional
#include <string_view>
#include <optional>

namespace rebuntu::adapters::cgroups::hierarchy {

// ============================================================================
// Helper: Parse controllers from a .controllers file
//
// The file contains space-separated controller names, one per line.
// Example: "cpu io memory pids"
// ============================================================================
static std::vector<ControllerType> parse_controllers(std::string_view content) {
    std::vector<ControllerType> enabled;
    
    // Convert string_view to string for istringstream
    std::string content_str{content};
    std::istringstream iss(content_str);
    std::string token;
    
    while (iss >> token) {
        if (token == "cpu") {
            enabled.push_back(ControllerType::kCpu);
        } else if (token == "memory") {
            enabled.push_back(ControllerType::kMemory);
        } else if (token == "io") {
            enabled.push_back(ControllerType::kIo);
        } else if (token == "pids") {
            enabled.push_back(ControllerType::kPids);
        } else if (token == "cpuset") {
            enabled.push_back(ControllerType::kCpuset);
        } else if (token == "hugetlb") {
            enabled.push_back(ControllerType::kHugetlb);
        } else if (token == "rdma") {
            enabled.push_back(ControllerType::kRdma);
        } else if (token == "misc") {
            enabled.push_back(ControllerType::kMisc);
        }
    }
    
    return enabled;
}

// ============================================================================
// Helper: Get global cgroup statistics from /sys/fs/cgroup/cgroup.stat
//
// Format:
//   nr_descendants 321
//   nr_dying_descendants 73
// ============================================================================
static CGroupStatistics read_global_stats() {
    CGroupStatistics stats;
    
    std::ifstream file("/sys/fs/cgroup/cgroup.stat");
    if (!file.is_open()) {
        return stats;  // Return defaults on error
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        int64_t value;
        
        if (iss >> key >> value) {
            if (key == "nr_descendants") {
                stats.nr_descendants = value;
            } else if (key == "nr_dying_descendants") {
                stats.nr_dying_descendants = value;
            }
        }
    }
    
    stats.captured_at = std::chrono::system_clock::now();
    return stats;
}

// ============================================================================
// Helper: Get controller availability for a cgroup directory
//
// Returns the list of controllers available for this specific cgroup.
// ============================================================================
static CGroupControllerInfo get_cgroup_controllers(const std::filesystem::path& path) {
    CGroupControllerInfo info;
    
    auto controllers_file = path / "cgroup.controllers";
    if (!std::filesystem::exists(controllers_file)) {
        return info;  // Return empty on error
    }
    
    std::ifstream file(controllers_file);
    if (!file.is_open()) {
        return info;
    }
    
    // Read all content
    std::stringstream buffer;
    buffer << file.rdbuf();
    auto content = buffer.str();
    
    info.enabled = parse_controllers(content);
    info.available = info.enabled;  // For this adapter, available == enabled
    
    return info;
}

// ============================================================================
// Helper: Get statistics for a specific cgroup
//
// Reads from /sys/fs/cgroup/<path>/cgroup.stat if available.
// ============================================================================
static CGroupStatistics get_cgroup_stats(const std::filesystem::path& path) {
    CGroupStatistics stats;
    
    // Note: cgroup.stat files are typically only at the root level in cgroup v2
    // Per-cgroup statistics require reading controller-specific files like:
    //   - memory.current for memory controller
    //   - cpu.stat for cpu controller
    
    std::ifstream file(path / "cgroup.stat");
    if (!file.is_open()) {
        stats.captured_at = std::chrono::system_clock::now();
        return stats;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        int64_t value;
        
        if (iss >> key >> value) {
            if (key == "nr_descendants") {
                stats.nr_descendants = value;
            } else if (key == "nr_dying_descendants") {
                stats.nr_dying_descendants = value;
            }
        }
    }
    
    // Try to read controller-specific stats
    std::ifstream memory_file(path / "memory.current");
    if (memory_file.is_open()) {
        int64_t val;
        if (memory_file >> val) {
            stats.memory_current_bytes = val;
        }
    }
    
    stats.captured_at = std::chrono::system_clock::now();
    return stats;
}

// ============================================================================
// Helper: Get parent path from cgroup path
//
// For example:
//   "/system.slice/ssh.service" -> "/"
//   "/user.slice/user-1000.slice" -> "/"
//   "/" -> std::nullopt (root has no parent)
// ============================================================================
static std::optional<std::string> get_parent_path(const std::string& path) {
    if (path.empty() || path == "/") {
        return std::nullopt;
    }
    
    // Find the last slash
    size_t last_slash = path.rfind('/');
    if (last_slash == 0) {
        // Direct child of root, parent is "/"
        return "/";
    } else if (last_slash != std::string::npos && last_slash > 0) {
        return path.substr(0, last_slash);
    }
    
    return std::nullopt;
}

// ============================================================================
// Helper: Check if a cgroup is a leaf (has no children)
//
// A cgroup is a leaf if nr_descendants == 0.
// ============================================================================
static bool is_leaf_cgroup(const CGroupStatistics& stats) {
    return stats.nr_descendants == 0;
}

// ============================================================================
// Helper: Calculate hierarchy depth for a path
//
// "/" has depth 0
// "/system.slice" has depth 1
// "/system.slice/ssh.service" has depth 2
// ============================================================================
static int calculate_depth(const std::string& path) {
    if (path.empty() || path == "/") return 0;
    
    int depth = 0;
    for (char c : path) {
        if (c == '/') depth++;
    }
    // Subtract 1 because root "/" has no depth
    return depth > 0 ? depth - 1 : 0;
}

// ============================================================================
// CGroupHierarchyAdapter Implementation
// ============================================================================

class CGroupHierarchyAdapterImpl : public CGroupHierarchyAdapter {
public:
    CGroupHierarchyAdapterImpl() = default;
    ~CGroupHierarchyAdapterImpl() override = default;
    
    CGroupHierarchyResult observe_hierarchy() override {
        CGroupHierarchyResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Read global statistics first
        result.global_statistics = read_global_stats();
        
        // Scan /sys/fs/cgroup for cgroups
        if (!scan_cgroup_hierarchy(result)) {
            result.status = core::SemanticStatus::kFailure;
            result.description = "Failed to scan cgroup hierarchy";
            result.error = core::Error{"E_CGROUP_SCAN_FAILED", "Cannot read cgroup filesystem"};
            return result;
        }
        
        // Build hierarchy graph
        result.hierarchy = build_hierarchy_graph(result.cgroups);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.total_cgroups = result.cgroups.size();
        result.provider_source = "cgroupfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed cgroup hierarchy";
        
        return result;
    }
    
    std::optional<CGroupObservation> observe_cgroup(std::string_view path) override {
        auto all_cgroups = observe_hierarchy();
        
        if (all_cgroups.status != core::SemanticStatus::kSuccess) {
            return std::nullopt;
        }
        
        for (const auto& cgroup : all_cgroups.cgroups) {
            if (cgroup.identity.path == path) {
                return cgroup;
            }
        }
        
        return std::nullopt;
    }
    
    CGroupHierarchy get_hierarchy() override {
        auto result = observe_hierarchy();
        if (result.status == core::SemanticStatus::kSuccess && result.hierarchy) {
            // Copy the hierarchy and ensure global_statistics is populated
            CGroupHierarchy hierarchy = *result.hierarchy;
            hierarchy.global_statistics = result.global_statistics;
            return hierarchy;
        }
        return CGroupHierarchy{};
    }
    
    std::optional<std::string> resolve_parent(std::string_view path) override {
        return get_parent_path(std::string(path));
    }

private:
    // Global statistics cache (updated on each observation)
    CGroupStatistics global_stats_;
    
    bool scan_cgroup_hierarchy(CGroupHierarchyResult& result) {
        std::filesystem::path cgroup_root("/sys/fs/cgroup");
        
        if (!std::filesystem::exists(cgroup_root)) {
            return false;
        }
        
        // Use recursive directory iterator to traverse the hierarchy
        try {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(
                    cgroup_root, std::filesystem::directory_options::skip_permission_denied)) {
                
                if (!entry.is_directory()) continue;
                
                // Skip . and .. directories
                auto path_str = entry.path().string();
                if (path_str == cgroup_root.string() || 
                    path_str == cgroup_root.string() + "/.") {
                    continue;
                }
                
                // Get relative path from root
                std::filesystem::path rel_path = entry.path();
                
                CGroupObservation observation;
                observation.identity.path = rel_path.string();
                observation.identity.id = -1;  // No kernel ID available without additional APIs
                
                // Get parent path
                auto parent = get_parent_path(observation.identity.path);
                if (parent) {
                    observation.parent_path = *parent;
                }
                
                // Get controller availability
                observation.controllers = get_cgroup_controllers(entry.path());
                
                // Get statistics
                observation.statistics = get_cgroup_stats(entry.path());
                
                // Set timestamps
                observation.observed_at = std::chrono::system_clock::now();
                observation.source = "cgroupfs";
                
                result.cgroups.push_back(std::move(observation));
            }
        } catch (const std::filesystem::filesystem_error& e) {
            return false;
        }
        
        // Sort by path to ensure consistent ordering
        std::sort(result.cgroups.begin(), result.cgroups.end(),
                  [](const CGroupObservation& a, const CGroupObservation& b) {
                      return a.identity.path < b.identity.path;
                  });
        
        return !result.cgroups.empty();
    }
    
    CGroupHierarchy build_hierarchy_graph(const std::vector<CGroupObservation>& cgroups) {
        CGroupHierarchy hierarchy;
        hierarchy.captured_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Index all cgroups by path
        for (const auto& c : cgroups) {
            hierarchy.cgroups_by_path[c.identity.path] = c;
            
            int depth = calculate_depth(c.identity.path);
            if (depth > hierarchy.max_depth) {
                hierarchy.max_depth = depth;
            }
        }
        
        // Build parent-child relationships
        for (const auto& [path, cgroup] : hierarchy.cgroups_by_path) {
            if (cgroup.parent_path) {
                hierarchy.children_by_parent[*cgroup.parent_path].push_back(path);
                
                // Check if this is a root path (direct child of /)
                if (*cgroup.parent_path == "/") {
                    hierarchy.root_paths.push_back(path);
                }
            } else {
                // No parent = root
                hierarchy.root_paths.push_back(path);
            }
        }
        
        // Calculate leaf cgroups and statistics
        for (const auto& [path, cgroup] : hierarchy.cgroups_by_path) {
            if (is_leaf_cgroup(cgroup.statistics)) {
                hierarchy.leaf_cgroups++;
            }
            
            if (cgroup.parent_path && !hierarchy.children_by_parent.count(path)) {
                // This cgroup has children (in the parent's list) but no entry as a key
                // meaning it doesn't appear in children_by_parent, which shouldn't happen
            }
        }
        
        // Set total_cgroups from the number of entries we indexed
        hierarchy.total_cgroups = hierarchy.cgroups_by_path.size();
        
        // Set global statistics from result (already populated in observe_hierarchy)
        hierarchy.global_statistics = global_stats_;
        
        auto end_time = std::chrono::steady_clock::now();
        hierarchy.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        return hierarchy;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<CGroupHierarchyAdapter> make_cgroup_hierarchy_adapter() {
    return std::make_unique<CGroupHierarchyAdapterImpl>();
}

}  // namespace rebuntu::adapters::cgroups::hierarchy