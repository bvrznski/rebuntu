// rebuntu::environment::directories — Operational Directory Layout (Phase 2.9)
//
// This establishes Rebuntu's canonical operational directory layout:
//
//   SYSTEM SCOPE (root):
//     - Config:  /etc/rebuntu
//     - State:   /var/lib/rebuntu
//     - Cache:   /var/cache/rebuntu
//     - Runtime: /run/rebuntu
//     - Data:    /usr/share/rebuntu (read-only resources)
//
//   USER SCOPE (~user):
//     - Config:  $XDG_CONFIG_HOME/rebuntu or ~/.config/rebuntu
//     - State:   $XDG_STATE_HOME/rebuntu or ~/.local/state/rebuntu
//     - Cache:   $XDG_CACHE_HOME/rebuntu or ~/.cache/rebuntu
//     - Data:    $XDG_DATA_HOME/rebuntu or ~/.local/share/rebuntu
//     - Runtime: $XDG_RUNTIME_DIR/rebuntu (if available)
//
//   SESSION SCOPE:
//     - Runtime: $XDG_RUNTIME_DIR/rebuntu/session-<session-id>
//     - Temp:    $XDG_RUNTIME_DIR/rebuntu/tmp
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/directories.hpp
//
// Phase 2.9 extends Phase 2.7 (scope) and Phase 2.8 (sessions):
// - Delegates path resolution to rebuntu::environment::scope namespace
// - Provides directory management operations (ensure, remove, discover)
// - Defines validation rules for Rebuntu directories

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <filesystem>

#include <observation/environment/scope.hpp>
#include <observation/environment/sessions.hpp>
#include <system/core/contracts.hpp>

// Using declarations from scope namespace (must come before any usage)
using rebuntu::environment::scope::ScopeContext;
using rebuntu::environment::scope::ExecutionScope;

namespace rebuntu::environment::directories {

// ============================================================================
// DirectoryType - Categories of operational directories
// ============================================================================

enum class DirectoryType {
    kConfig,       // Configuration storage (persistent, modifiable)
    kState,        // Runtime state (persistent between runs)
    kCache,        // Cached data (disposable, can be regenerated)
    kData,         // Read-only data/resources
    kRuntime,      // Session-scoped runtime files (IPC, locks, sockets)
    kTemp,         // Temporary files
    kLog,          // Log files and evidence
};

inline std::string_view to_string(DirectoryType t) {
    switch (t) {
        case DirectoryType::kConfig:  return "config";
        case DirectoryType::kState:   return "state";
        case DirectoryType::kCache:   return "cache";
        case DirectoryType::kData:    return "data";
        case DirectoryType::kRuntime: return "runtime";
        case DirectoryType::kTemp:    return "temp";
        case DirectoryType::kLog:     return "log";
    }
    return "unknown";
}

// ============================================================================
// DirectoryInfo - Information about a directory
// ============================================================================

struct DirectoryInfo {
    DirectoryType type = DirectoryType::kConfig;
    std::filesystem::path path;
    
    // Ownership and permissions
    uid_t expected_uid = 0;        // Who should own this directory?
    gid_t expected_gid = 0;        // What group should own it?
    mode_t expected_mode = 0755;   // Expected permission bits
    
    // State
    bool exists = false;
    bool is_accessible = true;
    
    // Verification status
    core::SemanticStatus verification_status = core::SemanticStatus::kUnknown;
    std::optional<std::string> verification_error;
    
    bool is_valid() const { return verification_status == core::SemanticStatus::kSuccess; }
};

// ============================================================================
// DirectoryPolicy - Ownership and permission requirements
// ============================================================================

struct DirectoryPolicy {
    DirectoryType type = DirectoryType::kConfig;
    
    // Who owns this directory?
    enum class OwnerType {
        kSystem,     // System-owned (root), all users read-only
        kUser,       // Per-user owned
        kSession,    // Per-session owned
        kRebuntu,    // Rebuntu process-owned (effective UID)
    } owner_type = OwnerType::kRebuntu;
    
    // Permission requirements
    mode_t required_mode = 0755;   // Minimum permissions
    mode_t maximum_mode = 0777;    // Maximum allowed permissions
    
    // Security constraints
    bool must_be_owner_executable = true;     // Must have execute for owner
    bool must_not_be_world_writable = true;   // Should not be world-writable
    bool must_not_have_symlinks_in_path = false; // Security-sensitive dirs
    
    // FHS/XDG mapping
    std::string_view fhs_section;  // e.g., "/etc", "/var/lib", "XDG_CONFIG_HOME"
};

// ============================================================================
// DirectoryOperationResult - Result of directory operations
// ============================================================================

enum class DirectoryOperationStatus {
    kSuccess,          // Operation succeeded
    kAlreadyExists,    // Directory already exists (idempotent success)
    kPermissionDenied, // Cannot access/create due to permissions
    kInvalidPath,      // Path is invalid or unsafe
    kMissingParent,    // Parent directory doesn't exist
    kUnknown,          // Unknown error
};

struct DirectoryOperationResult {
    DirectoryOperationStatus status = DirectoryOperationStatus::kUnknown;
    std::filesystem::path path;
    std::optional<std::string> error_message;
    
    core::SemanticStatus semantic_status() const {
        switch (status) {
            case DirectoryOperationStatus::kSuccess:
            case DirectoryOperationStatus::kAlreadyExists:
                return core::SemanticStatus::kSuccess;
            case DirectoryOperationStatus::kPermissionDenied:
            case DirectoryOperationStatus::kInvalidPath:
            case DirectoryOperationStatus::kMissingParent:
                return core::SemanticStatus::kFailure;
            case DirectoryOperationStatus::kUnknown:
                return core::SemanticStatus::kUnknown;
        }
        return core::SemanticStatus::kUnknown;
    }
    
    bool is_success() const { 
        return semantic_status() == core::SemanticStatus::kSuccess; 
    }
};

// ============================================================================
// Canonical Directory Paths - Where should things go?
// Note: Path resolution is delegated to rebuntu::environment::scope namespace.
// This module provides directory management operations on top of those paths.
// ============================================================================

// User data directory - XDG_DATA_HOME default is ~/.local/share
std::filesystem::path get_user_data_dir(const std::filesystem::path& home);

// System runtime directory (FHS /run/rebuntu)
std::filesystem::path get_system_runtime_dir();

// System data directory (FHS /usr/share/rebuntu)
std::filesystem::path get_system_data_dir();

// System log directory (FHS /var/log/rebuntu)  
std::filesystem::path get_system_log_dir();

// User runtime directory (XDG_RUNTIME_DIR based)
std::filesystem::path get_user_runtime_dir(ScopeContext ctx);

// Session-scoped directories
std::filesystem::path get_session_runtime_dir(const sessions::RuntimeDirectoryInfo& rt_info);
std::filesystem::path get_session_temp_dir(const sessions::RuntimeDirectoryInfo& rt_info);

// Delegated functions from scope module
using rebuntu::environment::scope::get_system_config_dir;
using rebuntu::environment::scope::get_system_state_dir;
using rebuntu::environment::scope::get_system_cache_dir;
using rebuntu::environment::scope::get_user_config_dir;
using rebuntu::environment::scope::get_user_state_dir;
using rebuntu::environment::scope::get_user_cache_dir;

// ============================================================================
// Directory Discovery - What exists and what state is it in?
// ============================================================================

// Discover directory info for a specific path
DirectoryInfo discover_directory(const std::filesystem::path& path);

// Discover all Rebuntu directories for a given scope
std::vector<DirectoryInfo> discover_all_directories(const ScopeContext& ctx);

// Verify directory state matches expectations
bool verify_directory_state(
    const DirectoryInfo& info,
    const DirectoryPolicy& policy,
    core::SemanticStatus* out_status = nullptr);

// ============================================================================
// Directory Management - Create and maintain directories
// ============================================================================

// Ensure a directory exists with correct ownership/permissions
DirectoryOperationResult ensure_directory(
    const std::filesystem::path& path,
    uid_t owner_uid = 0,
    gid_t owner_gid = 0,
    mode_t permissions = 0755,
    bool create_parents = true);

// Create a new Rebuntu directory with correct ownership
DirectoryOperationResult create_rebuntu_directory(
    const ScopeContext& ctx,
    DirectoryType type);

// Remove a directory (with safety checks)
DirectoryOperationResult remove_directory(
    const std::filesystem::path& path,
    bool recursive = false);

// ============================================================================
// Directory Validation - Is this directory safe to use?
// ============================================================================

enum class DirectoryValidationResult {
    kValid,           // Directory is valid and safe
    kMissing,         // Directory doesn't exist (may be created)
    kPermissionIssue, // Permissions are wrong
    kOwnershipIssue,  // Ownership is wrong
    kSymlinkRisk,     // Path contains unsafe symlinks
    kInvalidPath,     // Path is invalid or malformed
    kUnknown,         // Could not determine
};

struct DirectoryValidationResultDetails {
    DirectoryValidationResult result = DirectoryValidationResult::kUnknown;
    std::filesystem::path path;
    std::optional<std::string> explanation;
    
    bool is_valid() const { return result == DirectoryValidationResult::kValid; }
};

// Validate a directory for use with Rebuntu
DirectoryValidationResultDetails validate_directory_for_rebuntu(
    const std::filesystem::path& path,
    ScopeContext ctx,
    DirectoryType type);

// Check if a path is safe (no symlinks, correct ownership)
bool is_path_safe(const std::filesystem::path& path);

// ============================================================================
// Directory Policy - What rules apply to each directory?
// ============================================================================

DirectoryPolicy get_directory_policy(DirectoryType type, ExecutionScope scope);

// Get all policies for a given scope
std::vector<DirectoryPolicy> get_scope_policies(ExecutionScope scope);

}  // namespace rebuntu::environment::directories