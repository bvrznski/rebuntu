// rebuntu::adapters::procfs::mounts — Procfs Mounts Observation Implementation (Phase 5.17)
//
// This module implements the procfs-based filesystem observation adapter:
//   - Reads mount information from /proc/self/mountinfo
//   - Observes: source identity, target (mountpoint), filesystem type, options
//   - Capacity observation via statvfs(2) for mounted filesystems

#include "adapters/procfs/mounts/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstring>
#include <sys/statvfs.h>

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
// ProcfsMountsAdapter Implementation
// ============================================================================

class ProcfsMountsAdapter : public MountsAdapter {
public:
    ProcfsMountsAdapter() = default;
    ~ProcfsMountsAdapter() override = default;
    
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
        
        std::string line;
        while (std::getline(file, line)) {
            auto mount = parse_mount_line(line);
            if (mount) {
                // Try to get capacity for this mount
                auto capacity = get_filesystem_capacity(mount->identity.mountpoint);
                if (capacity) {
                    mount->capacity = std::move(*capacity);
                } else {
                    result.capacity_failures++;
                }
                
                result.mounts.push_back(std::move(*mount));
            }
        }
        
        file.close();
        
        // Sort mounts by mountpoint for consistent ordering
        std::sort(result.mounts.begin(), result.mounts.end(),
            [](const MountObservation& a, const MountObservation& b) {
                return a.identity.mountpoint < b.identity.mountpoint;
            });
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.total_mounts = result.mounts.size();
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

private:
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
        
        // Parse mount ID and parent ID (parent_id stored in observation)
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
                // Some mounts don't have device numbers (e.g., tmpfs, nfs)
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
        
        // Parse options (field 5)
        auto options_str = unescape_mountinfo(fields[6]);
        observation.options = split_string(options_str, ',');
        
        // Skip separator field "-" and parse filesystem type and source
        size_t dash_pos = std::distance(fields.begin(), 
            std::find(fields.begin(), fields.end(), "-"));
        if (dash_pos == fields.size() || dash_pos + 2 >= fields.size()) {
            return std::nullopt;
        }
        
        observation.filesystem_type = unescape_mountinfo(fields[dash_pos + 1]);
        observation.identity.source = unescape_mountinfo(fields[dash_pos + 2]);
        
        // Set provenance
        observation.observed_at = std::chrono::system_clock::now();
        observation.source = "procfs";
        
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