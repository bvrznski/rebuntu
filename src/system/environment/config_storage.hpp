// rebuntu::environment::config_storage — Configuration File Storage (Phase 2.11)
//
// This establishes Rebuntu's configuration file storage model:
//
//   - Config file read/write operations
//   - Atomic write with rollback safety
//   - Per-scope paths (system/user/session)
//   - Ownership and permission management
//   - Redaction at serialization boundaries
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/environment/config_storage.hpp
//
// Phase 2.11 extends Phase 2.9 (directory layout) and Phase 0.18 (configuration grammar):
// - Provides file-based storage for configuration values
// - Implements atomic write with fsync/rename pattern
// - Defines secret redaction boundaries

#pragma once

#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <iostream>  // for std::ifstream, std::ofstream
#include <fstream>
#include <filesystem>

#include <system/environment/scope.hpp>
#include <system/core/contracts.hpp>

// Using declarations from scope namespace (must come before any usage)
using rebuntu::environment::scope::ScopeContext;

namespace rebuntu::environment::config_storage {

// ============================================================================
// ConfigLoadResult - Result of loading a configuration file
// ============================================================================

struct ConfigLoadResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    std::map<std::string, std::string> values;  // Key-value pairs from file
    std::optional<std::string> error_message;
    
    bool is_success() const { return status == core::SemanticStatus::kSuccess; }
};

// ============================================================================
// ConfigWriteResult - Result of writing a configuration file
// ============================================================================

struct ConfigWriteResult {
    bool success = false;
    std::filesystem::path written_path;
    std::optional<std::string> error_message;
    
    core::SemanticStatus semantic_status() const {
        return success ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
    }
};

// ============================================================================
// ConfigFileFormat - Supported configuration file formats
// ============================================================================

enum class ConfigFileFormat {
    kEnv,      // KEY=value (systemd-style environment files)
    kToml,     // TOML format
    kJson,     // JSON format
    kIni,      // INI-style sections
};

inline std::string_view to_string(ConfigFileFormat f) {
    switch (f) {
        case ConfigFileFormat::kEnv:   return "env";
        case ConfigFileFormat::kToml:  return "toml";
        case ConfigFileFormat::kJson:  return "json";
        case ConfigFileFormat::kIni:   return "ini";
    }
    return "unknown";
}

// ============================================================================
// ConfigStorageOptions - Storage behavior configuration
// ============================================================================

struct ConfigStorageOptions {
    // File ownership and permissions
    uid_t owner_uid = 0;
    gid_t owner_gid = 0;
    mode_t file_mode = 0644;   // Readable by all, writable by owner
    
    // Behavior flags
    bool preserve_user_edits = true;      // Don't overwrite if user edited
    bool atomic_write = true;              // Use fsync/rename pattern
    bool create_parent_dirs = true;        // Create parent directories if missing
    
    // Secret handling
    std::vector<std::string> secret_keys;  // Keys containing secrets (redacted)
};

// ============================================================================
// ConfigFileLocation - Where a config file is stored for a scope
// ============================================================================

struct ConfigFileLocation {
    ScopeContext scope_context;
    std::filesystem::path path;        // Full path to the file
    bool exists = false;
    uid_t current_uid = 0;
    gid_t current_gid = 0;
    mode_t current_mode = 0;
    
    // Verification status
    bool is_valid = true;
    std::optional<std::string> validation_error;
};

// ============================================================================
// Core API - Configuration File Storage Operations
// ============================================================================

// Get the config directory for a given scope context
std::filesystem::path get_config_dir(const ScopeContext& ctx);

// Get a specific configuration file path for a scope
std::filesystem::path get_config_file_path(
    const ScopeContext& ctx,
    std::string_view filename,
    ConfigFileFormat format = ConfigFileFormat::kEnv);

// Discover the location and state of a config file
ConfigFileLocation discover_config_file(const std::filesystem::path& path);

// Load configuration from an environment-style file (KEY=value)
ConfigLoadResult load_env_file(const std::filesystem::path& path);

// Save configuration to an environment-style file
// Uses atomic write pattern with fsync/rename for safety
ConfigWriteResult save_env_file(
    const std::filesystem::path& path,
    const std::map<std::string, std::string>& values,
    const ConfigStorageOptions& options = {});

// Load configuration from a TOML-like file (simple parser)
ConfigLoadResult load_toml_file(const std::filesystem::path& path);

// Save configuration to a TOML-like file
ConfigWriteResult save_toml_file(
    const std::filesystem::path& path,
    const std::map<std::string, std::string>& values,
    const ConfigStorageOptions& options = {});

// ============================================================================
// Secret Redaction API - Never expose secret values in logs/diffs
// ============================================================================

struct SecretRedactionPolicy {
    bool is_secret = false;
    std::string redacted_value = "[REDACTED]";
    
    static SecretRedactionPolicy secret() { return {true, "[REDACTED]"}; }
    static SecretRedactionPolicy normal() { return {false, ""}; }
};

// Get a redacted view of config values (secrets replaced with placeholder)
std::map<std::string, std::string> get_redacted_values(
    const std::map<std::string, std::string>& values,
    const std::vector<std::string>& secret_keys);

// Format values for output, applying redaction to secrets
std::string format_config_for_display(
    const std::map<std::string, std::string>& values,
    const std::vector<std::string>& secret_keys = {});

// ============================================================================
// Atomic File Writer - Safe file updates with rollback capability
// ============================================================================

struct AtomicWriteResult {
    bool success = false;
    std::filesystem::path final_path;
    std::optional<std::string> error_message;
};

// Write to a file atomically using the fsync/rename pattern:
// 1. Write to temp file in same directory
// 2. fsync() the temp file  
// 3. Rename (atomic on POSIX)
// 4. fsync() parent directory
AtomicWriteResult atomic_write_file(
    const std::filesystem::path& path,
    std::string_view content,
    uid_t owner_uid = 0,
    gid_t owner_gid = 0,
    mode_t permissions = 0644);

}  // namespace rebuntu::environment::config_storage