// Rebuntu Path Safety Library Implementation (Phase 6.59)
//
// Implementation of path safety validation for filesystem operations.

#include "path_safety.hpp"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

namespace rebuntu::path_safety {

namespace fs = std::filesystem;

// ============================================================================
// Path Syntax Validation
// ============================================================================

SafetyCheckResult validate_path_syntax(const fs::path& path) {
    SafetyCheckResult result;
    
    // Convert to string for analysis
    auto path_str = path.string();
    
    // Check for empty path
    if (path_str.empty()) {
        return SafetyCheckResult::failed("empty path");
    }
    
    // Check for null bytes in path (security risk)
    if (path_str.find('\0') != std::string::npos) {
        return SafetyCheckResult::failed("path contains null byte");
    }
    
    // Check for control characters
    for (char c : path_str) {
        if (c < 32 && c != '\n' && c != '\t' && c != '\r') {
            return SafetyCheckResult::warning(
                "path contains control character: " + std::to_string(static_cast<int>(c)));
        }
    }
    
    // Check for path traversal patterns
    if (path_str.find("..") != std::string::npos) {
        // Allow ".." if it's only within a controlled context
        // For now, flag as potential issue but don't fail
        return SafetyCheckResult::warning("path may contain directory traversal");
    }
    
    return result;
}

// ============================================================================
// Path Boundary Validation
// ============================================================================

SafetyCheckResult validate_path_in_boundary(
    const fs::path& path,
    const fs::path& boundary,
    bool allow_boundary_as_target) {
    
    SafetyCheckResult result;
    
    // Normalize both paths for comparison
    auto normalized_path = fs::weakly_canonical(path);
    auto normalized_boundary = fs::weakly_canonical(boundary);
    
    // Handle empty paths
    if (normalized_path.empty()) {
        return SafetyCheckResult::failed("empty path");
    }
    if (normalized_boundary.empty()) {
        return SafetyCheckResult::failed("empty boundary");
    }
    
    // If boundary is not a directory, check if it matches the path exactly
    std::error_code ec;
    bool boundary_is_dir = fs::is_directory(normalized_boundary, ec);
    if (!boundary_is_dir && !allow_boundary_as_target) {
        return SafetyCheckResult::failed("boundary is not a directory");
    }
    
    // Convert to strings for prefix matching
    auto path_str = normalized_path.string();
    auto boundary_str = normalized_boundary.string();
    
    // Check if path starts with boundary (path must be under boundary)
    // Handle case where boundary ends with "/" or doesn't
    std::string boundary_with_sep = boundary_str;
    if (!boundary_with_sep.empty() && boundary_with_sep.back() != '/') {
        boundary_with_sep += '/';
    }
    
    bool is_under_boundary = 
        path_str == boundary_str ||  // Exact match
        (path_str.find(boundary_with_sep) == 0);  // Under boundary
    
    if (!is_under_boundary) {
        return SafetyCheckResult::failed(
            "path escapes boundary: " + path_str + " not under " + boundary_str);
    }
    
    return result;
}

// ============================================================================
// Symlink Policy Checking
// ============================================================================

SafetyCheckResult check_symlink_policy(
    const fs::path& path,
    const SymlinkPolicy& policy,
    std::error_code* ec) {
    
    SafetyCheckResult result;
    
    std::error_code local_ec;
    if (!ec) {
        ec = &local_ec;
    }
    
    // Check each component of the path for symlinks
    fs::path current_path;
    
    for (const auto& component : path) {
        current_path /= component;
        
        // Check if current component is a symlink
        bool is_symlink = fs::is_symlink(current_path, *ec);
        if (*ec) {
            return SafetyCheckResult::warning(
                "failed to check symlink status for: " + current_path.string());
        }
        
        if (is_symlink) {
            switch (policy.behavior) {
                case SymlinkBehavior::kFollow:
                    // Allow following, but log for audit if requested
                    if (policy.should_audit()) {
                        result.status = SafetyCheckStatus::kWarning;
                        if (!result.reason) {
                            result.reason = "symlink followed: " + current_path.string();
                        } else {
                            *result.reason += ", symlink: " + current_path.string();
                        }
                    }
                    break;
                    
                case SymlinkBehavior::kReject:
                    return SafetyCheckResult::failed(
                        "symlink forbidden by policy: " + current_path.string());
                    
                case SymlinkBehavior::kTrustedOnly: {
                    // Verify symlink target is owned by trusted user
                    struct stat st;
                    if (lstat(current_path.string().c_str(), &st) == 0) {
                        bool is_trusted = false;
                        for (uid_t uid : policy.trusted_uids) {
                            if (st.st_uid == uid) {
                                is_trusted = true;
                                break;
                            }
                        }
                        
                        if (!is_trusted) {
                            return SafetyCheckResult::failed(
                                "symlink target not owned by trusted user: " + 
                                current_path.string());
                        }
                    } else {
                        return SafetyCheckResult::warning(
                            "failed to stat symlink for ownership check: " + 
                            current_path.string());
                    }
                    
                    if (policy.should_audit()) {
                        result.status = SafetyCheckStatus::kWarning;
                        if (!result.reason) {
                            result.reason = "symlink resolved (trusted): " + current_path.string();
                        } else {
                            *result.reason += ", trusted symlink: " + current_path.string();
                        }
                    }
                    break;
                }
                
                case SymlinkBehavior::kAllowButAudit:
                    result.status = SafetyCheckStatus::kWarning;
                    if (!result.reason) {
                        result.reason = "symlink followed (audited): " + current_path.string();
                    } else {
                        *result.reason += ", audited symlink: " + current_path.string();
                    }
                    break;
            }
        }
    }
    
    return result;
}

// ============================================================================
// File Ownership Verification
// ============================================================================

SafetyCheckResult verify_ownership(
    const fs::path& path,
    uid_t expected_uid,
    bool allow_dir) {
    
    SafetyCheckResult result;
    
    struct stat st;
    if (lstat(path.string().c_str(), &st) != 0) {
        int err = errno;
        return SafetyCheckResult::failed(
            "failed to stat file: " + path.string() + 
            ", error: " + std::strerror(err));
    }
    
    // Check UID
    if (st.st_uid != expected_uid) {
        return SafetyCheckResult::failed(
            "ownership mismatch for " + path.string() + 
            ": expected uid " + std::to_string(expected_uid) + 
            ", got " + std::to_string(st.st_uid));
    }
    
    // Check file type
    bool is_dir = S_ISDIR(st.st_mode);
    bool is_file = S_ISREG(st.st_mode);
    
    if (!allow_dir && is_dir) {
        return SafetyCheckResult::failed(
            "expected regular file but got directory: " + path.string());
    }
    
    return result;
}

// ============================================================================
// Full Operation Validation
// ============================================================================

SafetyCheckResult validate_path_for_operation(
    const fs::path& path,
    const PathContext& context,
    std::error_code* ec) {
    
    SafetyCheckResult result;
    
    // 1. Validate path syntax
    auto syntax_result = validate_path_syntax(path);
    if (syntax_result.status == SafetyCheckStatus::kFailed) {
        return syntax_result;
    }
    if (syntax_result.status == SafetyCheckStatus::kWarning && !result.reason) {
        result.reason = syntax_result.reason;
    }
    
    // 2. Validate boundary restrictions
    switch (context.boundary) {
        case PathBoundary::kNone:
            break;  // No boundary check needed
            
        case PathBoundary::kUserHome: {
            auto home = fs::path(std::getenv("HOME"));
            if (!home.empty()) {
                auto boundary_result = validate_path_in_boundary(path, home);
                if (boundary_result.status == SafetyCheckStatus::kFailed) {
                    return boundary_result;
                }
            }
            break;
        }
        
        case PathBoundary::kSystemConfig: {
            static const fs::path config_paths[] = {
                "/etc", "/etc/rebuntu"
            };
            
            bool valid_boundary = false;
            for (const auto& cp : config_paths) {
                auto boundary_result = validate_path_in_boundary(path, cp);
                if (boundary_result.status == SafetyCheckStatus::kPassed) {
                    valid_boundary = true;
                    break;
                }
            }
            
            if (!valid_boundary) {
                return SafetyCheckResult::failed(
                    "path outside allowed system config boundaries: " + path.string());
            }
            break;
        }
        
        case PathBoundary::kCustom:
            if (context.custom_boundary.has_value()) {
                auto boundary_result = validate_path_in_boundary(path, *context.custom_boundary);
                if (boundary_result.status == SafetyCheckStatus::kFailed) {
                    return boundary_result;
                }
            }
            break;
            
        default:
            // kSystemData, kTempDir - could add specific checks here
            break;
    }
    
    // 3. Check symlink policy
    auto symlink_result = check_symlink_policy(path, context.symlink_policy, ec);
    if (symlink_result.status == SafetyCheckStatus::kFailed) {
        return symlink_result;
    }
    if (symlink_result.status == SafetyCheckStatus::kWarning && !result.reason) {
        result.reason = symlink_result.reason;
    }
    
    // 4. Verify ownership for write/create operations
    if (context.op_type == OperationType::kWrite || 
        context.op_type == OperationType::kCreate ||
        context.op_type == OperationType::kMetadata) {
        
        if (context.target_owner_uid.has_value()) {
            auto ownership_result = verify_ownership(path, *context.target_owner_uid);
            if (ownership_result.status == SafetyCheckStatus::kFailed) {
                return ownership_result;
            }
        }
    }
    
    // 5. For create operations, check parent directory exists and is writable
    if (context.op_type == OperationType::kCreate) {
        auto parent = path.parent_path();
        if (!parent.empty()) {
            struct stat st;
            if (stat(parent.string().c_str(), &st) != 0) {
                return SafetyCheckResult::failed(
                    "parent directory does not exist: " + parent.string());
            }
            
            // Verify we can write to parent
            uid_t current_uid = getuid();
            if (st.st_uid != current_uid && current_uid != 0) {
                mode_t mode = st.st_mode;
                if (!(mode & S_IWUSR)) {
                    return SafetyCheckResult::warning(
                        "parent directory not writable by current user");
                }
            }
        }
    }
    
    // If we have warnings, mark as warning but not failed
    if (result.status == SafetyCheckStatus::kWarning) {
        return result;
    }
    
    return SafetyCheckResult::passed();
}

// ============================================================================
// FileDescriptor Implementation
// ============================================================================

FileDescriptor::FileDescriptor(int fd) : fd_(fd) {}

FileDescriptor::~FileDescriptor() {
    close();
}

FileDescriptor::FileDescriptor(FileDescriptor&& other) noexcept 
    : fd_(other.fd_) {
    other.fd_ = -1;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& other) noexcept {
    if (this != &other) {
        close();
        fd_ = other.fd_;
        other.fd_ = -1;
    }
    return *this;
}

void FileDescriptor::close() {
    if (fd_ >= 0) {
        ::close(fd_);
        fd_ = -1;
    }
}

// ============================================================================
// Safe File Opening
// ============================================================================

std::optional<FileDescriptor> open_file_safely(
    const fs::path& path,
    int flags,
    mode_t mode) {
    
    // Check if we're trying to create a file that shouldn't exist yet
    if ((flags & O_CREAT) && (flags & O_EXCL)) {
        std::error_code ec;
        if (fs::exists(path, ec)) {
            return std::nullopt;  // File exists but should be new
        }
    }
    
    int fd = open(path.string().c_str(), flags, mode);
    if (fd < 0) {
        return std::nullopt;
    }
    
    return FileDescriptor(fd);
}

// ============================================================================
// File Identity Verification
// ============================================================================

std::optional<FileIdentity> get_file_identity(int fd) {
    struct stat st;
    if (fstat(fd, &st) != 0) {
        return std::nullopt;
    }
    
    FileIdentity identity;
    identity.device_id = st.st_dev;
    identity.inode_number = st.st_ino;
    identity.owner_uid = st.st_uid;
    identity.group_gid = st.st_gid;
    identity.size = st.st_size;
    
    return identity;
}

std::optional<FileIdentity> get_file_identity(const fs::path& path) {
    struct stat st;
    if (lstat(path.string().c_str(), &st) != 0) {
        return std::nullopt;
    }
    
    FileIdentity identity;
    identity.device_id = st.st_dev;
    identity.inode_number = st.st_ino;
    identity.owner_uid = st.st_uid;
    identity.group_gid = st.st_gid;
    identity.size = st.st_size;
    
    return identity;
}

// ============================================================================
// Safe Path Canonicalization
// ============================================================================

std::optional<ResolvedPath> safe_canonicalize(
    const fs::path& path,
    const SymlinkPolicy& policy,
    size_t max_depth) {
    
    ResolvedPath result;
    
    if (max_depth == 0) {
        return std::nullopt;  // Too many levels of symlinks
    }
    
    // Check for absolute or relative path
    bool is_absolute = fs::path(path).is_absolute();
    
    std::error_code ec;
    
    // Resolve step by step, tracking symlinks
    fs::path current_path;
    
    if (is_absolute) {
        current_path = "/";
    }
    
    for (const auto& component : path) {
        if (component == "." || component.empty()) {
            continue;  // Skip self-references and empty components
        }
        
        if (component == "..") {
            current_path = current_path.parent_path();
            continue;
        }
        
        current_path /= component;
        
        // Check for symlink at this level
        bool is_symlink = fs::is_symlink(current_path, ec);
        if (ec) {
            return std::nullopt;  // Failed to check
        }
        
        if (is_symlink) {
            // Apply policy
            auto symlink_result = check_symlink_policy(
                current_path, policy, &ec);
            
            if (symlink_result.status == SafetyCheckStatus::kFailed) {
                return std::nullopt;  // Policy violation
            }
            
            result.symlinks_resolved.push_back(current_path);
            
            // Recursively resolve the target
            auto target = fs::read_symlink(current_path, ec);
            if (ec) {
                return std::nullopt;
            }
            
            // If relative, make it relative to current path's parent
            if (!target.is_absolute()) {
                target = current_path.parent_path() / target;
            }
            
            // Resolve the target with reduced depth
            auto target_result = safe_canonicalize(target, policy, max_depth - 1);
            if (!target_result) {
                return std::nullopt;
            }
            
            // Merge results
            result.canonical_path = target_result->canonical_path;
            result.symlinks_resolved.insert(
                result.symlinks_resolved.end(),
                target_result->symlinks_resolved.begin(),
                target_result->symlinks_resolved.end());
            result.all_components_regular = target_result->all_components_regular;
            
            return result;
        }
    }
    
    // No more symlinks, get final canonical path
    result.canonical_path = fs::weakly_canonical(current_path, ec);
    if (ec) {
        return std::nullopt;
    }
    
    // Check the final file type
    struct stat st;
    if (stat(result.canonical_path.string().c_str(), &st) == 0) {
        result.all_components_regular = S_ISREG(st.st_mode);
    }
    
    return result;
}

}  // namespace rebuntu::path_safety