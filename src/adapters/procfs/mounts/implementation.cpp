// rebuntu::adapters::procfs::mounts — Procfs Mounts Observation Implementation (Phase 5.17)
// Mount Topology extension (Phase 5.18)
//
// This module implements the procfs-based filesystem observation adapter:
//   - Reads mount information from /proc/self/mountinfo
//   - Observes: source identity, target (mountpoint), filesystem type, options
//   - Capacity observation via statvfs(2) for mounted filesystems
//   - Topology: layered relationships (bind/overlay/network mounts)

#include "adapters/procfs/mounts/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstring>
#include <sys/statvfs.h>

// C++20 includes for string_view and optional
#include <string_view>
#include <optional>

namespace rebuntu::adapters::procfs::mounts {

// ============================================================================
// Helper: Escape sequences in mountinfo (octal to character)
// ============================================================================

static std::string unescape_mountinfo(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '\\' && i + 3 < input.size()) {
            // Check for octal escape sequence
            char c1 = input[i + 1];
            char c2 = input[i + 2];
            char c3 = input[i + 3];
            
            if (c1 >= '0' && c1 <= '7' &&
                c2 >= '0' && c2 <= '7' &&
                c3 >= '0' && c3 <= '7') {
                // Convert octal to character
                int value = (c1 - '0') * 64 + (c2 - '0') * 8 + (c3 - '0');
                result += static_cast<char>(value);
                i += 3;
            } else {
                result += input[i];
            }
        } else {
            result += input[i];
        }
    }
    
    return result;
}

// ============================================================================
// Helper: Split string by delimiter
// ============================================================================

static std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    
    while (std::getline(iss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

// ============================================================================
// Helper: Check if mount has option
// ============================================================================

static bool has_option(const std::vector<std::string>& options, std::string_view option) {
    for (const auto& opt : options) {
        // Handle options like "rw" vs "ro" - just check prefix
        if (opt == option || 
            (option.size() < opt.size() && opt.substr(0, option.size()) == option)) {
            return true;
        }
    }
    return false;
}

// ============================================================================
// Helper: Extract overlay/upper/lower layer info from mount options
// ============================================================================

static void parse_overlay_options(const std::vector<std::string>& options,
                                   MountRelationship& relationship) {
    for (const auto& opt : options) {
        // Overlay-specific options
        if (opt.starts_with("upperdir=")) {
            relationship.overlay_layers.push_back(opt.substr(9));
            relationship.relationship_type = MountTopologyType::kOverlay;
        } else if (opt.starts_with("workdir=")) {
            // workdir is part of overlay, already marked as overlay
        } else if (opt.starts_with("lowerdir=")) {
            // Extract lower directories (may be comma-separated)
            std::string lower_val = opt.substr(9);
            auto layers = split_string(lower_val, ',');
            relationship.overlay_layers.insert(relationship.overlay_layers.end(),
                                                layers.begin(), layers.end());
        } else if (opt.starts_with("redirect_dir=")) {
            // Overlay redirect dir
        }
    }
}

// ============================================================================
// Helper: Detect mount type from filesystem type and options
// ============================================================================

static MountTopologyType detect_topology_type(
    std::string_view fs_type,
    const std::vector<std::string>& options) {
    
    // Special filesystems (in-memory, virtual)
    if (fs_type == "tmpfs" || fs_type == "proc" || fs_type == "sysfs" ||
        fs_type == "devpts" || fs_type == "cgroup" || fs_type == "cgroup2" ||
        fs_type == "configfs" || fs_type == "securityfs" ||
        fs_type == "efivarfs" || fs_type == "bpf") {
        return MountTopologyType::kSpecial;
    }
    
    // Network filesystems
    if (fs_type == "nfs" || fs_type == "nfs4" || fs_type == "cifs" ||
        fs_type == "smbfs" || fs_type.starts_with("sshfs") ||
        fs_type.starts_with("fuse.sshfs")) {
        return MountTopologyType::kNetwork;
    }
    
    // Check for bind mount option
    if (has_option(options, "bind") || has_option(options, "rbind")) {
        return MountTopologyType::kBind;
    }
    
    // Check if it's an overlay filesystem type
    if (fs_type == "overlay" || fs_type == "overlayfs") {
        return MountTopologyType::kOverlay;
    }
    
    // Check for bind mount of overlay (bind mounted from /overlay or similar)
    // This is determined by parent relationship in the full implementation
    
    // Default to primary
    return MountTopologyType::kPrimary;
}

// ============================================================================
// Helper: Get filesystem capacity using statvfs
// ============================================================================

static std::optional<FilesystemCapacity> get_filesystem_capacity(std::string_view mountpoint) {
    FilesystemCapacity capacity;
    
    struct statvfs stat;
    if (statvfs(std::string(mountpoint).c_str(), &stat) != 0) {
        return std::nullopt;
    }
    
    // Block-based information
    capacity.block_size = stat.f_frsize;
    capacity.total_blocks = stat.f_blocks;
    capacity.free_blocks = stat.f_bfree;
    capacity.available_blocks = stat.f_bavail;
    capacity.used_blocks = capacity.total_blocks - capacity.free_blocks;
    
    // Inode information
    capacity.total_inodes = stat.f_files;
    capacity.free_inodes = stat.f_ffree;
    capacity.used_inodes = capacity.total_inodes - capacity.free_inodes;
    
    // Byte-based calculations (for human-readable output)
    capacity.capacity_bytes = static_cast<uint64_t>(stat.f_frsize) * stat.f_blocks;
    capacity.available_bytes = static_cast<uint64_t>(stat.f_frsize) * stat.f_bavail;
    capacity.used_bytes = capacity.capacity_bytes - capacity.available_bytes;
    
    capacity.captured_at = std::chrono::system_clock::now();
    
    return capacity;
}

// ============================================================================
// Helper: Parse mount relationship info from mountinfo line
//
// The format is:
// 36 35 98:0 /mnt1 /mnt2 rw,noatime master:1 - ext3 /dev/sda1 rw,errors=continue
//  *  *  *    *     *     *          *      *   *    *       *
//  0  1  2    3     4     5          6      7   8    9       10+
//
// Fields after "-" contain optional filesystem-specific data
// ============================================================================

static void parse_mount_relationship(
    const std::vector<std::string>& fields,
    MountRelationship& relationship) {
    
    // Find the separator field "-"
    auto it = std::find(fields.begin(), fields.end(), "-");
    if (it == fields.end()) {
        return;
    }
    
    size_t dash_idx = std::distance(fields.begin(), it);
    
    // After "-", we have: fs_type source [optional super_opts]
    // e.g., ext3 /dev/sda1 rw,errors=continue
    // or nfs server:/export rw,vers=4.2
    
    if (dash_idx + 1 < fields.size()) {
        relationship.base_source = unescape_mountinfo(fields[dash_idx + 2]);  // source field
        
        // Detect topology type from fs_type and options
        std::string fs_type = unescape_mountinfo(fields[dash_idx + 1]);
        
        // Get mount-specific options (after the source)
        if (dash_idx + 3 < fields.size()) {
            auto super_opts_str = unescape_mountinfo(fields[dash_idx + 3]);
            auto super_opts = split_string(super_opts_str, ',');
            
            // Check for overlay options
            parse_overlay_options(super_opts, relationship);
            
            // If not already detected as overlay, check for bind
            if (relationship.relationship_type == MountTopologyType::kPrimary) {
                if (has_option(super_opts, "bind") || has_option(super_opts, "rbind")) {
                    relationship.relationship_type = MountTopologyType::kBind;
                }
                
                // Network filesystems
                if (fs_type == "nfs" || fs_type == "nfs4" || fs_type == "cifs" ||
                    fs_type.starts_with("sshfs") || fs_type.starts_with("fuse.sshfs")) {
                    relationship.relationship_type = MountTopologyType::kNetwork;
                }
                
                // Special filesystems
                if (fs_type == "tmpfs" || fs_type == "proc" || fs_type == "sysfs" ||
                    fs_type == "devpts" || fs_type == "cgroup" || fs_type == "cgroup2") {
                    relationship.relationship_type = MountTopologyType::kSpecial;
                }
            }
        }
    }
}

// ============================================================================
// ProcfsMountsAdapter Implementation
// ============================================================================

class ProcfsMountsAdapter : public MountsAdapter {
public:
    ProcfsMountsAdapter() = default;
    ~ProcfsMountsAdapter() override = default;
    
    // Get freshness: timestamp of the last observation
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return last_observation_time_;
    }
    
    MountObservationResult force_refresh() override {
        auto result = observe_mounts();
        if (result.status == core::SemanticStatus::kSuccess) {
            last_observation_time_ = std::chrono::system_clock::now();
        }
        return result;
    }
    
    MountObservationResult observe_mounts() override {
        MountObservationResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        std::ifstream file("/proc/self/mountinfo");
        if (!file.is_open()) {
            result.status = core::SemanticStatus::kFailure;
            result.description = "Failed to open /proc/self/mountinfo";
            result.error = core::Error{"E_MOUNTINFO_UNAVAILABLE", "Cannot read mount table"};
            return result;
        }
        
        // First pass: collect all mounts with their parent relationships
        std::vector<std::optional<MountObservation>> temp_mounts;
        std::unordered_map<int, size_t> id_to_index;
        
        std::string line;
        while (std::getline(file, line)) {
            auto mount = parse_mount_line(line);
            if (mount) {
                // Extract basic topology information
                // This uses only filesystem type and options - no graph analysis needed yet
                
                // Detect relationship type from filesystem type and options
                auto topo_type = detect_topology_type(mount->filesystem_type, mount->options);
                
                if (topo_type != MountTopologyType::kPrimary) {
                    mount->relationship.relationship_type = topo_type;
                    
                    if (topo_type == MountTopologyType::kSpecial) {
                        mount->isnodev = true;
                    }
                }
                
                // Check for bind option in mount options
                mount->isbind = has_option(mount->options, "bind");
                
                temp_mounts.push_back(std::move(*mount));
            }
        }
        
        file.close();
        
        // Second pass: build relationship graph and assign relationships to children
        // We use parent_id from mountinfo to link mounts together
        for (size_t i = 0; i < temp_mounts.size(); ++i) {
            if (!temp_mounts[i]) continue;
            
            auto& m = *temp_mounts[i];
            int pid = m.parent_id;
            
            // Find parent in our list
            if (pid > 0 && id_to_index.count(pid)) {
                size_t parent_idx = id_to_index[pid];
                if (parent_idx < temp_mounts.size() && temp_mounts[parent_idx]) {
                    auto& parent = *temp_mounts[parent_idx];
                    
                    // If parent has overlay as relationship, and this mount
                    // is a bind of the same source, mark it as kBindOverlay
                    if (parent.relationship.relationship_type == MountTopologyType::kOverlay &&
                        m.identity.source == parent.identity.source) {
                        m.relationship.relationship_type = MountTopologyType::kBindOverlay;
                    }
                    
                    // Add to children map
                    children_map_[pid].push_back(m.parent_id);
                }
            }
            
            id_to_index[m.identity.minor] = i;  // Use minor as unique ID if needed
        }
        
        // Build the result
        for (const auto& mount : temp_mounts) {
            if (mount) {
                result.mounts.push_back(std::move(*mount));
                
                // Try to get capacity for this mount
                auto capacity = get_filesystem_capacity(result.mounts.back().identity.mountpoint);
                if (capacity) {
                    result.mounts.back().capacity = std::move(*capacity);
                } else {
                    result.capacity_failures++;
                }
            }
        }
        
        // Build topology graph
        result.topology = build_topology_graph(result.mounts);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.total_mounts = result.mounts.size();
        result.provider_source = "procfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed filesystem mounts";
        
        return result;
    }
    
    std::optional<MountObservation> observe_mount(std::string_view mountpoint) override {
        auto all_mounts = observe_mounts();
        
        if (all_mounts.status != core::SemanticStatus::kSuccess) {
            return std::nullopt;
        }
        
        for (const auto& mount : all_mounts.mounts) {
            if (mount.identity.mountpoint == mountpoint) {
                return mount;
            }
        }
        
        return std::nullopt;
    }
    
    MountTopology get_topology() override {
        auto result = observe_mounts();
        if (result.topology) {
            return *std::move(result.topology);
        }
        return MountTopology{};
    }
    
    std::optional<std::pair<int, MountIdentity>> resolve_to_source(int mount_id) override {
        // For now, return the identity of this mount
        // A full implementation would traverse parent relationships to find
        // the base source (for bind mounts, find what's being bound)
        
        auto topology = get_topology();
        if (topology.mounts_by_id.count(mount_id)) {
            return std::make_pair(mount_id, topology.mounts_by_id[mount_id].identity);
        }
        return std::nullopt;
    }

private:
    MountTopology build_topology_graph(const std::vector<MountObservation>& mounts) {
        MountTopology topology;
        topology.captured_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Index mounts by ID
        for (const auto& m : mounts) {
            // Use minor:minor as unique identifier, or create a synthetic ID
            int mount_id = (m.identity.major << 16) | (m.identity.minor & 0xFFFF);
            if (mount_id == 0 && m.parent_id != -1) {
                mount_id = m.parent_id + 1;  // Fallback for non-device mounts
            }
            
            auto mount_copy = m;
            mount_copy.relationship.parent_mount_id = m.parent_id;
            topology.mounts_by_id[mount_id] = std::move(mount_copy);
        }
        
        // Build parent-child relationships
        for (const auto& [id, m] : topology.mounts_by_id) {
            if (m.parent_id == 0 || m.parent_id == id) {
                topology.root_mount_ids.push_back(id);
            } else {
                children_map_[m.parent_id].push_back(id);
                topology.children_by_parent[m.parent_id].push_back(id);
            }
        }
        
        // Count by topology type
        for (const auto& [id, m] : topology.mounts_by_id) {
            switch (m.relationship.relationship_type) {
                case MountTopologyType::kPrimary:
                    topology.primary_mounts++;
                    break;
                case MountTopologyType::kBind:
                    topology.bind_mounts++;
                    break;
                case MountTopologyType::kOverlay:
                    topology.overlay_mounts++;
                    break;
                case MountTopologyType::kNetwork:
                    topology.network_mounts++;
                    break;
                case MountTopologyType::kSpecial:
                    topology.special_mounts++;
                    break;
                case MountTopologyType::kBindOverlay:
                    topology.bind_mounts++;  // Count as bind
                    break;
            }
            topology.total_mounts++;
        }
        
        auto end_time = std::chrono::steady_clock::now();
        topology.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        return topology;
    }
    
    // Map for building parent-child relationships
    std::unordered_map<int, std::vector<int>> children_map_;
    
    // Last observation timestamp for freshness tracking (mutable to allow updates in const methods)
    std::chrono::system_clock::time_point last_observation_time_{};
    
    static std::optional<MountObservation> parse_mount_line(const std::string& line) {
        // Format from /proc/self/mountinfo:
        // 36 35 98:0 /mnt1 /mnt2 rw,noatime master:1 - ext3 /dev/sda1 rw,errors=continue
        //  *  *  *    *     *     *          *      *   *    *       *
        //  0  1  2    3     4     5          6      7   8    9       10+
        
        std::istringstream iss(line);
        std::vector<std::string> fields;
        std::string field;
        
        while (iss >> field) {
            fields.push_back(field);
        }
        
        if (fields.size() < 10) {
            return std::nullopt;
        }
        
        // Parse mount ID and parent ID
        int parent_id = 0;
        try {
            parent_id = std::stoi(fields[1]);
        } catch (...) {
            return std::nullopt;
        }
        
        // Parse major:minor device number
        int major = -1, minor = -1;
        size_t colon_pos = fields[2].find(':');
        if (colon_pos != std::string::npos) {
            try {
                major = std::stoi(fields[2].substr(0, colon_pos));
                minor = std::stoi(fields[2].substr(colon_pos + 1));
            } catch (...) {
                // Some mounts don't have device numbers
            }
        }
        
        MountObservation observation;
        
        // Set parent ID (from mountinfo, used for understanding mount hierarchy)
        observation.parent_id = parent_id;
        
        // Identity
        observation.identity.major = major;
        observation.identity.minor = minor;
        observation.identity.source = unescape_mountinfo(fields[3]);  // Root of mount tree
        observation.identity.mountpoint = unescape_mountinfo(fields[4]);  // Mount point
        
        // Parse options (field 5 after root)
        auto options_str = unescape_mountinfo(fields[6]);
        observation.options = split_string(options_str, ',');
        
        // Skip separator field "-" and parse filesystem type and source
        size_t dash_pos = std::distance(fields.begin(), 
            std::find(fields.begin(), fields.end(), "-"));
        if (dash_pos == fields.size() || dash_pos + 2 >= fields.size()) {
            return std::nullopt;
        }
        
        observation.filesystem_type = unescape_mountinfo(fields[dash_pos + 1]);
        // Update source from the actual mount source field
        observation.identity.source = unescape_mountinfo(fields[dash_pos + 2]);
        
        // Parse relationship info (filesystem-specific options after source)
        parse_mount_relationship(fields, observation.relationship);
        
        // Note: Topology info is extracted in a separate pass after parsing all mounts
        // This is done in the main observe_mounts() method which has access to 'this'
        
        // Set provenance
        observation.observed_at = std::chrono::system_clock::now();
        observation.source = "procfs";
        observation.relationship.provenance_source = "procfs";
        
        return observation;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<MountsAdapter> make_procfs_mounts_adapter() {
    return std::make_unique<ProcfsMountsAdapter>();
}

}  // namespace rebuntu::adapters::procfs::mounts