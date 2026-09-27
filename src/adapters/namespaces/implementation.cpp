// rebuntu::adapters::namespaces — Linux Namespace Discovery Implementation (Phase 5.29)
//
// This module implements the namespace observation adapter:
//   - Reads namespace relationships from /proc/[pid]/ns/
//   - Observes: namespace type, inode number, process-to-namespace bindings
//   - Provides bounded facts where available

#include "adapters/namespaces/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

namespace rebuntu::adapters::namespaces {

// ============================================================================
// Helper: Parse namespace type from symlink name
// ============================================================================
static NamespaceType parse_namespace_type(const std::string& symlink_name) {
    if (symlink_name == "cgroup") return NamespaceType::kCgroup;
    if (symlink_name == "uts")    return NamespaceType::kUts;
    if (symlink_name == "ipc")    return NamespaceType::kIpc;
    if (symlink_name == "pid")    return NamespaceType::kPid;
    if (symlink_name == "net")    return NamespaceType::kNet;
    if (symlink_name == "mnt")    return NamespaceType::kMnt;
    if (symlink_name == "user")   return NamespaceType::kUser;
    if (symlink_name == "time")   return NamespaceType::kTime;
    return NamespaceType::kUnknown;
}

// ============================================================================
// Helper: Read inode number from namespace symlink path
// Returns 0 on failure
// ============================================================================
static uint64_t read_namespace_inode(const std::string& ns_path) {
    struct stat st;
    if (stat(ns_path.c_str(), &st) != 0) {
        return 0;
    }
    return static_cast<uint64_t>(st.st_ino);
}

// ============================================================================
// Helper: Read namespace symlink target to extract type and inode
// Format is "ns/[type]: [inode]" e.g., "ns/pid: [4026531836]"
// Returns false on failure
// ============================================================================
static bool parse_namespace_from_symlink(const std::string& ns_path,
                                         NamespaceType& type_out,
                                         uint64_t& inode_out) {
    char buffer[256];
    ssize_t len = readlink(ns_path.c_str(), buffer, sizeof(buffer) - 1);
    
    if (len <= 0) {
        return false;
    }
    
    buffer[len] = '\0';
    std::string target(buffer);
    
    // Expected format: "ns/[type]: [inode]"
    size_t colon_pos = target.find(':');
    if (colon_pos == std::string::npos) {
        return false;
    }
    
    // Extract the ns/type part
    std::string ns_part = target.substr(0, colon_pos);
    // Remove leading "ns/" prefix
    if (ns_part.size() > 3 && ns_part.substr(0, 3) == "ns/") {
        std::string type_str = ns_part.substr(3);
        type_out = parse_namespace_type(type_str);
    } else {
        return false;
    }
    
    // Extract inode number
    try {
        size_t inode_start = target.find_first_of("0123456789", colon_pos);
        if (inode_start != std::string::npos) {
            inode_out = std::stoull(target.substr(inode_start));
        } else {
            return false;
        }
    } catch (...) {
        return false;
    }
    
    return type_out != NamespaceType::kUnknown && inode_out > 0;
}

// ============================================================================
// Helper: Get list of all PIDs from /proc
// Returns sorted vector of PIDs
// ============================================================================
static std::vector<int> get_all_pids() {
    std::vector<int> pids;
    
    DIR* proc_dir = opendir("/proc");
    if (proc_dir == nullptr) {
        return pids;
    }
    
    struct dirent* entry;
    while ((entry = readdir(proc_dir)) != nullptr) {
        // Check if it's a numeric PID
        const char* name = entry->d_name;
        bool is_pid = name[0] != '\0';
        
        for (size_t i = 0; is_pid && name[i] != '\0'; ++i) {
            if (!isdigit(static_cast<unsigned char>(name[i]))) {
                is_pid = false;
            }
        }
        
        if (is_pid) {
            try {
                pids.push_back(std::stoi(entry->d_name));
            } catch (...) {
                // Skip invalid entries
            }
        }
    }
    
    closedir(proc_dir);
    
    // Sort for deterministic iteration
    std::sort(pids.begin(), pids.end());
    
    return pids;
}

// ============================================================================
// NamespaceDiscoveryAdapter Implementation
// ============================================================================

class NamespaceDiscoveryAdapterImpl : public NamespaceDiscoveryAdapter {
public:
    NamespaceDiscoveryAdapterImpl() = default;
    ~NamespaceDiscoveryAdapterImpl() override = default;
    
    NamespaceDiscoveryResult observe_all_namespaces() override {
        NamespaceDiscoveryResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Get all PIDs
        std::vector<int> pids = get_all_pids();
        result.total_processes_observed = pids.size();
        
        // Maps to track namespaces and their members
        std::map<NamespaceIdentity, NamespaceObservation> namespace_map;
        std::unordered_map<int, std::vector<NamespaceRelationship>> process_namespaces_map;
        
        for (int pid : pids) {
            std::string proc_ns_path = "/proc/" + std::to_string(pid) + "/ns";
            
            DIR* ns_dir = opendir(proc_ns_path.c_str());
            if (ns_dir == nullptr) {
                // Process may have terminated
                continue;
            }
            
            std::vector<NamespaceRelationship> relationships;
            
            struct dirent* entry;
            while ((entry = readdir(ns_dir)) != nullptr) {
                std::string name = entry->d_name;
                
                // Skip . and ..
                if (name == "." || name == "..") continue;
                
                std::string ns_symlink_path = proc_ns_path + "/" + name;
                
                NamespaceType type{NamespaceType::kUnknown};
                uint64_t inode_number{0};
                
                if (!parse_namespace_from_symlink(ns_symlink_path, type, inode_number)) {
                    result.errors.emplace_back(ns_symlink_path, core::Error{
                        "E_PARSE_FAILURE",
                        "Failed to parse namespace from symlink"
                    });
                    continue;
                }
                
                NamespaceIdentity identity{type, inode_number};
                
                // Add this process as a member of the namespace
                auto& ns_obs = namespace_map[identity];
                if (ns_obs.identity.inode_number == 0) {
                    ns_obs.identity = identity;
                    ns_obs.source = "procfs";
                }
                ns_obs.member_pids.push_back(pid);
                
                // Record process-to-namespace relationship
                relationships.emplace_back();
                auto& rel = relationships.back();
                rel.namespace_identity = identity;
                rel.symlink_path = ns_symlink_path;
            }
            
            closedir(ns_dir);
            
            if (!relationships.empty()) {
                process_namespaces_map[pid] = std::move(relationships);
            }
        }
        
        // Convert maps to vectors
        result.namespaces.reserve(namespace_map.size());
        for (auto& [identity, obs] : namespace_map) {
            result.namespaces.push_back(std::move(obs));
            
            // Update statistics by type
            switch (identity.type) {
                case NamespaceType::kCgroup:  result.cgroup_namespaces++; break;
                case NamespaceType::kUts:     result.uts_namespaces++;    break;
                case NamespaceType::kIpc:     result.ipc_namespaces++;    break;
                case NamespaceType::kPid:     result.pid_namespaces++;    break;
                case NamespaceType::kNet:     result.net_namespaces++;    break;
                case NamespaceType::kMnt:     result.mnt_namespaces++;    break;
                case NamespaceType::kUser:    result.user_namespaces++;   break;
                case NamespaceType::kTime:    result.time_namespaces++;   break;
                default:                      break;
            }
        }
        
        result.total_namespaces = namespace_map.size();
        result.process_namespaces = std::move(process_namespaces_map);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.provider_source = "procfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully discovered namespaces from /proc/[pid]/ns/";
        
        // Cache observation time
        last_observation_time_ = result.observed_at;
        
        return result;
    }
    
    std::optional<NamespaceObservation> observe_namespace(
        const NamespaceIdentity& identity) override {
        // This would require searching all processes to find which ones share this namespace
        // For simplicity, we return an empty observation (the data is available via observe_all_namespaces)
        return std::nullopt;
    }
    
    std::vector<int> get_namespace_members(NamespaceType type, uint64_t inode_number) override {
        // This method requires re-observing or caching the results
        // For now, we perform a quick scan
        std::vector<int> members;
        
        auto result = observe_all_namespaces();
        if (result.status == core::SemanticStatus::kSuccess) {
            for (const auto& obs : result.namespaces) {
                if (obs.identity.type == type && obs.identity.inode_number == inode_number) {
                    return obs.member_pids;
                }
            }
        }
        
        return members;
    }
    
    bool processes_share_namespace(int pid1, int pid2, NamespaceType type) override {
        std::string ns_path1 = "/proc/" + std::to_string(pid1) + "/ns/" + to_string(type);
        std::string ns_path2 = "/proc/" + std::to_string(pid2) + "/ns/" + to_string(type);
        
        uint64_t inode1 = read_namespace_inode(ns_path1);
        uint64_t inode2 = read_namespace_inode(ns_path2);
        
        return inode1 > 0 && inode1 == inode2;
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }
    
    NamespaceDiscoveryResult force_refresh() override {
        // Clear cache and perform fresh observation
        last_observation_time_ = {};
        return observe_all_namespaces();
    }

private:
    std::chrono::system_clock::time_point last_observation_time_{};
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<NamespaceDiscoveryAdapter> make_namespace_discovery_adapter() {
    return std::make_unique<NamespaceDiscoveryAdapterImpl>();
}

}  // namespace rebuntu::adapters::namespaces