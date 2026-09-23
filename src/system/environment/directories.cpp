// rebuntu::environment::directories — Operational Directory Layout Implementation (Phase 2.9)
#include <system/environment/directories.hpp>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <cerrno>
#include <filesystem>
#include <iostream>

// Using declarations from scope.hpp namespace
using rebuntu::environment::scope::ScopeContext;
using rebuntu::environment::scope::ExecutionScope;
using rebuntu::environment::scope::XDGBases;
using rebuntu::environment::scope::get_user_config_dir;
using rebuntu::environment::scope::get_user_state_dir;
using rebuntu::environment::scope::get_user_cache_dir;

namespace rebuntu::environment::directories {

// ============================================================================
// Canonical Directory Paths - Where should things go?
// Note: Path resolution is delegated to rebuntu::environment::scope namespace.
// Only directory-specific paths (not in scope module) are implemented here.
// ============================================================================

std::filesystem::path get_system_runtime_dir() {
    // /run/rebuntu is the canonical runtime directory per FHS
    return "/run/rebuntu";
}

std::filesystem::path get_system_data_dir() {
    return "/usr/share/rebuntu";
}

std::filesystem::path get_system_log_dir() {
    return "/var/log/rebuntu";
}

// ============================================================================
// User Data Directory Implementation
// ============================================================================

std::filesystem::path get_user_data_dir(const std::filesystem::path& home) {
    if (home.empty()) {
        return std::filesystem::path();
    }
    // User data directory under XDG_DATA_HOME with rebuntu subdirectory
    // XDG_DATA_HOME default is ~/.local/share -> ~/.local/share/rebuntu
    return home / ".local" / "share" / "rebuntu";
}

std::filesystem::path get_user_runtime_dir(const ScopeContext& ctx) {
    if (ctx.xdg.runtime_dir.has_value() && !ctx.is_root) {
        return *ctx.xdg.runtime_dir;
    }
    
    // Fallback: /run/user/<uid> for non-root
    if (!ctx.is_root && ctx.effective_uid != 0) {
        return std::filesystem::path("/run/user") / std::to_string(ctx.effective_uid);
    }
    
    return std::filesystem::path();
}

std::filesystem::path get_session_runtime_dir(const sessions::RuntimeDirectoryInfo& rt_info) {
    if (rt_info.status == sessions::RuntimeDirStatus::kAvailable) {
        return rt_info.path;
    }
    
    // Fallback for non-session contexts
    return std::filesystem::path();
}

std::filesystem::path get_session_temp_dir(const sessions::RuntimeDirectoryInfo& rt_info) {
    if (rt_info.status == sessions::RuntimeDirStatus::kAvailable) {
        return rt_info.path / "tmp";
    }
    
    // Fallback to system temp
    return std::filesystem::temp_directory_path() / "rebuntu-session-" / std::to_string(geteuid());
}

// ============================================================================
// Directory Discovery - What exists and what state is it in?
// ============================================================================

DirectoryInfo discover_directory(const std::filesystem::path& path) {
    DirectoryInfo info;
    info.path = path;
    
    std::error_code ec;
    if (!std::filesystem::exists(path, ec)) {
        info.exists = false;
        info.is_accessible = false;
        return info;
    }
    
    info.exists = true;
    info.is_accessible = true;
    
    // Get file attributes
    struct stat st;
    if (stat(path.string().c_str(), &st) == 0) {
        info.expected_uid = st.st_uid;
        info.expected_gid = st.st_gid;
        info.expected_mode = st.st_mode & 0777;
        
        // Check if it's a directory
        info.is_accessible = S_ISDIR(st.st_mode);
    }
    
    return info;
}

std::vector<DirectoryInfo> discover_all_directories(const ScopeContext& ctx) {
    std::vector<DirectoryInfo> result;
    
    DirectoryType types[] = {
        DirectoryType::kConfig,
        DirectoryType::kState,
        DirectoryType::kCache,
        DirectoryType::kRuntime,
        DirectoryType::kData,
        DirectoryType::kLog,
        DirectoryType::kTemp
    };
    
    for (auto type : types) {
        DirectoryInfo info;
        info.type = type;
        
        switch (type) {
            case DirectoryType::kConfig:
                if (ctx.is_root) {
                    info.path = get_system_config_dir();
                    info.expected_uid = 0;
                    info.expected_mode = 0755;
                } else {
                    info.path = get_user_config_dir(XDGBases::get_user_home());
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0700;
                }
                break;
            
            case DirectoryType::kState:
                if (ctx.is_root) {
                    info.path = get_system_state_dir();
                    info.expected_uid = 0;
                    info.expected_mode = 0755;
                } else {
                    info.path = get_user_state_dir(ctx.xdg.get_user_home());
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0700;
                }
                break;
            
            case DirectoryType::kCache:
                if (ctx.is_root) {
                    info.path = get_system_cache_dir();
                    info.expected_uid = 0;
                    info.expected_mode = 0755;
                } else {
                    info.path = get_user_cache_dir(ctx.xdg.get_user_home());
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0700;
                }
                break;
            
            case DirectoryType::kRuntime:
                if (!ctx.is_root && ctx.xdg.runtime_dir.has_value()) {
                    info.path = *ctx.xdg.runtime_dir / "rebuntu";
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0700;
                }
                // For discover_all, if runtime dir is unavailable, we skip it
                break;
            
            case DirectoryType::kData:
                if (ctx.is_root) {
                    info.path = get_system_data_dir();
                    info.expected_uid = 0;
                    info.expected_mode = 0755;
                } else {
                    info.path = get_user_data_dir(ctx.xdg.get_user_home());
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0700;
                }
                break;
            
            case DirectoryType::kLog:
                if (ctx.is_root) {
                    info.path = get_system_log_dir();
                    info.expected_uid = 0;
                    info.expected_mode = 0755;
                } else {
                    // For user scope, use a log directory in state
                    info.path = get_user_state_dir(ctx.xdg.get_user_home()) / "log";
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0700;
                }
                break;
            
            case DirectoryType::kTemp:
                // Temp directories are session-scoped or fall back to system temp
                if (!ctx.is_root && ctx.xdg.runtime_dir.has_value()) {
                    info.path = *ctx.xdg.runtime_dir / "tmp";
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0755;
                } else {
                    // Fallback to system temporary directory
                    info.path = std::filesystem::temp_directory_path() / "rebuntu-temp";
                    info.expected_uid = ctx.effective_uid;
                    info.expected_mode = 0755;
                }
                break;
        }
        
        if (!info.path.empty()) {
            result.push_back(discover_directory(info.path));
        }
    }
    
    return result;
}

bool verify_directory_state(
    const DirectoryInfo& info,
    const DirectoryPolicy& policy,
    core::SemanticStatus* out_status) {
    
    bool valid = true;
    std::string error_msg;
    
    // Check existence
    if (!info.exists) {
        valid = false;
        error_msg = "directory does not exist";
    }
    
    // Check accessibility
    if (valid && !info.is_accessible) {
        valid = false;
        error_msg = "directory is not accessible";
    }
    
    // Check ownership
    uid_t current_uid = geteuid();
    if (valid && policy.owner_type == DirectoryPolicy::OwnerType::kSystem && current_uid != 0) {
        valid = false;
        error_msg = "system directory requires root access";
    }
    
    // Check permissions
    if (valid) {
        struct stat st;
        if (stat(info.path.string().c_str(), &st) == 0) {
            mode_t actual_mode = st.st_mode & 0777;
            
            // Check world-writable
            if (policy.must_not_be_world_writable && (actual_mode & 0002)) {
                valid = false;
                error_msg = "directory is world-writable";
            }
            
            // Check execute permission for owner
            if (policy.must_be_owner_executable && !(actual_mode & 0100)) {
                valid = false;
                error_msg = "directory missing execute permission for owner";
            }
        }
    }
    
    if (out_status) {
        *out_status = valid ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
    }
    
    return valid;
}

// ============================================================================
// Directory Management - Create and maintain directories
// ============================================================================

DirectoryOperationResult ensure_directory(
    const std::filesystem::path& path,
    uid_t owner_uid,
    gid_t owner_gid,
    mode_t permissions,
    bool create_parents) {
    
    DirectoryOperationResult result;
    result.path = path;
    
    if (path.empty()) {
        result.status = DirectoryOperationStatus::kInvalidPath;
        result.error_message = "empty path";
        return result;
    }
    
    std::error_code ec;
    
    // Check if directory exists
    if (std::filesystem::exists(path, ec)) {
        if (!std::filesystem::is_directory(path, ec)) {
            result.status = DirectoryOperationStatus::kInvalidPath;
            result.error_message = "path exists but is not a directory";
            return result;
        }
        
        // Directory already exists - idempotent success
        result.status = DirectoryOperationStatus::kAlreadyExists;
        
        // Try to set ownership/permissions if we're root
        if (owner_uid == 0 || geteuid() == 0) {
            if (chown(path.string().c_str(), owner_uid, owner_gid) != 0) {
                std::cerr << "warning: failed to chown " << path << ": " 
                          << strerror(errno) << "\n";
            }
            
            if (chmod(path.string().c_str(), permissions) != 0) {
                std::cerr << "warning: failed to chmod " << path << ": " 
                          << strerror(errno) << "\n";
            }
        }
        
        return result;
    }
    
    // Create parent directories if requested
    if (create_parents) {
        auto parent = path.parent_path();
        if (!parent.empty() && !std::filesystem::exists(parent, ec)) {
            auto parent_result = ensure_directory(
                parent, owner_uid, owner_gid, permissions & 0755, create_parents);
            if (!parent_result.is_success()) {
                result.status = DirectoryOperationStatus::kMissingParent;
                result.error_message = "failed to create parent directory";
                return result;
            }
        }
    }
    
    // Create the directory
    std::error_code create_ec;
    bool created = std::filesystem::create_directory(path, create_ec);
    
    if (!created && !create_ec) {
        // Directory was just created by another process - idempotent success
        result.status = DirectoryOperationStatus::kAlreadyExists;
    } else if (created) {
        result.status = DirectoryOperationStatus::kSuccess;
        
        // Set ownership if we're root
        if (owner_uid == 0 || geteuid() == 0) {
            if (chown(path.string().c_str(), owner_uid, owner_gid) != 0) {
                std::cerr << "warning: failed to chown " << path << ": " 
                          << strerror(errno) << "\n";
            }
            
            if (chmod(path.string().c_str(), permissions) != 0) {
                std::cerr << "warning: failed to chmod " << path << ": " 
                          << strerror(errno) << "\n";
            }
        }
    } else {
        // Error creating directory
        result.status = DirectoryOperationStatus::kUnknown;
        result.error_message = create_ec.message();
    }
    
    return result;
}

DirectoryOperationResult create_rebuntu_directory(
    const ScopeContext& ctx,
    DirectoryType type) {
    
    DirectoryOperationResult result;
    
    std::filesystem::path path;
    uid_t owner_uid = ctx.effective_uid;
    gid_t owner_gid = getgid();
    mode_t permissions;
    
    switch (type) {
        case DirectoryType::kConfig:
            if (ctx.is_root) {
                path = get_system_config_dir();
            } else {
                path = get_user_config_dir(ctx.xdg.get_user_home());
            }
            permissions = ctx.is_root ? 0755 : 0700;
            break;
            
        case DirectoryType::kState:
            if (ctx.is_root) {
                path = get_system_state_dir();
            } else {
                path = get_user_state_dir(ctx.xdg.get_user_home());
            }
            permissions = ctx.is_root ? 0755 : 0700;
            break;
            
        case DirectoryType::kCache:
            if (ctx.is_root) {
                path = get_system_cache_dir();
            } else {
                path = get_user_cache_dir(ctx.xdg.get_user_home());
            }
            permissions = ctx.is_root ? 0755 : 0700;
            break;
            
        case DirectoryType::kRuntime:
            if (!ctx.is_root && ctx.xdg.runtime_dir.has_value()) {
                path = *ctx.xdg.runtime_dir / "rebuntu";
            } else {
                result.status = DirectoryOperationStatus::kInvalidPath;
                result.error_message = "runtime directory unavailable (no XDG_RUNTIME_DIR)";
                return result;
            }
            permissions = 0700;
            break;
            
        case DirectoryType::kData:
            if (ctx.is_root) {
                path = get_system_data_dir();
            } else {
                path = get_user_data_dir(ctx.xdg.get_user_home());
            }
            permissions = ctx.is_root ? 0755 : 0700;
            break;
            
        case DirectoryType::kLog:
            if (ctx.is_root) {
                path = get_system_log_dir();
            } else {
                path = get_user_state_dir(ctx.xdg.get_user_home()) / "log";
            }
            permissions = ctx.is_root ? 0755 : 0700;
            break;
            
        case DirectoryType::kTemp:
            // Temp directories don't have a specific rebuntu location
            result.status = DirectoryOperationStatus::kInvalidPath;
            result.error_message = "temp directory not applicable for create_rebuntu_directory";
            return result;
    }
    
    result.path = path;
    
    std::error_code ec;
    
    // Check if directory exists - idempotent success if it does
    if (std::filesystem::exists(path, ec) && std::filesystem::is_directory(path, ec)) {
        result.status = DirectoryOperationStatus::kAlreadyExists;
        
        // Try to set ownership/permissions if we're root
        if (owner_uid == 0 || geteuid() == 0) {
            if (chown(path.string().c_str(), owner_uid, owner_gid) != 0) {
                std::cerr << "warning: failed to chown " << path << ": " 
                          << strerror(errno) << "\n";
            }
            
            if (chmod(path.string().c_str(), permissions) != 0) {
                std::cerr << "warning: failed to chmod " << path << ": " 
                          << strerror(errno) << "\n";
            }
        }
        
        return result;
    }
    
    // Create the directory
    bool created = std::filesystem::create_directories(path, ec);
    
    if (!created && !ec) {
        // Directory was just created by another process - idempotent success
        result.status = DirectoryOperationStatus::kAlreadyExists;
    } else if (created || (!created && ec.value() == 0)) {
        result.status = DirectoryOperationStatus::kSuccess;
        
        // Set ownership if we're root
        if (owner_uid == 0 || geteuid() == 0) {
            if (chown(path.string().c_str(), owner_uid, owner_gid) != 0) {
                std::cerr << "warning: failed to chown " << path << ": " 
                          << strerror(errno) << "\n";
            }
            
            if (chmod(path.string().c_str(), permissions) != 0) {
                std::cerr << "warning: failed to chmod " << path << ": " 
                          << strerror(errno) << "\n";
            }
        }
    } else {
        // Error creating directory
        result.status = DirectoryOperationStatus::kUnknown;
        result.error_message = ec.message();
    }
    
    return result;
}

DirectoryOperationResult remove_directory(
    const std::filesystem::path& path,
    bool recursive) {
    
    DirectoryOperationResult result;
    result.path = path;
    
    if (path.empty()) {
        result.status = DirectoryOperationStatus::kInvalidPath;
        result.error_message = "empty path";
        return result;
    }
    
    std::error_code ec;
    if (!std::filesystem::exists(path, ec)) {
        result.status = DirectoryOperationStatus::kAlreadyExists;
        return result;  // Already doesn't exist - idempotent
    }
    
    if (!std::filesystem::is_directory(path, ec)) {
        result.status = DirectoryOperationStatus::kInvalidPath;
        result.error_message = "path exists but is not a directory";
        return result;
    }
    
    std::error_code remove_ec;
    
    if (recursive) {
        for (auto it = std::filesystem::directory_iterator(path, ec);
             !ec && it != std::filesystem::directory_iterator(); ) {
            std::filesystem::remove_all(it->path(), remove_ec);
            if (remove_ec) {
                result.status = DirectoryOperationStatus::kUnknown;
                result.error_message = "failed to remove directory contents";
                return result;
            }
            it.increment(ec);
        }
    }
    
    bool removed = std::filesystem::remove(path, remove_ec);
    
    if (removed) {
        result.status = DirectoryOperationStatus::kSuccess;
    } else {
        result.status = DirectoryOperationStatus::kUnknown;
        result.error_message = remove_ec.message();
    }
    
    return result;
}

// ============================================================================
// Directory Validation - Is this directory safe to use?
// ============================================================================

DirectoryValidationResultDetails validate_directory_for_rebuntu(
    const std::filesystem::path& path,
    ScopeContext ctx,
    DirectoryType type) {
    
    (void)ctx;  // Suppress unused parameter warnings
    (void)type; // Suppress unused parameter warnings
    
    DirectoryValidationResultDetails result;
    result.path = path;
    
    if (path.empty()) {
        result.result = DirectoryValidationResult::kInvalidPath;
        result.explanation = "empty path";
        return result;
    }
    
    std::error_code ec;
    
    // Check if directory exists
    bool exists = std::filesystem::exists(path, ec);
    if (!exists && !ec) {
        result.result = DirectoryValidationResult::kMissing;
        result.explanation = "directory does not exist";
        return result;
    }
    
    if (ec) {
        result.result = DirectoryValidationResult::kUnknown;
        result.explanation = "error checking path: " + ec.message();
        return result;
    }
    
    if (!std::filesystem::is_directory(path, ec)) {
        result.result = DirectoryValidationResult::kInvalidPath;
        result.explanation = "path exists but is not a directory";
        return result;
    }
    
    // Check for symlinks in path (security concern)
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        std::error_code symlink_ec;
        if (std::filesystem::is_symlink(parent, symlink_ec)) {
            result.result = DirectoryValidationResult::kSymlinkRisk;
            result.explanation = "path contains symlinks which may be a security risk";
            return result;
        }
        
        // Get real path to resolve any symlinks
        auto canonical = std::filesystem::canonical(parent, ec);
        if (ec) {
            break;
        }
        parent = canonical.parent_path();
    }
    
    // Check permissions
    struct stat st;
    if (stat(path.string().c_str(), &st) == 0) {
        mode_t actual_mode = st.st_mode & 0777;
        
        // Check world-writable
        if ((actual_mode & 0002)) {
            result.result = DirectoryValidationResult::kPermissionIssue;
            result.explanation = "directory is world-writable";
            return result;
        }
        
        // Check execute permission for owner
        if (!(actual_mode & 0100)) {
            result.result = DirectoryValidationResult::kPermissionIssue;
            result.explanation = "directory missing execute permission for owner";
            return result;
        }
    }
    
    result.result = DirectoryValidationResult::kValid;
    return result;
}

bool is_path_safe(const std::filesystem::path& path) {
    if (path.empty()) {
        return false;
    }
    
    std::error_code ec;
    
    // Check each component for symlinks
    auto parent = path.parent_path();
    while (!parent.empty() && parent != "/" && parent != ".") {
        if (std::filesystem::is_symlink(parent, ec)) {
            return false;
        }
        
        auto canonical = std::filesystem::canonical(parent, ec);
        if (ec) {
            break;
        }
        parent = canonical.parent_path();
    }
    
    // Check permissions - should not be world-writable
    struct stat st;
    if (stat(path.string().c_str(), &st) == 0) {
        mode_t actual_mode = st.st_mode & 0777;
        return !(actual_mode & 0002);  // Not world-writable
    }
    
    return true;  // If we can't stat, assume it's safe (will fail at use)
}

// ============================================================================
// Directory Policy - What rules apply to each directory?
// ============================================================================

DirectoryPolicy get_directory_policy(DirectoryType type, ExecutionScope scope) {
    DirectoryPolicy policy;
    policy.type = type;
    
    switch (scope) {
        case ExecutionScope::kSystem:
            policy.owner_type = DirectoryPolicy::OwnerType::kSystem;
            break;
            
        case ExecutionScope::kUser:
            policy.owner_type = DirectoryPolicy::OwnerType::kUser;
            break;
            
        case ExecutionScope::kSession:
            policy.owner_type = DirectoryPolicy::OwnerType::kSession;
            break;
    }
    
    switch (type) {
        case DirectoryType::kConfig:
            policy.required_mode = 0755;  // System: readable by all
            policy.maximum_mode = 0777;
            policy.must_not_be_world_writable = true;
            policy.fhs_section = scope == ExecutionScope::kSystem ? "/etc" : "XDG_CONFIG_HOME";
            break;
            
        case DirectoryType::kState:
            policy.required_mode = 0755;  // System: readable by all
            policy.maximum_mode = 0777;
            policy.must_not_be_world_writable = true;
            policy.fhs_section = scope == ExecutionScope::kSystem ? "/var/lib" : "XDG_STATE_HOME";
            break;
            
        case DirectoryType::kCache:
            policy.required_mode = 0755;  // System: readable by all
            policy.maximum_mode = 0777;
            policy.must_not_be_world_writable = true;
            policy.fhs_section = scope == ExecutionScope::kSystem ? "/var/cache" : "XDG_CACHE_HOME";
            break;
            
        case DirectoryType::kRuntime:
            policy.required_mode = 0700;  // Session: private to user
            policy.maximum_mode = 0777;
            policy.must_not_be_world_writable = true;
            policy.fhs_section = "$XDG_RUNTIME_DIR";
            break;
            
        case DirectoryType::kData:
            policy.required_mode = 0755;  // System: readable by all
            policy.maximum_mode = 0777;
            policy.must_not_be_world_writable = true;
            policy.fhs_section = scope == ExecutionScope::kSystem ? "/usr/share" : "XDG_DATA_HOME";
            break;
            
        case DirectoryType::kLog:
            policy.required_mode = 0755;  // System: readable by all
            policy.maximum_mode = 0777;
            policy.must_not_be_world_writable = true;
            policy.fhs_section = scope == ExecutionScope::kSystem ? "/var/log" : "XDG_STATE_HOME/log";
            break;
            
        case DirectoryType::kTemp:
            policy.required_mode = 0755;
            policy.maximum_mode = 0777;
            policy.must_not_be_world_writable = false;  // Temp can be world-writable
            policy.fhs_section = "$XDG_RUNTIME_DIR/tmp or /tmp";
            break;
    }
    
    return policy;
}

std::vector<DirectoryPolicy> get_scope_policies(ExecutionScope scope) {
    std::vector<DirectoryPolicy> policies;
    
    DirectoryType types[] = {
        DirectoryType::kConfig,
        DirectoryType::kState,
        DirectoryType::kCache,
        DirectoryType::kRuntime,
        DirectoryType::kData,
        DirectoryType::kLog,
        DirectoryType::kTemp
    };
    
    for (auto type : types) {
        policies.push_back(get_directory_policy(type, scope));
    }
    
    return policies;
}

}  // namespace rebuntu::environment::directories